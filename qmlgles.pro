# Add more folders to ship with the application, here
folder_01.source = qml/qmlgles
folder_01.target = qml
DEPLOYMENTFOLDERS = folder_01

QT += opengl

# Additional import path used to resolve QML modules in Creator's code model
QML_IMPORT_PATH =

symbian:TARGET.UID3 = 0xE0AC0F6C

# Smart Installer package's UID
# This UID is from the protected range and therefore the package will
# fail to install if self-signed. By default qmake uses the unprotected
# range value if unprotected UID is defined for the application and
# 0x2002CCCF value if protected UID is given to the application
#symbian:DEPLOYMENT.installer_header = 0x2002CCCF

# Allow network access on Symbian
symbian:TARGET.CAPABILITY += NetworkServices

# If your application uses the Qt Mobility libraries, uncomment the following
# lines and add the respective components to the MOBILITY variable.
# CONFIG += mobility
# MOBILITY +=

# Speed up launching on MeeGo/Harmattan when using applauncherd daemon
CONFIG += qdeclarative-boostable

# Add dependency to Symbian components
# CONFIG += qt-components

# The .cpp file which was generated for your project. Feel free to hack it.
SOURCES += src/main.cpp \
    src/glitem.cpp \
    src/shaderdebugger.cpp \
    src/glesrenderer.cpp \
    src/glcolorrgba.cpp \
    src/glpoint.cpp \
    src/glesbody.cpp \
    src/glescube.cpp \
    src/glesglobe.cpp \
    src/examplescene.cpp

HEADERS += \
    src/glitem.h \
    src/shaderdebugger.h \
    src/glesrenderer.h \
    src/glcolorrgba.h \
    src/glpoint.h \
    src/glesbody.h \
    src/glescube.h \
    src/glesglobe.h \
    src/gldefines.h \
    src/examplescene.h

# Please do not modify the following two lines. Required for deployment.
include(qmlapplicationviewer/qmlapplicationviewer.pri)
qtcAddDeployment()

OTHER_FILES += \
    qtc_packaging/debian_harmattan/rules \
	qtc_packaging/debian_harmattan/manifest.aegis \
    qtc_packaging/debian_harmattan/copyright \
    qtc_packaging/debian_harmattan/control \
    qtc_packaging/debian_harmattan/compat \
	src/vshader1.vsh \
    src/fshader1.fsh

RESOURCES += \
    resources.qrc
