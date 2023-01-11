#ifndef __parser__
#define __parser__

#include "Scanner.h"
#include "JsonElement.h"
namespace lin{
namespace json{
    class Parser{
    public:
        Parser(Scanner scanner):scanner_(scanner){};
        JsonElement* Parse();

    private:
        JsonObject* ParseObject();
        JsonArray* ParseArray();

        Scanner scanner_;
    };
};
};
#endif