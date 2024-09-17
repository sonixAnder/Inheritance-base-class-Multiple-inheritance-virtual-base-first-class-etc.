#include <iostream>
#include <cmath>
using namespace std;

class Equation
{
public:
    virtual void Solve() = 0;

    virtual ~Equation() {}
};

// Класс линейных уравнений
class LinearEquation : public Equation
{
private:
    double a, b;

public:
    LinearEquation(double _a, double _b) : a(_a), b(_b) {}

    // Переопределение виртуальной функции Solve()
    void Solve() override
    {
        if (a == 0)
        {
            if (b == 0)
            {
                cout << "Уравнение имеет бесконечное множество решений." << endl;
            }
            else
            {
                cout << "Уравнение не имеет решений." << endl;
            }
        }
        else
        {
            double x = -b / a;
            cout << "Корень уравнения: " << x << endl;
        }
    }
};

// Класс квадратных уравнений
class QuadraticEquation : public Equation
{
private:
    double a, b, c;

public:
    // Конструктор
    QuadraticEquation(double _a, double _b, double _c) : a(_a), b(_b), c(_c) {}

    // Переопределение виртуальной функции Solve()
    void Solve() override
    {
        double discriminant = b * b - 4 * a * c;
        if (discriminant >= 0)
        {
            double x1 = (-b + sqrt(discriminant)) / (2 * a);
            double x2 = (-b - sqrt(discriminant)) / (2 * a);
            cout << "Корни уравнения: " << x1 << " и " << x2 << endl;
        }
        else
        {
            cout << "Уравнение не имеет действительных корней." << endl;
        }
    }
};

int main()
{
    setlocale(LC_ALL, "ru");
    // Создание объекта линейного уравнения
    LinearEquation linear(2, 4);
    cout << "Линейное уравнение: 2x + 4 = 0" << endl;
    linear.Solve();

    // Создание объекта квадратного уравнения
    QuadraticEquation quadratic(1, -5, 6);
    cout << "Квадратное уравнение: x^2 - 5x + 6 = 0" << endl;
    quadratic.Solve();

    return 0;
}
