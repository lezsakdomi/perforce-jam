/*
 * Copyright 1993, 1995 Christopher Seiwald.
 *
 * This file is part of Jam - see jam.c for Copyright information.
 */

/*
 * jam.h - includes and globals for jam
 *
 * 04/08/94 (seiwald) - Coherent/386 support added.
 * 04/21/94 (seiwald) - DGUX is __DGUX__, not just __DGUX.
 * 05/04/94 (seiwald) - new globs.jobs (-j jobs)
 * 11/01/94 (wingerd) - let us define path of Jambase at compile time.
 * 12/30/94 (wingerd) - changed command buffer size for NT (MS-DOS shell).
 * 02/22/95 (seiwald) - Jambase now in /usr/local/lib.
 * 04/30/95 (seiwald) - FreeBSD added.  Live Free or Die.
 * 05/10/95 (seiwald) - SPLITPATH character set up here.
 * 08/20/95 (seiwald) - added LINUX.
 * 08/21/95 (seiwald) - added NCR.
 * 10/23/95 (seiwald) - added SCO.
 * 01/03/96 (seiwald) - SINIX (nixdorf) added.
 * 03/13/96 (seiwald) - Jambase now compiled in; remove JAMBASE variable.
 * 04/29/96 (seiwald) - AIX now has 31 and 42 OSVERs.
 * 11/21/96 (peterk)  - added BeOS with MW CW mwcc
 * 12/21/96 (seiwald) - OSPLAT now defined for NT.
 */

# ifdef VMS

int unlink( char *f ); 	/* In filevms.c */

# include <types.h>
# include <file.h>
# include <stat.h>
# include <stdio.h>
# include <ctype.h>
# include <stdlib.h>
# include <signal.h>
# include <string.h>
# include <time.h>
# include <unixlib.h>

# ifdef __DECC
# define OTHERSYMS "VMS=true","OS=OPENVMS"
# else
# define OTHERSYMS "VMS=true","OS=VMS"
# endif 

# define MAXLINE 1024 /* longest 'together' actions */
# define SPLITPATH ','
# define EXITOK 1
# define EXITBAD 0

# else

# ifdef NT

# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <ctype.h>
# include <malloc.h>
# include <memory.h>
# include <signal.h>
# include <string.h>
# include <time.h>

# ifdef _M_PPC
# define OTHERSYMS "NT=true","OS=NT","OSPLAT=PPC"
# else
# ifdef _ALPHA_
# define OTHERSYMS "NT=true","OS=NT","OSPLAT=ALPHA"
# else 
# define OTHERSYMS "NT=true","OS=NT","OSPLAT=X86"
# endif /* _ALPHA_ */
# endif /* _PPC_ */

# define SPLITPATH ';'
# define MAXLINE 996	/* longest 'together' actions */
# define EXITOK 0
# define EXITBAD 1

# else

# ifdef __OS2__

# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <ctype.h>
# include <malloc.h>
# include <signal.h>
# include <string.h>
# include <time.h>

# define OTHERSYMS "OS2=true","OS=OS2"
# define SPLITPATH ';'
# define MAXLINE 996	/* longest 'together' actions */
# define EXITOK 0
# define EXITBAD 1

# else

# ifdef __QNX__

# define unix

# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <ctype.h>
# include <malloc.h>
# include <signal.h>
# include <string.h>
# include <time.h>

# define OTHERSYMS "UNIX=true","OS=QNX"
# define SPLITPATH ':'
# define MAXLINE 996	/* longest 'together' actions */
# define EXITOK 0
# define EXITBAD 1

# else /* QNX */

# ifdef macintosh
# include <time.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>

# define OTHERSYMS "MAC=true","OS=MAC"
# define SPLITPATH ','
# define MAXLINE 1024	/* longest 'together' actions */
# define EXITOK 0
# define EXITBAD 1

# else /* not MAC */

# include <sys/types.h>
# include <sys/file.h>
# include <sys/stat.h>
# include <fcntl.h>
# ifndef ultrix
# include <stdlib.h>
# endif
# include <stdio.h>
# include <ctype.h>
# if !defined(__bsdi__)&&!defined(__FreeBSD__)
# if !defined(NeXT)&&!defined(__MACHTEN__)
# if !defined(MVS)
# include <malloc.h>
# endif
# endif
# endif
# include <memory.h>
# include <signal.h>
# include <string.h>
# include <time.h>

# ifdef _AIX
# define unix
# ifdef _AIX41
# define OTHERSYMS "UNIX=true","OS=AIX","OSVER=41"
# else
# define OTHERSYMS "UNIX=true","OS=AIX","OSVER=32"
# endif
# endif

# ifdef __BEOS__
# define OTHERSYMS "UNIX=true","OS=BEOS"
# define unix
# endif

