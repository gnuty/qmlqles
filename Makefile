#############################################################################
# Makefile for building: qmlgles
# Generated by qmake (2.01a) (Qt 5.0.0) on: Thu May 24 23:20:12 2012
# Project:  qmlgles.pro
# Template: app
# Command: /home/gnuty/dev/external/qt5/qtbase/bin/qmake -spec ../external/qt5/qtbase/mkspecs/linux-g++-32 CONFIG+=declarative_debug -o Makefile qmlgles.pro
#############################################################################

####### Compiler, tools and options

CC            = gcc
CXX           = g++
DEFINES       = -DQT_DECLARATIVE_DEBUG -DQT_DECLARATIVE_LIB -DQT_OPENGL_LIB -DQT_GUI_LIB -DQT_CORE_LIB -DQT_SHARED
CFLAGS        = -m32 -pipe -g -Wall -W -D_REENTRANT $(DEFINES)
CXXFLAGS      = -m32 -pipe -g -Wall -W -D_REENTRANT $(DEFINES)
INCPATH       = -I../external/qt5/qtbase/mkspecs/linux-g++-32 -I. -I../external/qt5/qtbase/include/QtCore -I../external/qt5/qtbase/include/QtGui -I../external/qt5/qtbase/include/QtOpenGL -I../external/qt5/qtdeclarative/include -I../external/qt5/qtdeclarative/include/QtDeclarative -I../external/qt5/qtbase/include -Iqmlapplicationviewer -I../external/qt5/qtbase/include/QtNetwork -I../external/qt5/qtxmlpatterns/include -I../external/qt5/qtxmlpatterns/include/QtXmlPatterns -I../external/qt5/qtbase/include/QtWidgets -I/usr/X11R6/include -I.
LINK          = g++
LFLAGS        = -m32 -Wl,-rpath,/home/gnuty/dev/external/qt5/qtbase/lib
LIBS          = $(SUBLIBS)  -L/home/gnuty/dev/external/qt5/qtbase/lib -L/usr/X11R6/lib -lQtDeclarative -L/home/gnuty/dev/external/qt5/qtbase/lib -L/usr/X11R6/lib -lQtSql -lQtNetwork -lQtV8 -lQtOpenGL -lQtWidgets -lQtGui -lQtCore -lGL -lpthread 
AR            = ar cqs
RANLIB        = 
QMAKE         = /home/gnuty/dev/external/qt5/qtbase/bin/qmake
TAR           = tar -cf
COMPRESS      = gzip -9f
COPY          = cp -f
SED           = sed
COPY_FILE     = $(COPY)
COPY_DIR      = $(COPY) -r
STRIP         = strip
INSTALL_FILE  = install -m 644 -p
INSTALL_DIR   = $(COPY_DIR)
INSTALL_PROGRAM = install -m 755 -p
DEL_FILE      = rm -f
SYMLINK       = ln -f -s
DEL_DIR       = rmdir
MOVE          = mv -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p

####### Output directory

OBJECTS_DIR   = ./

####### Files

SOURCES       = src/main.cpp \
		src/glitem.cpp \
		src/shaderdebugger.cpp \
		src/glesrenderer.cpp \
		src/glcolorrgba.cpp \
		src/glpoint.cpp \
		src/glesbody.cpp \
		src/glescube.cpp \
		src/glesglobe.cpp \
		src/examplescene.cpp \
		qmlapplicationviewer/qmlapplicationviewer.cpp moc_glitem.cpp \
		moc_glesrenderer.cpp \
		moc_examplescene.cpp \
		moc_qmlapplicationviewer.cpp \
		qrc_resources.cpp
OBJECTS       = main.o \
		glitem.o \
		shaderdebugger.o \
		glesrenderer.o \
		glcolorrgba.o \
		glpoint.o \
		glesbody.o \
		glescube.o \
		glesglobe.o \
		examplescene.o \
		qmlapplicationviewer.o \
		moc_glitem.o \
		moc_glesrenderer.o \
		moc_examplescene.o \
		moc_qmlapplicationviewer.o \
		qrc_resources.o
