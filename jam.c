/*
 * /+\
 * +\	Copyright 1993, 1996 Christopher Seiwald.
 * \+/
 *
 * This file is part of jam.
 *
 * License is hereby granted to use this software and distribute it
 * freely, as long as this copyright notice is retained and modifications 
 * are clearly marked.
 *
 * ALL WARRANTIES ARE HEREBY DISCLAIMED.
 */

# include "jam.h"
# include "option.h"
# include "make.h"
# ifdef FATFS
# include "patchlev.h"
# else
# include "patchlevel.h"
# endif

/* These get various function declarations. */

# include "lists.h"
# include "parse.h"
# include "variable.h"
# include "compile.h"
# include "rules.h"
# include "newstr.h"
# include "scan.h"
# ifdef FATFS
# include "timestam.h"
# else
# include "timestamp.h"
# endif

/* Macintosh is "special" */

# ifdef macintosh
# include <QuickDraw.h>
# endif

/* And UNIX for this */

# ifdef unix
# include <sys/utsname.h>
# endif

/*
 * jam.c - make redux
 *
 * See jam(1) and Jamfile(5) for usage information.
 *
 * These comments document the code.
 *
 * The top half of the code is structured such:
 *
 *                       jam 
 *                      / | \ 
 *                 +---+  |  \
 *                /       |   \ 
 *         jamgram     option  \ 
 *        /  |   \              \
 *       /   |    \              \
 *      /    |     \             |
 *  scan     |     compile      make
 *   |       |    /    \       / |  \
 *   |       |   /      \     /  |   \
 *   |       |  /        \   /   |    \
 * jambase parse         rules  search make1
 *                               |	|   \
 *                               |	|    \
 *                               |	|     \
 *                           timestamp command execute
 *
 *
 * The support routines are called by all of the above, but themselves
 * are layered thus:
 *
 *                     variable|expand
 *                      /  |   |   |
 *                     /   |   |   |
 *                    /    |   |   |
 *                 lists   |   |   filesys
 *                    \    |   |
 *                     \   |   |
 *                      \  |   |
 *                     newstr  |
 *                        \    |
 *                         \   |
 *                          \  |
 *                          hash
 *
 * Roughly, the modules are:
 *
 *	command.c - maintain lists of commands
 *	compile.c - compile parsed jam statements
 *	execunix.c - execute a shell script on UNIX
 *	execvms.c - execute a shell script, ala VMS
 *	expand.c - expand a buffer, given variable values
 *	fileunix.c - manipulate file names and scan directories on UNIX
 *	filevms.c - manipulate file names and scan directories on VMS
 *	hash.c - simple in-memory hashing routines 
 *	headers.c - handle #includes in source files
 *	jambase.c - compilable copy of Jambase
 *	jamgram.y - jam grammar
 *	lists.c - maintain lists of strings
 *	make.c - bring a target up to date, once rules are in place
 *	make1.c - execute command to bring targets up to date
 *	newstr.c - string manipulation routines
 *	option.c - command line option processing
 *	parse.c - make and destroy parse trees as driven by the parser
 *	regexp.c - Henry Spencer's regexp
 *	rules.c - access to RULEs, TARGETs, and ACTIONs
 *	scan.c - the jam yacc scanner
 *	search.c - find a target along $(SEARCH) or $(LOCATE) 
 *	timestamp.c - get the timestamp of a file or archive member
 *	variable.c - handle jam multi-element variables
 *
 * 05/04/94 (seiwald) - async multiprocess (-j) support
 * 02/08/95 (seiwald) - -n implies -d2.
 * 02/22/95 (seiwald) - -v for version info.
 */

struct globs globs = {
	0,			/* noexec */
	1,			/* jobs */
# ifdef macintosh
	{ 0, 0 },		/* debug - suppress tracing output */
# else
	{ 0, 1 }, 		/* debug ... */
# endif
	0			/* output commands, not run them */
} ;

/* Symbols to be defined as true for use in Jambase */

static char *othersyms[] = { OSSYMS OSPLATSYM, JAMVERSYM, 0 } ;

# ifndef __WATCOM__
# ifndef __OS2__
# ifndef NT
extern char **environ;
# endif
# endif
# endif

