/* Keep JAMVERSYM in sync with VERSION and PATCHLEVEL. */
/* It can be accessed as $(JAM) in the Jamfile. */

#define VERSION "2"
#ifndef PATCHLEVEL 
#define PATCHLEVEL "2.2"
#endif
#define JAMVERSYM "JAMVERSION=2.2"
