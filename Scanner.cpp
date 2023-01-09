#include "Scanner.h"
#include "ErrorFunc.h"

namespace lin{
namespace json{

    bool Scanner::IsAtEnd() { return current_ >= source_.size(); }
    char Scanner::Advance() { return source_[current_++]; }

    bool Scanner::IsDigit(char c)
    {
        return ((c >= '0') && (c <= '9'));
    }

    char Scanner::Peek()
    {
        if (IsAtEnd())
            return '\0';
        return source_[current_];
    }

    char Scanner::PeekNext()
    {
        if (current_ + 1 >= source_.size())
            return '\0';
        return source_[current_ + 1];
    }

    void Scanner::ScanTrue()
    {
        if (source_.compare(current_, 3, "rue") == 0)
        {
            current_ += 3;
        }
        else
        {
            Error("Scan 'true' error");
        }
    }

    void Scanner::ScanFalse()
    {
        if (source_.compare(current_, 4, "alse") == 0)
        {
            current_ += 4;
        }
        else
        {
            Error("Scan 'False' error");
        }
    }

    void Scanner::ScanNull()
    {
        if (source_.compare(current_, 3, "ull") == 0)
        {
            current_ += 3;
        }
        else
        {
            Error("Scan 'NULL' error");
        }
    }

    void Scanner::ScanString()
    {
        size_t pos = current_;
        while (Peek() != '\"' && !IsAtEnd())
            Advance();
        if (IsAtEnd())
        {
            Error("Invalid string: missing cosing quote!");
        }
        value_string_ = source_.substr(pos, current_ - pos - 1);
    }

    void Scanner::ScanNumber()
    {
        size_t pos = current_ - 1;
        while (IsDigit(Peek()))
        {
            Advance();
        }

        if (Peek() == '.' && IsDigit(PeekNext()))
        {
            Advance();
            while (isdigit(Peek()))
            {
                Advance();
            }
        }
        value_number_ = std::atof(source_.substr(pos, current_ - pos).c_str());
    }

    Scanner::JsonTokenType Scanner::Scan()
    {
        if (IsAtEnd())
        {
            return JsonTokenType::END_OF_SOURCE;
        }
        char c = Advance();
        switch (c)
        {
        case '{':
            return JsonTokenType::BEGIN_OBJECT;
        case '}':
            return JsonTokenType::END_OBJECT;
        case '[':
            return JsonTokenType::BEGIN_ARRAY;
        case ']':
            return JsonTokenType::END_ARRAY;
        case ':':
            return JsonTokenType::NAME_SEPRATOR;
        case ',':
            return JsonTokenType::VALUE_SEPRATOR;
        case 't':
            ScanTrue();
            return JsonTokenType::LITERAL_TRUE;
        case 'f':
            ScanFalse();
            return JsonTokenType::LITERAL_FALSE;
        case 'n':
            ScanNull();
            return JsonTokenType::LITERAL_NULL;
        case ' ':
        case '\t':
        case '\n':
        case '\r':
            return Scan();
        case '\"':
            return JsonTokenType::VALUE_STRING;
        case '-':
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            return JsonTokenType::VALUE_NUMBER;
        default:
            Error("Unsupported Token:" + c);
        }
        return JsonTokenType();
    }
}
}