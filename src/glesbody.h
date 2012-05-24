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
#ifndef GLESBODY_H
#define GLESBODY_H

#include <QVector>

#include "glpoint.h"
#include "glcolorrgba.h"
#include "glesrenderer.h"

/**
A 3d body that uses a GLESRenderer for drawing.
Overwrite makeSurface() in subclasses to create the points that form the surface.
Overwrite draw() if you do not want your body to be drawn with triangles.
*/
class GLESBody{
public:
     /**Constructor does NOT create the surface.
     */
     GLESBody();
    /** Destructor
     */
    virtual ~GLESBody();
    /** Creates the surface. Should be called, when a GL engine is already running.
      * To be overwritten by subclasses.
      * Is called automatically by draw, if required.
      * MUST NOT be called without a working GL engine.
      */
    virtual void makeSurface();
   /** Draws the surface and calls makeSurface if required.
    * Needs an active (made current) GL-Context.
    */
    virtual void draw(GLESRenderer * renderer);
    /**
      * Returns true, when line through p1 and p2 intersects body sphere
      * To be overwritten by subclasses.
      */
    virtual bool isHit(QVector3D p1, QVector3D p2);

    /**
      * Returns true, if enclosing spheres touch or intersect
      */
    virtual bool spheresAreColliding(const GLESBody * other);
   /** Set texture from file. Returns true on success
    */
    bool setTexture(const QString & textureFile);
   /** Set texture file.
    */
    bool setTextureFile(const QString & textureFile);

    /**
      * Moves the body by adding vMove to all vertices.
      */
    void move(QVector3D vMove);
    /**
      * Simple gettters
      */
    bool isSelected(){return selected;}
    const QVector3D & getCenter()const{return center;}

   /**Simple setters
    */
    void setColor(const GLColorRGBA & newVal){color = newVal;}
    void setSpecularColor(const GLColorRGBA & newVal){specularColor = newVal;}
    void setShininess(int newVal){shininess = newVal;}
    void setSelected(bool newVal){selected = newVal;}

    /**
      * Set new center and invalidate surface.
      */
    void setCenter(const QVector3D & newVal);

    /**
      *Simple getters
      */
    const GLColorRGBA & getColor()const{return color;}

protected:
    /**
      * The center of the enclosing sphere
      */
     QVector3D center;
     /**
       * The radius of the enclosing sphere
       */
     GLfloat radius;
    /** The array of points defining the surface.
     */
    QVector <GLPoint> points;
   /** The array with the indices. May be left empty. 
    */
    QVector <GLshort> indices;
   /** The flag for a valid surface.
    */
    bool surfaceIsValid;
   /** The texture to be used.
    */
    GLuint texture;
   /** The tetxure file.
    */
   QString textureFile;
  /** The diffuse and ambient color for the body.
   */
   GLColorRGBA color;
  /**The specular color
   */
   GLColorRGBA specularColor;
  /**Shoininess for specular color
  */
   int shininess;
   /**
     *  Flag for selected mode.
     */
   bool selected;
};

#endif