DIST          = ../external/qt5/qtbase/mkspecs/common/unix.conf \
		../external/qt5/qtbase/mkspecs/common/linux.conf \
		../external/qt5/qtbase/mkspecs/common/gcc-base.conf \
		../external/qt5/qtbase/mkspecs/common/gcc-base-unix.conf \
		../external/qt5/qtbase/mkspecs/common/g++-base.conf \
		../external/qt5/qtbase/mkspecs/common/g++-unix.conf \
		../external/qt5/qtbase/mkspecs/qconfig.pri \
		../external/qt5/qttools/modules/qt_clucene.pri \
		../external/qt5/qtbase/mkspecs/modules/qt_clucene.pri \
		../external/qt5/qtbase/src/modules/qt_core.pri \
		../external/qt5/qtbase/mkspecs/modules/qt_core.pri \
		../external/qt5/qtbase/src/modules/qt_dbus.pri \
		../external/qt5/qtbase/mkspecs/modules/qt_dbus.pri \
		../external/qt5/qtdeclarative/modules/qt_declarative.pri \
		../external/qt5/qtbase/mkspecs/modules/qt_declarative.pri \
		../external/qt5/qttools/modules/qt_designer.pri \
		../external/qt5/qtbase/mkspecs/modules/qt_designer.pri \
		../external/qt5/qttools/modules/qt_designercomponents.pri \
		../external/qt5/qtbase/mkspecs/modules/qt_designercomponents.pri \
		../external/qt5/qtbase/src/modules/qt_gui.pri \
		../external/qt5/qtbase/mkspecs/modules/qt_gui.pri \
		../external/qt5/qttools/modules/qt_help.pri \
		../external/qt5/qtbase/mkspecs/modules/qt_help.pri \
		../external/qt5/qtbase/src/modules/qt_network.pri \
		../external/qt5/qtbase/mkspecs/modules/qt_network.pri \
		../external/qt5/qtbase/src/modules/qt_opengl.pri \
		../external/qt5/qtbase/mkspecs/modules/qt_opengl.pri \
		../external/qt5/qtphonon/modules/qt_phonon.pri \
		../external/qt5/qtbase/mkspecs/modules/qt_phonon.pri \
		../external/qt5/qtbase/src/modules/qt_platformsupport.pri \
		../external/qt5/qtbase/mkspecs/modules/qt_platformsupport.pri \
		../external/qt5/qtbase/src/modules/qt_printsupport.pri \
		../external/qt5/qtbase/mkspecs/modules/qt_printsupport.pri \
		../external/qt5/qtdeclarative/modules/qt_qmldevtools.pri \
		../external/qt5/qtbase/mkspecs/modules/qt_qmldevtools.pri \
		../external/qt5/qtdeclarative/modules/qt_qmltest.pri \
		../external/qt5/qtbase/mkspecs/modules/qt_qmltest.pri \
		../external/qt5/qtdeclarative/modules/qt_qtquick1.pri \
		../external/qt5/qtbase/mkspecs/modules/qt_qtquick1.pri \
		../external/qt5/qtdeclarative/modules/qt_quick.pri \
		../external/qt5/qtbase/mkspecs/modules/qt_quick.pri \
		../external/qt5/qtscript/modules/qt_script.pri \
		../external/qt5/qtbase/mkspecs/modules/qt_script.pri \
		../external/qt5/qtscript/modules/qt_scripttools.pri \
		../external/qt5/qtbase/mkspecs/modules/qt_scripttools.pri \
		../external/qt5/qtbase/src/modules/qt_sql.pri \
		../external/qt5/qtbase/mkspecs/modules/qt_sql.pri \
		../external/qt5/qtsvg/modules/qt_svg.pri \
		../external/qt5/qtbase/mkspecs/modules/qt_svg.pri \
		../external/qt5/qtbase/src/modules/qt_testlib.pri \
		../external/qt5/qtbase/mkspecs/modules/qt_testlib.pri \
		../external/qt5/qttools/modules/qt_uitools.pri \
		../external/qt5/qtbase/mkspecs/modules/qt_uitools.pri \
		../external/qt5/qtjsbackend/src/modules/qt_v8.pri \
		../external/qt5/qtbase/mkspecs/modules/qt_v8.pri \
		../external/qt5/qtbase/src/modules/qt_widgets.pri \
		../external/qt5/qtbase/mkspecs/modules/qt_widgets.pri \
		../external/qt5/qtbase/src/modules/qt_xml.pri \
		../external/qt5/qtbase/mkspecs/modules/qt_xml.pri \
		../external/qt5/qtxmlpatterns/modules/qt_xmlpatterns.pri \
		../external/qt5/qtbase/mkspecs/modules/qt_xmlpatterns.pri \
		../external/qt5/qtbase/mkspecs/features/qt_functions.prf \
		../external/qt5/qtbase/mkspecs/features/qt_config.prf \
		../external/qt5/qtbase/mkspecs/features/exclusive_builds.prf \
		../external/qt5/qtbase/mkspecs/features/default_pre.prf \
		../external/qt5/qtbase/mkspecs/features/unix/default_pre.prf \
		qmlapplicationviewer/qmlapplicationviewer.pri \
		../external/qt5/qtbase/mkspecs/features/debug.prf \
		../external/qt5/qtbase/mkspecs/features/default_post.prf \
		../external/qt5/qtbase/mkspecs/features/declarative_debug.prf \
		../external/qt5/qtbase/mkspecs/features/unix/gdb_dwarf_index.prf \
		../external/qt5/qtbase/mkspecs/features/warn_on.prf \
		../external/qt5/qtbase/mkspecs/features/qt.prf \
		../external/qt5/qtbase/mkspecs/features/unix/opengl.prf \
		../external/qt5/qtbase/mkspecs/features/unix/thread.prf \
		../external/qt5/qtbase/mkspecs/features/moc.prf \
		../external/qt5/qtbase/mkspecs/features/wayland-scanner.prf \
		../external/qt5/qtbase/mkspecs/features/resources.prf \
		../external/qt5/qtbase/mkspecs/features/uic.prf \
		../external/qt5/qtbase/mkspecs/features/yacc.prf \
		../external/qt5/qtbase/mkspecs/features/lex.prf \
		../external/qt5/qtbase/mkspecs/features/include_source_dir.prf \
		resources.qrc \
		qmlgles.pro
