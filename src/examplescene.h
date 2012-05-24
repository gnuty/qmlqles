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
#ifndef EXAMPLESCENE_H
#define EXAMPLESCENE_H

#include "glitem.h"
#include "shaderdebugger.h"
#include "glescube.h"
#include "glesglobe.h"

/**
  * An example for a 3D scene. Contains coordinate axes, a simple Quad made from two triangles,
  * a cube without texture, a cube with a small texture on it and a globe with a rather large
  * (1024x512) texture.
  * Call showObject with "Triangles", "Cubes" or "Globe" to show the respective objects.
  */
class ExampleScene : public GLItem
{
    Q_OBJECT

public:
    ExampleScene();

public slots:
    /**
      * Rotate the scene
      */
    void rotate(float angle);
    /**
      * Reset scene to starting position.
      */
    void reset();
    /**
      * Select the object(s) to be shown
      */
    void showObject(QString object);

protected:
    /**
      * The overridden method that paints the objects.
      */
    void paintScene();

private:
    /**
      * Setup axes vertices and paint the coordinate axes.
      */
    void paintAxes();
    /**
      * Setup triangle vertices and colors and paint all vertices as triangles.
      */
    void paintTriangles();


    // viewing parameters
    float rotationAngle;
    float zOffset;

    //containers for demo data
    QVector<QVector3D>textures;
    QVector<QVector3D>vertices;
    QVector<QVector3D>normals;
    QVector<QVector4D>colors;

    //flags for the demo objects
    bool showAxes;
    bool showTriangles;
    bool showCubes;
    bool showGlobe;

    //the demo objects
    GLESCube * cube1; //cube without texture
    GLESCube * cube2; //cube with texture
    GLESGlobe * globe; //globe with texture

};

#endif // EXAMPLESCENE_H
