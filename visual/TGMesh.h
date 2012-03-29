
#ifndef TGMESH_H_
#define TGMESH_H_

#include "core/TGDef.h"
#include "core/TGDebug.h"
#include "core/TGVector.h"
#include "visual/TGShader.h"

class TGMesh
{
    enum BufferKind
    {
        VBO=0,
        ELEMENT=1,
        Z=2,
        Norm=3
    };
    GLuint myBuffers[4];
    GLuint *myDynBuffers;

    uint myHeight;
    uint myWidth;
    uint myBacklog;
    real myDx;
    real myDy;

    uint Index(uint row, uint col)
    {
        Bug(row >= myHeight, "H out of bounds");
        Bug(col >= myWidth, "W out of bounds");
        return myWidth*row+col;
    }
    uint Row(uint index)
    {
        return index/myWidth;
    }
    uint Col(uint index)
    {
        return index%myWidth;
    }

    public:
    TGMesh(uint height, uint width, real dx, real dy);
    ~TGMesh();

    void Create();
    void Draw(TGShader &shader, real *data, TGVectorF4 *normals, bool lines);
};

#endif
