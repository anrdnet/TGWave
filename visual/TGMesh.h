
#include "core/TGDef.h"
#include "core/TGDebug.h"
#include "core/TGVector.h"

class TGMesh
{
    enum BufferKind
    {
        VBO=0,
        ELEMENT=1,
        COLOR=2
    };
    GLuint myBuffers[3];

    uint myHeight;
    uint myWidth;
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
    TGVectorF4 *myData;
    public:
    TGMesh(uint height, uint width);
    ~TGMesh();

    void Map();
    void Unmap();

    TGVectorF4 &E(uint i, uint j)
    {
        Bug(myData == NULL, "Access Z when unmaped");

        return myData[Index(i,j)];
    }

    void Draw();
    void DrawLines();
};
