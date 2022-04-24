#---------------------------------------------------------------------------
#
# 	File: Makefile.sample 
#	
#		For ubuntu v16 12/23/17
#
#---------------------------------------------------------------------------

PGM = editres

CC=gcc
#CDEBUGFLAGS = -g -W

CDEBUGFLAGS =
DEFINES =

INCLUDES =

# INCLUDES = -I../include -I$(XDIR)/include -I/usr/include/x86_64-linux-gnu -I/usr/lib/gcc/x86_64-linux-gnu/5/include

# Only for my specific system for makedepend - see note below
DEPENDINCLUDES = -I../include -I/usr/include/x86_64-linux-gnu  -I/usr/lib/gcc/x86_64-linux-gnu/9/include

CFLAGS = $(CDEBUGFLAGS) $(INCLUDES) $(DEFINES)
LDFLAGS = -o

XLIBS = -lXm -lX11 -lXmu -lXt -lXaw

LIBS = $(XLIBS)

#---------------------------------------------------------------------------
OBJS = actions.o \
comm.o \
editres.o \
geometry.o \
handler.o \
setvalues.o \
svpopup.o \
utils.o \
widgets.o \
wtree.o 

#---------------------------------------------------------------------------

$(PGM): $(OBJS) 
	$(CC) $(LDFLAGS) $(PGM) $(OBJS) $(LIBS) 

relink:
	rm -f $(PGM)
	$(CC) $(LDFLAGS) $(PGM) $(OBJS) $(LIBS)

#all: clean depend $(PGM)
all: clean $(PGM) ctags

clean:
	rm -f $(PGM) *.o *.a 

ctags:	
	ctags -S *.c

depend:	
	makedepend $(DEPENDINCLUDES) $(DEFINES) *.c

# DO NOT DELETE

