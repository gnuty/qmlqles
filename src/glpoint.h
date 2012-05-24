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
#ifndef GLPOINT_H
#define GLPOINT_H

#include <QVector3D>

/**
A 3d-point to be used with GL-arrays. It encapsulates vertex, normal and texture coordinates. For maximum memory efficiency it does not contain ANY virtual function.  This means, it should NOT be subclassed.
Useage with Qt: QVector<GLPoint> Geometry;
Useage with STL: Vector <GLPoint> Geometry;
Do always use sizeof(GLPoint) for the stride parameter in glXXXXArray functions.
*/
class GLPoint{
public:
    /**Constructor
    */
    GLPoint(const QVector3D & vertex = QVector3D(0.0,0.0,0.0),
            const QVector3D & normal = QVector3D(0.0,1.0,0.0),
            const QVector3D & texCoord = QVector3D(0.0,0.0,0.0));
    /**Destructor
    */
    ~GLPoint();
   /** Returns address of _X coordinate of _Vertex
    */ 
   QVector3D * vertexPointer();
   /** Returns address of _X coordinate of _Normal
    */ 
   QVector3D * normalPointer();
   /** Returns address of _X coordinate of _TexCoord
    */ 
   QVector3D * texCoordPointer();
   /**
     * Moves the point by adding vMove to vertex.
     */
   void move(QVector3D vMove);

   /** For debugging.
    */
   void debugOutput(const QString & prefix);

private:
 QVector3D vertex;
 QVector3D normal;
 QVector3D texCoord;
};

#endif
