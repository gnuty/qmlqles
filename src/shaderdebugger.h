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
#ifndef SHADERDEBUGGER_H
#define SHADERDEBUGGER_H

#include <QGLWidget>
#include <QMatrix3x3>
#include <QMatrix4x4>

class ShaderDebugger
{
public:
    ShaderDebugger();
    static void setEnabled(bool newVal){enabled = newVal;}
    /**
      * Works on GLES platforms only.
      */
    static void debugUniforms(int programId);
    static void debugMatrix4x4(const QMatrix4x4 & m, const QString & caption = "QMatrix4x4");
    static void debugMatrix3x3(const QMatrix3x3 & m, const QString & caption = "QMatrix3x3");
    static void debugVector4D(const QVector4D & v, const QString & caption = "QVector4D");
    static void debugVector3D(const QVector3D & v, const QString & caption = "QVector3D");
private:
   static bool enabled;
};

#endif // SHADERDEBUGGER_H
