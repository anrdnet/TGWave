
#include "core/ANResourceManager.h"
#include "core/ANError.h"
#include <iostream>
#include <fstream>

const string DataDir("data/");

const string SubDirs[2] =
{
    "shaders/",
    "textures/"
};

ANResource ANResourceManager::CreateResource(ANResourceType type, string name)
{
    ifstream stream;
    string filename = DataDir+SubDirs[static_cast<uint>(type)]+name;
    stream.open(filename, ios::in | ios::binary);
    if(stream.fail())
    {
        throw ANError(filename).Prepend("Failed to open file");
    }
    stream.seekg(0, ios::end);
    uint length = stream.tellg();
    stream.seekg(0, ios::beg);
    char *data = new char[length+1];
    stream.read(data, length);
    data[length] = 0;
    ANResourceEntry entry(type, length, data);
    delete [] data;
    myResources.push_back(entry);
    return myResources.size() - 1;
}
