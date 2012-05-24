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

#ifndef GLCOLORRGBA_H
#define GLCOLORRGBA_H


/** A color class that supports RGBA colors. Color is saved as 4 GLfloat values
  * 0.0 = black, 1.0 = full intensity.
  * The "A" value is for transparency (very practical for window panes).
  * 0.0 = transparent, 1.0 = opaque
  */
# include <QGLWidget>

class GLColorRGBA {
 GLfloat _Red, _Green, _Blue, _Alpha;  //DO NOT CHANGE order of declaration! Is used as GLdouble *!
public:
  /** Constructs a black color.
  */
  GLColorRGBA();
  /** Constructs the specified color.
   */
  GLColorRGBA(GLfloat r, GLfloat g, GLfloat b, GLfloat a =1.0);
  /** Destructor, does nothing.
  */
  virtual ~GLColorRGBA();
  /**Returns a pointer to fR. To be used with GLColorXXXfv functions.
    */
  GLfloat * fv(); 
  /** For brightness adjustment. "a" value is not multiplied.
    */
  GLColorRGBA operator *(double f);
  /** Returns Red value.
    */
  double red();
  /** Copy operator.
  */
  GLColorRGBA operator=(const GLColorRGBA & toCopy);
  /**
    * Equal operator
    */
  bool operator==(const GLColorRGBA & other)const;
  /** Returns Green value.
  */
  double green();
  /** Copy constructor.
 */
   GLColorRGBA (const GLColorRGBA & toCopy);
  /** Returns Blue value.
  */
  double blue();
  /** Returns A (transparency) value.
  */
  double alpha();
  /**
    * Returns the inverted color with a= 1.0
    */
  GLColorRGBA inverted();
protected: // Protected methods
 /** Copy function. For internal use only. MUST be called by subclassed copy functions.
 */
  void copy(const GLColorRGBA & toCopy);
};

#endif
