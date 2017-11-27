#ifndef SHADER_H
#define SHADER_H

#include <GLES2/gl2.h>
#include <stdio.h>
#include <stdlib.h>

GLbyte* Loadfile(const char* location)
{
    FILE* fs;
    fs = fopen(location, "r");
    int i;
    for(i = 0; fgetc(fs) != EOF; i++);
    GLbyte* buffer = (GLbyte*)malloc(sizeof(char)*i -1);
    rewind(fs);
    for(i = 0 ;(buffer[i] = (GLbyte)fgetc(fs))!= EOF; i++);
    return buffer;
}


GLuint loadShader(GLenum shaderType, const char* pSource) {
    GLuint shader = glCreateShader(shaderType);
    if (shader) {
        glShaderSource(shader, 1, &pSource, NULL);
        glCompileShader(shader);
        GLint compiled = 0;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
        if (!compiled) {
            GLint infoLen = 0;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
            if (infoLen) {
                char* buf = (char*) malloc(infoLen);
                if (buf) {
                    glGetShaderInfoLog(shader, infoLen, NULL, buf);
                    printf("Could not compile shader %d:\n%s\n",
                            shaderType, buf);
                    free(buf);
                }
                glDeleteShader(shader);
                shader = 0;
            }
        }
    }
    return shader;
}

/*creating program fo shading*/

GLuint createProgram(const char* pVertexSource, const char* pFragmentSource) {
    GLuint vertexShader = loadShader(GL_VERTEX_SHADER, pVertexSource);
    if (!vertexShader) {
        return 0;
    }

    GLuint pixelShader = loadShader(GL_FRAGMENT_SHADER, pFragmentSource);
    if (!pixelShader) {
        return 0;
    }

    GLuint program = glCreateProgram();
    if (program) {
        glAttachShader(program, vertexShader);
        //checkGlError("glAttachShader");
        glAttachShader(program, pixelShader);
        //heckGlError("glAttachShader");
        glLinkProgram(program);
        GLint linkStatus = GL_FALSE;
        glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);
        if (linkStatus != GL_TRUE) {
            GLint bufLength = 0;
            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &bufLength);
            if (bufLength) {
                char* buf = (char*) malloc(bufLength);
                if (buf) {
                    glGetProgramInfoLog(program, bufLength, NULL, buf);
                    printf("Could not link program:\n%s\n", buf);
                    free(buf);
                }
            }
            glDeleteProgram(program);
            program = 0;
        }
    }
    return program;
}


/*to compile and link the shader program*/
GLuint MakeProgram(char* vertexShader, char* fragmentShader)
{
    GLuint programObject;
    GLuint vertex;
    GLuint fragment;
    if(vertexShader != NULL)
    {
        vertex = loadShader(GL_VERTEX_SHADER,vertexShader);
    }
    if(fragmentShader != NULL)
    {
        fragment = loadShader(GL_FRAGMENT_SHADER,fragmentShader);
    }
    programObject = glCreateProgram();
    if(programObject == 0)
    {
        return 0;
    }
    glAttachShader(programObject, vertex);                     //attach vertexShader to the program
    glAttachShader(programObject, fragment);
    return programObject;
}


#endif // SHADER_H
