
#include "TGMesh.h"
#include "core/TGDebug.h"
#include "core/TGVector.h"

TGMesh::TGMesh(uint height, uint width)
    : myHeight(height) , myWidth(width)
{
    Bug(sizeof(TGVectorF4) != 16, "TGVectorF4-size is not 16");

    glGenBuffers(3, myBuffers);
    glBindBuffer(GL_ARRAY_BUFFER, myBuffers[VBO]);
    CheckError();
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*2*height*width,
            NULL, GL_STATIC_DRAW);
    CheckError();
    TGVectorF4 *vdata = static_cast<TGVectorF4*>(glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY));
    if(vdata == NULL)
        CheckError();
    
    for(uint i = 0; i < (height*width); i++)
    {
        vdata[i].X = Col(i);
        vdata[i].Y = Row(i);
        vdata[i].Z = 0;
        vdata[i].W = 1;
    }
    glUnmapBuffer(GL_ARRAY_BUFFER);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, myBuffers[ELEMENT]);
    CheckError();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 
            ((2*width-1)*(height-1)+1)*sizeof(ushort), NULL, GL_STATIC_DRAW);
    ushort *edata = static_cast<ushort*>(glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_WRITE_ONLY));
    if(edata == NULL)
        CheckError();

    uint stride = 2*width - 1;
    for(uint i = 0; i < height-1; i++)
    {
        for(uint j = 0; j < width; j++)
        {
            uint ji = (i & 1) == 1 ? width - j - 1 : j;
            edata[i*stride + ji*2] = Index(i,j);
            edata[i*stride + ji*2+1] = Index(i+1, j);
        }
    }
    edata[(2*width-1)*(height-1)] = Index(height-1, (height & 1) == 1 ? 0 : width-1);

    glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
    CheckError();
    
    //glGenBuffers(backlog, myDynBuffers);
    //for(uint i = 0; i < backlog; i++)
    //{
    //    glBindBuffer(GL_ARRAY_BUFFER, myDynBuffers[i]);
    //    glBufferData(GL_ARRAY_BUFFER, height*width*sizeof(GLfloat), NULL, GL_DYNAMIC_DRAW);
    //}
}

TGMesh::~TGMesh()
{
    glDeleteBuffers(3, myBuffers);
}

void TGMesh::Draw(TGShader &shader, real *data, bool lines)
{
    glBindBuffer(GL_ARRAY_BUFFER, myBuffers[Z]);
    glBufferData(GL_ARRAY_BUFFER, myHeight*myWidth*sizeof(GLfloat), data, GL_STREAM_DRAW);
    shader.SetAttribute("Z", myBuffers[Z], 1, GL_FLOAT, 0, 0, 0);
    shader.SetAttribute("Grid", myBuffers[VBO], 2, GL_FLOAT, 16, 0, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, myBuffers[ELEMENT]);
    CheckError();

    if(!lines)
        glDrawElements(GL_TRIANGLE_STRIP, (2*myWidth-1)*(myHeight-1) + 1, GL_UNSIGNED_SHORT, 0);
    else
        glDrawElements(GL_LINE_STRIP, (2*myWidth-1)*(myHeight-1) + 1, GL_UNSIGNED_SHORT, 0);
    CheckError();
}
