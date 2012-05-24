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
#include "glesglobe.h"
#include <math.h>

GLESGlobe::GLESGlobe(const QString & textureFile, GLdouble radius, int latitudes, int longitudes)
 : GLESBody()
{
  this->radius = radius;
  this->latitudes = latitudes;
  this->longitudes = longitudes;
  setTextureFile(textureFile);
}

GLESGlobe::~GLESGlobe()
{
}

/** Sets geographic coordinates. Y is up, longitude in xz plane, latitude from xz plane up- and downwards.
  */
QVector3D GLESGlobe::vectorFromRadiusLongitudeLatitude(qreal radius, qreal longitude, qreal latitude)
{
  qreal radLongitude = longitude / 180.0 * M_PI; // may be more than +-180 degree
  qreal radLatitude = latitude / 180.0 * M_PI;
  //Not more than +- 90 degree.
  if(radLatitude > M_PI / 2.0)
    radLatitude = M_PI/ 2.0;
  if(radLatitude < -M_PI / 2.0)
    radLatitude = -M_PI/ 2.0;
  qreal x = radius * sin(radLongitude)* cos(radLatitude);
  qreal y = radius * sin(radLatitude);
  qreal z = radius * cos(radLongitude)* cos(radLatitude);
  return QVector3D(x, y, z);
}

/** Creates the surface. Creates a single point for every latitude/longitude pair and
 *  create triangles by indexing each point four times.
 */
void GLESGlobe::makeSurface(){
      //deltas must be full angle divided by number of segments -1, otherwise the surface is not complete,
	  //because a "closing" final triangle is needed.
  	  double deltaLatitude = 180.0 / (latitudes -1);
	  double deltaLongitude = 360.0 / (longitudes -1);
	  int nLatitude = 0;
	  int nLongitude = 0;
          QVector3D v0; //coordinates of the quads.Numbering counterclockwise, v0 = lower left
          QVector3D vN0;//true normals, parallel to radius vector
          QVector3D vTex0; //textures for a mercator projected bitmap
	  //for loops for latitude and longituide
          for (nLatitude = -latitudes / 2; nLatitude <=latitudes / 2; nLatitude ++){
	    for (nLongitude = 0; nLongitude <  longitudes; nLongitude++){
	       //create a single point for every latitude/longitude pair
               v0= vectorFromRadiusLongitudeLatitude(radius,
	                                     nLongitude * deltaLongitude,
	                                     nLatitude * deltaLatitude);
	       //v0.debugOutput(QString::number(nLatitude) + ":" +
	       //   QString::number(nLongitude) + " ");
               vN0 = v0.normalized();
	       vTex0.setX(nLongitude * deltaLongitude / 360.0);
	       vTex0.setY(nLatitude * deltaLatitude / 180.0 + 0.5);
	      points.append(GLPoint(v0, vN0, vTex0));

	      //set indices for two triangles
	      // ll = lower left, ur = upper right
	      if(nLatitude < latitudes / 2){ //stop before last row
	        int nRing = nLatitude + latitudes / 2;
	        int ll = (nRing * longitudes) + nLongitude;
	        int lr = (nRing * longitudes) + nLongitude + 1;
	        int ul = ((nRing +1) * longitudes) + nLongitude;
	        int ur = ((nRing +1) * longitudes) + nLongitude + 1;
	        //lower left triangle
	        indices.append(ll); indices.append(lr); indices.append(ul);
	        //upper right triangle
	        indices.append(lr); indices.append(ur); indices.append(ul);
	      }
	    } //end for nLongitude
	  } //end for nLatitude
          GLESBody::makeSurface();
}

