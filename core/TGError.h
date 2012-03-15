
#ifndef TGERROR_H_
#define TGERROR_H_

#include <exception>
#include <string>

using namespace std;

enum class TGErrorCode
{
    Unspecified,
    #define ERR(identifier, message) identifier,
    #include "Errors.def"
    #undef ERR
};

const string ErrorMessages[] =
{
    "Unspecified error",
    #define ERR(identifier, message) #message,
    #include "Errors.def"
    #undef ERR
};

class TGError : public exception
{
    TGErrorCode myCode;
    string myMessage;
    public:
    TGError(TGErrorCode code)
        : myCode(code),
        myMessage(ErrorMessages[(uint)code])
    {

    }
    TGError(string message)
        : myCode(TGErrorCode::Unspecified),
        myMessage(message)
    {

    }

    virtual ~TGError() throw(){ };

    virtual const char *what() const throw() 
    {
        return myMessage.c_str();
    }

    TGError &Prepend(string message)
    {
        myMessage = message + ": "+ myMessage;
        return *this;
    }

    TGError &Prepend(TGErrorCode code)
    {
        myCode = code;
        myMessage = ErrorMessages[(uint)code] + ": " + myMessage;
        return *this;
    }

    bool operator == (TGErrorCode code)
    {
        return myCode == code;
    }

    bool operator != (TGErrorCode code)
    {
        return myCode != code;
    }
};

#endif
