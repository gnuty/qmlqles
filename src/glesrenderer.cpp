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
#include "glesrenderer.h"
#include "shaderdebugger.h"

#define DEBUG_GLESRENDERER
GLESRenderer::GLESRenderer(QObject *parent,
                           const QString & vShaderFilename,
                           const QString & fShaderFilename )
    :QGLShaderProgram(parent)
{
    this->vShaderFileName = vShaderFilename;
    this->fShaderFileName = fShaderFilename;

    //flags
    initialized = false;
    bound = false;
    lightingEnabled = false; // flag for lighting
    invertedMvpMatrixValid = false; //delay matrix inversion until it is really neccessary
    textureEnabled = false;

    lightDirection = QVector3D(1.0,1.0,1.0); //position of directional light
    shininess = 200.0;
    ambientAndDiffuseColor = cl_White;
    ambientLightBrightness = 0.2;
    specularColor = cl_White;

    vShader = NULL; //vertex shader
    fShader = NULL; // fragment shader
    renderProgram = NULL;

    // Locations of shader variables
    //attributes
    location_aVertex = -1;
    location_aColor = -1;
    location_aNormal = -1;
    location_aTexCoord = -1;
    //uniforms
    //flags
    location_uColorArrayEnabled = -1;
    location_uTextureEnabled = -1;
    location_uLightingEnabled = -1;
    //matrices
    location_uNormalMatrix = -1;
    location_uMvpMatrix = -1;
    //lighting
    location_uAmbientAndDiffuseColor = -1;
    location_uAmbientLightBrightness = -1;
    location_uSpecularColor = -1;
    location_uLightDirection = -1;
    location_uHalfPlaneVector = -1;
    //texture
    location_uTextureSampler = -1;

    //viewport
    viewportX = 0;
    viewportY = 0;
    viewportW = 100;
    viewportH = 100;

    //clippings
    nearClip = 1.0;
    farClip = 10.0;
}

/**
  * Set modelview matrix. Updates mvpMatrix and normalMatrix too.
  * Call setPMatrix first.
  */
void GLESRenderer::setMvMatrix(const QMatrix4x4 newVal)
{
    mvMatrix = newVal;
    normalMatrix = mvMatrix.normalMatrix(); //invert and transpose mvMatrix
    invertedMvpMatrixValid = false; //delay matrix inversion until it is really neccessary

    if(bound && (location_uNormalMatrix != -1))
       setUniformValue(location_uNormalMatrix, normalMatrix);

    mvpMatrix = pMatrix * mvMatrix;
    if(bound && (location_uMvpMatrix != -1))
          setUniformValue(location_uMvpMatrix, mvpMatrix);
#ifdef DEBUG_GLESRENDERER
    ShaderDebugger::debugMatrix4x4(mvMatrix, "GLESRenderer uses modelview matrix:");
    ShaderDebugger::debugMatrix3x3(normalMatrix, "GLESRenderer uses normal matrix:");
    ShaderDebugger::debugMatrix4x4(mvpMatrix, "GLESRenderer uses  MVP matrix:");
#endif
}

/**
  * Sets mvMatrix to a lookAt transformation.
  * Call setPMatrix or setPerspective first.
  */
void GLESRenderer::setLookAt(const QVector3D & eye,const QVector3D & center,const QVector3D & up )
{
    QMatrix4x4 m;
    m.setToIdentity();
    m.lookAt(eye, center, up);
    setMvMatrix(m);
}

/**
  * Set projection matrix. Call setMvMatrix after this.
  */
void GLESRenderer::setPMatrix(const QMatrix4x4 newVal)
{
    pMatrix = newVal;
}

/**
  * Setup projection matrix. Call setMvMatrix after this.
  */
void GLESRenderer::setPerspective(GLfloat fovy, GLfloat aspect, GLfloat near, GLfloat far)
{
        this->nearClip = near;
        this->farClip = far;
        pMatrix.setToIdentity();
        pMatrix.perspective(fovy, aspect,near,far);
#ifdef DEBUG_GLESRENDERER
    ShaderDebugger::debugMatrix4x4(pMatrix, "GLESRenderer uses projection matrix:");
#endif
}


/**
  * Set viewport
  */
void GLESRenderer::setViewport(int x, int y, int w, int h)
{
    viewportX = x;
    viewportY = y;
    viewportW = w;
    viewportH = h;
}

/**
  * Uses viewport and matrix settings to reverse the vertex transformation chain.
  * WinX, winY, winZ are the coordinates in window coordinates. Lower left of viewport
  * is winX = 0, winY = 0. Use winZ = 0.0 for a point on near clipping plane
  * and winZ = 1.0 for a point on far clipping plane.
  * This function assumes, that the vertex shader computes gl_positon as v * mvpMatrix.
  * Use a custom shader reverse function, if this is not true.
  * Returns coordinate in object space.
  */
