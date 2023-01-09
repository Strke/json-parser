#ifndef __JsonElement__
#define __JsonElement__

#include<string>
#include<map>
#include<vector>

namespace civitasv{
namespace json{
    using JsonObject = std::map<std::string, JsonElement>;
    using JsonArray = std::vector<JsonElement>;
    class JsonElement{
    public:
        enum class Type{    //JSON的六种类型
            JSON_OBJECT,
            JSON_ARRAY,
            JSON_STRING,
            JSON_NUMBER,
            JSON_BOOL,
            JSON_NULL
        };
        union Value{
            JsonObject* value_object;
            JsonArray* value_array;
            std::string* value_string;
            float value_number;
            bool value_bool;

        };

        JsonElement(JsonObject* &value_object);
        JsonElement(JsonArray* &value_array);
        JsonElement(std::string* &value_string);
        JsonElement(float &value_number);
        JsonElement(bool &value_bool);

        JsonObject* AsObject();
        JsonArray* AsArray();
        std::string* AsString();
        float AsNumber();
        bool AsBool();

        std::string Dumps();


    private:
        Type type_;
        Value value_;
    };
};
};
#endif