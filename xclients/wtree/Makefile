#
#	File: Makefile for wtree
#

CC=cc

# will compile program
#INCLUDES = -I. -I../../../oldX11/include

# to satisfy makedepend
INCLUDES = -I../include -I../../../oldX11/include -I/usr/include/x86_64-linux-gnu -I-I/usr/include/x86_64-linux-gnu -I/usr/lib/gcc/x86_64-linux-gnu/5/include

CFLAGS = -g  -ggdb $(INCLUDES)
LDFLAGS = -o

XLIBS = -lXm -lX11 -lXmu -lXt -lXaw
LIBS = $(XLIBS)

OBJS = \
	Tree.o \
	Panner.o \
	Porthole.o \
	tst.o

tst: tst.o tst_util.o wtree.o
	$(CC) $(CFLAGS) tst.o tst_util.o wtree.o $(LIBS) $(LDFLAGS) $@

all: clean depend tst

clean:
	rm -f *.o tst

depend:
	makedepend $(INCLUDES) $(DEFINES) *.c

# DO NOT DELETE

Panner.o: /usr/include/X11/IntrinsicP.h /usr/include/X11/Intrinsic.h
Panner.o: /usr/include/X11/Xlib.h /usr/include/x86_64-linux-gnu/sys/types.h
Panner.o: /usr/include/features.h /usr/include/stdc-predef.h
Panner.o: /usr/include/x86_64-linux-gnu/sys/cdefs.h
Panner.o: /usr/include/x86_64-linux-gnu/bits/wordsize.h
Panner.o: /usr/include/x86_64-linux-gnu/bits/long-double.h
Panner.o: /usr/include/x86_64-linux-gnu/gnu/stubs.h
Panner.o: /usr/include/x86_64-linux-gnu/bits/types.h
Panner.o: /usr/include/x86_64-linux-gnu/bits/timesize.h
Panner.o: /usr/include/x86_64-linux-gnu/bits/typesizes.h
Panner.o: /usr/include/x86_64-linux-gnu/bits/time64.h
Panner.o: /usr/include/x86_64-linux-gnu/bits/types/clock_t.h
Panner.o: /usr/include/x86_64-linux-gnu/bits/types/clockid_t.h
Panner.o: /usr/include/x86_64-linux-gnu/bits/types/time_t.h
Panner.o: /usr/include/x86_64-linux-gnu/bits/types/timer_t.h
Panner.o: /usr/include/x86_64-linux-gnu/bits/stdint-intn.h
Panner.o: /usr/include/endian.h /usr/include/x86_64-linux-gnu/bits/endian.h
Panner.o: /usr/include/x86_64-linux-gnu/bits/endianness.h
Panner.o: /usr/include/x86_64-linux-gnu/bits/byteswap.h
Panner.o: /usr/include/x86_64-linux-gnu/bits/uintn-identity.h
Panner.o: /usr/include/x86_64-linux-gnu/sys/select.h
Panner.o: /usr/include/x86_64-linux-gnu/bits/select.h
Panner.o: /usr/include/x86_64-linux-gnu/bits/types/sigset_t.h
Panner.o: /usr/include/x86_64-linux-gnu/bits/types/__sigset_t.h
Panner.o: /usr/include/x86_64-linux-gnu/bits/types/struct_timeval.h
Panner.o: /usr/include/x86_64-linux-gnu/bits/types/struct_timespec.h
Panner.o: /usr/include/x86_64-linux-gnu/bits/pthreadtypes.h
Panner.o: /usr/include/x86_64-linux-gnu/bits/thread-shared-types.h
Panner.o: /usr/include/x86_64-linux-gnu/bits/pthreadtypes-arch.h
Panner.o: /usr/include/x86_64-linux-gnu/bits/struct_mutex.h
Panner.o: /usr/include/x86_64-linux-gnu/bits/struct_rwlock.h
Panner.o: /usr/include/X11/X.h /usr/include/X11/Xfuncproto.h
Panner.o: /usr/include/X11/Xosdefs.h /usr/include/X11/Xutil.h
Panner.o: /usr/include/X11/keysym.h /usr/include/X11/keysymdef.h
Panner.o: /usr/include/X11/Xresource.h /usr/include/string.h
Panner.o: /usr/include/x86_64-linux-gnu/bits/libc-header-start.h
Panner.o: /usr/include/x86_64-linux-gnu/bits/types/locale_t.h
Panner.o: /usr/include/x86_64-linux-gnu/bits/types/__locale_t.h
Panner.o: /usr/include/strings.h /usr/include/X11/Core.h
Panner.o: /usr/include/X11/Composite.h /usr/include/X11/Constraint.h
Panner.o: /usr/include/X11/Object.h /usr/include/X11/RectObj.h
Panner.o: /usr/include/X11/CoreP.h /usr/include/X11/CompositeP.h
Panner.o: /usr/include/X11/ConstrainP.h /usr/include/X11/ObjectP.h
Panner.o: /usr/include/X11/RectObjP.h /usr/include/X11/StringDefs.h
Panner.o: /usr/include/X11/Xmu/CharSet.h /usr/include/X11/Xaw/XawInit.h
Panner.o: /usr/include/X11/Xaw/PannerP.h /usr/include/X11/Xaw/Panner.h
Panner.o: /usr/include/X11/Xaw/Reports.h /usr/include/X11/Xaw/SimpleP.h
Panner.o: /usr/include/X11/Xaw/Simple.h /usr/include/X11/Xmu/Converters.h
Panner.o: /usr/include/X11/Xos.h /usr/include/fcntl.h
Panner.o: /usr/include/x86_64-linux-gnu/bits/fcntl.h
Panner.o: /usr/include/x86_64-linux-gnu/bits/fcntl-linux.h
Panner.o: /usr/include/x86_64-linux-gnu/bits/stat.h /usr/include/unistd.h
Panner.o: /usr/include/x86_64-linux-gnu/bits/posix_opt.h
Panner.o: /usr/include/x86_64-linux-gnu/bits/environments.h
Panner.o: /usr/include/x86_64-linux-gnu/bits/confname.h
Panner.o: /usr/include/x86_64-linux-gnu/bits/getopt_posix.h
Panner.o: /usr/include/x86_64-linux-gnu/bits/getopt_core.h
Panner.o: /usr/include/x86_64-linux-gnu/bits/unistd_ext.h
Panner.o: /usr/include/x86_64-linux-gnu/sys/time.h /usr/include/time.h
Panner.o: /usr/include/x86_64-linux-gnu/bits/time.h
Panner.o: /usr/include/x86_64-linux-gnu/bits/types/struct_tm.h
Panner.o: /usr/include/x86_64-linux-gnu/bits/types/struct_itimerspec.h
Panner.o: /usr/include/X11/Xarch.h /usr/include/X11/Xmu/Misc.h
Panner.o: /usr/include/X11/Xmu/Drawing.h /usr/include/stdio.h
Panner.o: /usr/include/x86_64-linux-gnu/bits/types/__fpos_t.h
Panner.o: /usr/include/x86_64-linux-gnu/bits/types/__mbstate_t.h
Panner.o: /usr/include/x86_64-linux-gnu/bits/types/__fpos64_t.h
Panner.o: /usr/include/x86_64-linux-gnu/bits/types/__FILE.h
Panner.o: /usr/include/x86_64-linux-gnu/bits/types/FILE.h
Panner.o: /usr/include/x86_64-linux-gnu/bits/types/struct_FILE.h
Panner.o: /usr/include/x86_64-linux-gnu/bits/stdio_lim.h
Panner.o: /usr/include/x86_64-linux-gnu/bits/sys_errlist.h
Panner.o: /usr/include/ctype.h /usr/include/math.h
Panner.o: /usr/include/x86_64-linux-gnu/bits/math-vector.h
Panner.o: /usr/include/x86_64-linux-gnu/bits/libm-simd-decl-stubs.h
Panner.o: /usr/include/x86_64-linux-gnu/bits/floatn.h
Panner.o: /usr/include/x86_64-linux-gnu/bits/floatn-common.h
Panner.o: /usr/include/x86_64-linux-gnu/bits/flt-eval-method.h
Panner.o: /usr/include/x86_64-linux-gnu/bits/fp-logb.h
Panner.o: /usr/include/x86_64-linux-gnu/bits/fp-fast.h
Panner.o: /usr/include/x86_64-linux-gnu/bits/mathcalls-helper-functions.h
Panner.o: /usr/include/x86_64-linux-gnu/bits/mathcalls.h
Panner.o: /usr/include/x86_64-linux-gnu/bits/mathcalls-narrow.h
Panner.o: /usr/include/x86_64-linux-gnu/bits/iscanonical.h
Porthole.o: /usr/include/X11/IntrinsicP.h /usr/include/X11/Intrinsic.h
Porthole.o: /usr/include/X11/Xlib.h /usr/include/x86_64-linux-gnu/sys/types.h
Porthole.o: /usr/include/features.h /usr/include/stdc-predef.h
Porthole.o: /usr/include/x86_64-linux-gnu/sys/cdefs.h
Porthole.o: /usr/include/x86_64-linux-gnu/bits/wordsize.h
Porthole.o: /usr/include/x86_64-linux-gnu/bits/long-double.h
Porthole.o: /usr/include/x86_64-linux-gnu/gnu/stubs.h
Porthole.o: /usr/include/x86_64-linux-gnu/bits/types.h
Porthole.o: /usr/include/x86_64-linux-gnu/bits/timesize.h
Porthole.o: /usr/include/x86_64-linux-gnu/bits/typesizes.h
Porthole.o: /usr/include/x86_64-linux-gnu/bits/time64.h
Porthole.o: /usr/include/x86_64-linux-gnu/bits/types/clock_t.h
Porthole.o: /usr/include/x86_64-linux-gnu/bits/types/clockid_t.h
Porthole.o: /usr/include/x86_64-linux-gnu/bits/types/time_t.h
Porthole.o: /usr/include/x86_64-linux-gnu/bits/types/timer_t.h
Porthole.o: /usr/include/x86_64-linux-gnu/bits/stdint-intn.h
Porthole.o: /usr/include/endian.h /usr/include/x86_64-linux-gnu/bits/endian.h
Porthole.o: /usr/include/x86_64-linux-gnu/bits/endianness.h
Porthole.o: /usr/include/x86_64-linux-gnu/bits/byteswap.h
Porthole.o: /usr/include/x86_64-linux-gnu/bits/uintn-identity.h
Porthole.o: /usr/include/x86_64-linux-gnu/sys/select.h
Porthole.o: /usr/include/x86_64-linux-gnu/bits/select.h
Porthole.o: /usr/include/x86_64-linux-gnu/bits/types/sigset_t.h
Porthole.o: /usr/include/x86_64-linux-gnu/bits/types/__sigset_t.h
Porthole.o: /usr/include/x86_64-linux-gnu/bits/types/struct_timeval.h
Porthole.o: /usr/include/x86_64-linux-gnu/bits/types/struct_timespec.h
Porthole.o: /usr/include/x86_64-linux-gnu/bits/pthreadtypes.h
Porthole.o: /usr/include/x86_64-linux-gnu/bits/thread-shared-types.h
Porthole.o: /usr/include/x86_64-linux-gnu/bits/pthreadtypes-arch.h
Porthole.o: /usr/include/x86_64-linux-gnu/bits/struct_mutex.h
Porthole.o: /usr/include/x86_64-linux-gnu/bits/struct_rwlock.h
Porthole.o: /usr/include/X11/X.h /usr/include/X11/Xfuncproto.h
Porthole.o: /usr/include/X11/Xosdefs.h /usr/include/X11/Xutil.h
Porthole.o: /usr/include/X11/keysym.h /usr/include/X11/keysymdef.h
Porthole.o: /usr/include/X11/Xresource.h /usr/include/string.h
Porthole.o: /usr/include/x86_64-linux-gnu/bits/libc-header-start.h
Porthole.o: /usr/include/x86_64-linux-gnu/bits/types/locale_t.h
Porthole.o: /usr/include/x86_64-linux-gnu/bits/types/__locale_t.h
Porthole.o: /usr/include/strings.h /usr/include/X11/Core.h
Porthole.o: /usr/include/X11/Composite.h /usr/include/X11/Constraint.h
Porthole.o: /usr/include/X11/Object.h /usr/include/X11/RectObj.h
Porthole.o: /usr/include/X11/CoreP.h /usr/include/X11/CompositeP.h
Porthole.o: /usr/include/X11/ConstrainP.h /usr/include/X11/ObjectP.h
Porthole.o: /usr/include/X11/RectObjP.h /usr/include/X11/StringDefs.h
Porthole.o: /usr/include/X11/Xaw/XawInit.h /usr/include/X11/Xaw/PortholeP.h
Porthole.o: /usr/include/X11/Xaw/Porthole.h /usr/include/X11/Xaw/Reports.h
Porthole.o: /usr/include/X11/Xmu/Misc.h
Tree.o: /usr/include/X11/IntrinsicP.h /usr/include/X11/Intrinsic.h
Tree.o: /usr/include/X11/Xlib.h /usr/include/x86_64-linux-gnu/sys/types.h
Tree.o: /usr/include/features.h /usr/include/stdc-predef.h
Tree.o: /usr/include/x86_64-linux-gnu/sys/cdefs.h
Tree.o: /usr/include/x86_64-linux-gnu/bits/wordsize.h
Tree.o: /usr/include/x86_64-linux-gnu/bits/long-double.h
Tree.o: /usr/include/x86_64-linux-gnu/gnu/stubs.h
Tree.o: /usr/include/x86_64-linux-gnu/bits/types.h
Tree.o: /usr/include/x86_64-linux-gnu/bits/timesize.h
Tree.o: /usr/include/x86_64-linux-gnu/bits/typesizes.h
Tree.o: /usr/include/x86_64-linux-gnu/bits/time64.h
Tree.o: /usr/include/x86_64-linux-gnu/bits/types/clock_t.h
Tree.o: /usr/include/x86_64-linux-gnu/bits/types/clockid_t.h
Tree.o: /usr/include/x86_64-linux-gnu/bits/types/time_t.h
Tree.o: /usr/include/x86_64-linux-gnu/bits/types/timer_t.h
Tree.o: /usr/include/x86_64-linux-gnu/bits/stdint-intn.h
Tree.o: /usr/include/endian.h /usr/include/x86_64-linux-gnu/bits/endian.h
Tree.o: /usr/include/x86_64-linux-gnu/bits/endianness.h
Tree.o: /usr/include/x86_64-linux-gnu/bits/byteswap.h
Tree.o: /usr/include/x86_64-linux-gnu/bits/uintn-identity.h
Tree.o: /usr/include/x86_64-linux-gnu/sys/select.h
Tree.o: /usr/include/x86_64-linux-gnu/bits/select.h
Tree.o: /usr/include/x86_64-linux-gnu/bits/types/sigset_t.h
Tree.o: /usr/include/x86_64-linux-gnu/bits/types/__sigset_t.h
Tree.o: /usr/include/x86_64-linux-gnu/bits/types/struct_timeval.h
Tree.o: /usr/include/x86_64-linux-gnu/bits/types/struct_timespec.h
Tree.o: /usr/include/x86_64-linux-gnu/bits/pthreadtypes.h
Tree.o: /usr/include/x86_64-linux-gnu/bits/thread-shared-types.h
Tree.o: /usr/include/x86_64-linux-gnu/bits/pthreadtypes-arch.h
Tree.o: /usr/include/x86_64-linux-gnu/bits/struct_mutex.h
Tree.o: /usr/include/x86_64-linux-gnu/bits/struct_rwlock.h
Tree.o: /usr/include/X11/X.h /usr/include/X11/Xfuncproto.h
Tree.o: /usr/include/X11/Xosdefs.h /usr/include/X11/Xutil.h
Tree.o: /usr/include/X11/keysym.h /usr/include/X11/keysymdef.h
Tree.o: /usr/include/X11/Xresource.h /usr/include/string.h
Tree.o: /usr/include/x86_64-linux-gnu/bits/libc-header-start.h
Tree.o: /usr/include/x86_64-linux-gnu/bits/types/locale_t.h
Tree.o: /usr/include/x86_64-linux-gnu/bits/types/__locale_t.h
Tree.o: /usr/include/strings.h /usr/include/X11/Core.h
Tree.o: /usr/include/X11/Composite.h /usr/include/X11/Constraint.h
Tree.o: /usr/include/X11/Object.h /usr/include/X11/RectObj.h
Tree.o: /usr/include/X11/CoreP.h /usr/include/X11/CompositeP.h
Tree.o: /usr/include/X11/ConstrainP.h /usr/include/X11/ObjectP.h
Tree.o: /usr/include/X11/RectObjP.h /usr/include/X11/StringDefs.h
Tree.o: /usr/include/X11/Xaw/XawInit.h /usr/include/X11/Xaw/Cardinals.h
Tree.o: /usr/include/X11/Xaw/TreeP.h /usr/include/X11/Xaw/Tree.h
Tree.o: /usr/include/X11/Xmu/Converters.h
tst.o: /usr/include/stdio.h
tst.o: /usr/include/x86_64-linux-gnu/bits/libc-header-start.h
tst.o: /usr/include/features.h /usr/include/stdc-predef.h
tst.o: /usr/include/x86_64-linux-gnu/sys/cdefs.h
tst.o: /usr/include/x86_64-linux-gnu/bits/wordsize.h
tst.o: /usr/include/x86_64-linux-gnu/bits/long-double.h
tst.o: /usr/include/x86_64-linux-gnu/gnu/stubs.h
tst.o: /usr/include/x86_64-linux-gnu/bits/types.h
tst.o: /usr/include/x86_64-linux-gnu/bits/timesize.h
tst.o: /usr/include/x86_64-linux-gnu/bits/typesizes.h
tst.o: /usr/include/x86_64-linux-gnu/bits/time64.h
tst.o: /usr/include/x86_64-linux-gnu/bits/types/__fpos_t.h
tst.o: /usr/include/x86_64-linux-gnu/bits/types/__mbstate_t.h
tst.o: /usr/include/x86_64-linux-gnu/bits/types/__fpos64_t.h
tst.o: /usr/include/x86_64-linux-gnu/bits/types/__FILE.h
tst.o: /usr/include/x86_64-linux-gnu/bits/types/FILE.h
tst.o: /usr/include/x86_64-linux-gnu/bits/types/struct_FILE.h
tst.o: /usr/include/x86_64-linux-gnu/bits/stdio_lim.h
tst.o: /usr/include/x86_64-linux-gnu/bits/sys_errlist.h /usr/include/Xm/Xm.h
tst.o: /usr/include/X11/Intrinsic.h /usr/include/X11/Xlib.h
tst.o: /usr/include/x86_64-linux-gnu/sys/types.h
tst.o: /usr/include/x86_64-linux-gnu/bits/types/clock_t.h
tst.o: /usr/include/x86_64-linux-gnu/bits/types/clockid_t.h
tst.o: /usr/include/x86_64-linux-gnu/bits/types/time_t.h
tst.o: /usr/include/x86_64-linux-gnu/bits/types/timer_t.h
tst.o: /usr/include/x86_64-linux-gnu/bits/stdint-intn.h /usr/include/endian.h
tst.o: /usr/include/x86_64-linux-gnu/bits/endian.h
tst.o: /usr/include/x86_64-linux-gnu/bits/endianness.h
tst.o: /usr/include/x86_64-linux-gnu/bits/byteswap.h
tst.o: /usr/include/x86_64-linux-gnu/bits/uintn-identity.h
tst.o: /usr/include/x86_64-linux-gnu/sys/select.h
tst.o: /usr/include/x86_64-linux-gnu/bits/select.h
tst.o: /usr/include/x86_64-linux-gnu/bits/types/sigset_t.h
tst.o: /usr/include/x86_64-linux-gnu/bits/types/__sigset_t.h
tst.o: /usr/include/x86_64-linux-gnu/bits/types/struct_timeval.h
tst.o: /usr/include/x86_64-linux-gnu/bits/types/struct_timespec.h
tst.o: /usr/include/x86_64-linux-gnu/bits/pthreadtypes.h
tst.o: /usr/include/x86_64-linux-gnu/bits/thread-shared-types.h
tst.o: /usr/include/x86_64-linux-gnu/bits/pthreadtypes-arch.h
tst.o: /usr/include/x86_64-linux-gnu/bits/struct_mutex.h
tst.o: /usr/include/x86_64-linux-gnu/bits/struct_rwlock.h
tst.o: /usr/include/X11/X.h /usr/include/X11/Xfuncproto.h
tst.o: /usr/include/X11/Xosdefs.h /usr/include/X11/Xutil.h
tst.o: /usr/include/X11/keysym.h /usr/include/X11/keysymdef.h
tst.o: /usr/include/X11/Xresource.h /usr/include/string.h
tst.o: /usr/include/x86_64-linux-gnu/bits/types/locale_t.h
tst.o: /usr/include/x86_64-linux-gnu/bits/types/__locale_t.h
tst.o: /usr/include/strings.h /usr/include/X11/Core.h
tst.o: /usr/include/X11/Composite.h /usr/include/X11/Constraint.h
tst.o: /usr/include/X11/Object.h /usr/include/X11/RectObj.h
tst.o: /usr/include/X11/Shell.h /usr/include/X11/SM/SMlib.h
tst.o: /usr/include/X11/SM/SM.h /usr/include/X11/ICE/ICElib.h
tst.o: /usr/include/X11/ICE/ICE.h /usr/include/X11/Xatom.h
tst.o: /usr/include/Xm/XmStrDefs.h /usr/include/X11/StringDefs.h
tst.o: /usr/include/Xm/XmStrDefs22.h /usr/include/Xm/XmStrDefs23.h
tst.o: /usr/include/Xm/VirtKeys.h /usr/include/Xm/Transfer.h
tst.o: /usr/include/Xm/DragC.h /usr/include/Xm/Display.h
tst.o: /usr/include/Xm/DropSMgr.h /usr/include/Xm/Primitive.h
tst.o: /usr/include/Xm/Manager.h /usr/include/Xm/Gadget.h
tst.o: /usr/include/Xm/TxtPropCv.h /usr/include/Xm/VendorS.h
tst.o: /usr/include/Xm/XmIm.h /usr/include/Xm/PushB.h /usr/include/Xm/Frame.h
tst.o: /usr/include/Xm/DrawingA.h Tree.h /usr/include/X11/Xmu/Converters.h
tst.o: Panner.h /usr/include/X11/Xaw/Reports.h Porthole.h tst_util.h tst.h
tst.o: wtree.h
tst_util.o: /usr/include/stdio.h
tst_util.o: /usr/include/x86_64-linux-gnu/bits/libc-header-start.h
tst_util.o: /usr/include/features.h /usr/include/stdc-predef.h
tst_util.o: /usr/include/x86_64-linux-gnu/sys/cdefs.h
tst_util.o: /usr/include/x86_64-linux-gnu/bits/wordsize.h
tst_util.o: /usr/include/x86_64-linux-gnu/bits/long-double.h
tst_util.o: /usr/include/x86_64-linux-gnu/gnu/stubs.h
tst_util.o: /usr/include/x86_64-linux-gnu/bits/types.h
tst_util.o: /usr/include/x86_64-linux-gnu/bits/timesize.h
tst_util.o: /usr/include/x86_64-linux-gnu/bits/typesizes.h
tst_util.o: /usr/include/x86_64-linux-gnu/bits/time64.h
tst_util.o: /usr/include/x86_64-linux-gnu/bits/types/__fpos_t.h
tst_util.o: /usr/include/x86_64-linux-gnu/bits/types/__mbstate_t.h
tst_util.o: /usr/include/x86_64-linux-gnu/bits/types/__fpos64_t.h
tst_util.o: /usr/include/x86_64-linux-gnu/bits/types/__FILE.h
tst_util.o: /usr/include/x86_64-linux-gnu/bits/types/FILE.h
tst_util.o: /usr/include/x86_64-linux-gnu/bits/types/struct_FILE.h
tst_util.o: /usr/include/x86_64-linux-gnu/bits/stdio_lim.h
tst_util.o: /usr/include/x86_64-linux-gnu/bits/sys_errlist.h
tst_util.o: /usr/include/Xm/Xm.h /usr/include/X11/Intrinsic.h
tst_util.o: /usr/include/X11/Xlib.h /usr/include/x86_64-linux-gnu/sys/types.h
tst_util.o: /usr/include/x86_64-linux-gnu/bits/types/clock_t.h
tst_util.o: /usr/include/x86_64-linux-gnu/bits/types/clockid_t.h
tst_util.o: /usr/include/x86_64-linux-gnu/bits/types/time_t.h
tst_util.o: /usr/include/x86_64-linux-gnu/bits/types/timer_t.h
tst_util.o: /usr/include/x86_64-linux-gnu/bits/stdint-intn.h
tst_util.o: /usr/include/endian.h /usr/include/x86_64-linux-gnu/bits/endian.h
tst_util.o: /usr/include/x86_64-linux-gnu/bits/endianness.h
tst_util.o: /usr/include/x86_64-linux-gnu/bits/byteswap.h
tst_util.o: /usr/include/x86_64-linux-gnu/bits/uintn-identity.h
tst_util.o: /usr/include/x86_64-linux-gnu/sys/select.h
tst_util.o: /usr/include/x86_64-linux-gnu/bits/select.h
tst_util.o: /usr/include/x86_64-linux-gnu/bits/types/sigset_t.h
tst_util.o: /usr/include/x86_64-linux-gnu/bits/types/__sigset_t.h
tst_util.o: /usr/include/x86_64-linux-gnu/bits/types/struct_timeval.h
tst_util.o: /usr/include/x86_64-linux-gnu/bits/types/struct_timespec.h
tst_util.o: /usr/include/x86_64-linux-gnu/bits/pthreadtypes.h
tst_util.o: /usr/include/x86_64-linux-gnu/bits/thread-shared-types.h
tst_util.o: /usr/include/x86_64-linux-gnu/bits/pthreadtypes-arch.h
tst_util.o: /usr/include/x86_64-linux-gnu/bits/struct_mutex.h
tst_util.o: /usr/include/x86_64-linux-gnu/bits/struct_rwlock.h
tst_util.o: /usr/include/X11/X.h /usr/include/X11/Xfuncproto.h
tst_util.o: /usr/include/X11/Xosdefs.h /usr/include/X11/Xutil.h
tst_util.o: /usr/include/X11/keysym.h /usr/include/X11/keysymdef.h
tst_util.o: /usr/include/X11/Xresource.h /usr/include/string.h
tst_util.o: /usr/include/x86_64-linux-gnu/bits/types/locale_t.h
tst_util.o: /usr/include/x86_64-linux-gnu/bits/types/__locale_t.h
tst_util.o: /usr/include/strings.h /usr/include/X11/Core.h
tst_util.o: /usr/include/X11/Composite.h /usr/include/X11/Constraint.h
tst_util.o: /usr/include/X11/Object.h /usr/include/X11/RectObj.h
tst_util.o: /usr/include/X11/Shell.h /usr/include/X11/SM/SMlib.h
tst_util.o: /usr/include/X11/SM/SM.h /usr/include/X11/ICE/ICElib.h
tst_util.o: /usr/include/X11/ICE/ICE.h /usr/include/X11/Xatom.h
tst_util.o: /usr/include/Xm/XmStrDefs.h /usr/include/X11/StringDefs.h
tst_util.o: /usr/include/Xm/XmStrDefs22.h /usr/include/Xm/XmStrDefs23.h
tst_util.o: /usr/include/Xm/VirtKeys.h /usr/include/Xm/Transfer.h
tst_util.o: /usr/include/Xm/DragC.h /usr/include/Xm/Display.h
tst_util.o: /usr/include/Xm/DropSMgr.h /usr/include/Xm/Primitive.h
tst_util.o: /usr/include/Xm/Manager.h /usr/include/Xm/Gadget.h
tst_util.o: /usr/include/Xm/TxtPropCv.h /usr/include/Xm/VendorS.h
tst_util.o: /usr/include/Xm/XmIm.h tst_util.h
wtree.o: /usr/include/Xm/Xm.h /usr/include/X11/Intrinsic.h
wtree.o: /usr/include/X11/Xlib.h /usr/include/x86_64-linux-gnu/sys/types.h
wtree.o: /usr/include/features.h /usr/include/stdc-predef.h
wtree.o: /usr/include/x86_64-linux-gnu/sys/cdefs.h
wtree.o: /usr/include/x86_64-linux-gnu/bits/wordsize.h
wtree.o: /usr/include/x86_64-linux-gnu/bits/long-double.h
wtree.o: /usr/include/x86_64-linux-gnu/gnu/stubs.h
wtree.o: /usr/include/x86_64-linux-gnu/bits/types.h
wtree.o: /usr/include/x86_64-linux-gnu/bits/timesize.h
wtree.o: /usr/include/x86_64-linux-gnu/bits/typesizes.h
wtree.o: /usr/include/x86_64-linux-gnu/bits/time64.h
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
wtree.o: /usr/include/x86_64-linux-gnu/bits/libc-header-start.h
wtree.o: /usr/include/x86_64-linux-gnu/bits/types/locale_t.h
wtree.o: /usr/include/x86_64-linux-gnu/bits/types/__locale_t.h
wtree.o: /usr/include/strings.h /usr/include/X11/Core.h
wtree.o: /usr/include/X11/Composite.h /usr/include/X11/Constraint.h
wtree.o: /usr/include/X11/Object.h /usr/include/X11/RectObj.h
wtree.o: /usr/include/X11/Shell.h /usr/include/X11/SM/SMlib.h
wtree.o: /usr/include/X11/SM/SM.h /usr/include/X11/ICE/ICElib.h
wtree.o: /usr/include/X11/ICE/ICE.h /usr/include/X11/Xatom.h
wtree.o: /usr/include/Xm/XmStrDefs.h /usr/include/X11/StringDefs.h
wtree.o: /usr/include/Xm/XmStrDefs22.h /usr/include/Xm/XmStrDefs23.h
wtree.o: /usr/include/Xm/VirtKeys.h /usr/include/Xm/Transfer.h
wtree.o: /usr/include/Xm/DragC.h /usr/include/Xm/Display.h
wtree.o: /usr/include/Xm/DropSMgr.h /usr/include/Xm/Primitive.h
wtree.o: /usr/include/Xm/Manager.h /usr/include/Xm/Gadget.h
wtree.o: /usr/include/Xm/TxtPropCv.h /usr/include/Xm/VendorS.h
wtree.o: /usr/include/Xm/XmIm.h /usr/include/Xm/PushB.h
wtree.o: /usr/include/Xm/Frame.h /usr/include/Xm/DrawingA.h Tree.h
wtree.o: /usr/include/X11/Xmu/Converters.h Panner.h
wtree.o: /usr/include/X11/Xaw/Reports.h Porthole.h tst_util.h wtree.h