QMAKE_TARGET  = qmlgles
DESTDIR       = 
TARGET        = qmlgles


first: all
####### Implicit rules

.SUFFIXES: .o .c .cpp .cc .cxx .C

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cc.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cxx.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.C.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.c.o:
	$(CC) -c $(CFLAGS) $(INCPATH) -o "$@" "$<"

####### Build rules

all: Makefile $(TARGET)

$(TARGET):  $(OBJECTS)  
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJCOMP) $(LIBS)
	{ test -z "$(DESTDIR)" || cd "$(DESTDIR)"; } && test $$(gdb --version | sed -e 's,[^0-9]\+\([0-9]\)\.\([0-9]\).*,\1\2,;q') -gt 72 && gdb --nx --batch --quiet -ex 'set confirm off' -ex 'save gdb-index .' -ex quit '$(TARGET)' && test -f $(TARGET).gdb-index && objcopy --add-section '.gdb_index=$(TARGET).gdb-index' --set-section-flags '.gdb_index=readonly' '$(TARGET)' '$(TARGET)' && rm -f $(TARGET).gdb-index || true

Makefile: qmlgles.pro  ../external/qt5/qtbase/mkspecs/linux-g++-32/qmake.conf ../external/qt5/qtbase/mkspecs/common/unix.conf \
		../external/qt5/qtbase/mkspecs/common/linux.conf \
		../external/qt5/qtbase/mkspecs/common/gcc-base.conf \
		../external/qt5/qtbase/mkspecs/common/gcc-base-unix.conf \
		../external/qt5/qtbase/mkspecs/common/g++-base.conf \
		../external/qt5/qtbase/mkspecs/common/g++-unix.conf \
		../external/qt5/qtbase/mkspecs/qconfig.pri \
		../external/qt5/qttools/modules/qt_clucene.pri \
		../external/qt5/qtbase/mkspecs/modules/qt_clucene.pri \
		../external/qt5/qtbase/src/modules/qt_core.pri \
		../external/qt5/qtbase/mkspecs/modules/qt_core.pri \
		../external/qt5/qtbase/src/modules/qt_dbus.pri \
		../external/qt5/qtbase/mkspecs/modules/qt_dbus.pri \
		../external/qt5/qtdeclarative/modules/qt_declarative.pri \
		../external/qt5/qtbase/mkspecs/modules/qt_declarative.pri \
		../external/qt5/qttools/modules/qt_designer.pri \
		../external/qt5/qtbase/mkspecs/modules/qt_designer.pri \
		../external/qt5/qttools/modules/qt_designercomponents.pri \
		../external/qt5/qtbase/mkspecs/modules/qt_designercomponents.pri \
		../external/qt5/qtbase/src/modules/qt_gui.pri \
		../external/qt5/qtbase/mkspecs/modules/qt_gui.pri \
		../external/qt5/qttools/modules/qt_help.pri \
		../external/qt5/qtbase/mkspecs/modules/qt_help.pri \
		../external/qt5/qtbase/src/modules/qt_network.pri \
		../external/qt5/qtbase/mkspecs/modules/qt_network.pri \
		../external/qt5/qtbase/src/modules/qt_opengl.pri \
		../external/qt5/qtbase/mkspecs/modules/qt_opengl.pri \
		../external/qt5/qtphonon/modules/qt_phonon.pri \
		../external/qt5/qtbase/mkspecs/modules/qt_phonon.pri \
		../external/qt5/qtbase/src/modules/qt_platformsupport.pri \
		../external/qt5/qtbase/mkspecs/modules/qt_platformsupport.pri \
		../external/qt5/qtbase/src/modules/qt_printsupport.pri \
		../external/qt5/qtbase/mkspecs/modules/qt_printsupport.pri \
		../external/qt5/qtdeclarative/modules/qt_qmldevtools.pri \
		../external/qt5/qtbase/mkspecs/modules/qt_qmldevtools.pri \
		../external/qt5/qtdeclarative/modules/qt_qmltest.pri \
		../external/qt5/qtbase/mkspecs/modules/qt_qmltest.pri \
		../external/qt5/qtdeclarative/modules/qt_qtquick1.pri \
		../external/qt5/qtbase/mkspecs/modules/qt_qtquick1.pri \
		../external/qt5/qtdeclarative/modules/qt_quick.pri \
		../external/qt5/qtbase/mkspecs/modules/qt_quick.pri \
		../external/qt5/qtscript/modules/qt_script.pri \
		../external/qt5/qtbase/mkspecs/modules/qt_script.pri \
		../external/qt5/qtscript/modules/qt_scripttools.pri \
		../external/qt5/qtbase/mkspecs/modules/qt_scripttools.pri \
		../external/qt5/qtbase/src/modules/qt_sql.pri \
		../external/qt5/qtbase/mkspecs/modules/qt_sql.pri \
		../external/qt5/qtsvg/modules/qt_svg.pri \
		../external/qt5/qtbase/mkspecs/modules/qt_svg.pri \
		../external/qt5/qtbase/src/modules/qt_testlib.pri \
		../external/qt5/qtbase/mkspecs/modules/qt_testlib.pri \
		../external/qt5/qttools/modules/qt_uitools.pri \
		../external/qt5/qtbase/mkspecs/modules/qt_uitools.pri \
		../external/qt5/qtjsbackend/src/modules/qt_v8.pri \
		../external/qt5/qtbase/mkspecs/modules/qt_v8.pri \
		../external/qt5/qtbase/src/modules/qt_widgets.pri \
		../external/qt5/qtbase/mkspecs/modules/qt_widgets.pri \
		../external/qt5/qtbase/src/modules/qt_xml.pri \
		../external/qt5/qtbase/mkspecs/modules/qt_xml.pri \
		../external/qt5/qtxmlpatterns/modules/qt_xmlpatterns.pri \
		../external/qt5/qtbase/mkspecs/modules/qt_xmlpatterns.pri \
		../external/qt5/qtbase/mkspecs/features/qt_functions.prf \
		../external/qt5/qtbase/mkspecs/features/qt_config.prf \
		../external/qt5/qtbase/mkspecs/features/exclusive_builds.prf \
		../external/qt5/qtbase/mkspecs/features/default_pre.prf \
		../external/qt5/qtbase/mkspecs/features/unix/default_pre.prf \
		qmlapplicationviewer/qmlapplicationviewer.pri \
		../external/qt5/qtbase/mkspecs/features/debug.prf \
		../external/qt5/qtbase/mkspecs/features/default_post.prf \
		../external/qt5/qtbase/mkspecs/features/declarative_debug.prf \
		../external/qt5/qtbase/mkspecs/features/unix/gdb_dwarf_index.prf \
		../external/qt5/qtbase/mkspecs/features/warn_on.prf \
		../external/qt5/qtbase/mkspecs/features/qt.prf \
		../external/qt5/qtbase/mkspecs/features/unix/opengl.prf \
		../external/qt5/qtbase/mkspecs/features/unix/thread.prf \
		../external/qt5/qtbase/mkspecs/features/moc.prf \
		../external/qt5/qtbase/mkspecs/features/wayland-scanner.prf \
		../external/qt5/qtbase/mkspecs/features/resources.prf \
		../external/qt5/qtbase/mkspecs/features/uic.prf \
		../external/qt5/qtbase/mkspecs/features/yacc.prf \
		../external/qt5/qtbase/mkspecs/features/lex.prf \
		../external/qt5/qtbase/mkspecs/features/include_source_dir.prf \
		resources.qrc \
		/home/gnuty/dev/external/qt5/qtbase/lib/libQtDeclarative.prl \
		/home/gnuty/dev/external/qt5/qtbase/lib/libQtSql.prl \
		/home/gnuty/dev/external/qt5/qtbase/lib/libQtCore.prl \
		/home/gnuty/dev/external/qt5/qtbase/lib/libQtNetwork.prl \
		/home/gnuty/dev/external/qt5/qtbase/lib/libQtV8.prl \
		/home/gnuty/dev/external/qt5/qtbase/lib/libQtGui.prl \
		/home/gnuty/dev/external/qt5/qtbase/lib/libQtOpenGL.prl \
		/home/gnuty/dev/external/qt5/qtbase/lib/libQtWidgets.prl
	$(QMAKE) -spec ../external/qt5/qtbase/mkspecs/linux-g++-32 CONFIG+=declarative_debug -o Makefile qmlgles.pro
