#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class FileHandler
{
protected:
    ifstream file;

public:
    FileHandler() {}

    ~FileHandler()
    {
        if (file.is_open())
        {
            file.close();
        }
    }

    void Open(const char* path)
    {
        file.open(path);
        if (!file.is_open())
        {
            cerr << "Ошибка открытия файла: " << path << endl;
        }
    }

    virtual void Display(const char* path)
    {
        if (file.is_open())
        {
            string line;
            while (getline(file, line))
            {
                cout << line << endl;
            }
        }
    }
};

class ASCIIHandler : public FileHandler
{
public:
    void Display(const char* path) override
    {
        Open(path);
        if (file.is_open())
        {
            char ch;
            while (file.get(ch))
            {
                cout << "ASCII code: " << static_cast<int>(ch) << " - " << ch << endl;
            }
        }
    }
};

class BinaryHandler : public FileHandler
{
public:
    void Display(const char* path) override
    {
        Open(path);
        if (file.is_open())
        {
            char ch;
            while (file.get(ch))
            {
                for (int i = 7; i >= 0; --i)
                {
                    cout << ((ch >> i) & 1);
                }
                cout << " ";
            }
        }
    }
};

int main()
{
    setlocale(LC_ALL, "ru");
    FileHandler fileHandler;
    ASCIIHandler asciiHandler;
    BinaryHandler binaryHandler;

    fileHandler.Open("example.txt");
    fileHandler.Display("example.txt");

    asciiHandler.Display("example.txt");

    binaryHandler.Display("example.txt");

    return 0;
}
