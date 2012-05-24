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
#ifndef GLESGLOBE_H
#define GLESGLOBE_H

#include "glesbody.h"
#include "glesrenderer.h"

/**
The earth.
*/
class GLESGlobe : public GLESBody
{
public:
    GLESGlobe(const QString & textureFile, GLdouble radius = 1.0, int latitudes = 18, int longitudes = 36);

    ~GLESGlobe();
    /** Creates the surface. Creates a single point for every latitude/longitude pair and
     *  creates the triangles for the surface by indexing each point four times.
     */
    virtual void makeSurface();

    /** Sets geographic coordinates. Y is up, longitude in xz plane, latitude from xz plane up- and downwards.
      */
    QVector3D vectorFromRadiusLongitudeLatitude(qreal radius, qreal longitude, qreal latitude);

private:

   GLdouble radius;
   int latitudes;
   int longitudes;
};

#endif
