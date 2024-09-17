#include <iostream>
#include <string>
using namespace std;

// Базовый класс "Домашнее животное"
class Pet
{
protected:
    string name;
    string species;

public:
    Pet(const string& name, const string& species) : name(name), species(species) {}

    virtual void makeSound() const = 0;

    void showInfo() const
    {
        cout << "Имя: " << name << endl;
        cout << "Вид: " << species << endl;
    }
};

//Собака
class Dog : public Pet
{
public:
    Dog(const string& name) : Pet(name, "Собака") {}

    void makeSound() const override
    {
        cout << "Гаф-Гаф!" << endl;
    }
};

//Кот
class Cat : public Pet
{
public:
    Cat(const string& name) : Pet(name, "Кот") {}

    void makeSound() const override
    {
        cout << "Мяу!" << endl;
    }
};

//Попуг
class Parrot : public Pet
{
public:
    Parrot(const string& name) : Pet(name, "Попугай") {}

    void makeSound() const override
    {
        cout << "Привет!" << endl;
    }
};

int main()
{
    setlocale(LC_ALL, "ru");
    Dog dog("Рэкс");
    Cat cat("Юки");
    Parrot parrot("Попуг");

    dog.showInfo();
    dog.makeSound();

    cout << endl;

    cat.showInfo();
    cat.makeSound();

    cout << endl;

    parrot.showInfo();
    parrot.makeSound();

    return 0;
}