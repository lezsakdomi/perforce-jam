#ifndef lint
static char const yysccsid[] = "@(#)yaccpar	1.9 (Berkeley) 02/21/93";
#endif
#define YYBYACC 1
#define YYMAJOR 1
#define YYMINOR 9
#define YYLEX yylex()
#define YYEMPTY -1
#define yyclearin (yychar=(YYEMPTY))
#define yyerrok (yyerrflag=0)
#define YYRECOVERING (yyerrflag!=0)
/* cfront 1.2 defines "c_plusplus" instead of "__cplusplus" */
#ifdef c_plusplus
#ifndef __cplusplus
#define __cplusplus
#endif
#endif
#ifdef __cplusplus
extern "C" { char *getenv(const char *); }
#else
extern char *getenv();
extern int yylex();
extern int yyparse();
#endif
#define YYPREFIX "yy"
#line 64 "jamgram.y"
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


#line 61 "y.tab.c"
#define _BANG 257
#define _BANG_EQUALS 258
#define _AMPERAMPER 259
#define _LPAREN 260
#define _RPAREN 261
#define _PLUS_EQUALS 262
#define _COLON 263
#define _SEMIC 264
#define _LANGLE 265
#define _LANGLE_EQUALS 266
#define _EQUALS 267
#define _RANGLE 268
#define _RANGLE_EQUALS 269
#define _QUESTION_EQUALS 270
#define ACTIONS 271
#define BIND 272
#define CASE 273
#define DEFAULT 274
#define ELSE 275
#define EXISTING 276
#define FOR 277
#define IF 278
#define IGNORE 279
#define IN 280
#define INCLUDE 281
#define LOCAL 282
#define ON 283
#define PIECEMEAL 284
#define QUIETLY 285
#define RULE 286
#define SWITCH 287
#define TOGETHER 288
#define UPDATED 289
#define _LBRACE 290
#define _BARBAR 291
#define _RBRACE 292
#define ARG 293
#define STRING 294
#define YYERRCODE 256
const short yylhs[] = {                                        -1,
    0,    1,    1,    1,    1,    2,    2,    2,    2,    2,
    2,    2,    2,    2,    2,    2,   11,   12,    2,    6,
    6,    6,    8,    8,    8,    8,    8,    8,    8,    8,
    8,    8,    8,    8,    7,    7,   13,    4,    4,    3,
   14,   14,    5,    9,    9,   15,   15,   15,   15,   15,
   15,   10,   10,
};
const short yylen[] = {                                         2,
    1,    0,    2,    4,    6,    3,    3,    3,    4,    6,
    5,    7,    5,    5,    7,    3,    0,    0,    9,    1,
    1,    1,    1,    3,    3,    3,    3,    3,    3,    3,
    2,    3,    3,    3,    0,    2,    4,    1,    3,    1,
    0,    2,    1,    0,    2,    1,    1,    1,    1,    1,
    1,    0,    2,
};
const short yydefred[] = {                                      0,
   44,    0,    0,   41,   41,    0,   41,    0,    0,    0,
    1,    0,    0,    0,    0,    0,    0,   43,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    3,   21,
   20,   22,    0,   41,   41,   51,   48,   50,   49,   47,
   46,    0,   45,   41,   31,    0,    0,    0,    0,    0,
    0,    0,   41,    0,    0,    0,    7,   42,    0,   41,
   16,    0,    6,   41,    8,   41,    0,    0,   41,    0,
    0,   34,   25,   26,   27,   24,   28,   29,   30,   32,
    0,    0,    4,    0,    0,    0,    0,   39,    0,   41,
    9,   53,   17,    0,    0,    0,    0,   13,   36,   11,
    0,    0,    0,    0,    5,    0,   10,   18,   12,   15,
   37,    0,   19,
};
const short yydgoto[] = {                                      10,
   11,   12,   27,   28,   13,   35,   86,   20,   14,   70,
  102,  112,   87,   22,   43,
};
const short yysindex[] = {                                   -182,
    0, -274, -252,    0,    0, -270,    0, -182,    0,    0,
    0, -182, -160, -152, -245, -252, -252,    0, -238, -237,
 -225, -250, -177, -165, -224, -240, -196, -189,    0,    0,
    0,    0, -191,    0,    0,    0,    0,    0,    0,    0,
    0, -187,    0,    0,    0, -227, -210, -210, -210, -210,
 -210, -210,    0, -252, -182, -252,    0,    0, -182,    0,
    0, -192,    0,    0,    0,    0, -136, -173,    0, -193,
 -181,    0,    0,    0,    0,    0,    0,    0,    0,    0,
 -198, -158,    0, -149, -176, -174, -192,    0, -145,    0,
    0,    0,    0, -182, -155, -182, -134,    0,    0,    0,
 -129, -164, -154, -165,    0, -182,    0,    0,    0,    0,
    0, -153,    0,
};
const short yyrindex[] = {                                    140,
    0,    0,    0,    0,    0,    0,    0, -150, -190,    0,
    0,    3,    0,    0,    0,    0,    0,    0, -221,    0,
    0, -246,    0,    0,    0,    0, -121,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0, -146,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0, -150,    0,    0,    0,    3,    0,
    0, -147,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0, -212,    0,    0,    0,    0, -147,    0,    0,    0,
    0,    0,    0, -150,    1,    3,    0,    0,    0,    0,
    0,    0,    0,    0,    0, -259,    0,    0,    0,    0,
    0,    0,    0,
};
const short yygindex[] = {                                      0,
   -8,  -22,    2,   82,    9,   80,   61,   -6,    0,    0,
    0,    0,    0,    0,    0,
};
#define YYTABLESIZE 295
const short yytable[] = {                                      26,
   14,   61,    2,   29,   16,   21,   23,   17,   25,   45,
   46,   19,   40,    2,   40,   40,   40,   40,   15,   47,
   40,   54,   24,   40,   19,   19,   48,   49,   50,   51,
   52,   54,    2,   72,   44,   67,   68,   23,   57,   23,
   18,   53,   58,   40,   40,   71,   81,   80,   33,   82,
   83,   63,   55,   56,   79,   73,   74,   75,   76,   77,
   78,   84,   19,   56,   19,   62,   64,   89,   23,   23,
   92,   43,   41,   41,   65,   66,   43,   33,   33,   43,
   85,  110,   18,   43,   69,  103,   59,  105,    1,   60,
   91,  101,   43,   95,    2,    3,   93,  111,    4,    5,
   54,   30,   41,    6,    7,    1,   31,    8,   94,   32,
    9,    2,    3,   33,   96,    4,   97,   98,  100,  104,
    6,    7,   34,   36,    8,   30,   37,    9,  106,  108,
   31,   38,   39,   32,  107,   40,   41,  109,  113,    2,
   42,    2,   38,   52,   35,   88,   90,   99,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,   14,    0,   14,    0,    2,    0,   14,   14,    0,
    0,   14,   14,    0,    0,    0,   14,   14,    0,    0,
   14,    0,   14,   14,    2,
};
const short yycheck[] = {                                       8,
    0,   24,    0,   12,  257,    4,    5,  260,    7,   16,
   17,    3,  259,  273,  261,  262,  263,  264,  293,  258,
  267,  259,  293,  270,   16,   17,  265,  266,  267,  268,
  269,  259,  292,  261,  280,   34,   35,  259,  264,  261,
  293,  280,  293,  290,  291,   44,   55,   54,  261,   56,
   59,  292,  290,  291,   53,   47,   48,   49,   50,   51,
   52,   60,   54,  291,   56,  290,  263,   66,  290,  291,
   69,  262,  263,  264,  264,  267,  267,  290,  291,  270,
  273,  104,  293,  274,  272,   94,  264,   96,  271,  267,
  264,   90,  283,  292,  277,  278,  290,  106,  281,  282,
  259,  262,  293,  286,  287,  271,  267,  290,  290,  270,
  293,  277,  278,  274,  264,  281,  293,  292,  264,  275,
  286,  287,  283,  276,  290,  262,  279,  293,  263,  294,
  267,  284,  285,  270,  264,  288,  289,  292,  292,    0,
  293,  292,  264,  290,  292,   64,   67,   87,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  271,   -1,  273,   -1,  273,   -1,  277,  278,   -1,
   -1,  281,  282,   -1,   -1,   -1,  286,  287,   -1,   -1,
  290,   -1,  292,  293,  292,
};
#define YYFINAL 10
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 294
#if YYDEBUG
char *yyname[] = {
"end-of-file",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"_BANG","_BANG_EQUALS",
"_AMPERAMPER","_LPAREN","_RPAREN","_PLUS_EQUALS","_COLON","_SEMIC","_LANGLE",
"_LANGLE_EQUALS","_EQUALS","_RANGLE","_RANGLE_EQUALS","_QUESTION_EQUALS",
"ACTIONS","BIND","CASE","DEFAULT","ELSE","EXISTING","FOR","IF","IGNORE","IN",
"INCLUDE","LOCAL","ON","PIECEMEAL","QUIETLY","RULE","SWITCH","TOGETHER",
"UPDATED","_LBRACE","_BARBAR","_RBRACE","ARG","STRING",
};
const char * const yyrule[] = {
"$accept : run",
"run : block",
"block :",
"block : rule block",
"block : LOCAL args _SEMIC block",
"block : LOCAL args _EQUALS args _SEMIC block",
"rule : _LBRACE block _RBRACE",
"rule : INCLUDE args _SEMIC",
"rule : ARG lol _SEMIC",
"rule : arg1 assign args _SEMIC",
"rule : arg1 ON args assign args _SEMIC",
"rule : arg1 DEFAULT _EQUALS args _SEMIC",
"rule : FOR ARG IN args _LBRACE block _RBRACE",
"rule : SWITCH args _LBRACE cases _RBRACE",
"rule : IF cond _LBRACE block _RBRACE",
"rule : IF cond _LBRACE block _RBRACE ELSE rule",
"rule : RULE ARG rule",
"$$1 :",
"$$2 :",
"rule : ACTIONS eflags ARG bindlist _LBRACE $$1 STRING $$2 _RBRACE",
"assign : _EQUALS",
"assign : _PLUS_EQUALS",
"assign : _QUESTION_EQUALS",
"cond : arg1",
"cond : arg1 _EQUALS arg1",
"cond : arg1 _BANG_EQUALS arg1",
"cond : arg1 _LANGLE arg1",
"cond : arg1 _LANGLE_EQUALS arg1",
"cond : arg1 _RANGLE arg1",
"cond : arg1 _RANGLE_EQUALS arg1",
"cond : arg1 IN args",
"cond : _BANG cond",
"cond : cond _AMPERAMPER cond",
"cond : cond _BARBAR cond",
"cond : _LPAREN cond _RPAREN",
"cases :",
"cases : case cases",
"case : CASE ARG _COLON block",
"lol : args",
"lol : args _COLON lol",
"args : argsany",
"argsany :",
"argsany : argsany ARG",
"arg1 : ARG",
"eflags :",
"eflags : eflags eflag",
"eflag : UPDATED",
"eflag : TOGETHER",
"eflag : IGNORE",
"eflag : QUIETLY",
"eflag : PIECEMEAL",
"eflag : EXISTING",
"bindlist :",
"bindlist : BIND args",
};
#endif
#ifndef YYSTYPE
typedef int YYSTYPE;
#endif
#ifdef YYSTACKSIZE
#undef YYMAXDEPTH
#define YYMAXDEPTH YYSTACKSIZE
#else
#ifdef YYMAXDEPTH
#define YYSTACKSIZE YYMAXDEPTH
#else
#define YYSTACKSIZE 500
#define YYMAXDEPTH 500
#endif
#endif
int yydebug;
int yynerrs;
int yyerrflag;
int yychar;
short *yyssp;
YYSTYPE *yyvsp;
YYSTYPE yyval;
YYSTYPE yylval;
short yyss[YYSTACKSIZE];
YYSTYPE yyvs[YYSTACKSIZE];
#define yystacksize YYSTACKSIZE
#define YYABORT goto yyabort
#define YYREJECT goto yyabort
#define YYACCEPT goto yyaccept
#define YYERROR goto yyerrlab

