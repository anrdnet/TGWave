
#include "TGMesh.h"
#include "core/TGDebug.h"
#include "core/TGVector.h"

TGMesh::TGMesh(uint height, uint width, real dx, real dy)
    : myHeight(height) , myWidth(width), myDx(dx), myDy(dy)
{

}

void TGMesh::Create()
{
    this->TGMesh::~TGMesh();
    Bug(sizeof(TGVectorF4) != 16, "TGVectorF4-size is not 16");

    glGenBuffers(3, myBuffers);
    glBindBuffer(GL_ARRAY_BUFFER, myBuffers[VBO]);
    CheckError();
    TGVectorF4 *vdata = new TGVectorF4[myHeight*myWidth];
    if(vdata == NULL)
        CheckError();
    
    for(uint i = 0; i < (myHeight*myWidth); i++)
    {
        vdata[i].X = Col(i) * myDx;
        vdata[i].Y = Row(i) * myDy;
        vdata[i].Z = 0;
        vdata[i].W = 1;
    }

    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*4*myHeight*myWidth,
            vdata, GL_STATIC_DRAW);
    CheckError();

    delete [] vdata;
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, myBuffers[ELEMENT]);
    CheckError();
    ushort *edata = new ushort[(2*myWidth-1)*(myHeight-1)+1];
    if(edata == NULL)
        CheckError();

    uint stride = 2*myWidth - 1;
    for(uint i = 0; i < myHeight-1; i++)
    {
        for(uint j = 0; j < myWidth; j++)
        {
            uint ji = (i & 1) == 1 ? myWidth - j - 1 : j;
            edata[i*stride + ji*2] = Index(i,j);
            edata[i*stride + ji*2+1] = Index(i+1, j);
        }
    }
    edata[(2*myWidth-1)*(myHeight-1)] = Index(myHeight-1, (myHeight & 1) == 1 ? 0 : myWidth-1);

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 
            ((2*myWidth-1)*(myHeight-1)+1)*sizeof(ushort), edata, GL_STATIC_DRAW);
    CheckError();
    delete [] edata;
    
    //glGenBuffers(backlog, myDynBuffers);
    //for(uint i = 0; i < backlog; i++)
    //{
    //    glBindBuffer(GL_ARRAY_BUFFER, myDynBuffers[i]);
    //    glBufferData(GL_ARRAY_BUFFER, myHeight*myWidth*sizeof(GLfloat), NULL, GL_DYNAMIC_DRAW);
    //}
}

TGMesh::~TGMesh()
{
    Debug("Delete mesh");
    if(glIsBuffer(myBuffers[0]))
        glDeleteBuffers(3, myBuffers);
}

void TGMesh::Draw(TGShader &shader, real *data, bool lines)
{
    CheckError();
    glBindBuffer(GL_ARRAY_BUFFER, myBuffers[Z]);
    CheckError();
    glBufferData(GL_ARRAY_BUFFER, myHeight*myWidth*sizeof(GLfloat), data, GL_STREAM_DRAW);
    CheckError();
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
