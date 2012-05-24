#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include <QGLShaderProgram>
#include <QDeclarativeItem>

#include "shaderdebugger.h"
#include "glesrenderer.h"
#include "glescube.h"
#include "glesglobe.h"

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
    void rotate(float angle);
    void reset();
    void callUpdate(){update();}

    /**
      * Select the object(s) to be shown
      */
    void showObject(QString object);

    //simple setters
    void setScreenHeight(int arg){screenHeight = arg;}
    void setViewportX(int arg){viewportX = arg;}
    void setViewportY(int arg){viewportY = arg;}
    void setViewportW(int arg){viewportW = arg;}
    void setViewportH(int arg){viewportH = arg;}

private:
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
    /**
      * Setup axes vertices and paint the coordinate axes.
      */
    void paintAxes();
    /**
      * Setup triangle vertices and colors and paint all vertices as triangles.
      */
    void paintTriangles();

    bool initialized;
    QMatrix4x4 mvpMatrix; //combined modelview and projection matrix
    QMatrix4x4 mvMatrix; //modelview matrix
    QMatrix4x4 pMatrix;  //projection matrix
    QMatrix3x3 normalMatrix; //matrix for normal transformation
    bool lightEnabled; // flag for lighting
    QVector3D lightDirection; //direction of directional light



    float rotationAngle;
    float zOffset;
    QVector<QVector3D>vertices;
    QVector<QVector3D>normals;
    QVector<QVector4D>colors;
    int screenHeight;
    int viewportX;
    int viewportY;
    int viewportW;
    int viewportH;

    //Status values of context
    bool depthTestOn;

    GLESRenderer * renderer;
    bool showTriangles;
    bool showCubes;
    GLESCube * cube1;
    GLESCube * cube2;
    bool showGlobe;
    GLESGlobe * globe;
};

#endif // GLWIDGET_H