actions.o: /usr/include/stdio.h
actions.o: /usr/include/x86_64-linux-gnu/bits/libc-header-start.h
actions.o: /usr/include/features.h /usr/include/stdc-predef.h
actions.o: /usr/include/x86_64-linux-gnu/sys/cdefs.h
actions.o: /usr/include/x86_64-linux-gnu/bits/wordsize.h
actions.o: /usr/include/x86_64-linux-gnu/bits/long-double.h
actions.o: /usr/include/x86_64-linux-gnu/gnu/stubs.h
actions.o: /usr/lib/gcc/x86_64-linux-gnu/9/include/stddef.h
actions.o: /usr/lib/gcc/x86_64-linux-gnu/9/include/stdarg.h
actions.o: /usr/include/x86_64-linux-gnu/bits/types.h
actions.o: /usr/include/x86_64-linux-gnu/bits/timesize.h
actions.o: /usr/include/x86_64-linux-gnu/bits/typesizes.h
actions.o: /usr/include/x86_64-linux-gnu/bits/time64.h
actions.o: /usr/include/x86_64-linux-gnu/bits/types/__fpos_t.h
actions.o: /usr/include/x86_64-linux-gnu/bits/types/__mbstate_t.h
actions.o: /usr/include/x86_64-linux-gnu/bits/types/__fpos64_t.h
actions.o: /usr/include/x86_64-linux-gnu/bits/types/__FILE.h
actions.o: /usr/include/x86_64-linux-gnu/bits/types/FILE.h
actions.o: /usr/include/x86_64-linux-gnu/bits/types/struct_FILE.h
actions.o: /usr/include/x86_64-linux-gnu/bits/stdio_lim.h
actions.o: /usr/include/x86_64-linux-gnu/bits/sys_errlist.h
actions.o: /usr/include/X11/Intrinsic.h /usr/include/X11/Xlib.h
actions.o: /usr/include/x86_64-linux-gnu/sys/types.h
actions.o: /usr/include/x86_64-linux-gnu/bits/types/clock_t.h
actions.o: /usr/include/x86_64-linux-gnu/bits/types/clockid_t.h
actions.o: /usr/include/x86_64-linux-gnu/bits/types/time_t.h
actions.o: /usr/include/x86_64-linux-gnu/bits/types/timer_t.h
actions.o: /usr/include/x86_64-linux-gnu/bits/stdint-intn.h
actions.o: /usr/include/endian.h /usr/include/x86_64-linux-gnu/bits/endian.h
actions.o: /usr/include/x86_64-linux-gnu/bits/endianness.h
actions.o: /usr/include/x86_64-linux-gnu/bits/byteswap.h
actions.o: /usr/include/x86_64-linux-gnu/bits/uintn-identity.h
actions.o: /usr/include/x86_64-linux-gnu/sys/select.h
actions.o: /usr/include/x86_64-linux-gnu/bits/select.h
actions.o: /usr/include/x86_64-linux-gnu/bits/types/sigset_t.h
actions.o: /usr/include/x86_64-linux-gnu/bits/types/__sigset_t.h
actions.o: /usr/include/x86_64-linux-gnu/bits/types/struct_timeval.h
actions.o: /usr/include/x86_64-linux-gnu/bits/types/struct_timespec.h
actions.o: /usr/include/x86_64-linux-gnu/bits/pthreadtypes.h
actions.o: /usr/include/x86_64-linux-gnu/bits/thread-shared-types.h
actions.o: /usr/include/x86_64-linux-gnu/bits/pthreadtypes-arch.h
actions.o: /usr/include/x86_64-linux-gnu/bits/struct_mutex.h
actions.o: /usr/include/x86_64-linux-gnu/bits/struct_rwlock.h
actions.o: /usr/include/X11/X.h /usr/include/X11/Xfuncproto.h
actions.o: /usr/include/X11/Xosdefs.h /usr/include/X11/Xutil.h
actions.o: /usr/include/X11/keysym.h /usr/include/X11/keysymdef.h
actions.o: /usr/include/X11/Xresource.h /usr/include/string.h
actions.o: /usr/include/x86_64-linux-gnu/bits/types/locale_t.h
actions.o: /usr/include/x86_64-linux-gnu/bits/types/__locale_t.h
actions.o: /usr/include/strings.h /usr/include/X11/Core.h
actions.o: /usr/include/X11/Composite.h /usr/include/X11/Constraint.h
actions.o: /usr/include/X11/Object.h /usr/include/X11/RectObj.h
actions.o: /usr/include/X11/Xmu/CharSet.h /usr/include/X11/Xaw/Cardinals.h
actions.o: editresP.h /usr/include/X11/Xmu/EditresP.h
comm.o: /usr/include/X11/Intrinsic.h /usr/include/X11/Xlib.h
comm.o: /usr/include/x86_64-linux-gnu/sys/types.h /usr/include/features.h
comm.o: /usr/include/stdc-predef.h /usr/include/x86_64-linux-gnu/sys/cdefs.h
comm.o: /usr/include/x86_64-linux-gnu/bits/wordsize.h
comm.o: /usr/include/x86_64-linux-gnu/bits/long-double.h
comm.o: /usr/include/x86_64-linux-gnu/gnu/stubs.h
comm.o: /usr/include/x86_64-linux-gnu/bits/types.h
comm.o: /usr/include/x86_64-linux-gnu/bits/timesize.h
comm.o: /usr/include/x86_64-linux-gnu/bits/typesizes.h
comm.o: /usr/include/x86_64-linux-gnu/bits/time64.h
comm.o: /usr/include/x86_64-linux-gnu/bits/types/clock_t.h
comm.o: /usr/include/x86_64-linux-gnu/bits/types/clockid_t.h
comm.o: /usr/include/x86_64-linux-gnu/bits/types/time_t.h
comm.o: /usr/include/x86_64-linux-gnu/bits/types/timer_t.h
comm.o: /usr/lib/gcc/x86_64-linux-gnu/9/include/stddef.h
comm.o: /usr/include/x86_64-linux-gnu/bits/stdint-intn.h
comm.o: /usr/include/endian.h /usr/include/x86_64-linux-gnu/bits/endian.h
comm.o: /usr/include/x86_64-linux-gnu/bits/endianness.h
comm.o: /usr/include/x86_64-linux-gnu/bits/byteswap.h
comm.o: /usr/include/x86_64-linux-gnu/bits/uintn-identity.h
comm.o: /usr/include/x86_64-linux-gnu/sys/select.h
comm.o: /usr/include/x86_64-linux-gnu/bits/select.h
comm.o: /usr/include/x86_64-linux-gnu/bits/types/sigset_t.h
comm.o: /usr/include/x86_64-linux-gnu/bits/types/__sigset_t.h
comm.o: /usr/include/x86_64-linux-gnu/bits/types/struct_timeval.h
comm.o: /usr/include/x86_64-linux-gnu/bits/types/struct_timespec.h
comm.o: /usr/include/x86_64-linux-gnu/bits/pthreadtypes.h
comm.o: /usr/include/x86_64-linux-gnu/bits/thread-shared-types.h
comm.o: /usr/include/x86_64-linux-gnu/bits/pthreadtypes-arch.h
comm.o: /usr/include/x86_64-linux-gnu/bits/struct_mutex.h
comm.o: /usr/include/x86_64-linux-gnu/bits/struct_rwlock.h
comm.o: /usr/include/X11/X.h /usr/include/X11/Xfuncproto.h
comm.o: /usr/include/X11/Xosdefs.h /usr/include/X11/Xutil.h
comm.o: /usr/include/X11/keysym.h /usr/include/X11/keysymdef.h
comm.o: /usr/include/X11/Xresource.h /usr/include/string.h
comm.o: /usr/include/x86_64-linux-gnu/bits/libc-header-start.h
comm.o: /usr/include/x86_64-linux-gnu/bits/types/locale_t.h
comm.o: /usr/include/x86_64-linux-gnu/bits/types/__locale_t.h
comm.o: /usr/include/strings.h /usr/include/X11/Core.h
comm.o: /usr/include/X11/Composite.h /usr/include/X11/Constraint.h
comm.o: /usr/include/X11/Object.h /usr/include/X11/RectObj.h
comm.o: /usr/include/X11/StringDefs.h /usr/include/X11/Xatom.h
comm.o: /usr/include/X11/cursorfont.h /usr/include/X11/Xproto.h
comm.o: /usr/include/X11/Xmd.h /usr/include/X11/Xprotostr.h
comm.o: /usr/include/X11/Xos.h /usr/include/fcntl.h
comm.o: /usr/include/x86_64-linux-gnu/bits/fcntl.h
comm.o: /usr/include/x86_64-linux-gnu/bits/fcntl-linux.h
comm.o: /usr/include/x86_64-linux-gnu/bits/stat.h /usr/include/unistd.h
comm.o: /usr/include/x86_64-linux-gnu/bits/posix_opt.h
comm.o: /usr/include/x86_64-linux-gnu/bits/environments.h
comm.o: /usr/include/x86_64-linux-gnu/bits/confname.h
comm.o: /usr/include/x86_64-linux-gnu/bits/getopt_posix.h
comm.o: /usr/include/x86_64-linux-gnu/bits/getopt_core.h
comm.o: /usr/include/x86_64-linux-gnu/bits/unistd_ext.h
comm.o: /usr/include/x86_64-linux-gnu/sys/time.h /usr/include/time.h
comm.o: /usr/include/x86_64-linux-gnu/bits/time.h
comm.o: /usr/include/x86_64-linux-gnu/bits/types/struct_tm.h
comm.o: /usr/include/x86_64-linux-gnu/bits/types/struct_itimerspec.h
comm.o: /usr/include/X11/Xarch.h /usr/include/stdio.h
comm.o: /usr/lib/gcc/x86_64-linux-gnu/9/include/stdarg.h
comm.o: /usr/include/x86_64-linux-gnu/bits/types/__fpos_t.h
comm.o: /usr/include/x86_64-linux-gnu/bits/types/__mbstate_t.h
comm.o: /usr/include/x86_64-linux-gnu/bits/types/__fpos64_t.h
comm.o: /usr/include/x86_64-linux-gnu/bits/types/__FILE.h
comm.o: /usr/include/x86_64-linux-gnu/bits/types/FILE.h
comm.o: /usr/include/x86_64-linux-gnu/bits/types/struct_FILE.h
comm.o: /usr/include/x86_64-linux-gnu/bits/stdio_lim.h
comm.o: /usr/include/x86_64-linux-gnu/bits/sys_errlist.h
comm.o: /usr/include/X11/Xmu/Error.h editresP.h
comm.o: /usr/include/X11/Xmu/EditresP.h
editres.o: /usr/include/stdio.h
editres.o: /usr/include/x86_64-linux-gnu/bits/libc-header-start.h
editres.o: /usr/include/features.h /usr/include/stdc-predef.h
editres.o: /usr/include/x86_64-linux-gnu/sys/cdefs.h
editres.o: /usr/include/x86_64-linux-gnu/bits/wordsize.h
editres.o: /usr/include/x86_64-linux-gnu/bits/long-double.h
editres.o: /usr/include/x86_64-linux-gnu/gnu/stubs.h
editres.o: /usr/lib/gcc/x86_64-linux-gnu/9/include/stddef.h
editres.o: /usr/lib/gcc/x86_64-linux-gnu/9/include/stdarg.h
editres.o: /usr/include/x86_64-linux-gnu/bits/types.h
editres.o: /usr/include/x86_64-linux-gnu/bits/timesize.h
editres.o: /usr/include/x86_64-linux-gnu/bits/typesizes.h
editres.o: /usr/include/x86_64-linux-gnu/bits/time64.h
editres.o: /usr/include/x86_64-linux-gnu/bits/types/__fpos_t.h
editres.o: /usr/include/x86_64-linux-gnu/bits/types/__mbstate_t.h
editres.o: /usr/include/x86_64-linux-gnu/bits/types/__fpos64_t.h
editres.o: /usr/include/x86_64-linux-gnu/bits/types/__FILE.h
editres.o: /usr/include/x86_64-linux-gnu/bits/types/FILE.h
editres.o: /usr/include/x86_64-linux-gnu/bits/types/struct_FILE.h
editres.o: /usr/include/x86_64-linux-gnu/bits/stdio_lim.h
editres.o: /usr/include/x86_64-linux-gnu/bits/sys_errlist.h
editres.o: /usr/include/X11/Intrinsic.h /usr/include/X11/Xlib.h
editres.o: /usr/include/x86_64-linux-gnu/sys/types.h
editres.o: /usr/include/x86_64-linux-gnu/bits/types/clock_t.h
editres.o: /usr/include/x86_64-linux-gnu/bits/types/clockid_t.h
editres.o: /usr/include/x86_64-linux-gnu/bits/types/time_t.h
editres.o: /usr/include/x86_64-linux-gnu/bits/types/timer_t.h
editres.o: /usr/include/x86_64-linux-gnu/bits/stdint-intn.h
editres.o: /usr/include/endian.h /usr/include/x86_64-linux-gnu/bits/endian.h
editres.o: /usr/include/x86_64-linux-gnu/bits/endianness.h
editres.o: /usr/include/x86_64-linux-gnu/bits/byteswap.h
editres.o: /usr/include/x86_64-linux-gnu/bits/uintn-identity.h
editres.o: /usr/include/x86_64-linux-gnu/sys/select.h
editres.o: /usr/include/x86_64-linux-gnu/bits/select.h
editres.o: /usr/include/x86_64-linux-gnu/bits/types/sigset_t.h
editres.o: /usr/include/x86_64-linux-gnu/bits/types/__sigset_t.h
editres.o: /usr/include/x86_64-linux-gnu/bits/types/struct_timeval.h
editres.o: /usr/include/x86_64-linux-gnu/bits/types/struct_timespec.h
editres.o: /usr/include/x86_64-linux-gnu/bits/pthreadtypes.h
editres.o: /usr/include/x86_64-linux-gnu/bits/thread-shared-types.h
editres.o: /usr/include/x86_64-linux-gnu/bits/pthreadtypes-arch.h
editres.o: /usr/include/x86_64-linux-gnu/bits/struct_mutex.h
editres.o: /usr/include/x86_64-linux-gnu/bits/struct_rwlock.h
editres.o: /usr/include/X11/X.h /usr/include/X11/Xfuncproto.h
editres.o: /usr/include/X11/Xosdefs.h /usr/include/X11/Xutil.h
editres.o: /usr/include/X11/keysym.h /usr/include/X11/keysymdef.h
editres.o: /usr/include/X11/Xresource.h /usr/include/string.h
editres.o: /usr/include/x86_64-linux-gnu/bits/types/locale_t.h
editres.o: /usr/include/x86_64-linux-gnu/bits/types/__locale_t.h
editres.o: /usr/include/strings.h /usr/include/X11/Core.h
editres.o: /usr/include/X11/Composite.h /usr/include/X11/Constraint.h
editres.o: /usr/include/X11/Object.h /usr/include/X11/RectObj.h
editres.o: /usr/include/X11/StringDefs.h /usr/include/X11/Xaw/Cardinals.h
editres.o: editresP.h /usr/include/X11/Xmu/EditresP.h
geometry.o: /usr/include/X11/Intrinsic.h /usr/include/X11/Xlib.h
geometry.o: /usr/include/x86_64-linux-gnu/sys/types.h /usr/include/features.h
geometry.o: /usr/include/stdc-predef.h
geometry.o: /usr/include/x86_64-linux-gnu/sys/cdefs.h
geometry.o: /usr/include/x86_64-linux-gnu/bits/wordsize.h
geometry.o: /usr/include/x86_64-linux-gnu/bits/long-double.h
geometry.o: /usr/include/x86_64-linux-gnu/gnu/stubs.h
geometry.o: /usr/include/x86_64-linux-gnu/bits/types.h
geometry.o: /usr/include/x86_64-linux-gnu/bits/timesize.h
geometry.o: /usr/include/x86_64-linux-gnu/bits/typesizes.h
geometry.o: /usr/include/x86_64-linux-gnu/bits/time64.h
geometry.o: /usr/include/x86_64-linux-gnu/bits/types/clock_t.h
geometry.o: /usr/include/x86_64-linux-gnu/bits/types/clockid_t.h
geometry.o: /usr/include/x86_64-linux-gnu/bits/types/time_t.h
geometry.o: /usr/include/x86_64-linux-gnu/bits/types/timer_t.h
geometry.o: /usr/lib/gcc/x86_64-linux-gnu/9/include/stddef.h
geometry.o: /usr/include/x86_64-linux-gnu/bits/stdint-intn.h
geometry.o: /usr/include/endian.h /usr/include/x86_64-linux-gnu/bits/endian.h
geometry.o: /usr/include/x86_64-linux-gnu/bits/endianness.h
geometry.o: /usr/include/x86_64-linux-gnu/bits/byteswap.h
geometry.o: /usr/include/x86_64-linux-gnu/bits/uintn-identity.h
geometry.o: /usr/include/x86_64-linux-gnu/sys/select.h
geometry.o: /usr/include/x86_64-linux-gnu/bits/select.h
geometry.o: /usr/include/x86_64-linux-gnu/bits/types/sigset_t.h
geometry.o: /usr/include/x86_64-linux-gnu/bits/types/__sigset_t.h
geometry.o: /usr/include/x86_64-linux-gnu/bits/types/struct_timeval.h
geometry.o: /usr/include/x86_64-linux-gnu/bits/types/struct_timespec.h
geometry.o: /usr/include/x86_64-linux-gnu/bits/pthreadtypes.h
geometry.o: /usr/include/x86_64-linux-gnu/bits/thread-shared-types.h
geometry.o: /usr/include/x86_64-linux-gnu/bits/pthreadtypes-arch.h
geometry.o: /usr/include/x86_64-linux-gnu/bits/struct_mutex.h
geometry.o: /usr/include/x86_64-linux-gnu/bits/struct_rwlock.h
geometry.o: /usr/include/X11/X.h /usr/include/X11/Xfuncproto.h
geometry.o: /usr/include/X11/Xosdefs.h /usr/include/X11/Xutil.h
geometry.o: /usr/include/X11/keysym.h /usr/include/X11/keysymdef.h
geometry.o: /usr/include/X11/Xresource.h /usr/include/string.h
geometry.o: /usr/include/x86_64-linux-gnu/bits/libc-header-start.h
geometry.o: /usr/include/x86_64-linux-gnu/bits/types/locale_t.h
geometry.o: /usr/include/x86_64-linux-gnu/bits/types/__locale_t.h
geometry.o: /usr/include/strings.h /usr/include/X11/Core.h
geometry.o: /usr/include/X11/Composite.h /usr/include/X11/Constraint.h
geometry.o: /usr/include/X11/Object.h /usr/include/X11/RectObj.h
geometry.o: /usr/include/X11/StringDefs.h /usr/include/X11/Shell.h
geometry.o: /usr/include/X11/SM/SMlib.h /usr/include/X11/SM/SM.h
geometry.o: /usr/include/X11/ICE/ICElib.h /usr/include/X11/ICE/ICE.h
geometry.o: /usr/include/stdio.h
geometry.o: /usr/lib/gcc/x86_64-linux-gnu/9/include/stdarg.h
geometry.o: /usr/include/x86_64-linux-gnu/bits/types/__fpos_t.h
geometry.o: /usr/include/x86_64-linux-gnu/bits/types/__mbstate_t.h
geometry.o: /usr/include/x86_64-linux-gnu/bits/types/__fpos64_t.h
geometry.o: /usr/include/x86_64-linux-gnu/bits/types/__FILE.h
geometry.o: /usr/include/x86_64-linux-gnu/bits/types/FILE.h
geometry.o: /usr/include/x86_64-linux-gnu/bits/types/struct_FILE.h
geometry.o: /usr/include/x86_64-linux-gnu/bits/stdio_lim.h
geometry.o: /usr/include/x86_64-linux-gnu/bits/sys_errlist.h
geometry.o: /usr/include/X11/Xaw/Cardinals.h editresP.h
geometry.o: /usr/include/X11/Xmu/EditresP.h
handler.o: /usr/include/X11/Intrinsic.h /usr/include/X11/Xlib.h
handler.o: /usr/include/x86_64-linux-gnu/sys/types.h /usr/include/features.h
handler.o: /usr/include/stdc-predef.h
handler.o: /usr/include/x86_64-linux-gnu/sys/cdefs.h
handler.o: /usr/include/x86_64-linux-gnu/bits/wordsize.h
handler.o: /usr/include/x86_64-linux-gnu/bits/long-double.h
handler.o: /usr/include/x86_64-linux-gnu/gnu/stubs.h
handler.o: /usr/include/x86_64-linux-gnu/bits/types.h
handler.o: /usr/include/x86_64-linux-gnu/bits/timesize.h
handler.o: /usr/include/x86_64-linux-gnu/bits/typesizes.h
handler.o: /usr/include/x86_64-linux-gnu/bits/time64.h
handler.o: /usr/include/x86_64-linux-gnu/bits/types/clock_t.h
handler.o: /usr/include/x86_64-linux-gnu/bits/types/clockid_t.h
handler.o: /usr/include/x86_64-linux-gnu/bits/types/time_t.h
handler.o: /usr/include/x86_64-linux-gnu/bits/types/timer_t.h
handler.o: /usr/lib/gcc/x86_64-linux-gnu/9/include/stddef.h
handler.o: /usr/include/x86_64-linux-gnu/bits/stdint-intn.h
handler.o: /usr/include/endian.h /usr/include/x86_64-linux-gnu/bits/endian.h
handler.o: /usr/include/x86_64-linux-gnu/bits/endianness.h
handler.o: /usr/include/x86_64-linux-gnu/bits/byteswap.h
handler.o: /usr/include/x86_64-linux-gnu/bits/uintn-identity.h
handler.o: /usr/include/x86_64-linux-gnu/sys/select.h
handler.o: /usr/include/x86_64-linux-gnu/bits/select.h
handler.o: /usr/include/x86_64-linux-gnu/bits/types/sigset_t.h
handler.o: /usr/include/x86_64-linux-gnu/bits/types/__sigset_t.h
handler.o: /usr/include/x86_64-linux-gnu/bits/types/struct_timeval.h
handler.o: /usr/include/x86_64-linux-gnu/bits/types/struct_timespec.h
handler.o: /usr/include/x86_64-linux-gnu/bits/pthreadtypes.h
handler.o: /usr/include/x86_64-linux-gnu/bits/thread-shared-types.h
handler.o: /usr/include/x86_64-linux-gnu/bits/pthreadtypes-arch.h
handler.o: /usr/include/x86_64-linux-gnu/bits/struct_mutex.h
handler.o: /usr/include/x86_64-linux-gnu/bits/struct_rwlock.h
handler.o: /usr/include/X11/X.h /usr/include/X11/Xfuncproto.h
handler.o: /usr/include/X11/Xosdefs.h /usr/include/X11/Xutil.h
handler.o: /usr/include/X11/keysym.h /usr/include/X11/keysymdef.h
handler.o: /usr/include/X11/Xresource.h /usr/include/string.h
handler.o: /usr/include/x86_64-linux-gnu/bits/libc-header-start.h
handler.o: /usr/include/x86_64-linux-gnu/bits/types/locale_t.h
handler.o: /usr/include/x86_64-linux-gnu/bits/types/__locale_t.h
handler.o: /usr/include/strings.h /usr/include/X11/Core.h
handler.o: /usr/include/X11/Composite.h /usr/include/X11/Constraint.h
handler.o: /usr/include/X11/Object.h /usr/include/X11/RectObj.h
handler.o: /usr/include/X11/StringDefs.h /usr/include/X11/Xaw/Cardinals.h
handler.o: /usr/include/X11/Xaw/List.h /usr/include/X11/Xaw/Simple.h
handler.o: /usr/include/X11/Xmu/Converters.h /usr/include/X11/Xaw/Panner.h
handler.o: /usr/include/X11/Xaw/Reports.h /usr/include/X11/Xaw/Toggle.h
handler.o: /usr/include/X11/Xaw/Command.h /usr/include/X11/Xaw/Label.h
handler.o: /usr/include/X11/Xfuncs.h /usr/include/X11/Xos.h
handler.o: /usr/include/fcntl.h /usr/include/x86_64-linux-gnu/bits/fcntl.h
handler.o: /usr/include/x86_64-linux-gnu/bits/fcntl-linux.h
handler.o: /usr/include/x86_64-linux-gnu/bits/stat.h /usr/include/unistd.h
handler.o: /usr/include/x86_64-linux-gnu/bits/posix_opt.h
handler.o: /usr/include/x86_64-linux-gnu/bits/environments.h
handler.o: /usr/include/x86_64-linux-gnu/bits/confname.h
handler.o: /usr/include/x86_64-linux-gnu/bits/getopt_posix.h
handler.o: /usr/include/x86_64-linux-gnu/bits/getopt_core.h
handler.o: /usr/include/x86_64-linux-gnu/bits/unistd_ext.h
handler.o: /usr/include/x86_64-linux-gnu/sys/time.h /usr/include/time.h
handler.o: /usr/include/x86_64-linux-gnu/bits/time.h
handler.o: /usr/include/x86_64-linux-gnu/bits/types/struct_tm.h
handler.o: /usr/include/x86_64-linux-gnu/bits/types/struct_itimerspec.h
handler.o: /usr/include/X11/Xarch.h /usr/include/stdio.h
handler.o: /usr/lib/gcc/x86_64-linux-gnu/9/include/stdarg.h
handler.o: /usr/include/x86_64-linux-gnu/bits/types/__fpos_t.h
handler.o: /usr/include/x86_64-linux-gnu/bits/types/__mbstate_t.h
handler.o: /usr/include/x86_64-linux-gnu/bits/types/__fpos64_t.h
handler.o: /usr/include/x86_64-linux-gnu/bits/types/__FILE.h
handler.o: /usr/include/x86_64-linux-gnu/bits/types/FILE.h
handler.o: /usr/include/x86_64-linux-gnu/bits/types/struct_FILE.h
handler.o: /usr/include/x86_64-linux-gnu/bits/stdio_lim.h
handler.o: /usr/include/x86_64-linux-gnu/bits/sys_errlist.h editresP.h
handler.o: /usr/include/X11/Xmu/EditresP.h
setvalues.o: /usr/include/X11/Intrinsic.h /usr/include/X11/Xlib.h
setvalues.o: /usr/include/x86_64-linux-gnu/sys/types.h
setvalues.o: /usr/include/features.h /usr/include/stdc-predef.h
setvalues.o: /usr/include/x86_64-linux-gnu/sys/cdefs.h
setvalues.o: /usr/include/x86_64-linux-gnu/bits/wordsize.h
setvalues.o: /usr/include/x86_64-linux-gnu/bits/long-double.h
setvalues.o: /usr/include/x86_64-linux-gnu/gnu/stubs.h
setvalues.o: /usr/include/x86_64-linux-gnu/bits/types.h
setvalues.o: /usr/include/x86_64-linux-gnu/bits/timesize.h
setvalues.o: /usr/include/x86_64-linux-gnu/bits/typesizes.h
setvalues.o: /usr/include/x86_64-linux-gnu/bits/time64.h
setvalues.o: /usr/include/x86_64-linux-gnu/bits/types/clock_t.h
setvalues.o: /usr/include/x86_64-linux-gnu/bits/types/clockid_t.h
setvalues.o: /usr/include/x86_64-linux-gnu/bits/types/time_t.h
setvalues.o: /usr/include/x86_64-linux-gnu/bits/types/timer_t.h
setvalues.o: /usr/lib/gcc/x86_64-linux-gnu/9/include/stddef.h
setvalues.o: /usr/include/x86_64-linux-gnu/bits/stdint-intn.h
setvalues.o: /usr/include/endian.h
setvalues.o: /usr/include/x86_64-linux-gnu/bits/endian.h
setvalues.o: /usr/include/x86_64-linux-gnu/bits/endianness.h
setvalues.o: /usr/include/x86_64-linux-gnu/bits/byteswap.h
setvalues.o: /usr/include/x86_64-linux-gnu/bits/uintn-identity.h
setvalues.o: /usr/include/x86_64-linux-gnu/sys/select.h
setvalues.o: /usr/include/x86_64-linux-gnu/bits/select.h
setvalues.o: /usr/include/x86_64-linux-gnu/bits/types/sigset_t.h
setvalues.o: /usr/include/x86_64-linux-gnu/bits/types/__sigset_t.h
setvalues.o: /usr/include/x86_64-linux-gnu/bits/types/struct_timeval.h
setvalues.o: /usr/include/x86_64-linux-gnu/bits/types/struct_timespec.h
setvalues.o: /usr/include/x86_64-linux-gnu/bits/pthreadtypes.h
setvalues.o: /usr/include/x86_64-linux-gnu/bits/thread-shared-types.h
setvalues.o: /usr/include/x86_64-linux-gnu/bits/pthreadtypes-arch.h
setvalues.o: /usr/include/x86_64-linux-gnu/bits/struct_mutex.h
setvalues.o: /usr/include/x86_64-linux-gnu/bits/struct_rwlock.h
setvalues.o: /usr/include/X11/X.h /usr/include/X11/Xfuncproto.h
setvalues.o: /usr/include/X11/Xosdefs.h /usr/include/X11/Xutil.h
setvalues.o: /usr/include/X11/keysym.h /usr/include/X11/keysymdef.h
setvalues.o: /usr/include/X11/Xresource.h /usr/include/string.h
setvalues.o: /usr/include/x86_64-linux-gnu/bits/libc-header-start.h
setvalues.o: /usr/include/x86_64-linux-gnu/bits/types/locale_t.h
setvalues.o: /usr/include/x86_64-linux-gnu/bits/types/__locale_t.h
setvalues.o: /usr/include/strings.h /usr/include/X11/Core.h
setvalues.o: /usr/include/X11/Composite.h /usr/include/X11/Constraint.h
setvalues.o: /usr/include/X11/Object.h /usr/include/X11/RectObj.h
setvalues.o: /usr/include/X11/StringDefs.h /usr/include/stdio.h
setvalues.o: /usr/lib/gcc/x86_64-linux-gnu/9/include/stdarg.h
setvalues.o: /usr/include/x86_64-linux-gnu/bits/types/__fpos_t.h
setvalues.o: /usr/include/x86_64-linux-gnu/bits/types/__mbstate_t.h
setvalues.o: /usr/include/x86_64-linux-gnu/bits/types/__fpos64_t.h
setvalues.o: /usr/include/x86_64-linux-gnu/bits/types/__FILE.h
setvalues.o: /usr/include/x86_64-linux-gnu/bits/types/FILE.h
setvalues.o: /usr/include/x86_64-linux-gnu/bits/types/struct_FILE.h
setvalues.o: /usr/include/x86_64-linux-gnu/bits/stdio_lim.h
setvalues.o: /usr/include/x86_64-linux-gnu/bits/sys_errlist.h
setvalues.o: /usr/include/X11/Xaw/AsciiText.h /usr/include/X11/Xaw/Text.h
setvalues.o: /usr/include/X11/Xaw/Simple.h /usr/include/X11/Xmu/Converters.h
setvalues.o: /usr/include/X11/Xaw/TextSink.h /usr/include/X11/Xaw/TextSrc.h
setvalues.o: /usr/include/X11/Xaw/AsciiSrc.h /usr/include/X11/Xaw/AsciiSink.h
setvalues.o: /usr/include/X11/Xaw/MultiSrc.h /usr/include/X11/Xaw/Cardinals.h
setvalues.o: /usr/include/X11/Xfuncs.h /usr/include/X11/Xos.h
setvalues.o: /usr/include/fcntl.h /usr/include/x86_64-linux-gnu/bits/fcntl.h
setvalues.o: /usr/include/x86_64-linux-gnu/bits/fcntl-linux.h
setvalues.o: /usr/include/x86_64-linux-gnu/bits/stat.h /usr/include/unistd.h
setvalues.o: /usr/include/x86_64-linux-gnu/bits/posix_opt.h
setvalues.o: /usr/include/x86_64-linux-gnu/bits/environments.h
setvalues.o: /usr/include/x86_64-linux-gnu/bits/confname.h
setvalues.o: /usr/include/x86_64-linux-gnu/bits/getopt_posix.h
setvalues.o: /usr/include/x86_64-linux-gnu/bits/getopt_core.h
setvalues.o: /usr/include/x86_64-linux-gnu/bits/unistd_ext.h
setvalues.o: /usr/include/x86_64-linux-gnu/sys/time.h /usr/include/time.h
setvalues.o: /usr/include/x86_64-linux-gnu/bits/time.h
setvalues.o: /usr/include/x86_64-linux-gnu/bits/types/struct_tm.h
setvalues.o: /usr/include/x86_64-linux-gnu/bits/types/struct_itimerspec.h
setvalues.o: /usr/include/X11/Xarch.h editresP.h
setvalues.o: /usr/include/X11/Xmu/EditresP.h
svpopup.o: /usr/include/X11/Intrinsic.h /usr/include/X11/Xlib.h
svpopup.o: /usr/include/x86_64-linux-gnu/sys/types.h /usr/include/features.h
svpopup.o: /usr/include/stdc-predef.h
svpopup.o: /usr/include/x86_64-linux-gnu/sys/cdefs.h
svpopup.o: /usr/include/x86_64-linux-gnu/bits/wordsize.h
svpopup.o: /usr/include/x86_64-linux-gnu/bits/long-double.h
svpopup.o: /usr/include/x86_64-linux-gnu/gnu/stubs.h
svpopup.o: /usr/include/x86_64-linux-gnu/bits/types.h
svpopup.o: /usr/include/x86_64-linux-gnu/bits/timesize.h
svpopup.o: /usr/include/x86_64-linux-gnu/bits/typesizes.h
svpopup.o: /usr/include/x86_64-linux-gnu/bits/time64.h
svpopup.o: /usr/include/x86_64-linux-gnu/bits/types/clock_t.h
svpopup.o: /usr/include/x86_64-linux-gnu/bits/types/clockid_t.h
svpopup.o: /usr/include/x86_64-linux-gnu/bits/types/time_t.h
svpopup.o: /usr/include/x86_64-linux-gnu/bits/types/timer_t.h
svpopup.o: /usr/lib/gcc/x86_64-linux-gnu/9/include/stddef.h
svpopup.o: /usr/include/x86_64-linux-gnu/bits/stdint-intn.h
svpopup.o: /usr/include/endian.h /usr/include/x86_64-linux-gnu/bits/endian.h
svpopup.o: /usr/include/x86_64-linux-gnu/bits/endianness.h
svpopup.o: /usr/include/x86_64-linux-gnu/bits/byteswap.h
svpopup.o: /usr/include/x86_64-linux-gnu/bits/uintn-identity.h
svpopup.o: /usr/include/x86_64-linux-gnu/sys/select.h
svpopup.o: /usr/include/x86_64-linux-gnu/bits/select.h
svpopup.o: /usr/include/x86_64-linux-gnu/bits/types/sigset_t.h
svpopup.o: /usr/include/x86_64-linux-gnu/bits/types/__sigset_t.h
svpopup.o: /usr/include/x86_64-linux-gnu/bits/types/struct_timeval.h
svpopup.o: /usr/include/x86_64-linux-gnu/bits/types/struct_timespec.h
svpopup.o: /usr/include/x86_64-linux-gnu/bits/pthreadtypes.h
svpopup.o: /usr/include/x86_64-linux-gnu/bits/thread-shared-types.h
svpopup.o: /usr/include/x86_64-linux-gnu/bits/pthreadtypes-arch.h
svpopup.o: /usr/include/x86_64-linux-gnu/bits/struct_mutex.h
svpopup.o: /usr/include/x86_64-linux-gnu/bits/struct_rwlock.h
svpopup.o: /usr/include/X11/X.h /usr/include/X11/Xfuncproto.h
svpopup.o: /usr/include/X11/Xosdefs.h /usr/include/X11/Xutil.h
svpopup.o: /usr/include/X11/keysym.h /usr/include/X11/keysymdef.h
svpopup.o: /usr/include/X11/Xresource.h /usr/include/string.h
svpopup.o: /usr/include/x86_64-linux-gnu/bits/libc-header-start.h
svpopup.o: /usr/include/x86_64-linux-gnu/bits/types/locale_t.h
svpopup.o: /usr/include/x86_64-linux-gnu/bits/types/__locale_t.h
svpopup.o: /usr/include/strings.h /usr/include/X11/Core.h
svpopup.o: /usr/include/X11/Composite.h /usr/include/X11/Constraint.h
svpopup.o: /usr/include/X11/Object.h /usr/include/X11/RectObj.h
svpopup.o: /usr/include/X11/StringDefs.h /usr/include/X11/Xatom.h
svpopup.o: /usr/include/X11/cursorfont.h /usr/include/X11/Shell.h
svpopup.o: /usr/include/X11/SM/SMlib.h /usr/include/X11/SM/SM.h
svpopup.o: /usr/include/X11/ICE/ICElib.h /usr/include/X11/ICE/ICE.h
svpopup.o: editresP.h /usr/include/X11/Xmu/EditresP.h
svpopup.o: /usr/include/X11/Xaw/AsciiText.h /usr/include/X11/Xaw/Text.h
svpopup.o: /usr/include/X11/Xaw/Simple.h /usr/include/X11/Xmu/Converters.h
svpopup.o: /usr/include/X11/Xaw/TextSink.h /usr/include/X11/Xaw/TextSrc.h
svpopup.o: /usr/include/X11/Xaw/AsciiSrc.h /usr/include/X11/Xaw/AsciiSink.h
svpopup.o: /usr/include/X11/Xaw/MultiSrc.h /usr/include/X11/Xaw/Cardinals.h
svpopup.o: /usr/include/X11/Xaw/Command.h /usr/include/X11/Xaw/Label.h
svpopup.o: /usr/include/X11/Xaw/Form.h /usr/include/stdio.h
svpopup.o: /usr/lib/gcc/x86_64-linux-gnu/9/include/stdarg.h
svpopup.o: /usr/include/x86_64-linux-gnu/bits/types/__fpos_t.h
svpopup.o: /usr/include/x86_64-linux-gnu/bits/types/__mbstate_t.h
svpopup.o: /usr/include/x86_64-linux-gnu/bits/types/__fpos64_t.h
svpopup.o: /usr/include/x86_64-linux-gnu/bits/types/__FILE.h
svpopup.o: /usr/include/x86_64-linux-gnu/bits/types/FILE.h
svpopup.o: /usr/include/x86_64-linux-gnu/bits/types/struct_FILE.h
svpopup.o: /usr/include/x86_64-linux-gnu/bits/stdio_lim.h
svpopup.o: /usr/include/x86_64-linux-gnu/bits/sys_errlist.h
utils.o: /usr/include/X11/Intrinsic.h /usr/include/X11/Xlib.h
utils.o: /usr/include/x86_64-linux-gnu/sys/types.h /usr/include/features.h
utils.o: /usr/include/stdc-predef.h /usr/include/x86_64-linux-gnu/sys/cdefs.h
utils.o: /usr/include/x86_64-linux-gnu/bits/wordsize.h
utils.o: /usr/include/x86_64-linux-gnu/bits/long-double.h
utils.o: /usr/include/x86_64-linux-gnu/gnu/stubs.h
utils.o: /usr/include/x86_64-linux-gnu/bits/types.h
utils.o: /usr/include/x86_64-linux-gnu/bits/timesize.h
utils.o: /usr/include/x86_64-linux-gnu/bits/typesizes.h
utils.o: /usr/include/x86_64-linux-gnu/bits/time64.h
utils.o: /usr/include/x86_64-linux-gnu/bits/types/clock_t.h
utils.o: /usr/include/x86_64-linux-gnu/bits/types/clockid_t.h
utils.o: /usr/include/x86_64-linux-gnu/bits/types/time_t.h
utils.o: /usr/include/x86_64-linux-gnu/bits/types/timer_t.h
utils.o: /usr/lib/gcc/x86_64-linux-gnu/9/include/stddef.h
utils.o: /usr/include/x86_64-linux-gnu/bits/stdint-intn.h
utils.o: /usr/include/endian.h /usr/include/x86_64-linux-gnu/bits/endian.h
utils.o: /usr/include/x86_64-linux-gnu/bits/endianness.h
utils.o: /usr/include/x86_64-linux-gnu/bits/byteswap.h
utils.o: /usr/include/x86_64-linux-gnu/bits/uintn-identity.h
utils.o: /usr/include/x86_64-linux-gnu/sys/select.h
utils.o: /usr/include/x86_64-linux-gnu/bits/select.h
utils.o: /usr/include/x86_64-linux-gnu/bits/types/sigset_t.h
utils.o: /usr/include/x86_64-linux-gnu/bits/types/__sigset_t.h
utils.o: /usr/include/x86_64-linux-gnu/bits/types/struct_timeval.h
utils.o: /usr/include/x86_64-linux-gnu/bits/types/struct_timespec.h
utils.o: /usr/include/x86_64-linux-gnu/bits/pthreadtypes.h
utils.o: /usr/include/x86_64-linux-gnu/bits/thread-shared-types.h
utils.o: /usr/include/x86_64-linux-gnu/bits/pthreadtypes-arch.h
utils.o: /usr/include/x86_64-linux-gnu/bits/struct_mutex.h
utils.o: /usr/include/x86_64-linux-gnu/bits/struct_rwlock.h
utils.o: /usr/include/X11/X.h /usr/include/X11/Xfuncproto.h
utils.o: /usr/include/X11/Xosdefs.h /usr/include/X11/Xutil.h
utils.o: /usr/include/X11/keysym.h /usr/include/X11/keysymdef.h
utils.o: /usr/include/X11/Xresource.h /usr/include/string.h
utils.o: /usr/include/x86_64-linux-gnu/bits/libc-header-start.h
utils.o: /usr/include/x86_64-linux-gnu/bits/types/locale_t.h
utils.o: /usr/include/x86_64-linux-gnu/bits/types/__locale_t.h
utils.o: /usr/include/strings.h /usr/include/X11/Core.h
utils.o: /usr/include/X11/Composite.h /usr/include/X11/Constraint.h
utils.o: /usr/include/X11/Object.h /usr/include/X11/RectObj.h
utils.o: /usr/include/X11/Xos.h /usr/include/fcntl.h
utils.o: /usr/include/x86_64-linux-gnu/bits/fcntl.h
utils.o: /usr/include/x86_64-linux-gnu/bits/fcntl-linux.h
utils.o: /usr/include/x86_64-linux-gnu/bits/stat.h /usr/include/unistd.h
utils.o: /usr/include/x86_64-linux-gnu/bits/posix_opt.h
utils.o: /usr/include/x86_64-linux-gnu/bits/environments.h
utils.o: /usr/include/x86_64-linux-gnu/bits/confname.h
utils.o: /usr/include/x86_64-linux-gnu/bits/getopt_posix.h
utils.o: /usr/include/x86_64-linux-gnu/bits/getopt_core.h
utils.o: /usr/include/x86_64-linux-gnu/bits/unistd_ext.h
utils.o: /usr/include/x86_64-linux-gnu/sys/time.h /usr/include/time.h
utils.o: /usr/include/x86_64-linux-gnu/bits/time.h
utils.o: /usr/include/x86_64-linux-gnu/bits/types/struct_tm.h
utils.o: /usr/include/x86_64-linux-gnu/bits/types/struct_itimerspec.h
utils.o: /usr/include/X11/Xarch.h /usr/include/X11/Shell.h
utils.o: /usr/include/X11/SM/SMlib.h /usr/include/X11/SM/SM.h
utils.o: /usr/include/X11/ICE/ICElib.h /usr/include/X11/ICE/ICE.h
utils.o: /usr/include/X11/StringDefs.h /usr/include/X11/Xaw/Cardinals.h
utils.o: /usr/include/X11/Xaw/Dialog.h /usr/include/X11/Xaw/Form.h
utils.o: /usr/include/X11/Xmu/Error.h /usr/include/stdio.h
utils.o: /usr/lib/gcc/x86_64-linux-gnu/9/include/stdarg.h
utils.o: /usr/include/x86_64-linux-gnu/bits/types/__fpos_t.h
utils.o: /usr/include/x86_64-linux-gnu/bits/types/__mbstate_t.h
utils.o: /usr/include/x86_64-linux-gnu/bits/types/__fpos64_t.h
utils.o: /usr/include/x86_64-linux-gnu/bits/types/__FILE.h
utils.o: /usr/include/x86_64-linux-gnu/bits/types/FILE.h
utils.o: /usr/include/x86_64-linux-gnu/bits/types/struct_FILE.h
utils.o: /usr/include/x86_64-linux-gnu/bits/stdio_lim.h
utils.o: /usr/include/x86_64-linux-gnu/bits/sys_errlist.h
utils.o: /usr/include/stdlib.h /usr/include/x86_64-linux-gnu/bits/waitflags.h
utils.o: /usr/include/x86_64-linux-gnu/bits/waitstatus.h
utils.o: /usr/include/x86_64-linux-gnu/bits/floatn.h
utils.o: /usr/include/x86_64-linux-gnu/bits/floatn-common.h
utils.o: /usr/include/alloca.h
utils.o: /usr/include/x86_64-linux-gnu/bits/stdlib-float.h editresP.h
utils.o: /usr/include/X11/Xmu/EditresP.h
widgets.o: /usr/include/stdio.h
widgets.o: /usr/include/x86_64-linux-gnu/bits/libc-header-start.h
widgets.o: /usr/include/features.h /usr/include/stdc-predef.h
widgets.o: /usr/include/x86_64-linux-gnu/sys/cdefs.h
widgets.o: /usr/include/x86_64-linux-gnu/bits/wordsize.h
widgets.o: /usr/include/x86_64-linux-gnu/bits/long-double.h
widgets.o: /usr/include/x86_64-linux-gnu/gnu/stubs.h
widgets.o: /usr/lib/gcc/x86_64-linux-gnu/9/include/stddef.h
widgets.o: /usr/lib/gcc/x86_64-linux-gnu/9/include/stdarg.h
widgets.o: /usr/include/x86_64-linux-gnu/bits/types.h
widgets.o: /usr/include/x86_64-linux-gnu/bits/timesize.h
widgets.o: /usr/include/x86_64-linux-gnu/bits/typesizes.h
widgets.o: /usr/include/x86_64-linux-gnu/bits/time64.h
widgets.o: /usr/include/x86_64-linux-gnu/bits/types/__fpos_t.h
widgets.o: /usr/include/x86_64-linux-gnu/bits/types/__mbstate_t.h
widgets.o: /usr/include/x86_64-linux-gnu/bits/types/__fpos64_t.h
widgets.o: /usr/include/x86_64-linux-gnu/bits/types/__FILE.h
widgets.o: /usr/include/x86_64-linux-gnu/bits/types/FILE.h
widgets.o: /usr/include/x86_64-linux-gnu/bits/types/struct_FILE.h
widgets.o: /usr/include/x86_64-linux-gnu/bits/stdio_lim.h
widgets.o: /usr/include/x86_64-linux-gnu/bits/sys_errlist.h
widgets.o: /usr/include/X11/Intrinsic.h /usr/include/X11/Xlib.h
widgets.o: /usr/include/x86_64-linux-gnu/sys/types.h
widgets.o: /usr/include/x86_64-linux-gnu/bits/types/clock_t.h
widgets.o: /usr/include/x86_64-linux-gnu/bits/types/clockid_t.h
widgets.o: /usr/include/x86_64-linux-gnu/bits/types/time_t.h
widgets.o: /usr/include/x86_64-linux-gnu/bits/types/timer_t.h
widgets.o: /usr/include/x86_64-linux-gnu/bits/stdint-intn.h
widgets.o: /usr/include/endian.h /usr/include/x86_64-linux-gnu/bits/endian.h
widgets.o: /usr/include/x86_64-linux-gnu/bits/endianness.h
widgets.o: /usr/include/x86_64-linux-gnu/bits/byteswap.h
widgets.o: /usr/include/x86_64-linux-gnu/bits/uintn-identity.h
widgets.o: /usr/include/x86_64-linux-gnu/sys/select.h
widgets.o: /usr/include/x86_64-linux-gnu/bits/select.h
widgets.o: /usr/include/x86_64-linux-gnu/bits/types/sigset_t.h
widgets.o: /usr/include/x86_64-linux-gnu/bits/types/__sigset_t.h
widgets.o: /usr/include/x86_64-linux-gnu/bits/types/struct_timeval.h
widgets.o: /usr/include/x86_64-linux-gnu/bits/types/struct_timespec.h
widgets.o: /usr/include/x86_64-linux-gnu/bits/pthreadtypes.h
widgets.o: /usr/include/x86_64-linux-gnu/bits/thread-shared-types.h
widgets.o: /usr/include/x86_64-linux-gnu/bits/pthreadtypes-arch.h
widgets.o: /usr/include/x86_64-linux-gnu/bits/struct_mutex.h
widgets.o: /usr/include/x86_64-linux-gnu/bits/struct_rwlock.h
widgets.o: /usr/include/X11/X.h /usr/include/X11/Xfuncproto.h
widgets.o: /usr/include/X11/Xosdefs.h /usr/include/X11/Xutil.h
widgets.o: /usr/include/X11/keysym.h /usr/include/X11/keysymdef.h
widgets.o: /usr/include/X11/Xresource.h /usr/include/string.h
widgets.o: /usr/include/x86_64-linux-gnu/bits/types/locale_t.h
widgets.o: /usr/include/x86_64-linux-gnu/bits/types/__locale_t.h
widgets.o: /usr/include/strings.h /usr/include/X11/Core.h
widgets.o: /usr/include/X11/Composite.h /usr/include/X11/Constraint.h
widgets.o: /usr/include/X11/Object.h /usr/include/X11/RectObj.h
widgets.o: /usr/include/X11/StringDefs.h /usr/include/X11/Xaw/AsciiText.h
widgets.o: /usr/include/X11/Xaw/Text.h /usr/include/X11/Xaw/Simple.h
widgets.o: /usr/include/X11/Xmu/Converters.h /usr/include/X11/Xaw/TextSink.h
widgets.o: /usr/include/X11/Xaw/TextSrc.h /usr/include/X11/Xaw/AsciiSrc.h
widgets.o: /usr/include/X11/Xaw/AsciiSink.h /usr/include/X11/Xaw/MultiSrc.h
widgets.o: /usr/include/X11/Xaw/Box.h /usr/include/X11/Xaw/Cardinals.h
widgets.o: /usr/include/X11/Xaw/Label.h /usr/include/X11/Xaw/List.h
widgets.o: /usr/include/X11/Xaw/MenuButton.h /usr/include/X11/Xaw/Command.h
widgets.o: /usr/include/X11/Xaw/Paned.h /usr/include/X11/Xaw/Panner.h
widgets.o: /usr/include/X11/Xaw/Reports.h /usr/include/X11/Xaw/Porthole.h
widgets.o: /usr/include/X11/Xaw/SmeBSB.h /usr/include/X11/Xaw/Sme.h
widgets.o: /usr/include/X11/Xaw/SmeLine.h /usr/include/X11/Xaw/SimpleMenu.h
widgets.o: /usr/include/X11/Shell.h /usr/include/X11/SM/SMlib.h
widgets.o: /usr/include/X11/SM/SM.h /usr/include/X11/ICE/ICElib.h
widgets.o: /usr/include/X11/ICE/ICE.h /usr/include/X11/Xaw/Toggle.h
widgets.o: /usr/include/X11/Xaw/Tree.h /usr/include/X11/Xaw/Viewport.h
widgets.o: /usr/include/X11/Xaw/Form.h editresP.h
widgets.o: /usr/include/X11/Xmu/EditresP.h
wtree.o: /usr/include/stdio.h
wtree.o: /usr/include/x86_64-linux-gnu/bits/libc-header-start.h
wtree.o: /usr/include/features.h /usr/include/stdc-predef.h
wtree.o: /usr/include/x86_64-linux-gnu/sys/cdefs.h
wtree.o: /usr/include/x86_64-linux-gnu/bits/wordsize.h
wtree.o: /usr/include/x86_64-linux-gnu/bits/long-double.h
wtree.o: /usr/include/x86_64-linux-gnu/gnu/stubs.h
wtree.o: /usr/lib/gcc/x86_64-linux-gnu/9/include/stddef.h
wtree.o: /usr/lib/gcc/x86_64-linux-gnu/9/include/stdarg.h
wtree.o: /usr/include/x86_64-linux-gnu/bits/types.h
wtree.o: /usr/include/x86_64-linux-gnu/bits/timesize.h
wtree.o: /usr/include/x86_64-linux-gnu/bits/typesizes.h
wtree.o: /usr/include/x86_64-linux-gnu/bits/time64.h
wtree.o: /usr/include/x86_64-linux-gnu/bits/types/__fpos_t.h
wtree.o: /usr/include/x86_64-linux-gnu/bits/types/__mbstate_t.h
wtree.o: /usr/include/x86_64-linux-gnu/bits/types/__fpos64_t.h
wtree.o: /usr/include/x86_64-linux-gnu/bits/types/__FILE.h
wtree.o: /usr/include/x86_64-linux-gnu/bits/types/FILE.h
wtree.o: /usr/include/x86_64-linux-gnu/bits/types/struct_FILE.h
wtree.o: /usr/include/x86_64-linux-gnu/bits/stdio_lim.h
wtree.o: /usr/include/x86_64-linux-gnu/bits/sys_errlist.h
wtree.o: /usr/include/X11/Intrinsic.h /usr/include/X11/Xlib.h
wtree.o: /usr/include/x86_64-linux-gnu/sys/types.h
wtree.o: /usr/include/x86_64-linux-gnu/bits/types/clock_t.h
wtree.o: /usr/include/x86_64-linux-gnu/bits/types/clockid_t.h
wtree.o: /usr/include/x86_64-linux-gnu/bits/types/time_t.h
wtree.o: /usr/include/x86_64-linux-gnu/bits/types/timer_t.h
wtree.o: /usr/include/x86_64-linux-gnu/bits/stdint-intn.h
wtree.o: /usr/include/endian.h /usr/include/x86_64-linux-gnu/bits/endian.h
wtree.o: /usr/include/x86_64-linux-gnu/bits/endianness.h
wtree.o: /usr/include/x86_64-linux-gnu/bits/byteswap.h
wtree.o: /usr/include/x86_64-linux-gnu/bits/uintn-identity.h
wtree.o: /usr/include/x86_64-linux-gnu/sys/select.h
wtree.o: /usr/include/x86_64-linux-gnu/bits/select.h
wtree.o: /usr/include/x86_64-linux-gnu/bits/types/sigset_t.h
wtree.o: /usr/include/x86_64-linux-gnu/bits/types/__sigset_t.h
wtree.o: /usr/include/x86_64-linux-gnu/bits/types/struct_timeval.h
wtree.o: /usr/include/x86_64-linux-gnu/bits/types/struct_timespec.h
wtree.o: /usr/include/x86_64-linux-gnu/bits/pthreadtypes.h
wtree.o: /usr/include/x86_64-linux-gnu/bits/thread-shared-types.h
wtree.o: /usr/include/x86_64-linux-gnu/bits/pthreadtypes-arch.h
wtree.o: /usr/include/x86_64-linux-gnu/bits/struct_mutex.h
wtree.o: /usr/include/x86_64-linux-gnu/bits/struct_rwlock.h
wtree.o: /usr/include/X11/X.h /usr/include/X11/Xfuncproto.h
wtree.o: /usr/include/X11/Xosdefs.h /usr/include/X11/Xutil.h
wtree.o: /usr/include/X11/keysym.h /usr/include/X11/keysymdef.h
wtree.o: /usr/include/X11/Xresource.h /usr/include/string.h
wtree.o: /usr/include/x86_64-linux-gnu/bits/types/locale_t.h
wtree.o: /usr/include/x86_64-linux-gnu/bits/types/__locale_t.h
wtree.o: /usr/include/strings.h /usr/include/X11/Core.h
wtree.o: /usr/include/X11/Composite.h /usr/include/X11/Constraint.h
wtree.o: /usr/include/X11/Object.h /usr/include/X11/RectObj.h
wtree.o: /usr/include/X11/StringDefs.h /usr/include/X11/Xaw/Cardinals.h
wtree.o: /usr/include/X11/Xaw/Toggle.h /usr/include/X11/Xaw/Command.h
wtree.o: /usr/include/X11/Xaw/Label.h /usr/include/X11/Xaw/Simple.h
wtree.o: /usr/include/X11/Xmu/Converters.h /usr/include/X11/Xaw/Viewport.h
wtree.o: /usr/include/X11/Xaw/Form.h /usr/include/X11/Xaw/Reports.h
wtree.o: /usr/include/X11/Xaw/Tree.h editresP.h
wtree.o: /usr/include/X11/Xmu/EditresP.h
