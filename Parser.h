#ifndef __parser__
#define __parser__

#include "Scanner.h"
#include "JsonElement.h"
namespace civitasv{
namespace json{
    class Parser{
    public:
        Parser(Scanner scanner);
        JsonElement* Parse();
    };
};
};




#endif