QVector3D GLESRenderer::unProjectViewportPoint(float winX, float winY, float winZ)
{
    //reverse viewport transformation
    float xClip = 2.0 * (winX - (viewportX + viewportW) / 2.0) / viewportW;
    float yClip = 2.0 * (winY - (viewportY + viewportH) / 2.0) / viewportH;
    float zClip = 2.0 * (winZ - (nearClip + farClip) / 2.0) / (farClip - nearClip);
    qDebug("xClip: %f  yClip: %f zClip %f", xClip, yClip, zClip);
    if(!invertedMvpMatrixValid)
    {
       invertedMvpMatrix = mvpMatrix.inverted();
       invertedMvpMatrixValid = true;
    }
    ShaderDebugger::debugMatrix4x4(mvpMatrix, "MVP Matrix:");
    ShaderDebugger::debugMatrix4x4(invertedMvpMatrix, "Inverted MVP Matrix:");
    QVector3D result = invertedMvpMatrix * QVector3D(xClip, yClip, zClip);
    return result;
}
/**
  * Returns the points on near and far clipping plane, that correspond to the
  * mouseX and mouseY coordinates of a mouse click.
  */
void GLESRenderer::calculateMousePoints(QVector3D * nearPoint, QVector3D * farPoint, int mouseX, int mouseY)
{
    float winX = viewportX + mouseX;
    float winY = viewportY + (viewportH - mouseY);
    * nearPoint = unProjectViewportPoint(winX, winY, 0.0);
    * farPoint = unProjectViewportPoint(winX, winY, 1.0);
}

/**
  * Set the color for ambient and diffuse lighting (or no lighting).
  * Alternatively use a color array and color attribute.
  */
void GLESRenderer::setAmbientAndDiffuseColor(const GLColorRGBA newVal)
{
    ambientAndDiffuseColor = newVal;
    if(bound && location_uAmbientAndDiffuseColor != -1)
            setUniformValue(location_uAmbientAndDiffuseColor,
                            ambientAndDiffuseColor.red(), ambientAndDiffuseColor.green(),
                            ambientAndDiffuseColor.blue(), ambientAndDiffuseColor.alpha());
}

/**
  * Set the dimming factor for ambient light.
  * Defaults to 0.2.
  */
void GLESRenderer::setAmbientLightBrightness(float newVal)
{
    ambientLightBrightness = newVal;
    if(bound && location_uAmbientLightBrightness != -1)
            setUniformValue(location_uAmbientLightBrightness, ambientLightBrightness);
}

/**
  * Set the color for specular lighting.
  */
void GLESRenderer::setSpecularColor(const GLColorRGBA newVal)
{
    specularColor = newVal;
    if(bound && (location_uSpecularColor != -1))
            setUniformValue(location_uSpecularColor,
                            specularColor.red(), specularColor.green(),
                            specularColor.blue(), specularColor.alpha());
}

/**
  * Set the shininess for specular lighting.
  */
void GLESRenderer::setShininess(float newVal)
{
    shininess = newVal;
    if(bound && (location_uShininess != -1))
            setUniformValue(location_uShininess, shininess);
}

/**
  * Enable / disable lighting.
  */
void GLESRenderer::setLightingEnabled(bool newVal)
{
    lightingEnabled = newVal;
    if(bound && (location_uLightingEnabled != -1))
          setUniformValue(location_uLightingEnabled, lightingEnabled);
}

/**
  * Enable / disable color array.
  */
void GLESRenderer::setColorArrayEnabled(bool newVal)
{
    colorArrayEnabled = newVal;
    if(bound && (location_uColorArrayEnabled != -1))
          setUniformValue(location_uColorArrayEnabled, colorArrayEnabled);
}

/**
  * Set the texture flag.
  */
void GLESRenderer::setTextureEnabled(bool newVal)
{
    textureEnabled = newVal;
    if(bound && (location_uTextureEnabled != -1))
          setUniformValue(location_uTextureEnabled, textureEnabled);
}

/**
  * Set light direction.
  */
void GLESRenderer::setLightDirection(const QVector3D & newVal)
{
    lightDirection = newVal;
#ifdef DEBUG_GLESRENDERER
    ShaderDebugger::debugVector3D(lightDirection, "GLESRenderer uses lightDirection in object space:");
#endif
    QMatrix4x4 nMatrix = QMatrix4x4(normalMatrix);
    lightDirection = (nMatrix * lightDirection);//transform to eye space
    halfPlaneVector = (lightDirection + QVector3D(0.0,0.0,1.0)).normalized();//eye direction is 0,0,1 in eye space
#ifdef DEBUG_GLESRENDERER
    ShaderDebugger::debugVector3D(lightDirection, "GLESRenderer uses lightDirection in eye space:");
    ShaderDebugger::debugVector3D(lightDirection, "GLESRenderer uses halfplane vector in eye space:");
#endif
    if(bound && (location_uLightDirection != -1))
          setUniformValue(location_uLightDirection, lightDirection);
    if(location_uHalfPlaneVector != -1)
      setUniformValue(location_uHalfPlaneVector, halfPlaneVector);
}

