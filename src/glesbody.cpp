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
#include "glesbody.h"

#include <QImage>
#include <QGLWidget>

/**Constructor does NOT create the surface.
*/
GLESBody::GLESBody()
{
  surfaceIsValid = false;
  texture = 0;
  color = cl_White;
  specularColor = cl_White;
  shininess = 50;
  radius = 0.0;
  selected = false;
}

/** Destructor
 */
GLESBody::~GLESBody()
{
	  if(texture != 0){//delete an existing texture
	    glDeleteTextures(1, &texture);
	    texture = 0;
	  }
}

/** Creates the surface. Should be called, when a GL engine is already running.
  * Is called automatically by draw, if required.
  */
void GLESBody::makeSurface(){
  setTexture(textureFile);
  surfaceIsValid = true;
}

/** Draws the surface and calls makeSurface if required.
 * Needs an active (made current) GL-Context.
 */
void GLESBody::draw(GLESRenderer * renderer){
  if(!surfaceIsValid)
    makeSurface();
  if(points.size() == 0) //check for existing points
    return;
  int stride = sizeof(GLPoint);
  bool oldTextureEnabled = false;

  //set colors
  renderer->setAmbientAndDiffuseColor(color);

  //enable required arrays
  renderer->activateAttributeArray(GLESRenderer::VERTEX_LOCATION,
                                   points[0].vertexPointer(), stride);
  if (renderer->isLightingEnabled())
      renderer->activateAttributeArray(GLESRenderer::NORMAL_LOCATION,
                                       points[0].normalPointer(), stride);
  if(texture != 0){
    glActiveTexture(GL_TEXTURE0); //use texture unit 0
    glBindTexture(GL_TEXTURE_2D, texture);
    oldTextureEnabled = renderer->isTextureEnabled();
    renderer->setTextureEnabled(true);
   }
  else renderer->setTextureEnabled(false);
  renderer->activateAttributeArray(GLESRenderer::TEXCOORD_LOCATION,
               points[0].texCoordPointer(), stride);

//   for(int i = 0; i < indices.count(); i++)
//    points[indices[i]].debugOutput("Point" +QString::number(i) + ":" + QString::number(indices[i]) + " ");

  if(indices.count() > 0)
    glDrawElements(GL_TRIANGLES, indices.count(),
                   GL_UNSIGNED_SHORT, indices.data());
  else
  glDrawArrays(GL_TRIANGLES, 0, points.size());

  if(isSelected())
  {
      bool lightingOn = renderer->isLightingEnabled();
      if(lightingOn)
          renderer->setLightingEnabled(false);
      GLColorRGBA pointColor(color.inverted());
      renderer->setAmbientAndDiffuseColor(pointColor);
      int oldPointSize = renderer->getPointSize();
      renderer->setPointSize(5);
      glDrawArrays(GL_POINTS, 0, points.size());
      if(lightingOn)
          renderer->setLightingEnabled(true);
      renderer->setPointSize(oldPointSize);
  }
  //disable arrays
  renderer->disableAttributeArrays();
  if(texture != 0)
    renderer->setTextureEnabled(oldTextureEnabled);
}

/** Set texture from file. Returns true on success
 */
bool GLESBody::setTexture(const QString & textureFile){
  if(textureFile == "")
    return false;

  QImage  image;
  if(texture != 0){//delete an existing texture
    glDeleteTextures(1, &texture);
    texture = 0;
  }

  qDebug("%s", QString("Loading Texture:" + textureFile).toLatin1().data());
  if (image.load(textureFile)){
   //we have got a valid image, give it to GL
    if (image.format() != QImage::Format_ARGB32) //make shure, that we have 32bit colors
      image = image.convertToFormat(QImage::Format_ARGB32);
    image = QGLWidget::convertToGLFormat(image);
    glGenTextures(1, &texture); // get a number (name) for the new texture and create a new texture object
    if(texture == 0) //GL does not work properly
    {
      qDebug("Could not create texture object. GL-engine not yet active?");
      return false;
    }
    glBindTexture(GL_TEXTURE_2D, texture); // Bind texture object to OpenGL.
    //All following calls work on the bound texture object.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
       GL_NEAREST); //use values of nearest pixel for magnification.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
        GL_NEAREST); // use nearest pixel minimization.
    // Replace with other values if aliasing occurs. See doc for GL_TEXTURE_MAG_FILTER

    //The next call copies the pixel data from the QImage, which is no longer needed afterwards.
    glTexImage2D(GL_TEXTURE_2D,
       0,                          // use only one resolution
       GL_RGBA,                    //internal format to use for the texture
       image.width(),
       image.height(),
       0,                          //width of the texture border, may be 0 or 1
       GL_RGBA,                    //format of the QImage
       GL_UNSIGNED_BYTE,           // QImage uses values from 0 to 255 for R,G,B,A
       image.bits()                //pointer to the first pixel in image
    );
    glBindTexture(GL_TEXTURE_2D, 0); // finally remove texture from OpenGL machine
    return true;
  }
  else{ //loading failed
    qDebug("Texture loading failed");
    return false;
  }
}

/** Set texture file.
 */
bool GLESBody::setTextureFile(const QString & textureFile){
 this->textureFile = textureFile;
 if(texture != 0) //we have an activated texture already. Replace it.
  return setTexture(textureFile);
 else return true; //texture is not yet active, leave it as it is
}

/**
  * Moves the body by adding vMove to all vertices.
  */
void GLESBody::move(QVector3D vMove)
{
    for(int i = 0; i < points.size(); i++)
        points[i].move(vMove);
    center = center + vMove;
}

/**
  * Returns true, when line through p1 and p2 intersects body shpere
  */
bool GLESBody::isHit(QVector3D p1, QVector3D p2)
{
   QVector3D lineVector = p2 - p1;
   double area = QVector3D::crossProduct((center - p1), lineVector).length();
   double distance = area / lineVector.length();
   //qDebug("Radius: %f", radius);
   return distance < radius;
}

/*
 * Returns true, if enclosing spheres touch or intersect
 */
bool GLESBody::spheresAreColliding(const GLESBody *other)
{
    bool result;
    if(this == other)
        result = false;
    else
    {
        GLdouble distance = (center - other->center).length();
        result = (radius + other->radius) >= distance;
    }
    if(result)
        return true; //hook for debugger
    else return false; //hook for debugger
}

/**
  * Set new center and invalidate surface.
  */
void GLESBody::setCenter(const QVector3D & newVal)
{
    center = newVal;
    surfaceIsValid = false;
}

