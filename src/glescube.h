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

#ifndef GLESCUBE_H_
#define GLESCUBE_H_

#include "glesbody.h"
#include "gldefines.h"


class GLESCube: public GLESBody {
public:
        GLESCube(const QVector3D lowerLeftFront = v_Z, const QVector3D upperRightBack = v_XY);
        virtual ~GLESCube();
    /** Creates the surface using 12 triangles. Should be called, when a GL engine is already running.
      * Is called automatically by draw, if required.
      * MUST NOT be called without a working GL engine.
      */
    virtual void makeSurface();
private:
        QVector3D llf; //lower left front
        QVector3D urb; //upper right back
};

#endif /* GLCUBE_H_ */