../external/qt5/qtbase/mkspecs/common/unix.conf:
../external/qt5/qtbase/mkspecs/common/linux.conf:
../external/qt5/qtbase/mkspecs/common/gcc-base.conf:
../external/qt5/qtbase/mkspecs/common/gcc-base-unix.conf:
../external/qt5/qtbase/mkspecs/common/g++-base.conf:
../external/qt5/qtbase/mkspecs/common/g++-unix.conf:
../external/qt5/qtbase/mkspecs/qconfig.pri:
../external/qt5/qttools/modules/qt_clucene.pri:
../external/qt5/qtbase/mkspecs/modules/qt_clucene.pri:
../external/qt5/qtbase/src/modules/qt_core.pri:
../external/qt5/qtbase/mkspecs/modules/qt_core.pri:
../external/qt5/qtbase/src/modules/qt_dbus.pri:
../external/qt5/qtbase/mkspecs/modules/qt_dbus.pri:
../external/qt5/qtdeclarative/modules/qt_declarative.pri:
../external/qt5/qtbase/mkspecs/modules/qt_declarative.pri:
../external/qt5/qttools/modules/qt_designer.pri:
../external/qt5/qtbase/mkspecs/modules/qt_designer.pri:
../external/qt5/qttools/modules/qt_designercomponents.pri:
../external/qt5/qtbase/mkspecs/modules/qt_designercomponents.pri:
../external/qt5/qtbase/src/modules/qt_gui.pri:
../external/qt5/qtbase/mkspecs/modules/qt_gui.pri:
../external/qt5/qttools/modules/qt_help.pri:
../external/qt5/qtbase/mkspecs/modules/qt_help.pri:
../external/qt5/qtbase/src/modules/qt_network.pri:
../external/qt5/qtbase/mkspecs/modules/qt_network.pri:
../external/qt5/qtbase/src/modules/qt_opengl.pri:
../external/qt5/qtbase/mkspecs/modules/qt_opengl.pri:
../external/qt5/qtphonon/modules/qt_phonon.pri:
../external/qt5/qtbase/mkspecs/modules/qt_phonon.pri:
../external/qt5/qtbase/src/modules/qt_platformsupport.pri:
../external/qt5/qtbase/mkspecs/modules/qt_platformsupport.pri:
../external/qt5/qtbase/src/modules/qt_printsupport.pri:
../external/qt5/qtbase/mkspecs/modules/qt_printsupport.pri:
../external/qt5/qtdeclarative/modules/qt_qmldevtools.pri:
../external/qt5/qtbase/mkspecs/modules/qt_qmldevtools.pri:
../external/qt5/qtdeclarative/modules/qt_qmltest.pri:
../external/qt5/qtbase/mkspecs/modules/qt_qmltest.pri:
../external/qt5/qtdeclarative/modules/qt_qtquick1.pri:
../external/qt5/qtbase/mkspecs/modules/qt_qtquick1.pri:
../external/qt5/qtdeclarative/modules/qt_quick.pri:
../external/qt5/qtbase/mkspecs/modules/qt_quick.pri:
../external/qt5/qtscript/modules/qt_script.pri:
../external/qt5/qtbase/mkspecs/modules/qt_script.pri:
../external/qt5/qtscript/modules/qt_scripttools.pri:
../external/qt5/qtbase/mkspecs/modules/qt_scripttools.pri:
../external/qt5/qtbase/src/modules/qt_sql.pri:
../external/qt5/qtbase/mkspecs/modules/qt_sql.pri:
../external/qt5/qtsvg/modules/qt_svg.pri:
../external/qt5/qtbase/mkspecs/modules/qt_svg.pri:
../external/qt5/qtbase/src/modules/qt_testlib.pri:
../external/qt5/qtbase/mkspecs/modules/qt_testlib.pri:
../external/qt5/qttools/modules/qt_uitools.pri:
../external/qt5/qtbase/mkspecs/modules/qt_uitools.pri:
../external/qt5/qtjsbackend/src/modules/qt_v8.pri:
../external/qt5/qtbase/mkspecs/modules/qt_v8.pri:
../external/qt5/qtbase/src/modules/qt_widgets.pri:
../external/qt5/qtbase/mkspecs/modules/qt_widgets.pri:
../external/qt5/qtbase/src/modules/qt_xml.pri:
../external/qt5/qtbase/mkspecs/modules/qt_xml.pri:
../external/qt5/qtxmlpatterns/modules/qt_xmlpatterns.pri:
../external/qt5/qtbase/mkspecs/modules/qt_xmlpatterns.pri:
../external/qt5/qtbase/mkspecs/features/qt_functions.prf:
../external/qt5/qtbase/mkspecs/features/qt_config.prf:
../external/qt5/qtbase/mkspecs/features/exclusive_builds.prf:
../external/qt5/qtbase/mkspecs/features/default_pre.prf:
../external/qt5/qtbase/mkspecs/features/unix/default_pre.prf:
qmlapplicationviewer/qmlapplicationviewer.pri:
../external/qt5/qtbase/mkspecs/features/debug.prf:
../external/qt5/qtbase/mkspecs/features/default_post.prf:
../external/qt5/qtbase/mkspecs/features/declarative_debug.prf:
../external/qt5/qtbase/mkspecs/features/unix/gdb_dwarf_index.prf:
../external/qt5/qtbase/mkspecs/features/warn_on.prf:
../external/qt5/qtbase/mkspecs/features/qt.prf:
../external/qt5/qtbase/mkspecs/features/unix/opengl.prf:
../external/qt5/qtbase/mkspecs/features/unix/thread.prf:
../external/qt5/qtbase/mkspecs/features/moc.prf:
../external/qt5/qtbase/mkspecs/features/wayland-scanner.prf:
../external/qt5/qtbase/mkspecs/features/resources.prf:
../external/qt5/qtbase/mkspecs/features/uic.prf:
../external/qt5/qtbase/mkspecs/features/yacc.prf:
../external/qt5/qtbase/mkspecs/features/lex.prf:
../external/qt5/qtbase/mkspecs/features/include_source_dir.prf:
resources.qrc:
/home/gnuty/dev/external/qt5/qtbase/lib/libQtDeclarative.prl:
/home/gnuty/dev/external/qt5/qtbase/lib/libQtSql.prl:
/home/gnuty/dev/external/qt5/qtbase/lib/libQtCore.prl:
/home/gnuty/dev/external/qt5/qtbase/lib/libQtNetwork.prl:
/home/gnuty/dev/external/qt5/qtbase/lib/libQtV8.prl:
/home/gnuty/dev/external/qt5/qtbase/lib/libQtGui.prl:
/home/gnuty/dev/external/qt5/qtbase/lib/libQtOpenGL.prl:
/home/gnuty/dev/external/qt5/qtbase/lib/libQtWidgets.prl:
qmake:  FORCE
	@$(QMAKE) -spec ../external/qt5/qtbase/mkspecs/linux-g++-32 CONFIG+=declarative_debug -o Makefile qmlgles.pro

