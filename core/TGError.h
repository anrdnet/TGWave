
#ifndef ANERROR_H_
#define ANERROR_H_

#include <exception>
#include <string>

using namespace std;

enum class ANErrorCode
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

class ANError : public exception
{
    ANErrorCode myCode;
    string myMessage;
    public:
    ANError(ANErrorCode code)
        : myCode(code),
        myMessage(ErrorMessages[(uint)code])
    {

    }
    ANError(string message)
        : myCode(ANErrorCode::Unspecified),
        myMessage(message)
    {

    }

    virtual ~ANError() throw(){ };

    virtual const char *what() const throw() 
    {
        return myMessage.c_str();
    }

    ANError &Prepend(string message)
    {
        myMessage = message + ": "+ myMessage;
        return *this;
    }

    ANError &Prepend(ANErrorCode code)
    {
        myCode = code;
        myMessage = ErrorMessages[(uint)code] + ": " + myMessage;
        return *this;
    }

    bool operator == (ANErrorCode code)
    {
        return myCode == code;
    }

    bool operator != (ANErrorCode code)
    {
        return myCode != code;
    }
};

#endif
