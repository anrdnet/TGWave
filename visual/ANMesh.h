
#include "core/ANDef.h"
#include "core/ANDebug.h"
#include "core/ANVector.h"

class ANMesh
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
    ANVectorF4 *myData;
    public:
    ANMesh(uint height, uint width);
    ~ANMesh();

    void Map();
    void Unmap();

    ANVectorF4 &E(uint i, uint j)
    {
        Bug(myData == NULL, "Access Z when unmaped");

        return myData[Index(i,j)];
    }

    void Draw();
    void DrawLines();
};
