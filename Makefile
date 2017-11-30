# Makefile for jam

# Default settings for Unix / Linux.
# Note: Configurations below may rely on these settings.
CC = cc
CFLAGS =
EXENAME = ./jam0
TARGET = -o $(EXENAME)

# Special flavors - uncomment appropriate lines

# AIX needs -lbsd, and has no identifying cpp symbol
# Use _AIX41 if you're not on 3.2 anymore.
# Also supports AIX53
#CC = gcc
#CFLAGS = -D_AIX
#LINKLIBS = -lbsd
#EXENAME = ./jam0
#TARGET = -o $(EXENAME)

# Darwin 90
# use gcc-4.2, gcc is linked to gcc-4.2
#CC = gcc$(COMPILER_SUFFIX)
#CFLAGS = -D__DARWIN__
#EXENAME = ./jam0
#TARGET = -o $(EXENAME)

# Cygwin - gcc & cygwin
#CC = gcc
#CFLAGS = -D__cygwin__

# Interix - gcc
#CC = gcc

# NCR seems to have a broken readdir() -- use gnu
#CC = gcc

# X64 NET 2005-2015
# Configured with MS CRT deprecation disabled.
# Use the following settings in your Command Prompt to build jam and P4 API
# Note: Do not uncomment these settings in this makefile.
# run the Visual Studio batch script vc/bin/amd64/vcvars64.bat
# set OSPLAT=x64
# set MSCVNT=%VSINSTALLDIR%\VC
# set MSVSVER=
#   where VS2005=8, VS2008=9, VS2010=10, VS2012=11, VS2013=12, VS2015=13
# set BUILD_WITH_SUB_DIRECTORIES=false
#
# Only uncomment the lines immediately below.
#CC = cl /nologo
#CFLAGS = /favor:blend /MT -D_M_AMD64 -DNT -D_CRT_SECURE_NO_DEPRECATE /wd4996
#TARGET = /Fejam0
#LINKLIBS = oldnames.lib kernel32.lib libcmt.lib
#EXENAME = .\jam0.exe

# X86 NET 2005-2015
# Configured with MS CRT deprecation disabled.
# Use the following settings in your Command Prompt to build jam and P4 API
# Note: Do not uncomment these settings in this makefile.
# run the Visual Studio batch script vc/bin/vcvars32.bat
# set OSPLAT=x86
# set MSCVNT=%VSINSTALLDIR%\VC
# set MSVSVER=
#   where VS2005=8, VS2008=9, VS2010=10, VS2012=11, VS2013=12, VS2015=13
# set BUILD_WITH_SUB_DIRECTORIES=false
#
# Only uncomment the lines immediately below.
#CC = cl /nologo
#CFLAGS = /MT -DNT -D_CRT_SECURE_NO_DEPRECATE /wd4996
#TARGET = /Fejam0
#LINKLIBS = oldnames.lib kernel32.lib libcmt.lib
#EXENAME = .\jam0.exe

# MingW32
#CC = gcc
#CFLAGS = -DMINGW
#EXENAME = ./jam0
#TARGET = -o $(EXENAME)

# MinGW-w64
#CC = gcc
#CFLAGS = -DMINGW64
#EXENAME = ./jam0
#TARGET = -o $(EXENAME)

# MPEIX
#CC = gcc
#CFLAGS = -I/usr/include -D_POSIX_SOURCE

# SOLARIS
#CC = gcc

# QNX rtp (neutrino)
#CC = gcc

# AS400 - icc wrapper around ILE C compiler.
# CC = icc 
# CFLAGS = -DAS400 -qDUPPROC
#
# Can't use ./jam0 as EXENAME on AS/400. It confuses icc et al.
# EXENAME = jam0  

SOURCES = \
	builtins.c \
	command.c compile.c execas400.c execunix.c execvms.c expand.c \
	filent.c fileos2.c fileunix.c filevms.c glob.c hash.c \
	headers.c jam.c jambase.c jamgram.c lists.c make.c make1.c \
	newstr.c option.c parse.c pathunix.c pathvms.c regexp.c \
	rules.c scan.c search.c timestamp.c variable.c

all: $(EXENAME)
	$(EXENAME)

$(EXENAME):
	$(CC) $(TARGET) $(CFLAGS) $(SOURCES) $(LINKLIBS)
