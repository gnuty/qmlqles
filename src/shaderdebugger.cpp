#include "shaderdebugger.h"

bool ShaderDebugger::enabled = false;

ShaderDebugger::ShaderDebugger()
{
}

void ShaderDebugger::debugUniforms(int programId)
{
    if(!enabled) return;
#ifdef GLES
    char name[256];
    int length;
    int size;
    GLenum type;
    int nUniforms;
    glGetProgramiv(programId, GL_ACTIVE_UNIFORMS, &nUniforms);
    for (int i = 0; i < nUniforms; i++)
    {
        glGetActiveUniform(programId,
                           i,
                           sizeof(name),
                           &length,
                           &size,
                           &type,
                           name );
        qDebug("Properties of uniform at index %i : %s", i, name);
        switch (type)
        {
        case GL_FLOAT_MAT3: qDebug("Type : GL_FLOAT_MAT3");break;
        case GL_FLOAT_MAT4: qDebug("Type : GL_FLOAT_MAT4");break;
        case GL_FLOAT_VEC2: qDebug("Type : GL_FLOAT_VEC2");break;
        case GL_FLOAT_VEC3: qDebug("Type : GL_FLOAT_VEC3");break;
        case GL_FLOAT_VEC4: qDebug("Type : GL_FLOAT_VEC4");break;
        case GL_FLOAT: qDebug("Type : GL_FLOAT");break;
        case GL_BOOL: qDebug("Type : GL_BOOL");break;
        default: qDebug("Type: %i", type);
        }
        qDebug("Array size: %i", size);
        int location = glGetUniformLocation(programId, name);
        qDebug("Location: %i", location);
    }
#else
    qDebug("ShaderDebugger::debugUniforms works on GLES platforms only.");
#endif
}


void ShaderDebugger::debugMatrix4x4(const QMatrix4x4 & m, const QString & caption)
{
    if(!enabled) return;

    qDebug("%s",qPrintable(caption));
    for(int row = 0; row < 4; row ++)
    {
       QVector4D vRow = m.row(row);
       QString sRow = QString("  Row %1:  %2\t %3\t%4\t%5")\
               .arg(row).arg(vRow.x(),4,'g',4).arg(vRow.y(),4,'g',4).arg(vRow.z(),4,'g',4).arg(vRow.w(),4,'g',4);
       qDebug("%s",qPrintable(sRow));
    }
}

void ShaderDebugger::debugMatrix3x3(const QMatrix3x3 & m, const QString & caption)
{
    if(!enabled) return;

    QMatrix4x4 m4x4 = QMatrix4x4(m);
    qDebug("%s",qPrintable(caption));
    for(int row = 0; row < 3; row ++)
    {
       QVector4D vRow = m4x4.row(row);
       QString sRow = QString("  Row %1:  %2\t %3\t%4")\
               .arg(row).arg(vRow.x(),4,'g',4).arg(vRow.y(),4,'g',4).arg(vRow.z(),4,'g',4);
       qDebug("%s",qPrintable(sRow));
    }
}

void ShaderDebugger::debugVector4D(const QVector4D & v, const QString & caption)
{
    if(!enabled) return;

    QVector4D vRow = v;
    QString sRow = QString(" %1\t%2\t%3\t%4")\
            .arg(vRow.x(),4,'g',4).arg(vRow.y(),4,'g',4).arg(vRow.z(),4,'g',4).arg(vRow.w(),4,'g',4);
    qDebug("%s",qPrintable(caption + sRow));
}

void ShaderDebugger::debugVector3D(const QVector3D & v, const QString & caption)
{
    if(!enabled) return;

    QVector3D vRow = v;
    QString sRow = QString(" %1\t%2\t%3")\
            .arg(vRow.x(),4,'g',4).arg(vRow.y(),4,'g',4).arg(vRow.z(),4,'g',4);
    qDebug("%s",qPrintable(caption + sRow));
}