/**
  * Set size of points drawn with GL_POINTS.
  */
void GLESRenderer::setPointSize(int newVal)
{
    pointSize = newVal;
    if(bound && (location_uPointSize != -1))
          setUniformValue(location_uPointSize, pointSize);
}

/**
  * Pops mvMatrix from stack and updates normalMatrix and mvpMatrix.
  */
void GLESRenderer::popMvMatrix()
{
    setMvMatrix(mvMatrixStack.pop());
}

/**
  * Translates mvMatrix by v
  */
void GLESRenderer::translate(const QVector3D & v)
{
    mvMatrix.translate(v);
    setMvMatrix(mvMatrix); //update normalMatrix and mvpMatrix and copy to shader
}

/**
  * Rotates mvMatrix by angle around axis
  */
void GLESRenderer::rotate(GLfloat angle, const QVector3D & axis)
{
    mvMatrix.rotate(angle, axis);
    setMvMatrix(mvMatrix); //update normalMatrix and mvpMatrix and copy to shader
}

/**
  * Scales mvMatrix.
  */
void GLESRenderer::scale(const QVector3D & v )
{
    mvMatrix.scale(v);
    setMvMatrix(mvMatrix);//update normalMatrix and mvpMatrix and copy to shader
}

/**
  * Compile shaders, get attribute and uniform locations.
  * This function needs an active OpenGL context.
  */
bool GLESRenderer::initialize()
{
    if(initialized)
        return true;
    //Setup shaders and program
    vShader = new QGLShader(QGLShader::Vertex,this); //vertex shader
    vShader->compileSourceFile(vShaderFileName);
    if(!vShader->isCompiled())
    {
        qDebug("GLESRenderer::initialize: Compiling vertex shader failed. Log follows:\n%s",
               qPrintable(vShader->log()));
        return false;
    }
    fShader = new QGLShader(QGLShader::Fragment,this); // fragment shader
    fShader->compileSourceFile(fShaderFileName);
    if(!fShader->isCompiled())
    {
        qDebug("GLESRenderer::initialize: Compiling fragment shader failed. Log follows:\n%s",
               qPrintable(fShader->log()));
        return false;
    }

    renderProgram = new QGLShaderProgram(this);
    renderProgram->addShader(vShader);
    renderProgram->addShader(fShader);
    renderProgram->link();
    if(!renderProgram->isLinked())
    {
        qDebug("GLESRenderer::initialize: Linking program failed. Log follows:\n%s",
               qPrintable(renderProgram->log()));
        return false;
    }

    // Get all locations of shader variables
    //Get locations of attributes and uniforms
    //Non existing attributes and uniforms will return -1
    //Attributes
    location_aVertex = renderProgram->attributeLocation("a_Vertex");
    location_aColor = renderProgram->attributeLocation("a_Color");
    location_aNormal = renderProgram->attributeLocation("a_Normal");
    location_aTexCoord = renderProgram->attributeLocation("a_TexCoord");
    //Uniforms
    //flags
    location_uLightingEnabled = renderProgram->uniformLocation("u_LightingEnabled");
    location_uColorArrayEnabled = renderProgram->uniformLocation("u_ColorArrayEnabled");
    location_uTextureEnabled = renderProgram->uniformLocation("u_TextureEnabled");
    //matrices
    location_uNormalMatrix = renderProgram->uniformLocation("u_NormalMatrix");
    location_uMvpMatrix = renderProgram->uniformLocation("u_MvpMatrix");
    //lighting
    location_uAmbientAndDiffuseColor = renderProgram->uniformLocation("u_AmbientAndDiffuseColor");
    location_uAmbientLightBrightness = renderProgram->uniformLocation("u_AmbientLightBrightness");
    location_uLightDirection = renderProgram->uniformLocation("u_LightDirection");
    location_uSpecularColor = renderProgram->uniformLocation("u_SpecularColor");
    location_uShininess = renderProgram->uniformLocation("u_Shininess");
    location_uHalfPlaneVector = renderProgram->uniformLocation("u_HalfPlaneVector");
    //texture
    location_uTextureSampler = renderProgram->uniformLocation("s_Texture");
    //point size
    location_uPointSize = renderProgram->uniformLocation("u_PointSize");

#ifdef DEBUG_GLESRENDERER
    ShaderDebugger::setEnabled(true);
    ShaderDebugger::debugUniforms(renderProgram->programId());
    ShaderDebugger::setEnabled(false);
#endif
    initialized = true;
    return true;
}

