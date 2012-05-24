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
#include "glpoint.h"

/**Constructor
*/
GLPoint::    GLPoint(const QVector3D & vertex, const QVector3D & normal, const QVector3D & texCoord)
{
 this->vertex = vertex;
 this->normal = normal;
 this->texCoord = texCoord;
}

/**Destructor
*/
GLPoint::~GLPoint()
{
}

/** Returns address of _X coordinate of vertex
 */ 
QVector3D * GLPoint::vertexPointer(){
  return &vertex;
}
/** Returns address of _X coordinate of normal
 */ 
QVector3D  * GLPoint::normalPointer(){
  return  &normal;
}
/** Returns address of _X coordinate of texCoord
 */ 
QVector3D  * GLPoint::texCoordPointer(){
  return  &texCoord;
}

/**
  * Moves the point by adding vMove to vertex.
  */
void GLPoint::move(QVector3D vMove)
{
    vertex = vertex + vMove;
}

void GLPoint::debugOutput(const QString & prefix){
    qDebug("%s", qPrintable("GLPoint " + prefix));
    QString s = QString(" Vertex: x = %1; y = %2; z = %3")
                .arg(vertex.x()).arg(vertex.y()).arg(vertex.z());
    qDebug("%s", qPrintable(s));
    s = QString(" Normal: x = %1; y = %2; z = %3")
                .arg(normal.x()).arg(normal.y()).arg(normal.z());
    qDebug("%s", qPrintable(s));
    s = QString(" TexCoord: x = %1; y = %2; z = %3")
                .arg(texCoord.x()).arg(texCoord.y()).arg(texCoord.z());
    qDebug("%s", qPrintable(s));
}

