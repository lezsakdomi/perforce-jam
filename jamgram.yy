/*
 * Copyright 1993, 1995 Christopher Seiwald.
 *
 * This file is part of Jam - see jam.c for Copyright information.
 */

/*
 * jamgram.yy - jam grammar
 *
 * 04/13/94 (seiwald) - added shorthand L0 for null list pointer
 * 06/01/94 (seiwald) - new 'actions existing' does existing sources
 * 08/23/94 (seiwald) - Support for '+=' (append to variable)
 * 08/31/94 (seiwald) - Allow ?= as alias for "default =".
 * 09/15/94 (seiwald) - if conditionals take only single arguments, so
 *			that 'if foo == bar' gives syntax error (use =).
 * 02/11/95 (seiwald) - when scanning arguments to rules, only treat
 *			punctuation keywords as keywords.  All arg lists
 *			are terminated with punctuation keywords.
 */

%token ARG STRING

%left `||`
%left `&&`
%left `!`

%{
#include "jam.h"

#include "lists.h"
#include "parse.h"
#include "scan.h"
#include "compile.h"
#include "newstr.h"

# define F0 (void (*)())0
# define P0 (PARSE *)0
# define S0 (char *)0

# define pset( l,r,a ) 	  parse_make( compile_set,P0,P0,S0,S0,l,r,a )
# define pset1( l,p,a )	  parse_make( compile_settings,p,P0,S0,S0,l,L0,a )
# define pstng( p,l,r,a ) pset1( p, parse_make( F0,P0,P0,S0,S0,l,r,0 ), a )
# define prule( s,p )     parse_make( compile_rule,p,P0,s,S0,L0,L0,0 )
# define prules( l,r )	  parse_make( compile_rules,l,r,S0,S0,L0,L0,0 )
# define pfor( s,p,l )    parse_make( compile_foreach,p,P0,s,S0,l,L0,0 )
# define psetc( s,p )     parse_make( compile_setcomp,p,P0,s,S0,L0,L0,0 )
# define psete( s,l,s1,f ) parse_make( compile_setexec,P0,P0,s,s1,l,L0,f )
# define pincl( l )       parse_make( compile_include,P0,P0,S0,S0,l,L0,0 )
# define pswitch( l,p )   parse_make( compile_switch,p,P0,S0,S0,l,L0,0 )
# define plocal( l,r,p )  parse_make( compile_local,p,P0,S0,S0,l,r,0 )
# define pnull()	  parse_make( compile_null,P0,P0,S0,S0,L0,L0,0 )
# define pcases( l,r )    parse_make( F0,l,r,S0,S0,L0,L0,0 )
# define pcase( s,p )     parse_make( F0,p,P0,s,S0,L0,L0,0 )
# define pif( l,r )	  parse_make( compile_if,l,r,S0,S0,L0,L0,0 )
# define pthen( l,r )	  parse_make( F0,l,r,S0,S0,L0,L0,0 )
# define pcond( c,l,r )	  parse_make( F0,l,r,S0,S0,L0,L0,c )
# define pcomp( c,l,r )	  parse_make( F0,P0,P0,S0,S0,l,r,c )
# define plol( p,l )	  parse_make( F0,p,P0,S0,S0,l,L0,0 )


%}

%%

run	: block
		{ 
		    if( $1.parse->func == compile_null )
		    {
			parse_free( $1.parse );
		    }
		    else
		    {
			parse_save( $1.parse ); 
		    }
		}
	;

/*
 * block - one or more rules
 * rule - any one of jam's rules
 */

block	: /* empty */
		{ $$.parse = pnull(); }
	| rule block
		{ $$.parse = prules( $1.parse, $2.parse ); }
	| `local` args `;` block
		{ $$.parse = plocal( $2.list, L0, $4.parse ); }
	| `local` args `=` args `;` block
		{ $$.parse = plocal( $2.list, $4.list, $6.parse ); }
	;

