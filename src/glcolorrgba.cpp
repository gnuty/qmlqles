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

#include "glcolorrgba.h"

/** Constructs a black color.
*/
GLColorRGBA::GLColorRGBA(){
 _Red = 0.0;
 _Green = 0.0;
 _Blue = 0.0;
 _Alpha = 1.0;
}
/** Constructs the specified color.
*/
GLColorRGBA::GLColorRGBA(GLfloat r, GLfloat g, GLfloat b, GLfloat a){
 _Red = r;
 _Green = g;
 _Blue = b;
 _Alpha = a;
}
/** Copy constructor.
 */
GLColorRGBA::GLColorRGBA (const GLColorRGBA & toCopy){
   copy(toCopy);
}

/** Destructor, does nothing.
*/
GLColorRGBA::~GLColorRGBA(){
}

GLfloat * GLColorRGBA::fv(){
 return &_Red;
}

/**
  * Returns the inverted color with a= 1.0
  */
GLColorRGBA GLColorRGBA::inverted()
{
    return GLColorRGBA(1.0 -_Red, 1.0 - _Green, 1.0 - _Blue, 1.0);
}

/** For brightness adjustment. "a" value is not multipiled.
*/
GLColorRGBA GLColorRGBA::operator *(double f){
 return GLColorRGBA(_Red * f,
                   _Green * f,
                   _Blue * f,
                   _Alpha);
}
/** Returns Red value. */
double GLColorRGBA::red(){
  return _Red;
}
/** Returns Green value. */
double GLColorRGBA::green(){
  return _Green;
}
/** Returns Blue value. */
double GLColorRGBA::blue(){
  return _Blue;
}
/** Returns A (transparency) value. */
double GLColorRGBA::alpha(){
  return _Alpha;
}
/** Copy operator.
 */
GLColorRGBA GLColorRGBA::operator = (const GLColorRGBA & toCopy){
  copy(toCopy);
  return * this;
}

/**
  * Equal operator
  */
bool GLColorRGBA::operator== (const GLColorRGBA & other)const
{
    return _Red == other._Red
        && _Green == other._Green
        && _Blue == other._Blue
        && _Alpha == other._Alpha;
}

/** Copy function. For internal use only.
 */
void GLColorRGBA::copy(const GLColorRGBA & toCopy){
  _Red = toCopy._Red;
  _Green = toCopy._Green;
  _Blue = toCopy._Blue;
  _Alpha = toCopy._Alpha;
}
