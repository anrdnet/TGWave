
#ifndef TGDEBUG_H_
#define TGDEBUG_H_

#include "core/TGDef.h"
#include <iostream>
#include <GL/gl.h>
#include <GL/glu.h>
#include "core/TGError.h"
#include <string>
#include <cstdlib>
#define Debug(x) std::cerr<<__FILE__<<":"<<__LINE__<<" "<<x<<std::endl

#define CheckError() _CheckError(__FILE__,__LINE__)

inline void _CheckError(const char *file, uint line)
{
    GLenum err = glGetError();
    //Debug("Checking for error "<<err);
    if(err != GL_NO_ERROR) 
    {
        Debug("Some error at: "<<file<<":"<<line<<" "<<err);
        throw TGError(TGErrorCode::GL);
    }
}

inline void Bug(bool condition, string message)
{
    if(condition)
    {
        std::cerr<<"#BUG: "<<message;
        abort();
    }
}

void DumpBuffer(const byte *buffer, uint length);

#endif
