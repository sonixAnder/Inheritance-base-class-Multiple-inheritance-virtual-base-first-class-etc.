#define _CRT_SECURE_NO_WARNINGS
#include <cstring>
#include <iostream>
#include <bitset>
#include <cmath>
using namespace std;

class String
{
protected:
    char* str;
    size_t length;

public:
    String() : str(nullptr), length(0) {}
    String(const char* s)
    {
        if (s)
        {
            length = strlen(s);
            str = new char[length + 1];
            strcpy(str, s);
        }
        else
        {
            str = nullptr;
            length = 0;
        }
    }

    // Конструктор копирования
    String(const String& other)
    {
        length = other.length;
        if (other.str)
        {
            str = new char[length + 1];
            strcpy(str, other.str);
        }
        else
        {
            str = nullptr;
        }
    }

    // Оператор присваивания
    String& operator=(const String& other)
    {
        if (this != &other)
        {
            delete[] str;
            length = other.length;
            if (other.str)
            {
                str = new char[length + 1];
                strcpy(str, other.str);
            }
            else
            {
                str = nullptr;
            }
        }
        return *this;
    }

    // Получение длины строки
    size_t getLength() const
    {
        return length;
    }

    // Очистка строки
    void clear()
    {
        delete[] str;
        str = nullptr;
        length = 0;
    }

    // Деструктор
    virtual ~String()
    {
        delete[] str;
    }

    // Оператор конкатенации строк (+)
    String operator+(const String& other) const
    {
        size_t newLength = length + other.length;
        char* newStr = new char[newLength + 1];

        strcpy(newStr, str);
        strcat(newStr, other.str);

        String result(newStr);
        delete[] newStr;
        return result;
    }

    // Оператор конкатенации с присваиванием (+=)
    String& operator+=(const String& other)
    {
        *this = *this + other;
        return *this;
    }

    // Оператор равенства (==)
    bool operator==(const String& other) const
    {
        if (length != other.length) return false;
        return strcmp(str, other.str) == 0;
    }

    // Оператор неравенства (!=)
    bool operator!=(const String& other) const
    {
        return !(*this == other);
    }

    // Метод для вывода строки
    friend ostream& operator<<(ostream& os, const String& s)
    {
        if (s.str) os << s.str;
        return os;
    }
};


class BitString : public String
{
private:
    bool isValidBitString(const char* s) const
    {
        for (size_t i = 0; i < strlen(s); ++i)
        {
            if (s[i] != '0' && s[i] != '1')
            {
                return false;
            }
        }
        return true;
    }

public:
    BitString() : String() {}

    BitString(const char* s) : String()
    {
        if (isValidBitString(s))
        {
            length = strlen(s);
            str = new char[length + 1];
            strcpy(str, s);
        }
        else
        {
            clear();
        }
    }

    BitString(const BitString& other) : String(other) {}

    BitString& operator=(const BitString& other)
    {
        if (this != &other) {
            String::operator=(other);
        }
        return *this;
    }

    ~BitString() {}

    void negate()
    {
        if (!str) return;

        int64_t number = bitset<64>(str).to_ullong();

        number = ~number + 1;

        bitset<64> bitsetNumber(number);
        string bitString = bitsetNumber.to_string();

        size_t firstOne = bitString.find('1');
        string result = bitString.substr(firstOne);

        delete[] str;
        length = result.length();
        str = new char[length + 1];
        strcpy(str, result.c_str());
    }

    BitString operator+(const BitString& other) const
    {
        int64_t num1 = bitset<64>(str).to_ullong();
        int64_t num2 = bitset<64>(other.str).to_ullong();

        int64_t resultNumber = num1 + num2;

        bitset<64> bitsetResult(resultNumber);
        string resultString = bitsetResult.to_string();

        size_t firstOne = resultString.find('1');
        string result = resultString.substr(firstOne);

        return BitString(result.c_str());
    }

    BitString& operator+=(const BitString& other)
    {
        *this = *this + other;
        return *this;
    }

    bool operator==(const BitString& other) const
    {
        return String::operator==(other);
    }

    bool operator!=(const BitString& other) const
    {
        return String::operator!=(other);
    }
};

int main()
{
    setlocale(LC_ALL, "ru");
    BitString bs1("1010");
    BitString bs2("0011");

    BitString sum = bs1 + bs2;
    cout << "Сумма: " << sum << endl;

    bs1.negate();
    cout << "Инверсия знака: " << bs1 << endl;

    return 0;
}
