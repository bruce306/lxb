#
# File: Makefile.linux
#
#-------------------------------------------------------------

CC=gcc
CDEBUGFLAGS = -g
INCLUDES = -I. -I../include -I../oldX11/include/X11 -I../oldX11/include -I/usr/include/x86_64-linux-gnu -I/usr/include/x86_64-linux-gnu/gnu  -I/usr/lib/gcc/x86_64-linux-gnu/5/include

DEFINES =
CFLAGS = $(CDEBUGFLAGS) $(INCLUDES) $(DEFINES)
LIBS = 
LDFLAGS = -o

XLIBS = -lXm -lXpm -lXt -lXext -lX11

all: depend cvt ss scvt install 

xenum.h: xenum
	cp xenum xenum.h

rstruct.h: cvt xres
	./cvt

tsizes.h: ss scvt xtypes 
	./ss; 
	$(CC) -c getsizes.c
	$(CC) -o getsizes getsizes.o
	rm getsizes.o getsizes.c
	./getsizes 
	./scvt
	 rm tmpsizes

ss: ss.c
	$(CC) -g -c ss.c
	$(CC) -o ss ss.o
	rm ss.o

scvt:	scvt.c 
	$(CC) -c scvt.c
	$(CC) -o scvt scvt.o
	rm scvt.o

cvt:	cvt.c	
	$(CC) -c cvt.c
	$(CC) -o cvt cvt.o
	rm cvt.o

getsizes: ss scvt xtypes getsizes.c
	./ss; 
	$(CC) -c getsizes.c
	$(CC) -o getsizes getsizes.o

install:	../include/tsizes.h ../include/rstruct.h ../include/xenum.h

../include/tsizes.h:	tsizes.h
	cp tsizes.h ../include

../include/rstruct.h:	rstruct.h
	cp rstruct.h ../include

../include/xenum.h:	xenum.h
	cp xenum.h ../include
	
clean:
	rm -f core *.o cvt *.bak ss getsizes scvt rstruct.h tsizes.h xenum.h getsizes.c tmpsizes 

ctags:	
	ctags *.c *.h 

depend:	
	makedepend $(INCLUDES) $(DEFINES) *.c

dummy:

# DO NOT DELETE

