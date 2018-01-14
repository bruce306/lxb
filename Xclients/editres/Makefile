#---------------------------------------------------------------------------
#
# 	File: Makefile
#	
#		For ubuntu v16 12/23/17
#		BEP
#
#---------------------------------------------------------------------------

#  change these to point to the build direcorties for the program &misc X source
#
Home = /home/lxb
XDIR = /home/lxb/lxb/oldX11
PGM = editres

CC=gcc
CDEBUGFLAGS = -g -ggdb

DEFINES =
# INCLUDES = -I../include -I$(XDIR)/include -I/usr/include/x86_64-linux-gnu -I/usr/lib/gcc/x86_64-linux-gnu/5/include

INCLUDES = -I../include -I$(XDIR)/include 


CFLAGS = $(CDEBUGFLAGS) $(INCLUDES) $(DEFINES)
LDFLAGS = -o

#
#  use my built and installed Motif library - Ubuntu v16 12/23/17
#
#    -the libs exist but not the header files for all X11
#    - built and installed the latest Motif libs from Sourceforge
#    - need to have libs in this order or get a bad window error
#
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
	makedepend $(INCLUDES) $(DEFINES) *.c


# DO NOT DELETE

actions.o: /usr/include/stdio.h /usr/include/features.h
actions.o: /usr/include/stdc-predef.h /usr/include/libio.h
actions.o: /usr/include/_G_config.h /usr/include/wchar.h
actions.o: /usr/include/X11/Intrinsic.h /usr/include/X11/Xlib.h
actions.o: /usr/include/X11/X.h /usr/include/X11/Xfuncproto.h
actions.o: /usr/include/X11/Xosdefs.h /usr/include/X11/Xutil.h
actions.o: /usr/include/X11/keysym.h /usr/include/X11/keysymdef.h
actions.o: /usr/include/X11/Xresource.h /usr/include/string.h
actions.o: /usr/include/xlocale.h /usr/include/X11/Core.h
actions.o: /usr/include/X11/Composite.h /usr/include/X11/Constraint.h
actions.o: /usr/include/X11/Object.h /usr/include/X11/RectObj.h
actions.o: /home/lxb/lxb/oldX11/include/X11/Xmu/CharSet.h
actions.o: /home/lxb/lxb/oldX11/include/X11/Xaw/Cardinals.h editresP.h
actions.o: /home/lxb/lxb/oldX11/include/X11/Xmu/EditresP.h
comm.o: /usr/include/X11/Intrinsic.h /usr/include/X11/Xlib.h
comm.o: /usr/include/X11/X.h /usr/include/X11/Xfuncproto.h
comm.o: /usr/include/X11/Xosdefs.h /usr/include/X11/Xutil.h
comm.o: /usr/include/X11/keysym.h /usr/include/X11/keysymdef.h
comm.o: /usr/include/X11/Xresource.h /usr/include/string.h
comm.o: /usr/include/features.h /usr/include/stdc-predef.h
comm.o: /usr/include/xlocale.h /usr/include/X11/Core.h
comm.o: /usr/include/X11/Composite.h /usr/include/X11/Constraint.h
comm.o: /usr/include/X11/Object.h /usr/include/X11/RectObj.h
comm.o: /usr/include/X11/StringDefs.h /usr/include/X11/Xatom.h
comm.o: /usr/include/X11/cursorfont.h /usr/include/X11/Xproto.h
comm.o: /usr/include/X11/Xmd.h /usr/include/X11/Xprotostr.h
comm.o: /usr/include/X11/Xos.h /usr/include/fcntl.h /usr/include/time.h
comm.o: /usr/include/unistd.h /usr/include/getopt.h /usr/include/X11/Xarch.h
comm.o: /usr/include/stdio.h /usr/include/libio.h /usr/include/_G_config.h
comm.o: /usr/include/wchar.h /home/lxb/lxb/oldX11/include/X11/Xmu/Error.h
comm.o: editresP.h /home/lxb/lxb/oldX11/include/X11/Xmu/EditresP.h
editres.o: /usr/include/stdio.h /usr/include/features.h
editres.o: /usr/include/stdc-predef.h /usr/include/libio.h
editres.o: /usr/include/_G_config.h /usr/include/wchar.h
editres.o: /usr/include/X11/Intrinsic.h /usr/include/X11/Xlib.h
editres.o: /usr/include/X11/X.h /usr/include/X11/Xfuncproto.h
editres.o: /usr/include/X11/Xosdefs.h /usr/include/X11/Xutil.h
editres.o: /usr/include/X11/keysym.h /usr/include/X11/keysymdef.h
editres.o: /usr/include/X11/Xresource.h /usr/include/string.h
editres.o: /usr/include/xlocale.h /usr/include/X11/Core.h
editres.o: /usr/include/X11/Composite.h /usr/include/X11/Constraint.h
editres.o: /usr/include/X11/Object.h /usr/include/X11/RectObj.h
editres.o: /usr/include/X11/StringDefs.h
editres.o: /home/lxb/lxb/oldX11/include/X11/Xaw/Cardinals.h editresP.h
editres.o: /home/lxb/lxb/oldX11/include/X11/Xmu/EditresP.h
geometry.o: /usr/include/X11/Intrinsic.h /usr/include/X11/Xlib.h
geometry.o: /usr/include/X11/X.h /usr/include/X11/Xfuncproto.h
geometry.o: /usr/include/X11/Xosdefs.h /usr/include/X11/Xutil.h
geometry.o: /usr/include/X11/keysym.h /usr/include/X11/keysymdef.h
geometry.o: /usr/include/X11/Xresource.h /usr/include/string.h
geometry.o: /usr/include/features.h /usr/include/stdc-predef.h
geometry.o: /usr/include/xlocale.h /usr/include/X11/Core.h
geometry.o: /usr/include/X11/Composite.h /usr/include/X11/Constraint.h
geometry.o: /usr/include/X11/Object.h /usr/include/X11/RectObj.h
geometry.o: /usr/include/X11/StringDefs.h /usr/include/X11/Shell.h
geometry.o: /usr/include/X11/SM/SMlib.h /usr/include/X11/SM/SM.h
geometry.o: /usr/include/X11/ICE/ICElib.h /usr/include/X11/ICE/ICE.h
geometry.o: /usr/include/stdio.h /usr/include/libio.h
geometry.o: /usr/include/_G_config.h /usr/include/wchar.h
geometry.o: /home/lxb/lxb/oldX11/include/X11/Xaw/Cardinals.h editresP.h
geometry.o: /home/lxb/lxb/oldX11/include/X11/Xmu/EditresP.h
handler.o: /usr/include/X11/Intrinsic.h /usr/include/X11/Xlib.h
handler.o: /usr/include/X11/X.h /usr/include/X11/Xfuncproto.h
handler.o: /usr/include/X11/Xosdefs.h /usr/include/X11/Xutil.h
handler.o: /usr/include/X11/keysym.h /usr/include/X11/keysymdef.h
handler.o: /usr/include/X11/Xresource.h /usr/include/string.h
handler.o: /usr/include/features.h /usr/include/stdc-predef.h
handler.o: /usr/include/xlocale.h /usr/include/X11/Core.h
handler.o: /usr/include/X11/Composite.h /usr/include/X11/Constraint.h
handler.o: /usr/include/X11/Object.h /usr/include/X11/RectObj.h
handler.o: /usr/include/X11/StringDefs.h
handler.o: /home/lxb/lxb/oldX11/include/X11/Xaw/Cardinals.h
handler.o: /home/lxb/lxb/oldX11/include/X11/Xaw/List.h
handler.o: /home/lxb/lxb/oldX11/include/X11/Xaw/Simple.h
handler.o: /home/lxb/lxb/oldX11/include/X11/Xmu/Converters.h
handler.o: /home/lxb/lxb/oldX11/include/X11/Xaw/Panner.h
handler.o: /home/lxb/lxb/oldX11/include/X11/Xaw/Reports.h
handler.o: /home/lxb/lxb/oldX11/include/X11/Xaw/Toggle.h
handler.o: /home/lxb/lxb/oldX11/include/X11/Xaw/Command.h
handler.o: /home/lxb/lxb/oldX11/include/X11/Xaw/Label.h
handler.o: /usr/include/X11/Xfuncs.h /usr/include/X11/Xos.h
handler.o: /usr/include/fcntl.h /usr/include/time.h /usr/include/unistd.h
handler.o: /usr/include/getopt.h /usr/include/X11/Xarch.h
handler.o: /usr/include/stdio.h /usr/include/libio.h /usr/include/_G_config.h
handler.o: /usr/include/wchar.h editresP.h
handler.o: /home/lxb/lxb/oldX11/include/X11/Xmu/EditresP.h
setvalues.o: /usr/include/X11/Intrinsic.h /usr/include/X11/Xlib.h
setvalues.o: /usr/include/X11/X.h /usr/include/X11/Xfuncproto.h
setvalues.o: /usr/include/X11/Xosdefs.h /usr/include/X11/Xutil.h
setvalues.o: /usr/include/X11/keysym.h /usr/include/X11/keysymdef.h
setvalues.o: /usr/include/X11/Xresource.h /usr/include/string.h
setvalues.o: /usr/include/features.h /usr/include/stdc-predef.h
setvalues.o: /usr/include/xlocale.h /usr/include/X11/Core.h
setvalues.o: /usr/include/X11/Composite.h /usr/include/X11/Constraint.h
setvalues.o: /usr/include/X11/Object.h /usr/include/X11/RectObj.h
setvalues.o: /usr/include/X11/StringDefs.h /usr/include/stdio.h
setvalues.o: /usr/include/libio.h /usr/include/_G_config.h
setvalues.o: /usr/include/wchar.h
setvalues.o: /home/lxb/lxb/oldX11/include/X11/Xaw/AsciiText.h
setvalues.o: /home/lxb/lxb/oldX11/include/X11/Xaw/Text.h
setvalues.o: /home/lxb/lxb/oldX11/include/X11/Xaw/Simple.h
setvalues.o: /home/lxb/lxb/oldX11/include/X11/Xmu/Converters.h
setvalues.o: /home/lxb/lxb/oldX11/include/X11/Xaw/TextSink.h
setvalues.o: /home/lxb/lxb/oldX11/include/X11/Xaw/TextSrc.h
setvalues.o: /home/lxb/lxb/oldX11/include/X11/Xaw/AsciiSrc.h
setvalues.o: /home/lxb/lxb/oldX11/include/X11/Xaw/AsciiSink.h
setvalues.o: /home/lxb/lxb/oldX11/include/X11/Xaw/MultiSrc.h
setvalues.o: /home/lxb/lxb/oldX11/include/X11/Xaw/Cardinals.h
setvalues.o: /usr/include/X11/Xfuncs.h /usr/include/X11/Xos.h
setvalues.o: /usr/include/fcntl.h /usr/include/time.h /usr/include/unistd.h
setvalues.o: /usr/include/getopt.h /usr/include/X11/Xarch.h editresP.h
setvalues.o: /home/lxb/lxb/oldX11/include/X11/Xmu/EditresP.h
svpopup.o: /usr/include/X11/Intrinsic.h /usr/include/X11/Xlib.h
svpopup.o: /usr/include/X11/X.h /usr/include/X11/Xfuncproto.h
svpopup.o: /usr/include/X11/Xosdefs.h /usr/include/X11/Xutil.h
svpopup.o: /usr/include/X11/keysym.h /usr/include/X11/keysymdef.h
svpopup.o: /usr/include/X11/Xresource.h /usr/include/string.h
svpopup.o: /usr/include/features.h /usr/include/stdc-predef.h
svpopup.o: /usr/include/xlocale.h /usr/include/X11/Core.h
svpopup.o: /usr/include/X11/Composite.h /usr/include/X11/Constraint.h
svpopup.o: /usr/include/X11/Object.h /usr/include/X11/RectObj.h
svpopup.o: /usr/include/X11/StringDefs.h /usr/include/X11/Xatom.h
svpopup.o: /usr/include/X11/cursorfont.h /usr/include/X11/Shell.h
svpopup.o: /usr/include/X11/SM/SMlib.h /usr/include/X11/SM/SM.h
svpopup.o: /usr/include/X11/ICE/ICElib.h /usr/include/X11/ICE/ICE.h
svpopup.o: editresP.h /home/lxb/lxb/oldX11/include/X11/Xmu/EditresP.h
svpopup.o: /home/lxb/lxb/oldX11/include/X11/Xaw/AsciiText.h
svpopup.o: /home/lxb/lxb/oldX11/include/X11/Xaw/Text.h
svpopup.o: /home/lxb/lxb/oldX11/include/X11/Xaw/Simple.h
svpopup.o: /home/lxb/lxb/oldX11/include/X11/Xmu/Converters.h
svpopup.o: /home/lxb/lxb/oldX11/include/X11/Xaw/TextSink.h
svpopup.o: /home/lxb/lxb/oldX11/include/X11/Xaw/TextSrc.h
svpopup.o: /home/lxb/lxb/oldX11/include/X11/Xaw/AsciiSrc.h
svpopup.o: /home/lxb/lxb/oldX11/include/X11/Xaw/AsciiSink.h
svpopup.o: /home/lxb/lxb/oldX11/include/X11/Xaw/MultiSrc.h
svpopup.o: /home/lxb/lxb/oldX11/include/X11/Xaw/Cardinals.h
svpopup.o: /home/lxb/lxb/oldX11/include/X11/Xaw/Command.h
svpopup.o: /home/lxb/lxb/oldX11/include/X11/Xaw/Label.h
svpopup.o: /home/lxb/lxb/oldX11/include/X11/Xaw/Form.h /usr/include/stdio.h
svpopup.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
utils.o: /usr/include/X11/Intrinsic.h /usr/include/X11/Xlib.h
utils.o: /usr/include/X11/X.h /usr/include/X11/Xfuncproto.h
utils.o: /usr/include/X11/Xosdefs.h /usr/include/X11/Xutil.h
utils.o: /usr/include/X11/keysym.h /usr/include/X11/keysymdef.h
utils.o: /usr/include/X11/Xresource.h /usr/include/string.h
utils.o: /usr/include/features.h /usr/include/stdc-predef.h
utils.o: /usr/include/xlocale.h /usr/include/X11/Core.h
utils.o: /usr/include/X11/Composite.h /usr/include/X11/Constraint.h
utils.o: /usr/include/X11/Object.h /usr/include/X11/RectObj.h
utils.o: /usr/include/X11/Xos.h /usr/include/fcntl.h /usr/include/time.h
utils.o: /usr/include/unistd.h /usr/include/getopt.h /usr/include/X11/Xarch.h
utils.o: /usr/include/X11/Shell.h /usr/include/X11/SM/SMlib.h
utils.o: /usr/include/X11/SM/SM.h /usr/include/X11/ICE/ICElib.h
utils.o: /usr/include/X11/ICE/ICE.h /usr/include/X11/StringDefs.h
utils.o: /home/lxb/lxb/oldX11/include/X11/Xaw/Cardinals.h
utils.o: /home/lxb/lxb/oldX11/include/X11/Xaw/Dialog.h
utils.o: /home/lxb/lxb/oldX11/include/X11/Xaw/Form.h /usr/include/stdio.h
utils.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
utils.o: editresP.h /home/lxb/lxb/oldX11/include/X11/Xmu/EditresP.h
widgets.o: /usr/include/stdio.h /usr/include/features.h
widgets.o: /usr/include/stdc-predef.h /usr/include/libio.h
widgets.o: /usr/include/_G_config.h /usr/include/wchar.h
widgets.o: /usr/include/X11/Intrinsic.h /usr/include/X11/Xlib.h
widgets.o: /usr/include/X11/X.h /usr/include/X11/Xfuncproto.h
widgets.o: /usr/include/X11/Xosdefs.h /usr/include/X11/Xutil.h
widgets.o: /usr/include/X11/keysym.h /usr/include/X11/keysymdef.h
widgets.o: /usr/include/X11/Xresource.h /usr/include/string.h
widgets.o: /usr/include/xlocale.h /usr/include/X11/Core.h
widgets.o: /usr/include/X11/Composite.h /usr/include/X11/Constraint.h
widgets.o: /usr/include/X11/Object.h /usr/include/X11/RectObj.h
widgets.o: /usr/include/X11/StringDefs.h
widgets.o: /home/lxb/lxb/oldX11/include/X11/Xaw/AsciiText.h
widgets.o: /home/lxb/lxb/oldX11/include/X11/Xaw/Text.h
widgets.o: /home/lxb/lxb/oldX11/include/X11/Xaw/Simple.h
widgets.o: /home/lxb/lxb/oldX11/include/X11/Xmu/Converters.h
widgets.o: /home/lxb/lxb/oldX11/include/X11/Xaw/TextSink.h
widgets.o: /home/lxb/lxb/oldX11/include/X11/Xaw/TextSrc.h
widgets.o: /home/lxb/lxb/oldX11/include/X11/Xaw/AsciiSrc.h
widgets.o: /home/lxb/lxb/oldX11/include/X11/Xaw/AsciiSink.h
widgets.o: /home/lxb/lxb/oldX11/include/X11/Xaw/MultiSrc.h
widgets.o: /home/lxb/lxb/oldX11/include/X11/Xaw/Box.h
widgets.o: /home/lxb/lxb/oldX11/include/X11/Xaw/Cardinals.h
widgets.o: /home/lxb/lxb/oldX11/include/X11/Xaw/Label.h
widgets.o: /home/lxb/lxb/oldX11/include/X11/Xaw/List.h
widgets.o: /home/lxb/lxb/oldX11/include/X11/Xaw/MenuButton.h
widgets.o: /home/lxb/lxb/oldX11/include/X11/Xaw/Command.h
widgets.o: /home/lxb/lxb/oldX11/include/X11/Xaw/Paned.h
widgets.o: /home/lxb/lxb/oldX11/include/X11/Xaw/Panner.h
widgets.o: /home/lxb/lxb/oldX11/include/X11/Xaw/Reports.h
widgets.o: /home/lxb/lxb/oldX11/include/X11/Xaw/Porthole.h
widgets.o: /home/lxb/lxb/oldX11/include/X11/Xaw/SmeBSB.h
widgets.o: /home/lxb/lxb/oldX11/include/X11/Xaw/Sme.h
widgets.o: /home/lxb/lxb/oldX11/include/X11/Xaw/SmeLine.h
widgets.o: /home/lxb/lxb/oldX11/include/X11/Xaw/SimpleMenu.h
widgets.o: /usr/include/X11/Shell.h /usr/include/X11/SM/SMlib.h
widgets.o: /usr/include/X11/SM/SM.h /usr/include/X11/ICE/ICElib.h
widgets.o: /usr/include/X11/ICE/ICE.h
widgets.o: /home/lxb/lxb/oldX11/include/X11/Xaw/Toggle.h
widgets.o: /home/lxb/lxb/oldX11/include/X11/Xaw/Tree.h
widgets.o: /home/lxb/lxb/oldX11/include/X11/Xaw/Viewport.h
widgets.o: /home/lxb/lxb/oldX11/include/X11/Xaw/Form.h editresP.h
widgets.o: /home/lxb/lxb/oldX11/include/X11/Xmu/EditresP.h
wtree.o: /usr/include/stdio.h /usr/include/features.h
wtree.o: /usr/include/stdc-predef.h /usr/include/libio.h
wtree.o: /usr/include/_G_config.h /usr/include/wchar.h
wtree.o: /usr/include/X11/Intrinsic.h /usr/include/X11/Xlib.h
wtree.o: /usr/include/X11/X.h /usr/include/X11/Xfuncproto.h
wtree.o: /usr/include/X11/Xosdefs.h /usr/include/X11/Xutil.h
wtree.o: /usr/include/X11/keysym.h /usr/include/X11/keysymdef.h
wtree.o: /usr/include/X11/Xresource.h /usr/include/string.h
wtree.o: /usr/include/xlocale.h /usr/include/X11/Core.h
wtree.o: /usr/include/X11/Composite.h /usr/include/X11/Constraint.h
wtree.o: /usr/include/X11/Object.h /usr/include/X11/RectObj.h
wtree.o: /usr/include/X11/StringDefs.h
wtree.o: /home/lxb/lxb/oldX11/include/X11/Xaw/Cardinals.h
wtree.o: /home/lxb/lxb/oldX11/include/X11/Xaw/Toggle.h
wtree.o: /home/lxb/lxb/oldX11/include/X11/Xaw/Command.h
wtree.o: /home/lxb/lxb/oldX11/include/X11/Xaw/Label.h
wtree.o: /home/lxb/lxb/oldX11/include/X11/Xaw/Simple.h
wtree.o: /home/lxb/lxb/oldX11/include/X11/Xmu/Converters.h
wtree.o: /home/lxb/lxb/oldX11/include/X11/Xaw/Viewport.h
wtree.o: /home/lxb/lxb/oldX11/include/X11/Xaw/Form.h
wtree.o: /home/lxb/lxb/oldX11/include/X11/Xaw/Reports.h
wtree.o: /home/lxb/lxb/oldX11/include/X11/Xaw/Tree.h editresP.h
wtree.o: /home/lxb/lxb/oldX11/include/X11/Xmu/EditresP.h
