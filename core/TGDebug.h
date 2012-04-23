
#ifndef TGDEBUG_H_
#define TGDEBUG_H_

#include "core/TGDef.h"
#include <cstdio>
#include <GL/gl.h>
#include <GL/glu.h>
#include "core/TGError.h"
#include <string>
#include <cstdlib>
#define _str2(x) #x
#define _str(x) _str2(x)
#define _line _str(__LINE__)
#define Debug(...) printf(__FILE__ ":" _line " "  __VA_ARGS__); printf("\n")

#define CheckError() _CheckError(__FILE__,__LINE__)

inline void _CheckError(const char *file, uint line)
{
    GLenum err = glGetError();
    //Debug("Checking for error "<<err);
    if(err != GL_NO_ERROR) 
    {
        Debug("Some error at: %s:%d %d",file,line,err);
        throw TGError(string(reinterpret_cast<const char*>(gluErrorString(err)))).Prepend(TGErrorCode::GL);
    }
}

inline void Bug(bool condition, string message)
{
    if(condition)
    {
        Debug("#BUG: %s", message.c_str());
        throw TGError(message);
    }
}

void DumpBuffer(const byte *buffer, uint length);

#endif