cvt.o: /usr/include/stdio.h /usr/include/features.h
cvt.o: /usr/include/stdc-predef.h /usr/include/x86_64-linux-gnu/sys/cdefs.h
cvt.o: /usr/include/x86_64-linux-gnu/bits/wordsize.h
cvt.o: /usr/include/x86_64-linux-gnu/gnu/stubs.h
cvt.o: /usr/lib/gcc/x86_64-linux-gnu/5/include/stddef.h
cvt.o: /usr/include/x86_64-linux-gnu/bits/types.h
cvt.o: /usr/include/x86_64-linux-gnu/bits/typesizes.h /usr/include/libio.h
cvt.o: /usr/include/_G_config.h /usr/include/wchar.h
cvt.o: /usr/lib/gcc/x86_64-linux-gnu/5/include/stdarg.h
cvt.o: /usr/include/x86_64-linux-gnu/bits/stdio_lim.h
cvt.o: /usr/include/x86_64-linux-gnu/bits/sys_errlist.h /usr/include/stdlib.h
cvt.o: /usr/include/x86_64-linux-gnu/bits/waitflags.h
cvt.o: /usr/include/x86_64-linux-gnu/bits/waitstatus.h /usr/include/endian.h
cvt.o: /usr/include/x86_64-linux-gnu/bits/endian.h
cvt.o: /usr/include/x86_64-linux-gnu/bits/byteswap.h
cvt.o: /usr/include/x86_64-linux-gnu/bits/byteswap-16.h
cvt.o: /usr/include/x86_64-linux-gnu/sys/types.h /usr/include/time.h
cvt.o: /usr/include/x86_64-linux-gnu/sys/select.h
cvt.o: /usr/include/x86_64-linux-gnu/bits/select.h
cvt.o: /usr/include/x86_64-linux-gnu/bits/sigset.h
cvt.o: /usr/include/x86_64-linux-gnu/bits/time.h
cvt.o: /usr/include/x86_64-linux-gnu/sys/sysmacros.h
cvt.o: /usr/include/x86_64-linux-gnu/bits/pthreadtypes.h
cvt.o: /usr/include/alloca.h
cvt.o: /usr/include/x86_64-linux-gnu/bits/stdlib-float.h
cvt.o: /usr/include/string.h /usr/include/xlocale.h
scvt.o: /usr/include/stdio.h /usr/include/features.h
scvt.o: /usr/include/stdc-predef.h /usr/include/x86_64-linux-gnu/sys/cdefs.h
scvt.o: /usr/include/x86_64-linux-gnu/bits/wordsize.h
scvt.o: /usr/include/x86_64-linux-gnu/gnu/stubs.h
scvt.o: /usr/lib/gcc/x86_64-linux-gnu/5/include/stddef.h
scvt.o: /usr/include/x86_64-linux-gnu/bits/types.h
scvt.o: /usr/include/x86_64-linux-gnu/bits/typesizes.h /usr/include/libio.h
scvt.o: /usr/include/_G_config.h /usr/include/wchar.h
scvt.o: /usr/lib/gcc/x86_64-linux-gnu/5/include/stdarg.h
scvt.o: /usr/include/x86_64-linux-gnu/bits/stdio_lim.h
scvt.o: /usr/include/x86_64-linux-gnu/bits/sys_errlist.h
scvt.o: /usr/include/stdlib.h /usr/include/x86_64-linux-gnu/bits/waitflags.h
scvt.o: /usr/include/x86_64-linux-gnu/bits/waitstatus.h /usr/include/endian.h
scvt.o: /usr/include/x86_64-linux-gnu/bits/endian.h
scvt.o: /usr/include/x86_64-linux-gnu/bits/byteswap.h
scvt.o: /usr/include/x86_64-linux-gnu/bits/byteswap-16.h
scvt.o: /usr/include/x86_64-linux-gnu/sys/types.h /usr/include/time.h
scvt.o: /usr/include/x86_64-linux-gnu/sys/select.h
scvt.o: /usr/include/x86_64-linux-gnu/bits/select.h
scvt.o: /usr/include/x86_64-linux-gnu/bits/sigset.h
scvt.o: /usr/include/x86_64-linux-gnu/bits/time.h
scvt.o: /usr/include/x86_64-linux-gnu/sys/sysmacros.h
scvt.o: /usr/include/x86_64-linux-gnu/bits/pthreadtypes.h
scvt.o: /usr/include/alloca.h
scvt.o: /usr/include/x86_64-linux-gnu/bits/stdlib-float.h
scvt.o: /usr/include/string.h /usr/include/xlocale.h
ss.o: /usr/include/stdio.h /usr/include/features.h /usr/include/stdc-predef.h
ss.o: /usr/include/x86_64-linux-gnu/sys/cdefs.h
ss.o: /usr/include/x86_64-linux-gnu/bits/wordsize.h
ss.o: /usr/include/x86_64-linux-gnu/gnu/stubs.h
ss.o: /usr/lib/gcc/x86_64-linux-gnu/5/include/stddef.h
ss.o: /usr/include/x86_64-linux-gnu/bits/types.h
ss.o: /usr/include/x86_64-linux-gnu/bits/typesizes.h /usr/include/libio.h
ss.o: /usr/include/_G_config.h /usr/include/wchar.h
ss.o: /usr/lib/gcc/x86_64-linux-gnu/5/include/stdarg.h
ss.o: /usr/include/x86_64-linux-gnu/bits/stdio_lim.h
ss.o: /usr/include/x86_64-linux-gnu/bits/sys_errlist.h /usr/include/stdlib.h
ss.o: /usr/include/x86_64-linux-gnu/bits/waitflags.h
ss.o: /usr/include/x86_64-linux-gnu/bits/waitstatus.h /usr/include/endian.h
ss.o: /usr/include/x86_64-linux-gnu/bits/endian.h
ss.o: /usr/include/x86_64-linux-gnu/bits/byteswap.h
ss.o: /usr/include/x86_64-linux-gnu/bits/byteswap-16.h
ss.o: /usr/include/x86_64-linux-gnu/sys/types.h /usr/include/time.h
ss.o: /usr/include/x86_64-linux-gnu/sys/select.h
ss.o: /usr/include/x86_64-linux-gnu/bits/select.h
ss.o: /usr/include/x86_64-linux-gnu/bits/sigset.h
ss.o: /usr/include/x86_64-linux-gnu/bits/time.h
ss.o: /usr/include/x86_64-linux-gnu/sys/sysmacros.h
ss.o: /usr/include/x86_64-linux-gnu/bits/pthreadtypes.h /usr/include/alloca.h
ss.o: /usr/include/x86_64-linux-gnu/bits/stdlib-float.h /usr/include/string.h
ss.o: /usr/include/xlocale.h
