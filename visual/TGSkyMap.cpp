
#include "TGSkyMap.h"
#include "SDL/SDL.h"

TGSkyMap::TGSkyMap(real size, const TGVectorF4 &center)
    : mySize(size), myCenter(center)
{

}

TGSkyMap::~TGSkyMap()
{
    if(glIsBuffer(myBuffers[VBO]))
        glDeleteBuffers(3, myBuffers);
    if(glIsTexture(myTexture))
        glDeleteTextures(1, &myTexture);
}

void TGSkyMap::Create(const char *textureFile)
{
    glGenBuffers(3, myBuffers);
    glGenTextures(1, &myTexture);

    real size = mySize/2;

    TGVectorF4 vdata[12] = {
        /*0 */TGVectorF4(-size,-size,-size) + myCenter,
        /*1 */TGVectorF4(size, -size, -size) + myCenter,
        /*2 */TGVectorF4(-size, -size, size) + myCenter,
        /*3 */TGVectorF4(size, -size, size) + myCenter,
        /*4 */TGVectorF4(-size, size, -size) + myCenter,
        /*5 */TGVectorF4(size, size,-size) + myCenter,
        /*6 */TGVectorF4(-size, size, size) + myCenter,
        /*7 */TGVectorF4(size, size, size) + myCenter,
        /*0 */TGVectorF4(-size,-size,-size) + myCenter,
        /*4 */TGVectorF4(-size,size,-size) + myCenter,
        /*4 */TGVectorF4(-size, size, -size) + myCenter,
        /*6 */TGVectorF4(-size, size, size) + myCenter,
    };

    glBindBuffer(GL_ARRAY_BUFFER, myBuffers[VBO]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(TGVectorF4)*12, vdata, GL_STATIC_DRAW);

    real tdata[12*2] = {
        0, 1,  1./4., 1,  3./4., 1, 2./4., 1,
        0, 1./2.,  1./4., 1./2.,  3./4., 1./2., 2./4., 1./2.,
        4./4., 1,  4./4., 1./2.,
        1./4., 0,  2./4., 0,
    };

    glBindBuffer(GL_ARRAY_BUFFER, myBuffers[TexCoord]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(real)*2*12, tdata, GL_STATIC_DRAW);

    ushort edata[12*3] = {
         0, 5, 4,  0, 1, 5,
         1, 7, 5,  1, 3, 7,
         3, 6, 7,  3, 2, 6,
         2, 9, 6,  2, 8, 9,
         0, 3, 1,  0, 2, 3,
        10, 5, 7, 10, 7,11
    };

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, myBuffers[Element]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(ushort)*12*3, edata, GL_STATIC_DRAW);

    SDL_Surface *bitmap = SDL_LoadBMP(textureFile);
    if((bitmap->w & (bitmap->w - 1)) != 0 || (bitmap->h & (bitmap->h -1)) != 0)
        Debug("Skymap dimesions not multiple of 2");

    GLenum textureFormat;
    uint Bpp = bitmap->format->BytesPerPixel;
    if (Bpp == 4)
    {
            if (bitmap->format->Rmask == 0x000000ff)
                    textureFormat = GL_RGBA;
            else
                    textureFormat = GL_BGRA;
    } 
    else if (Bpp == 3)
    {
            if (bitmap->format->Rmask == 0x000000ff)
                    textureFormat = GL_RGB;
            else
                    textureFormat = GL_BGR;
    } 
    else 
    {
        Bug(true, "Unknown skymap format");
    }

    glBindTexture(GL_TEXTURE_2D, myTexture);
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, bitmap->w, bitmap->h, textureFormat, GL_UNSIGNED_BYTE, bitmap->pixels);

    SDL_FreeSurface(bitmap);
}

void TGSkyMap::Draw(TGShader &shader, bool setTex)
{
    if(setTex)
        shader.SetTexture("Tiles", myTexture, 3);
    CheckError();
    shader.SetAttribute("Vertex", myBuffers[VBO], 4, GL_FLOAT, 0, 0);
    shader.SetAttribute("TexCoord", myBuffers[TexCoord], 2, GL_FLOAT, 0, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, myBuffers[Element]);
    CheckError();

    glDrawElements(GL_TRIANGLES, 12*3, GL_UNSIGNED_SHORT, 0);
}
