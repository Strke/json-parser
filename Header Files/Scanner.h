#ifndef __scanner__
#define __scanner__

#include<string>
#include<iostream>

namespace lin{
namespace json{
    class Scanner{
    public:
        Scanner(std::string source)
        : source_(source), current_(0){
        };
        enum class JsonTokenType{  //所有会出现的标志类型
            BEGIN_OBJECT,  //  {
            END_OBJECT,    //  }

            VALUE_SEPRATOR, // ,
            NAME_SEPRATOR,  // :

            VALUE_STRING,  // "string"
            VALUE_NUMBER,  // 1, 2, 2e10

            LITERAL_TRUE,  //true
            LITERAL_FALSE, //false
            LITERAL_NULL,  //null

            BEGIN_ARRAY,   //[
            END_ARRAY,     //]

            END_OF_SOURCE,   //EOF
        };

        friend std::ostream &operator <<(std::ostream &os, const JsonTokenType& item){
            switch (item){
            case JsonTokenType::BEGIN_ARRAY:
                os << "[" << "\n";
                break;
            case JsonTokenType::END_ARRAY:
                os << "]" << "\n";
                break;
            case JsonTokenType::BEGIN_OBJECT:
                os << "{" << "\n";
                break;
            case JsonTokenType::END_OBJECT:
                os << "}" << "\n";
                break;
            case JsonTokenType::VALUE_SEPRATOR:
                os << "," << "\n";
                break;
            case JsonTokenType::NAME_SEPRATOR:
                os << ":" << "\n";
                break;
            case JsonTokenType::VALUE_STRING:
                os << "String" << "\n";
                break;
            case JsonTokenType::VALUE_NUMBER:
                os << "Number()" << "\n";
                break;
            case JsonTokenType::LITERAL_TRUE:
                os << "true" << "\n";
                break;
            case JsonTokenType::LITERAL_FALSE:
                os << "false" << "\n";
                break;
            case JsonTokenType::LITERAL_NULL:
                os << "null" << "\n";
                break;
            case JsonTokenType::END_OF_SOURCE:
                os << "EOF" << "\n";
                break;
            default:
                break;
            }
            return os;
        }

        JsonTokenType Scan(); //从当前已经扫描到的位置出发，扫描下一个并返回下一个token的type
        std::string GetValueString(){return value_string_;}
        int GetValueNumber(){return value_number_;}
        void Rollback();


    private:
        std::string source_;  //json source
        size_t current_; //最近处理到的位置
        size_t prev_pos_;
        std::string value_string_;
        float value_number_;



        bool IsAtEnd();//是否扫描完毕
        char Advance();//返回下一个字符
        void ScanTrue();
        void ScanFalse();
        void ScanNull();
        void ScanString();
        void ScanNumber();

        bool IsDigit(char c);
        char Peek();
        char PeekNext();

    };
}
}
#endif