dist: 
	@$(CHK_DIR_EXISTS) .tmp/qmlgles1.0.0 || $(MKDIR) .tmp/qmlgles1.0.0 
	$(COPY_FILE) --parents $(SOURCES) $(DIST) .tmp/qmlgles1.0.0/ && $(COPY_FILE) --parents src/glitem.h src/shaderdebugger.h src/glesrenderer.h src/glcolorrgba.h src/glpoint.h src/glesbody.h src/glescube.h src/glesglobe.h src/gldefines.h src/examplescene.h qmlapplicationviewer/qmlapplicationviewer.h .tmp/qmlgles1.0.0/ && $(COPY_FILE) --parents resources.qrc .tmp/qmlgles1.0.0/ && $(COPY_FILE) --parents src/main.cpp src/glitem.cpp src/shaderdebugger.cpp src/glesrenderer.cpp src/glcolorrgba.cpp src/glpoint.cpp src/glesbody.cpp src/glescube.cpp src/glesglobe.cpp src/examplescene.cpp qmlapplicationviewer/qmlapplicationviewer.cpp .tmp/qmlgles1.0.0/ && (cd `dirname .tmp/qmlgles1.0.0` && $(TAR) qmlgles1.0.0.tar qmlgles1.0.0 && $(COMPRESS) qmlgles1.0.0.tar) && $(MOVE) `dirname .tmp/qmlgles1.0.0`/qmlgles1.0.0.tar.gz . && $(DEL_FILE) -r .tmp/qmlgles1.0.0


