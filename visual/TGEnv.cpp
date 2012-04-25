
#include "visual/TGEnv.h"
#include "core/TGDebug.h"
#include "core/TGVector.h"
#include "TilesTextureData.h"
#include <GL/glu.h>

TGEnv::TGEnv()
{

}

TGEnv::~TGEnv()
{
    if(glIsBuffer(myBuffers[0]))
        glDeleteBuffers(3, myBuffers);
    if(glIsTexture(myTexture))
        glDeleteTextures(1, &myTexture);
}

void TGEnv::Create(real tw, real th, real border, real height, real depth)
{
    glGenBuffers(3, myBuffers);
    CheckError();
    TGVectorF4 vdata[36];
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
    vdata[16] = TGVectorF4(0, height, 0);
    vdata[17] = TGVectorF4(tw, height, 0);
    vdata[18] = TGVectorF4(0, height, th);
    vdata[19] = TGVectorF4(tw, height, th);
    vdata[20] = TGVectorF4(0, height-depth, 0);
    vdata[21] = TGVectorF4(tw, height-depth, 0);
    vdata[22] = TGVectorF4(0, height-depth, th);
    vdata[23] = TGVectorF4(tw, height-depth, th);

    vdata[24] = TGVectorF4(-border, height, -border);
    vdata[25] = TGVectorF4(tw+border, height, -border);
    vdata[26] = TGVectorF4(-border, height, th+border);
    vdata[27] = TGVectorF4(tw+border, height, th+border);
    vdata[28] = TGVectorF4(-border, height - depth - 0.1, -border);
    vdata[29] = TGVectorF4(tw+border, height - depth - 0.1, -border);
    vdata[30] = TGVectorF4(-border, height -depth - 0.1 , th+border);
    vdata[31] = TGVectorF4(tw+border, height - depth - 0.1, th+border);

    vdata[32] = TGVectorF4(0, height, 0);
    vdata[33] = TGVectorF4(tw, height, 0);
    vdata[34] = TGVectorF4(0, height, th);
    vdata[35] = TGVectorF4(tw, height, th);

    glBindBuffer(GL_ARRAY_BUFFER, myBuffers[VBO]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(TGVectorF4)*36, vdata, GL_STATIC_DRAW);

    real TexScale = 1.5;
    real tdata[72];
    tdata[(w*0+0)*2] =( -border)*TexScale;
    tdata[(w*0+0)*2+1] =(-border)*TexScale;
    tdata[(w*0+1)*2] =( -border)*TexScale;
    tdata[(w*0+1)*2+1] =0;
    tdata[(w*0+2)*2] =( -border)*TexScale;
    tdata[(w*0+2)*2+1] =(tw)*TexScale;
    tdata[(w*0+3)*2] =( -border)*TexScale;
    tdata[(w*0+3)*2+1] =(tw+border)*TexScale;
    tdata[(w*1+0)*2] = 0;
    tdata[(w*1+0)*2+1] =(-border)*TexScale;
    tdata[(w*1+1)*2] = 0;
    tdata[(w*1+1)*2+1] =0;
    tdata[(w*1+2)*2] = 0;
    tdata[(w*1+2)*2+1] =(tw)*TexScale;
    tdata[(w*1+3)*2] = 0;
    tdata[(w*1+3)*2+1] =(tw+border)*TexScale;
    tdata[(w*2+0)*2] =( th)*TexScale;
    tdata[(w*2+0)*2+1] =(-border)*TexScale;
    tdata[(w*2+1)*2] =( th)*TexScale;
    tdata[(w*2+1)*2+1] =0;
    tdata[(w*2+2)*2] =( th)*TexScale;
    tdata[(w*2+2)*2+1] =(tw)*TexScale;
    tdata[(w*2+3)*2] =( th)*TexScale;
    tdata[(w*2+3)*2+1] =(tw+border)*TexScale;
    tdata[(w*3+0)*2] =( th+border)*TexScale;
    tdata[(w*3+0)*2+1] =(-border)*TexScale;
    tdata[(w*3+1)*2] =( th+border)*TexScale;
    tdata[(w*3+1)*2+1] =0;
    tdata[(w*3+2)*2] =( th+border)*TexScale;
    tdata[(w*3+2)*2+1] =(tw)*TexScale;
    tdata[(w*3+3)*2] =( th+border)*TexScale;
    tdata[(w*3+3)*2+1] =(tw+border)*TexScale;

    tdata[(16)*2] = 0;
    tdata[(16)*2+1] =( -depth)*TexScale;
    tdata[(17)*2] = 0;
    tdata[(17)*2+1] =( depth + tw)*TexScale;
    tdata[(18)*2] =( th)*TexScale;
    tdata[(18)*2+1] =( -depth)*TexScale;
    tdata[(19)*2] =( th)*TexScale;
    tdata[(19)*2+1] =( depth + tw)*TexScale;
    tdata[(20)*2] = 0;
    tdata[(20)*2+1] =0;
    tdata[(21)*2] = 0;
    tdata[(21)*2+1] =(tw)*TexScale;
    tdata[(22)*2] =( th)*TexScale;
    tdata[(22)*2+1] =0;
    tdata[(23)*2] =( th)*TexScale;
    tdata[(23)*2+1] =(tw)*TexScale;

    tdata[(24)*2] = 0;
    tdata[(24)*2+1] = 0;
    tdata[(25)*2] = 0;
    tdata[(25)*2+1] = 0;
    tdata[(26)*2] = 0;
    tdata[(26)*2+1] = 0;
    tdata[(27)*2] = 0;
    tdata[(27)*2+1] = 0;
    tdata[(28)*2] = 0;
    tdata[(28)*2+1] = 0;
    tdata[(29)*2] = 0;
    tdata[(29)*2+1] = 0;
    tdata[(30)*2] = 0;
    tdata[(30)*2+1] = 0;
    tdata[(31)*2] = 0;
    tdata[(31)*2+1] = 0;
    tdata[(32)*2] =( -depth)*TexScale;
    tdata[(32)*2+1] = 0;
    tdata[(33)*2] =( -depth)*TexScale;
    tdata[(33)*2+1] =( tw)*TexScale;
    tdata[(34)*2] =( th+depth)*TexScale;
    tdata[(34)*2+1] = 0;
    tdata[(35)*2] =( th+depth)*TexScale;
    tdata[(35)*2+1] =( tw)*TexScale;

    glBindBuffer(GL_ARRAY_BUFFER, myBuffers[TexCoord]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(real)*2*36, tdata, GL_STATIC_DRAW);

    ushort edata[102] = {
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
        18,20,16,
        18,22,20,
        32,20,21,
        32,21,33,
        17,21,23,
        17,23,19,
        35,23,22,
        35,22,34,
        20,22,23,
        20,23,21,
        24,29,28,
        24,25,29,
        25,31,29,
        25,27,31,
        27,30,31,
        27,26,30,
        26,28,30,
        26,24,28
    };

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, myBuffers[Element]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(ushort)*102, edata, GL_STATIC_DRAW);

    glGenTextures(1, &myTexture);
    CheckError();
    glBindTexture(GL_TEXTURE_2D, myTexture);
    CheckError();
    glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
    //gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, TilesTexture.width, TilesTexture.height, GL_RGB, GL_UNSIGNED_BYTE, TilesTexture.pixel_data);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, TilesTexture.width, TilesTexture.height, 0, GL_RGB, GL_UNSIGNED_BYTE, TilesTexture.pixel_data);
    CheckError();
}

void TGEnv::Draw(TGShader &shader)
{
    shader.SetTexture("Tiles", myTexture, 1);
    CheckError();
    shader.SetAttribute("Vertex", myBuffers[VBO], 4, GL_FLOAT, 0, 0);
    shader.SetAttribute("TexCoord", myBuffers[TexCoord], 2, GL_FLOAT, 0, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, myBuffers[Element]);
    CheckError();

    glDrawElements(GL_TRIANGLES, 102, GL_UNSIGNED_SHORT, 0);
    CheckError();
}
