
#ifndef TGRESOURCEMTGAGER_H_
#define TGRESOURCEMTGAGER_H_

#include <string>
#include <vector>
#include "core/TGDef.h"
#include "core/TGDebug.h"

enum class TGResourceType
{
    Shader = 0,
    Texture = 1
};

typedef uint TGResource;

class TGResourceManager
{
    struct TGResourceEntry
    {
        TGResourceType Type;
        uint Length;
        string Data;
        TGResourceEntry(TGResourceType type, uint length, char *data)
            : Type(type), Length(length), Data(data)
        {
        }
    };

    vector<TGResourceEntry> myResources;
    public:
    TGResource CreateResource(TGResourceType type, string name);
    const string &GetData(TGResource resource)
    {
        return myResources.at(static_cast<uint>(resource)).Data;
    }

    void ReleaseResource(TGResource resource);
};

#endif
