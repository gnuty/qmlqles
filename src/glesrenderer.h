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
#ifndef GLESRENDERER_H
#define GLESRENDERER_H

#include <QGLShaderProgram>
#include <QList>
#include <QStack>

#include "glcolorrgba.h"
#include "gldefines.h"

/**
  * A render program that supports vertex, colors, normals, texCoords, textures and matrix manipulation.
  * Owns a modelview and a projection matrix which can be used like in the old days of OpenGL 1.
  * The vertex shader program needs to stick to the following variable names:
  * attribute highp vec4 a_Vertex;
  * attribute highp vec4 a_Color;
  * attribute highp vec3 a_Normal;
  * attribute highp vec2 a_TexCoord;
  *
  * uniform bool u_ColorArrayEnabled
  * uniform bool u_LightingEnabled;
  * uniform highp mat4 u_MvpMatrix;
  * uniform highp mat3 u_NormalMatrix;
  * uniform highp vec3 u_LightDirection;
  * uniform highp vec4 u_AmbientAndDiffuseColor;
  * uniform highp vec4 u_SpecularColor;
  * uniform highp float u_Shininess;
  * uniform highp int u_PointSize;
  *
  * The fragment shader texture variable must have the following name:
  * uniform sampler2d s_Texture;
  *
  * These names are used to determine the locations of the varables in the shaders.
  * If you need more variables, subclass GLRenderer and add new variable(s) to
  * location_XXX variables. Extend virtual intialize(), bind() and disableAttributeArrays() functions
  * to support the new variable(s).
  *
  * The shader source should be in a separate file (e.g. added to the resources).
  * Example shaders vshader1 and fshader1 emulate a simple fixed-function lighted OpenGL 1 scene.
  *
  * Call initialize, after a valid OpenGL context has been made current.
  * Setup viewing with setViewport, setLookAt and setPerspective.
  * Viewport coordinates must be given as
  * GL-viewport coordinates, where lower left is (0,0).
  * Call bind to bind the program and set the uniform values you need.
  * After this, call activateAttributeLocation to enable the attribute arrays.
  * To change attribute arrays, call disableAttributeArrays and then again activateAttributeLocations.
  * Finally call release.
  */
class GLESRenderer : public QGLShaderProgram
{
    Q_OBJECT
public:
    typedef enum{
        VERTEX_LOCATION,
        NORMAL_LOCATION,
        COLOR_LOCATION,
        TEXCOORD_LOCATION
    }AttributeLocation;

    explicit GLESRenderer(QObject *parent,
                          const QString & vShaderFilename,
                          const QString & fShaderFilename );
    virtual ~GLESRenderer(){}

    //======================================================================================
    //Setters for uniforms
    /**
      * Set modelview matrix. Updates mvpMatrix and normalMatrix too.
      * Call setPMatrix or setPerspective first.
      */
    void setMvMatrix(const QMatrix4x4 newVal);
    /**
      * Getter for debugging.
      */
    const QMatrix4x4 & getMvMatrix(){return mvMatrix;}
     /**
       * Getter for debugging.
       */
     const QMatrix3x3 & getNormalMatrix(){return normalMatrix;}

    /**
      * Sets mvMatrix to a lookAt transformation.
      * Call setPMatrix or setPerspective first.
      */
    void setLookAt(const QVector3D & eye,const QVector3D & center,const QVector3D & up );

    /**
      * Set projection matrix. Call setMvMatrix after this.
      */
    void setPMatrix(const QMatrix4x4 newVal);
    /**
      * Getter for debugging.
      */
    const QMatrix4x4 & getPMatrix(){return pMatrix;}
    /**
      * Setup projection matrix. Call setMvMatrix after this.
      */
    void setPerspective(GLfloat fovy, GLfloat aspect, GLfloat nearClip, GLfloat farClip);
    
    /**
      * Set viewport
      * Viewport coordinates must be given as
      * GL-viewport coordinates, where lower left is (0,0).
      */
    void setViewport(int x, int y, int w, int h);
    /**
      * Uses viewport and matrix settings to reverse the vertex transformation chain.
      * WinX, winY, winZ are the coordinates in window coordinates. Lower left of viewport
      * is winX = 0, winY = 0. Use winZ = 0.0 for a point on near clipping plane
      * and winZ = 1.0 for a point on far clipping plane.
      * This function assumes, that the vertex shader computes gl_positon as v * mvpMatrix.
      * Use a custom shader reverse function, if this is not true.
      * Returns coordinate in object space.
      */
    QVector3D unProjectViewportPoint(float winX, float winY, float winZ);
    /**
      * Returns the points on near and far clipping plane, that correspond to the
      * mouseX and mouseY coordinates of a mouse click.
      */
    void calculateMousePoints(QVector3D * nearPoint, QVector3D * farPoint, int mouseX, int mouseY);
    /**
      * Set the color for ambient and diffuse lighting (or no lighting).
      * Alternatively use a color array and color attribute.
      * Defaults to white.
      */
    void setAmbientAndDiffuseColor(const GLColorRGBA newVal);
    /**
      * Set the dimming factor for ambient light.
      * Defaults to 0.2.
      */
    void setAmbientLightBrightness(float newVal);

    /**
      * Set the color for specular lighting.
      * Defaults to white.
      */
    void setSpecularColor(const GLColorRGBA newVal);
    /**
      * Set the shininess (exponent) for specular lighting.
      * Defaults to 50.
      */
    void setShininess(float newVal);