rule	: `{` block `}`
		{ $$.parse = $2.parse; }
	| `include` args `;`
		{ $$.parse = pincl( $2.list ); }
	| ARG lol `;`
		{ $$.parse = prule( $1.string, $2.parse ); }
	| arg1 assign args `;`
		{ $$.parse = pset( $1.list, $3.list, $2.number ); }
	| arg1 `on` args assign args `;`
		{ $$.parse = pstng( $3.list, $1.list, $5.list, $4.number ); }
	| arg1 `default` `=` args `;`
		{ $$.parse = pset( $1.list, $4.list, ASSIGN_DEFAULT ); }
	| `for` ARG `in` args `{` block `}`
		{ $$.parse = pfor( $2.string, $6.parse, $4.list ); }
	| `switch` args `{` cases `}`
		{ $$.parse = pswitch( $2.list, $4.parse ); }
	| `if` cond `{` block `}` 
		{ $$.parse = pif( $2.parse, pthen( $4.parse, pnull() ) ); }
	| `if` cond `{` block `}` `else` rule
		{ $$.parse = pif( $2.parse, pthen( $4.parse, $7.parse ) ); }
	| `rule` ARG rule
		{ $$.parse = psetc( $2.string, $3.parse ); }
	| `actions` eflags ARG bindlist `{`
		{ yymode( SCAN_STRING ); }
	  STRING 
		{ yymode( SCAN_NORMAL ); }
	  `}`
		{ $$.parse = psete( $3.string,$4.list,$7.string,$2.number ); }
	;

/*
 * assign - = or +=
 */

assign	: `=`
		{ $$.number = ASSIGN_SET; }
	| `+=`
		{ $$.number = ASSIGN_APPEND; }
	| `?=`
		{ $$.number = ASSIGN_DEFAULT; }
	;

/*
 * cond - a conditional for 'if'
 */

cond	: arg1 
		{ $$.parse = pcomp( COND_EXISTS, $1.list, L0 ); }
	| arg1 `=` arg1 
		{ $$.parse = pcomp( COND_EQUALS, $1.list, $3.list ); }
	| arg1 `!=` arg1
		{ $$.parse = pcomp( COND_NOTEQ, $1.list, $3.list ); }
	| arg1 `<` arg1
		{ $$.parse = pcomp( COND_LESS, $1.list, $3.list ); }
	| arg1 `<=` arg1 
		{ $$.parse = pcomp( COND_LESSEQ, $1.list, $3.list ); }
	| arg1 `>` arg1 
		{ $$.parse = pcomp( COND_MORE, $1.list, $3.list ); }
	| arg1 `>=` arg1 
		{ $$.parse = pcomp( COND_MOREEQ, $1.list, $3.list ); }
	| arg1 `in` args
		{ $$.parse = pcomp( COND_IN, $1.list, $3.list ); }
	| `!` cond
		{ $$.parse = pcond( COND_NOT, $2.parse, P0 ); }
	| cond `&&` cond 
		{ $$.parse = pcond( COND_AND, $1.parse, $3.parse ); }
	| cond `||` cond
		{ $$.parse = pcond( COND_OR, $1.parse, $3.parse ); }
	| `(` cond `)`
		{ $$.parse = $2.parse; }
	;

/*
 * cases - action elements inside a 'switch'
 * case - a single action element inside a 'switch'
 *
 * Unfortunately, a right-recursive rule.
 */

cases	: /* empty */
		{ $$.parse = P0; }
	| case cases
		{ $$.parse = pcases( $1.parse, $2.parse ); }
	;

case	: `case` ARG `:` block
		{ $$.parse = pcase( $2.string, $4.parse ); }
	;

/*
 * lol - list of lists
 */

lol	: args
		{ $$.parse = plol( P0, $1.list ); }
	| args `:` lol
		{ $$.parse = plol( $3.parse, $1.list ); }
	;

/*
 * args - zero or more ARGs in a LIST
 * arg1 - exactly one ARG in a LIST 
 */

args	: argsany
		{ yymode( SCAN_NORMAL ); }
	;

argsany	: /* empty */
		{ $$.list = L0; yymode( SCAN_PUNCT ); }
	| argsany ARG
		{ $$.list = list_new( $1.list, copystr( $2.string ) ); }
	;

arg1	: ARG 
		{ $$.list = list_new( L0, copystr( $1.string ) ); }
	;

/*
 * eflags - zero or more modifiers to 'executes'
 * eflag - a single modifier to 'executes'
 */

eflags	: /* empty */
		{ $$.number = 0; }
	| eflags eflag
		{ $$.number = $1.number | $2.number; }
	;

eflag	: `updated`
		{ $$.number = EXEC_UPDATED; }
	| `together`
		{ $$.number = EXEC_TOGETHER; }
	| `ignore`
		{ $$.number = EXEC_IGNORE; }
	| `quietly`
		{ $$.number = EXEC_QUIETLY; }
	| `piecemeal`
		{ $$.number = EXEC_PIECEMEAL; }
	| `existing`
		{ $$.number = EXEC_EXISTING; }
	;


/*
 * bindlist - list of variable to bind for an action
 */

bindlist : /* empty */
		{ $$.list = L0; }
	| `bind` args
		{ $$.list = $2.list; }
	;


