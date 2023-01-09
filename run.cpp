#include "Scanner.h"
#include "Scanner.cpp"
#include <iostream>


int main(){

    using namespace lin::json;
    auto source = R"(
        {
            "glossary" : {
                "test" : true,
                "hello" : null,
                "hello2" : "miaomiao"
            }
        }
    )";
    //auto source2 = "[1, 2, 3, 4, 5, \"Hello\"]";
    Scanner scanner(source);
    Scanner::JsonTokenType type;
    while((type = scanner.Scan()) != Scanner::JsonTokenType::END_OF_SOURCE){
        std::cout << "Type: " << type;
        if(type == Scanner::JsonTokenType::VALUE_NUMBER){
            std::cout << "Value:" << scanner.GetValueNumber();
        }
        else if(type == Scanner::JsonTokenType::VALUE_STRING){
            std::cout << "String:" << scanner.GetValueString();
        }
        std::cout << '\n';
    }

    return 0;
}