int
yyparse()
{
    register int yym, yyn, yystate;
#if YYDEBUG
    register char *yys;

    if ((yys = getenv("YYDEBUG")))
    {
        yyn = *yys;
        if (yyn >= '0' && yyn <= '9')
            yydebug = yyn - '0';
    }
#endif

    yynerrs = 0;
    yyerrflag = 0;
    yychar = (-1);

    yyssp = yyss;
    yyvsp = yyvs;
    *yyssp = yystate = 0;

yyloop:
    if ((yyn = yydefred[yystate])) goto yyreduce;
    if (yychar < 0)
    {
        if ((yychar = yylex()) < 0) yychar = 0;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("%sdebug: state %d, reading %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
    }
    if ((yyn = yysindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: state %d, shifting to state %d\n",
                    YYPREFIX, yystate, yytable[yyn]);
#endif
        if (yyssp >= yyss + yystacksize - 1)
        {
            goto yyoverflow;
        }
        *++yyssp = yystate = yytable[yyn];
        *++yyvsp = yylval;
        yychar = (-1);
        if (yyerrflag > 0)  --yyerrflag;
        goto yyloop;
    }
    if ((yyn = yyrindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
        yyn = yytable[yyn];
        goto yyreduce;
    }
    if (yyerrflag) goto yyinrecovery;
#if defined(lint) || defined(__GNUC__)
    goto yynewerror;
#endif
yynewerror:
    yyerror("syntax error");
#if defined(lint) || defined(__GNUC__)
    goto yyerrlab;
#endif
yyerrlab:
    ++yynerrs;
yyinrecovery:
    if (yyerrflag < 3)
    {
        yyerrflag = 3;
        for (;;)
        {
            if ((yyn = yysindex[*yyssp]) && (yyn += YYERRCODE) >= 0 &&
                    yyn <= YYTABLESIZE && yycheck[yyn] == YYERRCODE)
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: state %d, error recovery shifting\
 to state %d\n", YYPREFIX, *yyssp, yytable[yyn]);
#endif
                if (yyssp >= yyss + yystacksize - 1)
                {
                    goto yyoverflow;
                }
                *++yyssp = yystate = yytable[yyn];
                *++yyvsp = yylval;
                goto yyloop;
            }
            else
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: error recovery discarding state %d\n",
                            YYPREFIX, *yyssp);
#endif
                if (yyssp <= yyss) goto yyabort;
                --yyssp;
                --yyvsp;
            }
        }
    }
    else
    {
        if (yychar == 0) goto yyabort;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("%sdebug: state %d, error recovery discards token %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
        yychar = (-1);
        goto yyloop;
    }
yyreduce:
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: state %d, reducing by rule %d (%s)\n",
                YYPREFIX, yystate, yyn, yyrule[yyn]);
