
#ifndef ANRESOURCEMANAGER_H_
#define ANRESOURCEMANAGER_H_

#include <string>
#include <vector>
#include "core/ANDef.h"
#include "core/ANDebug.h"

enum class ANResourceType
{
    Shader = 0,
    Texture = 1
};

typedef uint ANResource;

class ANResourceManager
{
    struct ANResourceEntry
    {
        ANResourceType Type;
        uint Length;
        string Data;
        ANResourceEntry(ANResourceType type, uint length, char *data)
            : Type(type), Length(length), Data(data)
        {
        }
    };

    vector<ANResourceEntry> myResources;
    public:
    ANResource CreateResource(ANResourceType type, string name);
    const string &GetData(ANResource resource)
    {
        return myResources.at(static_cast<uint>(resource)).Data;
    }

    void ReleaseResource(ANResource resource);
};

#endif
