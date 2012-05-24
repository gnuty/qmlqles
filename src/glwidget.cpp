#include "glwidget.h"
#include "math.h"

#include <QFile>

GLItem::GLItem(QDeclarativeItem *parent) :
    QDeclarativeItem(parent)// QGLWidget(parent)
{
/*    setAutoFillBackground(false);
    setAttribute(Qt::WA_OpaquePaintEvent);
    setAttribute(Qt::WA_NoSystemBackground);
    setAttribute(Qt::WA_NativeWindow);
    setAttribute(Qt::WA_PaintOnScreen, true);
    setAttribute(Qt::WA_StyledBackground, false);
    setAttribute(Qt::WA_AcceptTouchEvents);
    setAutoBufferSwap(false);
    */
    initialized = false;
    lightEnabled = true;
    rotationAngle = 0.0;
    zOffset = 0.0;
    setFlags(0);
    ShaderDebugger::setEnabled(false);
    renderer = new GLESRenderer(this, ":/resources/src/vshader1.vsh", ":/resources/src/fshader1.fsh");

    showTriangles = true;
    cube1 = new GLESCube();
    cube1->move(QVector3D(0.1,0.1,0.1));
    cube1->setTextureFile(":/resources/textures/xclock.png");

    cube2 = new GLESCube();
    cube2->move(QVector3D(-1.1,-1.1,-1.1));
    cube2->setColor(cl_Red);
    showCubes = false;

    globe = new GLESGlobe(":/resources/textures/earthmap1024x512.jpg", 1.0, 36, 72);
    showGlobe = false;
}

/**
  * Select the object(s) to be shown
  */
void GLItem::showObject(QString object)
{
    showTriangles = false;
    showCubes = false;
    showGlobe = false;
    if(object == "Globe")
        showGlobe = true;
    else if(object == "Cubes")
         showCubes = true;
    else if(object == "Triangles")
        showTriangles = true;
}

void GLItem::initializeGL()
{
    if (initialized)
        return;
    initialized = renderer->initialize();
}


void GLItem::resizeGL()
{
    //transform QML screen coordinates to OpenGL viewport coordinates
    glViewport(viewportX, screenHeight - viewportY - viewportH, viewportW, viewportH);
}

/**
  * To be called whenever mvMatrix has been modified
  */
void  GLItem::setupNormalAndMVPMatrix()
{
    normalMatrix = mvMatrix.normalMatrix();

    mvpMatrix = pMatrix * mvMatrix;
}

void GLItem::paintGL()
{
    //get old status
    depthTestOn = glIsEnabled(GL_DEPTH_TEST);

     glEnable(GL_DEPTH_TEST);
     glClear(GL_DEPTH_BUFFER_BIT ); // DO NOT clear color buffer!!! QML does this for us!

     //preset uniforms in renderer
     renderer->setPerspective(45.0, (float)width() / (float)height(), 1.0, 10.0);
     QVector3D eye(0.0,0.0,4.0);
     QVector3D center(0.0,0.0,0.0);
     QVector3D up(0.0,1.0,0.0);
     renderer->setLookAt(eye, center, up);
     lightDirection = QVector3D(0.0, 0.0, 1.0).normalized(); //light should not rotate
     renderer->setLightDirection(lightDirection); //transforms to eyespace using nMatrix

 /*    //Debugging
     ShaderDebugger::setEnabled(true);
     QVector3D normal = v_Z;
     QMatrix4x4 mvMatrix = renderer->getMvMatrix();
     ShaderDebugger::debugMatrix4x4(mvMatrix, "mvMatrix");
     QMatrix4x4 nMatrix = QMatrix4x4(mvMatrix.normalMatrix());
     ShaderDebugger::debugMatrix4x4(nMatrix, "nMatrix");
     normal = normal * nMatrix;
     lightDirection = (nMatrix * lightDirection);
     double brightness = QVector3D::dotProduct(normal, lightDirection);
     qDebug("brightness: %lf", brightness);
     ShaderDebugger::setEnabled(false);
*/
     renderer->bind(); //transfers all preset uniforms to shader

     renderer->setLightingEnabled(false);
     renderer->rotate(0.1 * rotationAngle, v_Y);
     paintAxes();

     if(showGlobe)
         renderer->rotate(rotationAngle, QVector3D(0.0, 1.0, 0.0));
     else renderer->rotate(rotationAngle, QVector3D(1.0, 1.0, 1.0)); //rotate the objects
     if(showCubes)
     {
         renderer->setLightingEnabled(true);
         renderer->setColorArrayEnabled(false);
         cube1->draw(renderer);
         cube2->draw(renderer);
     }
     if(showGlobe)
     {
         renderer->setLightingEnabled(true);
         renderer->setColorArrayEnabled(false);
         globe->draw(renderer);
     }
     if(showTriangles)
         paintTriangles();

     renderer->release();
     //restore old status
     if(depthTestOn)
         glDisable(GL_DEPTH_TEST);
     //swapBuffers();
}

void GLItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->beginNativePainting();
    if(!initialized) //skip if already initialized
        initializeGL();
    if(!initialized)
    {
        qDebug("Renderer initialization failed. No graphic output available.");
        return;
    }
    resizeGL();
    paintGL();
    painter->endNativePainting();
}

void GLItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{

}

void GLItem::paintAxes()
{
    renderer->setLightingEnabled(false);
    renderer->setColorArrayEnabled(true);
    vertices.clear();
    vertices.append(QVector3D(-1.0,0.0,0.0));
    vertices.append(QVector3D(1.0,0.0,0.0));
    vertices.append(QVector3D(0.0,-1.0,0.0));
    vertices.append(QVector3D(0.0,1.0,0.0));
    vertices.append(QVector3D(0.0,0.0,-1.0));
    vertices.append(QVector3D(0.0,0.0,1.0));
    renderer->activateAttributeArray(GLESRenderer::VERTEX_LOCATION ,
                                     vertices.data(), sizeof(QVector3D));

    colors.clear();
    colors.append(QVector4D(1.0,0.0,0.0,1.0));
    colors.append(QVector4D(1.0,0.0,0.0,1.0));
    colors.append(QVector4D(0.0,1.0,0.0,1.0));
    colors.append(QVector4D(0.0,1.0,0.0,1.0));
    colors.append(QVector4D(0.0,0.0,1.0,1.0));
    colors.append(QVector4D(0.0,0.0,1.0,1.0));

    renderer->activateAttributeArray(GLESRenderer::COLOR_LOCATION,
                                     colors.constData(), sizeof(QVector4D));
    glDrawArrays(GL_LINES, 0, vertices.size());
    renderer->disableAttributeArrays();
}

void GLItem::rotate(float angle)
{
    rotationAngle += angle;
    zOffset = sin(rotationAngle / 2.0 / 180.0 * M_PI);
}

void GLItem::reset()
{
    rotationAngle = 0.0;
    zOffset = 0.0;
}

void GLItem::paintTriangles()
{
    renderer->setLightingEnabled(true);
    renderer->setColorArrayEnabled(true);
    vertices.clear();
    colors.clear();
    vertices.append(QVector3D(0.0,0.0,0.0));
    colors.append(QVector4D(1.0,0.0,0.0,1.0));
    normals.append(QVector3D(1.0, 0.0,0.0));

    vertices.append(QVector3D(1.0,0.0,0.0));
    colors.append(QVector4D(1.0,0.0,0.0,1.0));
    normals.append(QVector3D(1.0, 0.0,0.0));

    vertices.append(QVector3D(0.0,1.0,0.0));
    colors.append(QVector4D(1.0,0.0,0.0,1.0));
    normals.append(QVector3D(1.0, 0.0, 0.0));


    vertices.append(QVector3D(1.0,0.0,0.0));
    colors.append(QVector4D(1.0,0.0,0.0,1.0));
    normals.append(QVector3D(0.0, 1.0,0.0));

    vertices.append(QVector3D(1.0,1.0,0.0));
    colors.append(QVector4D(0.0,1.0,0.0,1.0));
    normals.append(QVector3D(0.0, 1.0,0.0));

    vertices.append(QVector3D(0.0,1.0,0.0));
    colors.append(QVector4D(0.0,0.0,1.0,1.0));
    normals.append(QVector3D(0.0, 1.0,0.0));

    renderer->activateAttributeArray(GLESRenderer::COLOR_LOCATION,
                                     colors.constData(), sizeof(QVector4D));
    renderer->activateAttributeArray(GLESRenderer::VERTEX_LOCATION,
                                     vertices.constData(), sizeof(QVector3D));
    renderer->activateAttributeArray(GLESRenderer::NORMAL_LOCATION,
                                     normals.constData(), sizeof(QVector3D));
    renderer->bind();

    glDrawArrays(GL_TRIANGLES, 0, vertices.size());

    renderer->disableAttributeArrays();
    renderer->release();
}


