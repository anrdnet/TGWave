
#include "ANDebug.h"
#include <iomanip>
#include <cctype>

void DumpBuffer(const byte *buffer, uint length)
{
    ios::fmtflags old = cerr.flags();
    for(uint i = 0; i * 8 < length; i++)
    {
        for(uint j = 0; j < 8; j++)
        {
            if(i*8+j >= length)
                cerr<<"  ";
            else
            {
                cerr<<hex<<setw(2)<<setfill('0')<<(int)buffer[i*8+j];
            }
            cerr<<" ";
        }
        cerr<<"   ";
        for(uint j = 0; j < 8; j++)
        {
            if(i*8+j >= length)
                cerr<<" ";
            else if(isprint((char)buffer[i*8+j]))
            {
                cerr<<(char)buffer[i*8+j];
            }
            else
                cerr<<'.';
        }
        cerr<<endl;
    }
    cerr.flags(old);
}
