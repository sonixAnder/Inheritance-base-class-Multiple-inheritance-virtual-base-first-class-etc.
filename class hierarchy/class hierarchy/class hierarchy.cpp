#include <iostream>
using namespace std;

template <typename T1, typename T2>
class base
{
protected:
    T1 value1;
    T2 value2;

public:
    base(const T1& val1, const T2& val2) : value1(val1), value2(val2) {}

    ~base() {}

    T1 getValue1() const { return value1; }
    T2 getValue2() const { return value2; }
};

template <typename T1, typename T2, typename T3, typename T4>
class child : public base<T1, T2>
{
protected:
    T3 value3;
    T4 value4;

public:
    child(const T1& val1, const T2& val2, const T3& val3, const T4& val4)
        : base<T1, T2>(val1, val2), value3(val3), value4(val4) {}

    ~child() {}

    T3 getValue3() const { return value3; }
    T4 getValue4() const { return value4; }
};

template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
class child2 : public child<T1, T2, T3, T4>
{
protected:
    T5 value5;
    T6 value6;

public:
    child2(const T1& val1, const T2& val2, const T3& val3, const T4& val4,
        const T5& val5, const T6& val6)
        : child<T1, T2, T3, T4>(val1, val2, val3, val4), value5(val5), value6(val6) {}

    ~child2() {}

    T5 getValue5() const { return value5; }
    T6 getValue6() const { return value6; }
};

int main()
{
    setlocale(LC_ALL, "ru");
    child2<int, double, char, string, float, bool> obj(
        10, 3.14, 'A', "Привет", 2.5f, true);

    cout << "Значение 1: " << obj.getValue1() << endl;
    cout << "Значение 2: " << obj.getValue2() << endl;
    cout << "Значение 3: " << obj.getValue3() << endl;
    cout << "Значение 4: " << obj.getValue4() << endl;
    cout << "Значение 5: " << obj.getValue5() << endl;
    cout << "Значение 6: " << obj.getValue6() << endl;

    return 0;
}