#endif
    yym = yylen[yyn];
    yyval = yyvsp[1-yym];
    switch (yyn)
    {
case 1:
#line 102 "jamgram.y"
{ 
		    if( yyvsp[0].parse->func == compile_null )
		    {
			parse_free( yyvsp[0].parse );
			parse_save( P0 );
		    }
		    else
		    {
			parse_save( yyvsp[0].parse ); 
		    }
		}
break;
case 2:
#line 121 "jamgram.y"
{ yyval.parse = pnull(); }
break;
case 3:
#line 123 "jamgram.y"
{ yyval.parse = prules( yyvsp[-1].parse, yyvsp[0].parse ); }
break;
case 4:
#line 125 "jamgram.y"
{ yyval.parse = plocal( yyvsp[-2].list, L0, yyvsp[0].parse ); }
break;
case 5:
#line 127 "jamgram.y"
{ yyval.parse = plocal( yyvsp[-4].list, yyvsp[-2].list, yyvsp[0].parse ); }
break;
case 6:
#line 131 "jamgram.y"
{ yyval.parse = yyvsp[-1].parse; }
break;
case 7:
#line 133 "jamgram.y"
{ yyval.parse = pincl( yyvsp[-1].list ); }
break;
case 8:
#line 135 "jamgram.y"
{ yyval.parse = prule( yyvsp[-2].string, yyvsp[-1].parse ); }
break;
case 9:
#line 137 "jamgram.y"
{ yyval.parse = pset( yyvsp[-3].list, yyvsp[-1].list, yyvsp[-2].number ); }
break;
case 10:
#line 139 "jamgram.y"
{ yyval.parse = pstng( yyvsp[-3].list, yyvsp[-5].list, yyvsp[-1].list, yyvsp[-2].number ); }
break;
case 11:
#line 141 "jamgram.y"
{ yyval.parse = pset( yyvsp[-4].list, yyvsp[-1].list, ASSIGN_DEFAULT ); }
break;
case 12:
#line 143 "jamgram.y"
{ yyval.parse = pfor( yyvsp[-5].string, yyvsp[-1].parse, yyvsp[-3].list ); }
break;
case 13:
#line 145 "jamgram.y"
{ yyval.parse = pswitch( yyvsp[-3].list, yyvsp[-1].parse ); }
break;
case 14:
#line 147 "jamgram.y"
{ yyval.parse = pif( yyvsp[-3].parse, pthen( yyvsp[-1].parse, pnull() ) ); }
break;
case 15:
#line 149 "jamgram.y"
{ yyval.parse = pif( yyvsp[-5].parse, pthen( yyvsp[-3].parse, yyvsp[0].parse ) ); }
break;
case 16:
#line 151 "jamgram.y"
{ yyval.parse = psetc( yyvsp[-1].string, yyvsp[0].parse ); }
break;
case 17:
#line 153 "jamgram.y"
{ yymode( SCAN_STRING ); }
break;
case 18:
#line 155 "jamgram.y"
{ yymode( SCAN_NORMAL ); }
break;
case 19:
#line 157 "jamgram.y"
{ yyval.parse = psete( yyvsp[-6].string,yyvsp[-5].list,yyvsp[-2].string,yyvsp[-7].number ); }
break;
case 20:
#line 165 "jamgram.y"
{ yyval.number = ASSIGN_SET; }
break;
case 21:
#line 167 "jamgram.y"
{ yyval.number = ASSIGN_APPEND; }
break;
case 22:
#line 169 "jamgram.y"
{ yyval.number = ASSIGN_DEFAULT; }
break;
case 23:
#line 177 "jamgram.y"
{ yyval.parse = pcomp( COND_EXISTS, yyvsp[0].list, L0 ); }
break;
case 24:
#line 179 "jamgram.y"
{ yyval.parse = pcomp( COND_EQUALS, yyvsp[-2].list, yyvsp[0].list ); }
break;
case 25:
#line 181 "jamgram.y"
{ yyval.parse = pcomp( COND_NOTEQ, yyvsp[-2].list, yyvsp[0].list ); }
break;
case 26:
#line 183 "jamgram.y"
{ yyval.parse = pcomp( COND_LESS, yyvsp[-2].list, yyvsp[0].list ); }
break;
case 27:
#line 185 "jamgram.y"
{ yyval.parse = pcomp( COND_LESSEQ, yyvsp[-2].list, yyvsp[0].list ); }
break;
case 28:
#line 187 "jamgram.y"
{ yyval.parse = pcomp( COND_MORE, yyvsp[-2].list, yyvsp[0].list ); }
break;
case 29:
#line 189 "jamgram.y"
{ yyval.parse = pcomp( COND_MOREEQ, yyvsp[-2].list, yyvsp[0].list ); }
break;
case 30:
#line 191 "jamgram.y"
{ yyval.parse = pcomp( COND_IN, yyvsp[-2].list, yyvsp[0].list ); }
break;
case 31:
#line 193 "jamgram.y"
{ yyval.parse = pcond( COND_NOT, yyvsp[0].parse, P0 ); }
break;
case 32:
#line 195 "jamgram.y"
{ yyval.parse = pcond( COND_AND, yyvsp[-2].parse, yyvsp[0].parse ); }
break;
case 33:
#line 197 "jamgram.y"
{ yyval.parse = pcond( COND_OR, yyvsp[-2].parse, yyvsp[0].parse ); }
break;
case 34:
#line 199 "jamgram.y"
{ yyval.parse = yyvsp[-1].parse; }
break;
case 35:
#line 210 "jamgram.y"
{ yyval.parse = P0; }
break;
case 36:
#line 212 "jamgram.y"
{ yyval.parse = pcases( yyvsp[-1].parse, yyvsp[0].parse ); }
break;
case 37:
#line 216 "jamgram.y"
{ yyval.parse = pcase( yyvsp[-2].string, yyvsp[0].parse ); }
break;
case 38:
#line 224 "jamgram.y"
{ yyval.parse = plol( P0, yyvsp[0].list ); }
break;
case 39:
#line 226 "jamgram.y"
{ yyval.parse = plol( yyvsp[0].parse, yyvsp[-2].list ); }
break;
case 40:
#line 235 "jamgram.y"
{ yymode( SCAN_NORMAL ); }
break;
case 41:
#line 239 "jamgram.y"
{ yyval.list = L0; yymode( SCAN_PUNCT ); }
break;
case 42:
#line 241 "jamgram.y"
{ yyval.list = list_new( yyvsp[-1].list, copystr( yyvsp[0].string ) ); }
break;
case 43:
#line 245 "jamgram.y"
{ yyval.list = list_new( L0, copystr( yyvsp[0].string ) ); }
break;
case 44:
#line 254 "jamgram.y"
{ yyval.number = 0; }
break;
case 45:
#line 256 "jamgram.y"
{ yyval.number = yyvsp[-1].number | yyvsp[0].number; }
break;
case 46:
#line 260 "jamgram.y"
{ yyval.number = EXEC_UPDATED; }
break;
case 47:
#line 262 "jamgram.y"
{ yyval.number = EXEC_TOGETHER; }
break;
case 48:
#line 264 "jamgram.y"
{ yyval.number = EXEC_IGNORE; }
break;
case 49:
#line 266 "jamgram.y"
{ yyval.number = EXEC_QUIETLY; }
break;
case 50:
#line 268 "jamgram.y"
{ yyval.number = EXEC_PIECEMEAL; }
break;
case 51:
#line 270 "jamgram.y"
{ yyval.number = EXEC_EXISTING; }
break;
case 52:
#line 279 "jamgram.y"
{ yyval.list = L0; }
break;
case 53:
#line 281 "jamgram.y"
{ yyval.list = yyvsp[0].list; }
break;
#line 696 "y.tab.c"
    }
    yyssp -= yym;
    yystate = *yyssp;
    yyvsp -= yym;
    yym = yylhs[yyn];
    if (yystate == 0 && yym == 0)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: after reduction, shifting from state 0 to\
 state %d\n", YYPREFIX, YYFINAL);
#endif
        yystate = YYFINAL;
        *++yyssp = YYFINAL;
        *++yyvsp = yyval;
        if (yychar < 0)
        {
            if ((yychar = yylex()) < 0) yychar = 0;
#if YYDEBUG
            if (yydebug)
            {
                yys = 0;
                if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
                if (!yys) yys = "illegal-symbol";
                printf("%sdebug: state %d, reading %d (%s)\n",
                        YYPREFIX, YYFINAL, yychar, yys);
            }
#endif
        }
        if (yychar == 0) goto yyaccept;
        goto yyloop;
    }
    if ((yyn = yygindex[yym]) && (yyn += yystate) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yystate)
        yystate = yytable[yyn];
    else
        yystate = yydgoto[yym];
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: after reduction, shifting from state %d \
to state %d\n", YYPREFIX, *yyssp, yystate);
#endif
    if (yyssp >= yyss + yystacksize - 1)
    {
        goto yyoverflow;
    }
    *++yyssp = yystate;
    *++yyvsp = yyval;
    goto yyloop;
yyoverflow:
    yyerror("yacc stack overflow");
yyabort:
    return (1);
yyaccept:
    return (0);
}
