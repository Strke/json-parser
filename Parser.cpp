#include "Parser.h"
#include "Header Files/JsonElement.h"
#include "Header Files/ErrorFunc.h"

namespace lin{
namespace json{
    using JsonTokenType = Scanner::JsonTokenType;
    

    JsonObject* Parser::ParseObject(){
        JsonObject* res = new JsonObject(); 
        JsonTokenType next = scanner_.Scan();
        if(next == JsonTokenType::END_OF_SOURCE){
            return res;
        }
        scanner_.Rollback();
        while(true){
            next = scanner_.Scan();
            if(next != JsonTokenType::VALUE_STRING){
                Error("Key must be string");
            }
            std::string key = scanner_.GetValueString();
            next = scanner_.Scan();
            if(next != JsonTokenType::NAME_SEPRATOR){
                Error("Expected':'!");
            }
            (*res)[key] = Parse();
            next = scanner_.Scan();
            if(next == JsonTokenType::END_OBJECT){
                break;
            }
            if(next != JsonTokenType::VALUE_SEPRATOR){
                Error("Expected':'!");
            }
        }
        return res;
    }

    JsonArray* Parser::ParseArray(){
        JsonArray* res = new JsonArray();
        JsonTokenType next = scanner_.Scan();
        if(next == JsonTokenType::END_ARRAY){
            return res;
        }
        scanner_.Rollback();

        while(true){
            res->push_back(Parse());
            next = scanner_.Scan();

            if(next == JsonTokenType::END_ARRAY){
                break;
            }

            if(next != JsonTokenType::VALUE_SEPRATOR){
                Error("Expectd ':'");
            }
        }

        return res;
    }
    JsonElement* Parser::Parse(){
        JsonElement* element = new JsonElement();
        JsonTokenType token_type = scanner_.Scan();
        switch(token_type){
            case JsonTokenType::END_OF_SOURCE:{
                break;
            }
            case JsonTokenType::BEGIN_OBJECT:{
                JsonObject* object = ParseObject();
                element -> value(object);
                break;
            }
            case JsonTokenType::BEGIN_ARRAY:{
                JsonArray* array = ParseArray();
                element -> value(array);
                break;
            }
            case JsonTokenType::VALUE_STRING:{
                std::string* val = new std::string(scanner_.GetValueString());
                element -> value(val);
                break;
            }
            case JsonTokenType::VALUE_NUMBER:{
                float val = scanner_.GetValueNumber();
                element -> value(val);
                break;
            }
            case JsonTokenType::LITERAL_TRUE:{
                element -> value(true);
                break;
            }
            case JsonTokenType::LITERAL_FALSE:{
                element -> value(false);
                break;
            }
            case JsonTokenType::LITERAL_FALSE:{
                break;
            }
        }
        return element;
    };
};
};