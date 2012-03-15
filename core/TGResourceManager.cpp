
#include "core/TGResourceManager.h"
#include "core/TGError.h"
#include <iostream>
#include <fstream>

const string DataDir("data/");

const string SubDirs[2] =
{
    "shaders/",
    "textures/"
};

TGResource TGResourceManager::CreateResource(TGResourceType type, string name)
{
    ifstream stream;
    string filename = DataDir+SubDirs[static_cast<uint>(type)]+name;
    stream.open(filename, ios::in | ios::binary);
    if(stream.fail())
    {
        throw TGError(filename).Prepend("Failed to open file");
    }
    stream.seekg(0, ios::end);
    uint length = stream.tellg();
    stream.seekg(0, ios::beg);
    char *data = new char[length+1];
    stream.read(data, length);
    data[length] = 0;
    TGResourceEntry entry(type, length, data);
    delete [] data;
    myResources.push_back(entry);
    return myResources.size() - 1;
}