clean:compiler_clean 
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) *~ core *.core


####### Sub-libraries

distclean: clean
	-$(DEL_FILE) $(TARGET) 
	-$(DEL_FILE) Makefile


check: first

mocclean: compiler_moc_header_clean compiler_moc_source_clean

mocables: compiler_moc_header_make_all compiler_moc_source_make_all

compiler_wayland-server-header_make_all:
compiler_wayland-server-header_clean:
compiler_wayland-client-header_make_all:
compiler_wayland-client-header_clean:
compiler_moc_header_make_all: moc_glitem.cpp moc_glesrenderer.cpp moc_examplescene.cpp moc_qmlapplicationviewer.cpp
compiler_moc_header_clean:
	-$(DEL_FILE) moc_glitem.cpp moc_glesrenderer.cpp moc_examplescene.cpp moc_qmlapplicationviewer.cpp
moc_glitem.cpp: src/glesrenderer.h \
		src/glcolorrgba.h \
		src/gldefines.h \
		src/glitem.h
	/home/gnuty/dev/external/qt5/qtbase/bin/moc $(DEFINES) $(INCPATH) src/glitem.h -o moc_glitem.cpp

moc_glesrenderer.cpp: src/glcolorrgba.h \
		src/gldefines.h \
		src/glesrenderer.h
	/home/gnuty/dev/external/qt5/qtbase/bin/moc $(DEFINES) $(INCPATH) src/glesrenderer.h -o moc_glesrenderer.cpp

