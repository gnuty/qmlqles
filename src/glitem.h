/***************************************************************************
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
#ifndef GLITEM_H
#define GLITEM_H

#include <QGLWidget>
#include <QGLShaderProgram>
#include <QDeclarativeItem>

#include "glesrenderer.h"

/**
  * A QML Item that was developed from a QGLWidget. The inheritance was changed to
  * QDeclarativeItem, so that the GLWidget can be used with QML.
  * QML calls the virtual paint() function, when the widget needs to be repainted.
  * paint is implemented to call the initializeGL, resizeGL and paintGL known from
  * QGLWidget.
  * When the constructor of QGLWidget is run, there will be no valid OpenGL context
  * available to initialize the shader programs. Therefore, initialization is
  * delayed until paint is called for the first time. The initialized flag is used to skip
  * this on following calls to paint.
  * It is very important not to call glClear with the GL_COLOR_BUFFER_BIT set, because
  * this will clear the whole screen. Clear the viewport with an underlying QML Rectangle
  * or by drawing something on the far clipping plane.
  * The viewport is set in resizeGL to match the coordinates of the underlying QML Rectangle.
  * This requires to transform the QML screen-coordinates to OpenGL screen-coordinates.
  */
class GLItem : public QDeclarativeItem //QGLWidget
{
    Q_OBJECT

    Q_PROPERTY (int screenHeight READ getScreenHeight WRITE setScreenHeight)
    Q_PROPERTY (int viewportX READ getViewportX WRITE setViewportX)
    Q_PROPERTY (int viewportY READ getViewportY WRITE setViewportY)
    Q_PROPERTY (int viewportW READ getViewportW WRITE setViewportW)
    Q_PROPERTY (int viewportH READ getViewportH WRITE setViewportH)

public:
    explicit GLItem(QDeclarativeItem *parent = 0);
    /**
      * The overridden paint method. Calls initializeGL, resizeGL and paintGL.
      */
    void paint(QPainter * painter, const QStyleOptionGraphicsItem *, QWidget *);

    // coordinates for setting the viewport must be given as absolute QML screen coordinates
    int getScreenHeight() const{return screenHeight;}
    int getViewportX() const{return viewportX;}
    int getViewportY() const{return viewportY;}
    int getViewportW() const{return viewportW;}
    int getViewportH() const{return viewportH;}

    void mousePressEvent(QGraphicsSceneMouseEvent *event);
signals:
    
public slots:
    void callUpdate(){update();}


    //simple setters
    void setScreenHeight(int arg){screenHeight = arg;}
    void setViewportX(int arg){viewportX = arg;}
    void setViewportY(int arg){viewportY = arg;}
    void setViewportW(int arg){viewportW = arg;}
    void setViewportH(int arg){viewportH = arg;}

protected:
    /**
      * Virtual function for drawing all objects.
      * Default implementation draws nothing.
      * Must be overridden by subclasses.
      */
    virtual void paintScene();

    /**
      * Transform to GL viewport coordinates winX and winY
      */
    QPointF mouseToViewport(const QPointF & mousePos);
    /**
      * To be called whenever mvMatrix has been modified
      */
    void setupNormalAndMVPMatrix();
    /**
      * Create rendering program and set basic values to GL context.
      */
    void initializeGL();
    /**
      * Set the viewport so that it matches the underlying QML Rectangle.
      */
    void resizeGL();
    /**
      * Setup matrices and activate drawing program.
      */
    void paintGL();

    bool initialized;
    QMatrix4x4 mvpMatrix; //combined modelview and projection matrix
    QMatrix4x4 mvMatrix; //modelview matrix
    QMatrix4x4 pMatrix;  //projection matrix
    QMatrix3x3 normalMatrix; //matrix for normal transformation
    bool lightEnabled; // flag for lighting
    QVector3D lightDirection; //direction of directional light


    int screenHeight;
    int viewportX;
    int viewportY;
    int viewportW;
    int viewportH;

    //Status values of OpenGL rendering context
    bool depthTestOn;
    bool blendingOn;

    GLESRenderer * renderer;

};

#endif // GLWIDGET_H