# ifdef macintosh
# ifdef MPW
QDGlobals qd;
# endif
main( int argc, char **argv, char **environ )
# else
main( argc, argv )
char	**argv;
# endif
{
	int		n;
	char		*s;
	struct option	optv[N_OPTS];
	char		*all = "all";
	int		anyhow = 0;
	int		status;

# ifdef macintosh
	InitGraf(&qd.thePort);
# endif

	argc--, argv++;

	if( ( n = getoptions( argc, argv, "d:j:f:s:t:ano:v", optv ) ) < 0 )
	{
	    printf( "\nusage: jam [ options ] targets...\n\n" );

            printf( "-a      Build all targets, even if they are current.\n" );
            printf( "-dx     Set the debug level to x (0-9).\n" );
            printf( "-fx     Read x instead of Jambase.\n" );
            printf( "-jx     Run up to x shell commands concurrently.\n" );
            printf( "-n      Don't actually execute the updating actions.\n" );
            printf( "-ox     Write the updating actions to file x.\n" );
	    printf( "-sx=y   Set variable x=y, overriding environment.\n" );
            printf( "-tx     Rebuild x, even if it is up-to-date.\n" );
            printf( "-v      Print the version of jam and exit.\n\n" );

	    exit( EXITBAD );
	}

	argc -= n, argv += n;

	/* Version info. */

	if( ( s = getoptval( optv, 'v', 0 ) ) )
	{
	    printf( "Jam/MR  " );
	    printf( "Version %s.%s.  ", VERSION, PATCHLEVEL );
	    printf( "Copyright 1993, 1999 Christopher Seiwald.\n" );

	    return EXITOK;
	}

	/* Pick up interesting options */

	if( ( s = getoptval( optv, 'n', 0 ) ) )
	    globs.noexec++, globs.debug[2] = 1;

	if( ( s = getoptval( optv, 'a', 0 ) ) )
	    anyhow++;

	if( ( s = getoptval( optv, 'j', 0 ) ) )
	    globs.jobs = atoi( s );

	/* Turn on/off debugging */

	for( n = 0; s = getoptval( optv, 'd', n ); n++ )
	{
	    int i;

	    /* First -d, turn off defaults. */

	    if( !n )
		for( i = 0; i < DEBUG_MAX; i++ )
		    globs.debug[i] = 0;

	    i = atoi( s );

	    if( i < 0 || i >= DEBUG_MAX )
	    {
		printf( "Invalid debug level '%s'.\n", s );
		continue;
	    }

	    /* n turns on levels 1-n */
	    /* +n turns on level n */

	    if( *s == '+' )
		globs.debug[i] = 1;
	    else while( i )
		globs.debug[i--] = 1;
	}

	/* Set JAMDATE first */

	{
	    char *date;
	    time_t clock;
	    time( &clock );
	    date = newstr( ctime( &clock ) );

	    /* Trim newline from date */

	    if( strlen( date ) == 25 )
		date[ 24 ] = 0;

	    var_set( "JAMDATE", list_new( L0, newstr( date ) ), VAR_SET );
	}

	/* And JAMUNAME */
# ifdef unix
	{
	    struct utsname u;

	    if( uname( &u ) >= 0 )
	    {
		var_set( "JAMUNAME", 
			list_new( 
			list_new(
			list_new(
			list_new(
			list_new( L0, 
				newstr( u.sysname ) ),
				newstr( u.nodename ) ),
				newstr( u.release ) ),
				newstr( u.version ) ),
				newstr( u.machine ) ), VAR_SET );
	    }
	}
# endif /* unix */

	/* load up environment variables */

# ifdef MPW
	/*
	 * The third parameter of main() on the mac (at least when this
	 * is compiled with MPW tools) does not have entries of the form
	 * "name=value", but instead "name\0value".  Since var_defines()
	 * expects the former, we need to munge them before passing.
	 */
	{
	    char **munged, **src, **dest;
	    int envsize;

	    /* First determine the size of environ */
	    for( src = environ, envsize = 1; *src; src++, envsize++ );
	    munged = malloc( sizeof( char* ) * envsize );

	    for( src = environ, dest = munged; *src; src++, dest++ )
	    {
	    	/*
		 * Can't use strlen() to find the length of the environ
		 * entries without finding the first \0, and adding the
		 * lengths of the "name" and "value" parts (taking into
		 * account the terminating \0's.
		 */
		char *first0;
		int lenplusterminator;
		for( first0 = *src; *first0; first0++ );

		lenplusterminator = 2 + (first0-*src) + strlen(first0+1);
		*dest = malloc( lenplusterminator );
		memcpy( *dest, *src, lenplusterminator);
		*(*dest + (first0-*src)) = '=';
	    }
	    *dest = NULL;
	    var_defines( munged );
	}
# else
	var_defines( environ );
# endif
	var_defines( othersyms );

	/* Load up variables set on command line. */

	for( n = 0; s = getoptval( optv, 's', n ); n++ )
	{
	    char *symv[2];
	    symv[0] = s;
	    symv[1] = 0;
	    var_defines( symv );
	}

	/* Initialize builtins */

	compile_builtins();

	/* Parse ruleset */

	for( n = 0; s = getoptval( optv, 'f', n ); n++ )
	    parse_file( s );

	if( !n )
	    parse_file( "+" );

	status = yyanyerrors();

	/* Manually touch -t targets */

	for( n = 0; s = getoptval( optv, 't', n ); n++ )
	    touchtarget( s );

	/* If an output file is specified, set globs.cmdout to that */

	if( s = getoptval( optv, 'o', 0 ) )
	{
	    if( !( globs.cmdout = fopen( s, "w" ) ) )
	    {
		printf( "Failed to write to '%s'\n", s );
		exit( EXITBAD );
	    }
	    globs.noexec++;
	}

	/* Now make target */

	if( !argc )
	    status |= make( 1, &all, anyhow );
	else
	    status |= make( argc, argv, anyhow );

	/* Widely scattered cleanup */

	var_done();
	donerules();
	donestamps();
	donestr();

	/* close cmdout */

	if( globs.cmdout )
	    fclose( globs.cmdout );

	return status ? EXITBAD : EXITOK;
}
