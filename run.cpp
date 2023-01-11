#include "Header Files/Scanner.h"
#include "Scanner.cpp"
#include "Header Files/Parser.h"
#include "Parser.cpp"
#include <iostream>


int main(){

    using namespace lin::json;
    auto source = R"(
        {
            "glossary" : {
                "test": true,
                "hello": null,
                "hello2": "miaomiao"
            }
        }
    )";
    //auto source2 = "[1, 2, 3, 4, 5, \"Hello\"]";
    Scanner scanner(source);

    Parser parser(scanner);

    JsonElement* element = parser.Parse();
    std::cout << element->Dumps();

    return 0;
}