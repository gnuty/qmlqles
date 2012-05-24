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
#include "examplescene.h"
#include "math.h"

ExampleScene::ExampleScene()
{
    rotationAngle = 0.0;
    zOffset = 0.0;
    setFlags(0);
    ShaderDebugger::setEnabled(false);
    renderer = new GLESRenderer(this, ":/resources/src/vshader1.vsh", ":/resources/src/fshader1.fsh");

    showTriangles = true;
    cube1 = new GLESCube();
    cube1->move(QVector3D(0.1,0.1,0.1));
    cube1->setTextureFile(":/resources/textures/xclock.png");

    cube2 = new GLESCube();
    cube2->move(QVector3D(-1.1,-1.1,-1.1));
    cube2->setColor(cl_Red);
    showCubes = false;

    globe = new GLESGlobe(":/resources/textures/earthmap1024x512.jpg", 1.0, 36, 72);
    showGlobe = false;
}

void ExampleScene::paintScene()
{
    renderer->rotate(0.1 * rotationAngle, v_Y);
    paintAxes();

    if(showGlobe)
        renderer->rotate(rotationAngle, QVector3D(0.0, 1.0, 0.0));
    else renderer->rotate(rotationAngle, QVector3D(1.0, 1.0, 1.0)); //rotate the objects
    if(showCubes)
    {
        renderer->setLightingEnabled(true);
        renderer->setColorArrayEnabled(false);
        cube1->draw(renderer);
        cube2->draw(renderer);
    }
    if(showGlobe)
    {
        renderer->setLightingEnabled(true);
        renderer->setColorArrayEnabled(false);
        globe->draw(renderer);
    }
    if(showTriangles)
        paintTriangles();
}

void ExampleScene::paintAxes()
{
    renderer->setLightingEnabled(false);
    renderer->setColorArrayEnabled(true);
    vertices.clear();
    vertices.append(QVector3D(-1.0,0.0,0.0));
    vertices.append(QVector3D(1.0,0.0,0.0));
    vertices.append(QVector3D(0.0,-1.0,0.0));
    vertices.append(QVector3D(0.0,1.0,0.0));
    vertices.append(QVector3D(0.0,0.0,-1.0));
    vertices.append(QVector3D(0.0,0.0,1.0));
    renderer->activateAttributeArray(GLESRenderer::VERTEX_LOCATION ,
                                     vertices.data(), sizeof(QVector3D));

    colors.clear();
    colors.append(QVector4D(1.0,0.0,0.0,1.0));
    colors.append(QVector4D(1.0,0.0,0.0,1.0));
    colors.append(QVector4D(0.0,1.0,0.0,1.0));
    colors.append(QVector4D(0.0,1.0,0.0,1.0));
    colors.append(QVector4D(0.0,0.0,1.0,1.0));
    colors.append(QVector4D(0.0,0.0,1.0,1.0));

    renderer->activateAttributeArray(GLESRenderer::COLOR_LOCATION,
                                     colors.constData(), sizeof(QVector4D));

    //Dummy texture coordinates
    // Without these, nothing is drawn on my desktop computer (Dell Notebook with GForce GPU)
    textures.clear();
    textures.append(QVector3D(-1.0,0.0,0.0));
    textures.append(QVector3D(1.0,0.0,0.0));
    textures.append(QVector3D(0.0,-1.0,0.0));
    textures.append(QVector3D(0.0,1.0,0.0));
    textures.append(QVector3D(0.0,0.0,-1.0));
    textures.append(QVector3D(0.0,0.0,1.0));
    //Dummy texture unit activation
    renderer->activateAttributeArray(GLESRenderer::TEXCOORD_LOCATION ,
                                     textures.data(), sizeof(QVector3D));

    glDrawArrays(GL_LINES, 0, vertices.size());
    renderer->disableAttributeArrays();
}

void ExampleScene::rotate(float angle)
{
    rotationAngle += angle;
    zOffset = sin(rotationAngle / 2.0 / 180.0 * M_PI);
}

void ExampleScene::reset()
{
    rotationAngle = 0.0;
    zOffset = 0.0;
}

void ExampleScene::paintTriangles()
{
    renderer->setLightingEnabled(true);
    renderer->setColorArrayEnabled(true);
    vertices.clear();
    colors.clear();
    vertices.append(QVector3D(0.0,0.0,0.0));
    colors.append(QVector4D(1.0,0.0,0.0,1.0));
    normals.append(QVector3D(1.0, 0.0,0.0));

    vertices.append(QVector3D(1.0,0.0,0.0));
    colors.append(QVector4D(1.0,0.0,0.0,1.0));
    normals.append(QVector3D(1.0, 0.0,0.0));

    vertices.append(QVector3D(0.0,1.0,0.0));
    colors.append(QVector4D(1.0,0.0,0.0,1.0));
    normals.append(QVector3D(1.0, 0.0, 0.0));


    vertices.append(QVector3D(1.0,0.0,0.0));
    colors.append(QVector4D(1.0,0.0,0.0,1.0));
    normals.append(QVector3D(0.0, 1.0,0.0));

    vertices.append(QVector3D(1.0,1.0,0.0));
    colors.append(QVector4D(0.0,1.0,0.0,1.0));
    normals.append(QVector3D(0.0, 1.0,0.0));

    vertices.append(QVector3D(0.0,1.0,0.0));
    colors.append(QVector4D(0.0,0.0,1.0,1.0));
    normals.append(QVector3D(0.0, 1.0,0.0));

    renderer->activateAttributeArray(GLESRenderer::COLOR_LOCATION,
                                     colors.constData(), sizeof(QVector4D));
    renderer->activateAttributeArray(GLESRenderer::VERTEX_LOCATION,
                                     vertices.constData(), sizeof(QVector3D));
    renderer->activateAttributeArray(GLESRenderer::NORMAL_LOCATION,
                                     normals.constData(), sizeof(QVector3D));
    renderer->bind();

    glDrawArrays(GL_TRIANGLES, 0, vertices.size());

    renderer->disableAttributeArrays();
    renderer->release();
}

/**
  * Select the object(s) to be shown
  */
void ExampleScene::showObject(QString object)
{
    showTriangles = false;
    showCubes = false;
    showGlobe = false;
    if(object == "Globe")
        showGlobe = true;
    else if(object == "Cubes")
         showCubes = true;
    else if(object == "Triangles")
        showTriangles = true;
}
