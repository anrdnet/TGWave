
#ifndef ANDEBUG_H_
#define ANDEBUG_H_

#include "core/ANDef.h"
#include <iostream>
#include <GL/gl.h>
#include <GL/glu.h>
#include "core/ANError.h"
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
        throw ANError(ANErrorCode::GL);
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