# ifdef __bsdi__
# define OTHERSYMS "UNIX=true","OS=BSDI"
# endif
# if defined (COHERENT) && defined (_I386)
# define OTHERSYMS "UNIX=true","OS=COHERENT"
# endif
# ifdef __FreeBSD__
# define OTHERSYMS "UNIX=true","OS=FREEBSD"
# endif
# ifdef __DGUX__
# define OTHERSYMS "UNIX=true","OS=DGUX"
# endif
# ifdef __hpux
# define OTHERSYMS "UNIX=true","OS=HPUX"
# endif
# ifdef __sgi
# define OTHERSYMS "UNIX=true","OS=IRIX"
# endif
# ifdef __ISC
# define OTHERSYMS "UNIX=true","OS=ISC"
# endif
# ifdef linux
# define OTHERSYMS "UNIX=true","OS=LINUX"
# endif
# ifdef __MACHTEN__
# define OTHERSYMS "UNIX=true","OS=MACHTEN"
# endif
# ifdef MVS
# define unix
# define OTHERSYMS "UNIX=true","OS=MVS"
# endif
# ifdef _ATT4
# define OTHERSYMS "UNIX=true","OS=NCR"
# endif
# ifdef NeXT
# define OTHERSYMS "UNIX=true","OS=NEXT"
# endif
# ifdef __osf__
# define OTHERSYMS "UNIX=true","OS=OSF"
# endif
# ifdef _SEQUENT_
# define OTHERSYMS "UNIX=true","OS=PTX"
# endif
# ifdef M_XENIX
# define OTHERSYMS "UNIX=true","OS=SCO"
# endif
# ifdef sinix
# define OTHERSYMS "UNIX=true","OS=SINIX"
# endif
# ifdef sun
# if defined(__svr4__) || defined(__SVR4)
# define OTHERSYMS "UNIX=true","OS=SOLARIS"
# else
# define OTHERSYMS "UNIX=true","OS=SUNOS"
# endif
# endif
# ifdef ultrix
# define OTHERSYMS "UNIX=true","OS=ULTRIX"
# endif
# if defined(__USLC__) && !defined(M_XENIX)
# define OTHERSYMS "UNIX=true","OS=UNIXWARE"
# endif
# ifndef OTHERSYMS
# define OTHERSYMS "UNIX=true","OS=UNKNOWN"
# endif

# define MAXLINE 10240	/* longest 'together' actions' */
# define SPLITPATH ':'
# define EXITOK 0
# define EXITBAD 1

# endif /* mac */

# endif /* QNX */

# endif /* OS/2 */

# endif /* NT */

# endif /* UNIX */

/* You probably don't need to muck with these. */

# define MAXSYM	1024	/* longest symbol in the environment */
# define MAXJPATH 1024	/* longest filename */

# define MAXJOBS 64	/* silently enforce -j limit */
# define MAXARGC 32	/* words in $(JAMSHELL) */

# define CMDBUF 10240	/* size of command blocks */

/* Jam private definitions below. */

# define DEBUG_MAX	10

struct globs {
	int	noexec;
	int	jobs;
	char	debug[DEBUG_MAX];
} ;

extern struct globs globs;

# define DEBUG_MAKE	( globs.debug[ 1 ] )	/* show actions when executed */
# define DEBUG_MAKEQ	( globs.debug[ 2 ] )	/* show even quiet actions */
# define DEBUG_EXEC	( globs.debug[ 2 ] )	/* show text of actons */
# define DEBUG_MAKEPROG	( globs.debug[ 3 ] )	/* show progress of make0 */
# define DEBUG_BIND	( globs.debug[ 3 ] )	/* show when files bound */

# define DEBUG_EXECCMD	( globs.debug[ 4 ] )	/* show execcmds()'s work */

# define DEBUG_COMPILE	( globs.debug[ 5 ] )	/* show rule invocations */

# define DEBUG_HEADER	( globs.debug[ 6 ] )	/* show result of header scan */
# define DEBUG_BINDSCAN	( globs.debug[ 6 ] )	/* show result of dir scan */
# define DEBUG_SEARCH	( globs.debug[ 6 ] )	/* show attempts at binding */

# define DEBUG_VARSET	( globs.debug[ 7 ] )	/* show variable settings */
# define DEBUG_VARGET	( globs.debug[ 8 ] )	/* show variable fetches */
# define DEBUG_VAREXP	( globs.debug[ 8 ] )	/* show variable expansions */
# define DEBUG_IF	( globs.debug[ 8 ] )	/* show 'if' calculations */
# define DEBUG_LISTS	( globs.debug[ 9 ] )	/* show list manipulation */
# define DEBUG_SCAN	( globs.debug[ 9 ] )	/* show scanner tokens */
# define DEBUG_MEM	( globs.debug[ 9 ] )	/* show memory use */

