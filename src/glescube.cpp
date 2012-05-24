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

#include "glescube.h"

GLESCube::GLESCube(const QVector3D lowerLeftFront, const QVector3D upperRightBack)
:GLESBody()
{
      llf = center + lowerLeftFront;
      urb = center + upperRightBack;
}

GLESCube::~GLESCube()
{
}

/** Creates the surface using 12 triangles. Should be called, when a GL engine is already running.
  * Is called automatically by draw, if required.
  */
void GLESCube::makeSurface()
{
    QVector3D v0 = center + QVector3D(llf.x(), llf.y(), urb.z());
    QVector3D vX = center + QVector3D(urb.x(), llf.y(), urb.z());
    QVector3D vY = center + QVector3D(llf.x(), urb.y(), urb.z());
    QVector3D vZ = center + QVector3D(llf.x(), llf.y(), llf.z());
    QVector3D vXY = center + QVector3D(urb.x(), urb.y(), urb.z());
    QVector3D vXZ = center + QVector3D(urb.x(), llf.y(), llf.z());
    QVector3D vYZ = center + QVector3D(llf.x(), urb.y(), llf.z());
    QVector3D vXYZ = center + QVector3D(urb.x(), urb.y(), llf.z());

    //parameter order for GLPoint: Vertex, Normal TexCoord
    //Front
    points.append(GLPoint(vZ, v_Z, v_Zero));
    points.append(GLPoint(vXZ, v_Z, v_X));
    points.append(GLPoint(vYZ, v_Z, v_Y));

    points.append(GLPoint(vXZ, v_Z, v_X));
    points.append(GLPoint(vXYZ, v_Z, v_XY));
    points.append(GLPoint(vYZ, v_Z, v_Y));

    //Back
    points.append(GLPoint(vX, -v_Z, v_X));
    points.append(GLPoint(v0, -v_Z, v_Zero));
    points.append(GLPoint(vY, -v_Z, v_Y));

    points.append(GLPoint(vY, -v_Z, v_Y));
    points.append(GLPoint(vXY, -v_Z, v_XY));
    points.append(GLPoint(vX, -v_Z, v_X));

   //Top
    points.append(GLPoint(vY, v_Y, v_Zero));
    points.append(GLPoint(vXYZ, v_Y, v_XY));
    points.append(GLPoint(vXY, v_Y, v_X));

    points.append(GLPoint(vYZ, v_Y, v_Y));
    points.append(GLPoint(vXYZ, v_Y, v_XY));
    points.append(GLPoint(vY, v_Y, v_Zero));

    //Bottom
    points.append(GLPoint(v0, -v_Y, v_Zero));
    points.append(GLPoint(vX, -v_Y, v_Y));
    points.append(GLPoint(vZ, -v_Y, v_X));

    points.append(GLPoint(vX, -v_Y, v_Y));
    points.append(GLPoint(vXZ, -v_Y, v_XY));
    points.append(GLPoint(vZ, -v_Y, v_X));

    //Left
    points.append(GLPoint(v0, -v_X, v_Zero));
    points.append(GLPoint(vZ, -v_X, v_Y));
    points.append(GLPoint(vY, -v_X, v_X));

    points.append(GLPoint(vZ, -v_X, v_Y));
    points.append(GLPoint(vYZ, -v_X, v_XY));
    points.append(GLPoint(vY, -v_X, v_X));

    //Right
    points.append(GLPoint(vX, v_X, v_Zero));
    points.append(GLPoint(vXY, v_X, v_Y));
    points.append(GLPoint(vXZ, v_X, v_X));

    points.append(GLPoint(vXZ, v_X, v_X));
    points.append(GLPoint(vXY, v_X, v_Y));
    points.append(GLPoint(vXYZ, v_X, v_XY));

    GLESBody::makeSurface();
}
