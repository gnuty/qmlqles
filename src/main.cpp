/**************************************************************************
 *       Last changes: 30.03.2012
 *       Licence: GPL
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#include <QtGui/QApplication>
#include "qmlapplicationviewer.h"
#include <QtDeclarative>

#include "examplescene.h"

/**
  * A combined QML and OpenGL ES2 application. The QmlApplicationViewer's viewport is set to an
  * OpenGL context by calling setViewport with a QGLWidget. This will result in a total screen
  * clearing, whenever glClear is called with the GL_COLOR_BUFFER_BIT set. Therefore, glClear
  * must not be called with this bit set. Instead, a QML Rectangle object is used to clear the
  * background of the OpenGL viewport. This requires, that the OpenGL viewport and the rectangle
  * share the same area on screen. Because of the different coordinate systems (QML: 0,0 = top left,
  * y down, OpenGL: 0,0 = bottom left, y up) the coordinates of the enclosing QML Rectangle have to
  * be transformed to set the OpenGL viewport.
  * OpenGL initialization requires a valid OpenGL context. Therefore, it must not be done in the
  * constructor of the GLWidget. The GLWidget class performs initialization on the first paint() call
  * and skips this code on following calls to paint() using a "initialized" flag.
  * Refer to the documentation of the GLWidget class.
  */


Q_DECL_EXPORT int main(int argc, char *argv[])
{
    QScopedPointer<QApplication> app(createApplication(argc, argv));
    qmlRegisterType<ExampleScene>("GLItems", 1,0,"ExampleScene");
    QmlApplicationViewer viewer;
    viewer.setOrientation(QmlApplicationViewer::ScreenOrientationAuto);
    viewer.setMainQmlFile(QLatin1String("qml/qmlgles/main.qml"));
    viewer.setViewport(new QGLWidget());
#ifdef GLES
    viewer.showFullScreen();
#else
    viewer.setGeometry(0,0,840, 480);
    viewer.show();
#endif
    return app->exec();
}
