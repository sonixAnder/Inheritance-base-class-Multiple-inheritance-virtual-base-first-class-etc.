#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <iostream>
#include <cstring>
using namespace std;

//Животные
class Pet
{
protected:
    string name;
public:
    Pet(const string& name) : name(name) {}
    virtual ~Pet() {}

    virtual void ShowCharacteristics() const = 0;
};

class Dog : public virtual Pet
{
private:
    string breed;
public:
    Dog(const string& name, const string& breed) : Pet(name), breed(breed) {}

    void ShowCharacteristics() const override
    {
        cout << "Собака: " << name << ", Порода: " << breed << endl;
    }
};

class Cat : public virtual Pet
{
private:
    string color;
public:
    Cat(const string& name, const string& color) : Pet(name), color(color) {}

    void ShowCharacteristics() const override
    {
        cout << "Кот: " << name << ", Цвет: " << color << endl;
    }
};

class Parrot : public virtual Pet
{
private:
    string featherColor;
public:
    Parrot(const string& name, const string& featherColor) : Pet(name), featherColor(featherColor) {}

    void ShowCharacteristics() const override
    {
        cout << "Попугай: " << name << ", Цвет пера: " << featherColor << endl;
    }
};

//Строки
class String
{
protected:
    char* str;
public:
    String() : str(nullptr) {}

    String(const char* s)
    {
        str = new char[strlen(s) + 1];
        strcpy(str, s);
    }

    String(const String& other)
    {
        str = new char[strlen(other.str) + 1];
        strcpy(str, other.str);
    }

    String& operator=(const String& other)
    {
        if (this != &other)
        {
            delete[] str;
            str = new char[strlen(other.str) + 1];
            strcpy(str, other.str);
        }
        return *this;
    }

    virtual ~String()
    {
        delete[] str;
    }

    int Length() const
    {
        return strlen(str);
    }

    void Clear()
    {
        delete[] str;
        str = nullptr;
    }

    friend String operator+(const String& a, const String& b)
    {
        String result;
        result.str = new char[a.Length() + b.Length() + 1];
        strcpy(result.str, a.str);
        strcat(result.str, b.str);
        return result;
    }

    String& operator+=(const String& other)
    {
        char* newStr = new char[Length() + other.Length() + 1];
        strcpy(newStr, str);
        strcat(newStr, other.str);
        delete[] str;
        str = newStr;
        return *this;
    }

    bool operator==(const String& other) const
    {
        return strcmp(str, other.str) == 0;
    }

    bool operator!=(const String& other) const
    {
        return !(*this == other);
    }
};

class BitString : public virtual String
{
public:
    BitString() : String() {}

    BitString(const char* s) : String(s)
    {
        for (int i = 0; i < Length(); ++i)
        {
            if (str[i] != '0' && str[i] != '1')
            {
                Clear();
                break;
            }
        }
    }

    BitString(const BitString& other) : String(other) {}

    BitString& operator=(const BitString& other)
    {
        String::operator=(other);
        return *this;
    }

    void InvertSign()
    {
        for (int i = 0; i < Length(); ++i)
        {
            str[i] = (str[i] == '0') ? '1' : '0';
        }
    }

    friend BitString operator+(const BitString& a, const BitString& b)
    {
        BitString result;
        result.str = new char[a.Length() + b.Length() + 1];
        strcpy(result.str, a.str);
        strcat(result.str, b.str);
        return result;
    }

    BitString& operator+=(const BitString& other)
    {
        char* newStr = new char[Length() + other.Length() + 1];
        strcpy(newStr, str);
        strcat(newStr, other.str);
        delete[] str;
        str = newStr;
        return *this;
    }
};

int main()
{
    setlocale(LC_ALL, "ru");
    Dog dog("Вэнди", "Немецкая овчарка");
    Cat cat("Мия", "Серая");
    Parrot parrot("Попуг", "Зелёный");

    dog.ShowCharacteristics();
    cat.ShowCharacteristics();
    parrot.ShowCharacteristics();

    cout << "-----------------" << endl;

    BitString bitString1("1010101001");
    BitString bitString2("1100110");

    bitString1 += bitString2;
    cout << "Результат после добавления: " << bitString1.Length() << endl;

    bitString1.InvertSign();
    cout << "После инвертирования знака: " << bitString2.Length() << endl;

    return 0;
}