moc_examplescene.cpp: src/glitem.h \
		src/glesrenderer.h \
		src/glcolorrgba.h \
		src/gldefines.h \
		src/shaderdebugger.h \
		src/glescube.h \
		src/glesbody.h \
		src/glpoint.h \
		src/glesglobe.h \
		src/examplescene.h
	/home/gnuty/dev/external/qt5/qtbase/bin/moc $(DEFINES) $(INCPATH) src/examplescene.h -o moc_examplescene.cpp

moc_qmlapplicationviewer.cpp: qmlapplicationviewer/qmlapplicationviewer.h
	/home/gnuty/dev/external/qt5/qtbase/bin/moc $(DEFINES) $(INCPATH) qmlapplicationviewer/qmlapplicationviewer.h -o moc_qmlapplicationviewer.cpp

compiler_wayland-code_make_all:
compiler_wayland-code_clean:
compiler_rcc_make_all: qrc_resources.cpp
compiler_rcc_clean:
	-$(DEL_FILE) qrc_resources.cpp
qrc_resources.cpp: resources.qrc \
		src/fshader1.fsh \
		src/vshader1.vsh
	/home/gnuty/dev/external/qt5/qtbase/bin/rcc -name resources resources.qrc -o qrc_resources.cpp

compiler_image_collection_make_all: qmake_image_collection.cpp
compiler_image_collection_clean:
	-$(DEL_FILE) qmake_image_collection.cpp
compiler_moc_source_make_all:
compiler_moc_source_clean:
compiler_uic_make_all:
compiler_uic_clean:
compiler_yacc_decl_make_all:
compiler_yacc_decl_clean:
compiler_yacc_impl_make_all:
compiler_yacc_impl_clean:
compiler_lex_make_all:
compiler_lex_clean:
compiler_clean: compiler_moc_header_clean compiler_rcc_clean 

####### Compile

main.o: src/main.cpp src/examplescene.h \
		src/glitem.h \
		src/glesrenderer.h \
		src/glcolorrgba.h \
		src/gldefines.h \
		src/shaderdebugger.h \
		src/glescube.h \
		src/glesbody.h \
		src/glpoint.h \
		src/glesglobe.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o main.o src/main.cpp

