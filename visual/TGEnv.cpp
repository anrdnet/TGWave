
#include "visual/TGEnv.h"
#include "core/TGDebug.h"
#include "core/TGVector.h"

TGEnv::TGEnv()
{

}

void TGEnv::Create(real tw, real th, real border, real height, real depth)
{
    glGenBuffers(2, myBuffers);
    CheckError();
    TGVectorF4 vdata[20];
    static const uint w = 4;
    vdata[w*0+0] = TGVectorF4(-border, height, -border);
    vdata[w*0+1] = TGVectorF4(0, height, -border);
    vdata[w*0+2] = TGVectorF4(tw, height, -border);
    vdata[w*0+3] = TGVectorF4(tw+border, height, -border);
    vdata[w*1+0] = TGVectorF4(-border, height, 0);
    vdata[w*1+1] = TGVectorF4(0, height, 0);
    vdata[w*1+2] = TGVectorF4(tw, height, 0);
    vdata[w*1+3] = TGVectorF4(tw+border, height, 0);
    vdata[w*2+0] = TGVectorF4(-border, height, th);
    vdata[w*2+1] = TGVectorF4(0, height, th);
    vdata[w*2+2] = TGVectorF4(tw, height, th);
    vdata[w*2+3] = TGVectorF4(tw+border, height, th);
    vdata[w*3+0] = TGVectorF4(-border, height, th+border);
    vdata[w*3+1] = TGVectorF4(0, height, th+border);
    vdata[w*3+2] = TGVectorF4(tw, height, th+border);
    vdata[w*3+3] = TGVectorF4(tw+border, height, th+border);
    vdata[16] = TGVectorF4(0, height-depth, 0);
    vdata[17] = TGVectorF4(tw, height-depth, 0);
    vdata[18] = TGVectorF4(0, height-depth, th);
    vdata[19] = TGVectorF4(tw, height-depth, th);
    vdata[20] = TGVectorF4(-border, height-depth - 0.1, -border);
    vdata[21] = TGVectorF4(tw+border, height - depth - 0.1, -border);
    vdata[22] = TGVectorF4(-border, height -depth - 0.1 , th+border);
    vdata[23] = TGVectorF4(tw+border, height - depth - 0.1, th+border);

    glBindBuffer(GL_ARRAY_BUFFER, myBuffers[VBO]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(TGVectorF4)*24, vdata, GL_STATIC_DRAW);

    ushort edata[96] = {
         0, 4, 5,
         0, 5, 1,
         1, 5, 6,
         1, 6, 2,
         2, 6, 7,
         2, 7, 3,
         6,10,11,
         6,11, 7,
        10,14,15,
        10,15,11,
         9,13,14,
         9,14,10,
         8,12,13,
         8,13, 9,
         4, 8, 9,
         4, 9, 5,
         9,16, 5,
         9,18,16,
         5,16,17,
         5,17, 6,
         6,17,19,
         6,19,10,
        10,19,18,
        10,18,9,
         0,21,20,
         0, 3,21,
         3,23,21,
         3,15,23,
        15,22,23,
        15,12,22,
        12,20,22,
        12, 0,20
    };

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, myBuffers[Element]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(ushort)*96, edata, GL_STATIC_DRAW);
}

void TGEnv::Draw(TGShader &shader)
{
    shader.SetAttribute("Vertex", myBuffers[VBO], 4, GL_FLOAT, 0, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, myBuffers[Element]);
    CheckError();

    glDrawElements(GL_TRIANGLES, 96, GL_UNSIGNED_SHORT, 0);
}