/**
  * Bind program and transfer attribute and uniform data to the shaders.
  * Calls initialize, if not already initialized.
  */
bool GLESRenderer::bind()
{
    bool ok = true;
    if(!initialized)
       ok = initialize();
    if(!ok)
        return false;

    renderProgram->bind();
    //Activate uniforms
    //flags
    if(location_uColorArrayEnabled != -1)
      setUniformValue(location_uColorArrayEnabled, colorArrayEnabled);
    if(location_uLightingEnabled != -1)
      setUniformValue(location_uLightingEnabled, lightingEnabled);
    if(location_uTextureEnabled != -1)
        setUniformValue(location_uTextureEnabled, textureEnabled);
    //matrices
    if( location_uNormalMatrix != -1)
       setUniformValue(location_uNormalMatrix, normalMatrix);
    if(location_uMvpMatrix != -1)
      setUniformValue(location_uMvpMatrix, mvpMatrix);
    //lighting
    if(location_uAmbientAndDiffuseColor != -1)
        setUniformValue(location_uAmbientAndDiffuseColor,
                        ambientAndDiffuseColor.red(), ambientAndDiffuseColor.green(),
                        ambientAndDiffuseColor.blue(), ambientAndDiffuseColor.alpha());
    if(location_uAmbientLightBrightness != -1)
                setUniformValue(location_uAmbientLightBrightness, ambientLightBrightness);
    if(location_uLightDirection != -1)
      setUniformValue(location_uLightDirection, lightDirection);
    if(location_uSpecularColor != -1)
        setUniformValue(location_uSpecularColor,
                        specularColor.red(), specularColor.green(),
                        specularColor.blue(), specularColor.alpha());
    if(location_uShininess != -1)
            setUniformValue(location_uShininess, shininess);
    if(location_uHalfPlaneVector != -1)
      setUniformValue(location_uHalfPlaneVector, halfPlaneVector);
    //texture
    if(location_uTextureSampler != -1)
        setUniformValue(location_uTextureSampler, 0); //set sampler to use texture unit 0
    //point size
    if(location_uPointSize != -1)
          setUniformValue(location_uPointSize, pointSize);
    bound = true;
    return bound;
}

/**
  * Enables Vertex, normal, color or texCoord arrays and sets start adresses of arrays
  * Type may be: VERTEX_LOCATION, NORMAL_LOCATION, COLOR_LOCATION, TEXCOORD_LOCATION
  */
bool GLESRenderer::activateAttributeArray (AttributeLocation arrayLocation, const QVector3D * values, int stride )
{
    int location = -1;
    int elements = 3;
    switch(arrayLocation){
      case VERTEX_LOCATION: location = location_aVertex; break;
      case NORMAL_LOCATION: location = location_aNormal; break;
      case COLOR_LOCATION : {
                                location = location_aColor;
                                elements = 4; //RGBA colors
                             }break;
      case TEXCOORD_LOCATION : location = location_aTexCoord; break;
      default: return false;
    }

    if(values && (location != -1))
    {
        enableAttributeArray(location);
        setAttributeArray(location, GL_FLOAT, values, elements, stride);
        activeAttributeLocations.append(location);
        return true;
    }
    else return false;
}

/**
  * Enables Vertex, normal, color or texCoord arrays and sets start adresses of arrays
  * Type may be: VERTEX_LOCATION, COLOR_LOCATION
  */
bool GLESRenderer::activateAttributeArray (AttributeLocation arrayLocation, const QVector4D * values, int stride )
{
    int location = -1;
    switch(arrayLocation){
      case VERTEX_LOCATION: location = location_aVertex; break;
      case COLOR_LOCATION : location = location_aColor; break;
      default: return false;
    }

    if(values && (location != -1))
    {
        enableAttributeArray(location);
        setAttributeArray(location, GL_FLOAT, values, 3, stride);
        activeAttributeLocations.append(location);
        return true;
    }
    else return false;
}

/**
  * Disables all enabled attribute arrays.
  */
void GLESRenderer::disableAttributeArrays()
{
    for(int i = 0; i < activeAttributeLocations.size(); i++)
        disableAttributeArray(activeAttributeLocations[i]);
    activeAttributeLocations.clear();
}

/**
  * Releases program. To be called, when all rendering is finished.
  */
void GLESRenderer::release()
{
    disableAttributeArrays();
    QGLShaderProgram::release();
    bound = false;
}