glitem.o: src/glitem.cpp src/glitem.h \
		src/glesrenderer.h \
		src/glcolorrgba.h \
		src/gldefines.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o glitem.o src/glitem.cpp

shaderdebugger.o: src/shaderdebugger.cpp src/shaderdebugger.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o shaderdebugger.o src/shaderdebugger.cpp

glesrenderer.o: src/glesrenderer.cpp src/glesrenderer.h \
		src/glcolorrgba.h \
		src/gldefines.h \
		src/shaderdebugger.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o glesrenderer.o src/glesrenderer.cpp

glcolorrgba.o: src/glcolorrgba.cpp src/glcolorrgba.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o glcolorrgba.o src/glcolorrgba.cpp

glpoint.o: src/glpoint.cpp src/glpoint.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o glpoint.o src/glpoint.cpp

glesbody.o: src/glesbody.cpp src/glesbody.h \
		src/glpoint.h \
		src/glcolorrgba.h \
		src/glesrenderer.h \
		src/gldefines.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o glesbody.o src/glesbody.cpp

glescube.o: src/glescube.cpp src/glescube.h \
		src/glesbody.h \
		src/glpoint.h \
		src/glcolorrgba.h \
		src/glesrenderer.h \
		src/gldefines.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o glescube.o src/glescube.cpp

glesglobe.o: src/glesglobe.cpp src/glesglobe.h \
		src/glesbody.h \
		src/glpoint.h \
		src/glcolorrgba.h \
		src/glesrenderer.h \
		src/gldefines.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o glesglobe.o src/glesglobe.cpp

examplescene.o: src/examplescene.cpp src/examplescene.h \
		src/glitem.h \
		src/glesrenderer.h \
		src/glcolorrgba.h \
		src/gldefines.h \
		src/shaderdebugger.h \
		src/glescube.h \
		src/glesbody.h \
		src/glpoint.h \
		src/glesglobe.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o examplescene.o src/examplescene.cpp

qmlapplicationviewer.o: qmlapplicationviewer/qmlapplicationviewer.cpp qmlapplicationviewer/qmlapplicationviewer.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o qmlapplicationviewer.o qmlapplicationviewer/qmlapplicationviewer.cpp

moc_glitem.o: moc_glitem.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_glitem.o moc_glitem.cpp

moc_glesrenderer.o: moc_glesrenderer.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_glesrenderer.o moc_glesrenderer.cpp

moc_examplescene.o: moc_examplescene.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_examplescene.o moc_examplescene.cpp

moc_qmlapplicationviewer.o: moc_qmlapplicationviewer.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_qmlapplicationviewer.o moc_qmlapplicationviewer.cpp

qrc_resources.o: qrc_resources.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o qrc_resources.o qrc_resources.cpp

####### Install

install_itemfolder_01: first FORCE
	@$(CHK_DIR_EXISTS) $(INSTALL_ROOT)/opt/qmlgles/qml/ || $(MKDIR) $(INSTALL_ROOT)/opt/qmlgles/qml/ 
	-$(INSTALL_DIR) /home/gnuty/dev/qmlgles/qml/qmlgles $(INSTALL_ROOT)/opt/qmlgles/qml/


uninstall_itemfolder_01:  FORCE
	-$(DEL_FILE) -r $(INSTALL_ROOT)/opt/qmlgles/qml/qmlgles
	-$(DEL_DIR) $(INSTALL_ROOT)/opt/qmlgles/qml/ 


install_target: first FORCE
	@$(CHK_DIR_EXISTS) $(INSTALL_ROOT)/opt/qmlgles/bin/ || $(MKDIR) $(INSTALL_ROOT)/opt/qmlgles/bin/ 
	-$(INSTALL_PROGRAM) "$(QMAKE_TARGET)" "$(INSTALL_ROOT)/opt/qmlgles/bin/$(QMAKE_TARGET)"

uninstall_target:  FORCE
	-$(DEL_FILE) "$(INSTALL_ROOT)/opt/qmlgles/bin/$(QMAKE_TARGET)"
	-$(DEL_DIR) $(INSTALL_ROOT)/opt/qmlgles/bin/ 


install:  install_itemfolder_01 install_target  FORCE

uninstall: uninstall_itemfolder_01 uninstall_target   FORCE

FORCE:

