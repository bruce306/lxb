#
# File: Makefile
#
# modified: 01.16.22
#
#-------------------------------------------------------------

CC=gcc
CDEBUGFLAGS = -g
INCLUDES = -I. -I/usr/include
DEFINES =
CFLAGS = $(CDEBUGFLAGS) $(INCLUDES) $(DEFINES)
LIBS = 
LDFLAGS = -o

XLIBS = -lXm -lXpm -lXt -lXext -lX11

all: cvt ss scvt install 

xenum.h: xenum
	cp xenum xenum.h

rstruct.h: cvt xres
	./cvt

tsizes.h: ss scvt xtypes 
	./ss; 
	$(CC) -c getsizes.c
	$(CC) -o getsizes getsizes.o
	rm getsizes.o getsizes.c
	./getsizes; 
	./scvt; rm tmpsizes

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

install:	../include/tsizes.h ../include/rstruct.h ../include/xenum.h

../include/tsizes.h:	tsizes.h
	cp tsizes.h ../include

../include/rstruct.h:	rstruct.h
	cp rstruct.h ../include

../include/xenum.h:	xenum.h
	cp xenum.h ../include
	
clean:
	rm -f core *.o cvt *.bak ss getsizes scvt rstruct.h tsizes.h xenum.h getsizes.c tmpsizes ../include/tsizes.h ../include/rstruct.h ../include/xenum.h

ctags:	
	ctags *.c *.h 

dummy:

depend:	
	makedepend -I/usr/include -I. *.c

# DO NOT DELETE

cvt.o: /usr/include/stdio.h /usr/include/libio.h /usr/include/_G_config.h
cvt.o: /usr/include/sys/cdefs.h
scvt.o: /usr/include/stdio.h /usr/include/libio.h /usr/include/_G_config.h
scvt.o: /usr/include/sys/cdefs.h
ss.o: /usr/include/stdio.h /usr/include/libio.h /usr/include/_G_config.h
ss.o: /usr/include/sys/cdefs.h