    /**
      * Enable / disable lighting.
      */
    void setLightingEnabled(bool newVal);
    /**
      * Returns lighting flag.
      */
    bool isLightingEnabled(){return lightingEnabled;}
    /**
      * Enable / disable color array.
      */
    void setColorArrayEnabled(bool newVal);
    /**
      * Returns lighting flag.
      */
    bool isColorArrayEnabled(){return colorArrayEnabled;}
    /**
      * Set the texture flag.
      */
    void setTextureEnabled(bool newVal);
    /**
      * Returns texture flag;
      */
    bool isTextureEnabled(){return textureEnabled;}
    /**
      * Set light direction.
      */
    void setLightDirection(const QVector3D & newVal);
    /**
      * Getter.
      */
    const QVector3D getLightDirection(){return lightDirection;}

    /**
      * Set size of points drawn with GL_POINTS.
      */
    void setPointSize(int newVal);

    /**
      * Returns pointSize;
      */
    int getPointSize(){return pointSize;}

    /**
      * Pushes mvMatrix.
      */
    void pushMvMatrix(){mvMatrixStack.push(mvMatrix);}

    /**
      * Pops mvMatrix from stack and updates normalMatrix and mvpMatrix.
      */
    void popMvMatrix();

    /**
      * Translates mvMatrix by v
      */
    void translate(const QVector3D & v);
    /**
      * Rotates mvMatrix by angle around axis
      */
    void rotate(GLfloat angle, const QVector3D & axis);
    /**
      * Scales mvMatrix.
      */
    void scale(const QVector3D & v );

    //======================================================================================
    //Attribute setters
    /**
      * Enables Vertex, normal, color or texCoord arrays and sets start adresses of arrays
      * Type may be: VERTEX_LOCATION, NORMAL_LOCATION, COLOR_LOCATION, TEXCOORD_LOCATION
      */
    bool activateAttributeArray (AttributeLocation location, const QVector3D * values, int stride = 0 );
    /**
      * Enables Vertex, normal, color or texCoord arrays and sets start adresses of arrays
      * Type may be: VERTEX_LOCATION, COLOR_LOCATION
      */
    bool activateAttributeArray (AttributeLocation location, const QVector4D * values, int stride = 0 );
    /**
      * Disables all enabled attribute arrays.
      * To be called after rendering an object.
      */
    virtual void disableAttributeArrays();

    //Binding etc.
    /**
      * Compile shaders, get attribute and uniform locations.
      * This function needs an active OpenGL context.
      * Returns false, if initialization failed.
      */
    virtual bool initialize();

    /**
      * Bind program and transfer attribute and uniform data to the shaders.
      * Calls initialize, if not alraedy initialized.
      * Returns false, if binding failed.
      */
    virtual bool bind();

    /**
      * Releases program. To be called, when all rendering is finished.
      * Calls disableAttributeArrays and releases program.
      */
    void release();

public slots:
protected:
    bool initialized;
    bool bound;

    //Uniforms to be passed to the shader
    //flags
    bool lightingEnabled; // flag for lighting
    bool colorArrayEnabled; //flag for a valid color array
    bool textureEnabled; //flag for active texturing
    bool invertedMvpMatrixValid; //flag for a valid inverted ModelViewProjection matrix
    //matrices
    QMatrix4x4 mvpMatrix; //combined modelview and projection matrix
    //The inverted mvp matrix for unproject purposes
    //Use the invertedMvpMatrixValid flag for calculating it when required.
    QMatrix4x4 invertedMvpMatrix;
    QStack <QMatrix4x4>mvMatrixStack;
    QMatrix4x4 mvMatrix; //modelview matrix
    QMatrix4x4 pMatrix;  //projection matrix
    float nearClip; //near clipping plane
    float farClip;  //far clipping plane
    QMatrix3x3 normalMatrix; //matrix for normal transformation
    //lighting
    QVector3D lightDirection; //direction of directional light
    QVector3D halfPlaneVector; //half plane vector for specular light calculation
    GLColorRGBA ambientAndDiffuseColor;
    float ambientLightBrightness;
    GLColorRGBA specularColor;
    float shininess;
    //texturing
    int pointSize;

    //Shaders and program
    QString vShaderFileName; //vertex shader
    QString fShaderFileName; //fragment shader
    QGLShader * vShader; //vertex shader
    QGLShader * fShader; // fragment shader
    QGLShaderProgram * renderProgram;

    // Locations of shader variables
    int location_aVertex;
    int location_aColor;
    int location_aNormal;
    int location_aTexCoord;
    int location_uColorArrayEnabled;
    int location_uLightingEnabled;
    int location_uNormalMatrix;
    int location_uMvpMatrix;
    int location_uAmbientAndDiffuseColor;
    int location_uAmbientLightBrightness;
    int location_uSpecularColor;
    int location_uShininess;
    int location_uLightDirection;
    int location_uHalfPlaneVector;
    int location_uPointSize;
    int location_uTextureSampler;
    int location_uTextureEnabled;

    //The list of enabled attribute locations
    QList<int>activeAttributeLocations;
    //viewport
    int viewportX;
    int viewportY;
    int viewportW;
    int viewportH;
};

#endif // GLESRENDERER_H
