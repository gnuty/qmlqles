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
#include "glitem.h"
#include "math.h"

#include <QFile>
#include <QGraphicsSceneMouseEvent>

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
    lightDirection = QVector3D(1.0, 2.0, 3.0).normalized();
    setAcceptedMouseButtons(Qt::LeftButton | Qt::RightButton);
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
    // DO NOT modify settings of context, without restoring their old values!
    // See documentation of QPainter::beginNativePainting
    //get old status
    depthTestOn = glIsEnabled(GL_DEPTH_TEST);

     glEnable(GL_DEPTH_TEST);
     //Set Blending to 100% source and 0% destination.
     //The default values may hve been modified by the QML engine

     glBlendFunc(1.0, 0.0);
     glClear(GL_DEPTH_BUFFER_BIT); // DO NOT clear color buffer!!! QML does this for us!
     //preset uniforms in renderer
     renderer->setPerspective(45.0, (float)width() / (float)height(), 1.0, 10.0);
     QVector3D eye(0.0,0.0,4.0);
     QVector3D center(0.0,0.0,0.0);
     QVector3D up(0.0,1.0,0.0);
     renderer->setLookAt(eye, center, up);
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

     paintScene(); //draws all objects

     renderer->release();
     //restore old status
     if(depthTestOn)
         glDisable(GL_DEPTH_TEST);
     glFlush();
}

void GLItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
   // painter->drawRect(0,0, width(), height());
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
    qDebug("Mouse pressed at screen coordinates x: %i, y: %i", event->screenPos().x(), event->screenPos().y());
    qDebug("Mouse pressed at viewport coordinates x: %f, y: %f", event->pos().x(), event->pos().y());
    QPointF viewportPos = mouseToViewport(event->pos());
    float winX = viewportPos.x();
    float winY = viewportPos.y();
    float winZ = 0.0;
    QVector3D nearPoint = renderer->unProjectViewportPoint( winX, winY, winZ);

    qDebug("Point on near clipping plane: %f, %f, %f", nearPoint.x(), nearPoint.y(), nearPoint.z());
}



/**
  * Transform to GL viewport coordinates winX and winY
  */
QPointF GLItem::mouseToViewport(const QPointF & mousePos)
{
    return QPointF(mousePos.x(), height() - mousePos.y());
}

/**
  * Virtual function for drawing all objects.
  * Default implementation draws nothing.
  * Must be overridden by subclasses.
  */
void GLItem::paintScene()
{
    qDebug("%s", "GLItem::drawScene() was called. This function draws nothing. Override GLItem::drawScene function to draw your scene.");
}
