#ifndef DRAW_GEO_H
#define DRAW_GEO_H
#include <stdio.h>
#include <stdlib.h>
#include <GLES2/gl2.h>
#define VERTEX_POS_SIZE 3 // x, y and z
#define VERTEX_NORMAL_SIZE 3 // x, y and z
#define VERTEX_TEXCOORD0_SIZE 2 // s and t
#define VERTEX_COLOR_SIZE 4
#define VERTEX_POS_INDX 0
#define VERTEX_NORMAL_INDX 1
#define VERTEX_TEXCOORD0_INDX 2
#define VERTEX_COLOR_INDX 1
//
// numVertices – number of vertices
// vtxBuf – an array of pointers describing attribute data
// vtxStrides – an array of stride values for each attribute
// numIndices – number of element indices of primitive
// indices – actual element index buffer
//
void drawPrimitiveTexture(GLuint program,GLint numVertices,GLfloat **vtxBuf, GLint *vtxStrides,GLint numIndices, GLushort *indices)
{
    GLuint vboIds[4];
 // vboIds[0] – used to store vertex position
 // vboIds[1] – used to store vertex normal
 // vboIds[2] – used to store vertex texture coordinate 0
 // vboIds[3] – used to store element indices
    glGenBuffers(4, vboIds);
    glBindBuffer(GL_ARRAY_BUFFER, vboIds[0]);
    glBufferData(GL_ARRAY_BUFFER, vtxStrides[0] * numVertices,vtxBuf[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, vboIds[1]);
    glBufferData(GL_ARRAY_BUFFER, vtxStrides[1] * numVertices,vtxBuf[1], GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, vboIds[2]);
    glBufferData(GL_ARRAY_BUFFER, vtxStrides[2] * numVertices,vtxBuf[2], GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboIds[3]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(GLushort) * numIndices,indices, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, vboIds[0]);
    glEnableVertexAttribArray(VERTEX_POS_INDX);
    glBindBuffer(GL_ARRAY_BUFFER, vboIds[1]);
    glEnableVertexAttribArray(VERTEX_NORMAL_INDX);
    glBindBuffer(GL_ARRAY_BUFFER, vboIds[2]);
    glEnableVertexAttribArray(VERTEX_TEXCOORD0_INDX);
    glVertexAttribPointer(VERTEX_POS_INDX, VERTEX_POS_SIZE,GL_FLOAT, GL_FALSE, vtxStrides[0], 0);
    glVertexAttribPointer(VERTEX_NORMAL_INDX, VERTEX_NORMAL_SIZE,GL_FLOAT, GL_FALSE, vtxStrides[1], 0);
    glVertexAttribPointer(VERTEX_TEXCOORD0_INDX,VERTEX_TEXCOORD0_SIZE,GL_FLOAT, GL_FALSE, vtxStrides[2], 0);
    glBindAttribLocation(program, VERTEX_POS_INDX, "v_position");
    glBindAttribLocation(program, VERTEX_NORMAL_INDX, "v_normal");
    glBindAttribLocation(program, VERTEX_TEXCOORD0_INDX,"v_texcoord");
    glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_SHORT, 0);
    glDeleteBuffers(4, vboIds);
}

void drawPrimitive(GLuint prgm,GLint numVertices,GLfloat **vtxBuf, GLint *vtxSize,GLint numIndices, GLushort *indices, GLenum primitive)
{
    GLuint vboIds[3];
 // vboIds[0] – used to store vertex position
 // vboIds[1] – used to store color
 // vboIds[2] – used to store element indices

    glGenBuffers(3, vboIds);
    glBindBuffer(GL_ARRAY_BUFFER, vboIds[0]);
    glBufferData(GL_ARRAY_BUFFER, 5*vtxSize[0] * numVertices,vtxBuf[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, vboIds[1]);
    glBufferData(GL_ARRAY_BUFFER, 3*vtxSize[1] * numVertices,vtxBuf[1], GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboIds[2]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(GLushort) * numIndices,indices, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, vboIds[1]);
    glVertexAttribPointer(VERTEX_COLOR_INDX, VERTEX_COLOR_SIZE,GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(VERTEX_COLOR_INDX);
    glBindBuffer(GL_ARRAY_BUFFER, vboIds[0]);
    glVertexAttribPointer(VERTEX_POS_INDX, VERTEX_POS_SIZE,GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(VERTEX_POS_INDX);
    //glBindAttribLocation(prgm, VERTEX_POS_INDX, "vPosition");
    //glBindAttribLocation(prgm, VERTEX_COLOR_INDX, "vColor");
    glEnable(GL_PRIMITIVE_RESTART);
    glDrawElements(primitive, numIndices, GL_UNSIGNED_SHORT, 0);
    glDeleteBuffers(3, vboIds);
}



#endif // DRAW_GEO_H
