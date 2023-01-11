#ifndef __ERROR__
#define __ERROR__

#include <stdexcept>


namespace lin{
namespace json{
    inline void Error(const char* message){
        throw std::logic_error(message);
    }
}
}


#endif