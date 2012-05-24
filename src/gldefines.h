/********************************************************
 * Convenience objects for building OpenGL surfaces.
 *
 *  Created on: 24.04.2012
 *      Licence: GPL
 *
 *******************************************************/
#ifndef GLDEFINES_H
#define GLDEFINES_H

#include <QVector3D>
#include "glcolorrgba.h"

//Predefined vectors

const static QVector3D v_Zero = QVector3D(0.0, 0.0, 0.0);
const static QVector3D v_X = QVector3D(1.0, 0.0, 0.0);
const static QVector3D v_Y = QVector3D(0.0, 1.0, 0.0);
const static QVector3D v_Z = QVector3D(0.0, 0.0, 1.0);
const static QVector3D v_XY = QVector3D(1.0, 1.0, 0.0);
const static QVector3D v_XZ = QVector3D(1.0, 0.0, 1.0);
const static QVector3D v_YZ = QVector3D(0.0, 1.0, 1.0);
const static QVector3D v_XYZ = QVector3D(1.0, 1.0, 1.0);


/** Predefined global colors for convenience.
  */
const static GLColorRGBA cl_White      = GLColorRGBA(1.0,1.0,1.0);
const static GLColorRGBA cl_Black      = GLColorRGBA(0.0,0.0,0.0);
const static GLColorRGBA cl_Red        = GLColorRGBA(1.0,0.0,0.0);
const static GLColorRGBA cl_Green      = GLColorRGBA(0.0,1.0,0.0);
const static GLColorRGBA cl_Blue       = GLColorRGBA(0.0,0.0,1.0);
const static GLColorRGBA cl_LightBlue  = GLColorRGBA(0.5,0.5,1.0);
const static GLColorRGBA cl_Gray       = GLColorRGBA(0.5,0.5,0.5);
const static GLColorRGBA cl_Yellow     = GLColorRGBA(1.0,1.0,0.0);
const static GLColorRGBA cl_Magenta    = GLColorRGBA(1.0,0.0,1.0);
const static GLColorRGBA cl_Cyan       = GLColorRGBA(0.0,1.0,1.0);



#endif // GLDEFINES_H
