
#include "TGSkyMap.h"
#include "SDL/SDL.h"

TGSkyMap::TGSkyMap(real size, const TGVectorF4 &center)
    : mySize(size), myCenter(center)
{

}

TGSkyMap::~TGSkyMap()
{
    if(glIsBuffer(myBuffers[VBO]))
        glDeleteBuffers(2, myBuffers);
    if(glIsTexture(myTexture) && own)
        glDeleteTextures(1, &myTexture);
}

char const * const filePostfix[6] = {
    "_r.bmp",
    "_l.bmp",
    "_u.bmp",
    "_d.bmp",
    "_f.bmp",
    "_b.bmp",
};

const GLenum Faces[6] = {
    GL_TEXTURE_CUBE_MAP_POSITIVE_X,
    GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
    GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
    GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
    GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
    GL_TEXTURE_CUBE_MAP_NEGATIVE_Z,
};

void TGSkyMap::Create(const char *textureFile)
{
    own = true;
    glGenBuffers(2, myBuffers);
    glGenTextures(1, &myTexture);

    real size = 1;

    TGVectorF4 vdata[12] = {
        /*0 */TGVectorF4(-size,-size,-size),
        /*1 */TGVectorF4(size, -size, -size),
        /*2 */TGVectorF4(-size, -size, size),
        /*3 */TGVectorF4(size, -size, size),
        /*4 */TGVectorF4(-size, size, -size),
        /*5 */TGVectorF4(size, size,-size),
        /*6 */TGVectorF4(-size, size, size),
        /*7 */TGVectorF4(size, size, size),
        /*0 */TGVectorF4(-size,-size,-size),
        /*4 */TGVectorF4(-size,size,-size),
        /*4 */TGVectorF4(-size, size, -size),
        /*6 */TGVectorF4(-size, size, size),
    };

    glBindBuffer(GL_ARRAY_BUFFER, myBuffers[VBO]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(TGVectorF4)*12, vdata, GL_STATIC_DRAW);

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

    uint namelen = strlen(textureFile) + 6;
    char name[namelen+1];
    name[namelen] = 0;
    memcpy(name, textureFile, namelen);
    for(uint i = 0; i < 6; i++)
    {
        memcpy(name + namelen - 6, filePostfix[i], 6);
        Debug("%s",name);
        SDL_Surface *bitmap = SDL_LoadBMP(name);
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

        glBindTexture(GL_TEXTURE_CUBE_MAP, myTexture);
        gluBuild2DMipmaps(Faces[i], GL_RGB, bitmap->w, bitmap->h, textureFormat, GL_UNSIGNED_BYTE, bitmap->pixels);

        SDL_FreeSurface(bitmap);
    }
}

void TGSkyMap::Draw(TGShader &shader, bool setTex)
{
    if(setTex)
        shader.SetTexture("Tex", myTexture, 3, GL_TEXTURE_CUBE_MAP);
    CheckError();
    shader.SetAttribute("Vertex", myBuffers[VBO], 4, GL_FLOAT, 0, 0);
    shader.SetUniformf("Size", mySize);
    shader.SetUniformv4("Center", myCenter);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, myBuffers[Element]);
    CheckError();

    glDrawElements(GL_TRIANGLES, 12*3, GL_UNSIGNED_SHORT, 0);
}
