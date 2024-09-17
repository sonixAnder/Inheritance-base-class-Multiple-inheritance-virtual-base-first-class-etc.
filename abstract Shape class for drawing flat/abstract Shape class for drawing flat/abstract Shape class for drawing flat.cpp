#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
using namespace std;

class Shape
{
public:
    virtual void Show() const = 0;
    virtual void Save(ofstream& out) const = 0;
    virtual void Load(ifstream& in) = 0;
    virtual ~Shape() {}
};

class Square : public Shape
{
private:
    int x, y;
    int side;

public:
    Square(int x = 0, int y = 0, int side = 0) : x(x), y(y), side(side) {}

    void Show() const override
    {
        cout << "Square: [" << x << ", " << y << "], side = " << side << endl;
    }

    void Save(ofstream& out) const override
    {
        out << "Square " << x << " " << y << " " << side << endl;
    }

    void Load(ifstream& in) override
    {
        in >> x >> y >> side;
    }
};

class Rectangle : public Shape
{
private:
    int x, y;
    int width, height;

public:
    Rectangle(int x = 0, int y = 0, int width = 0, int height = 0)
        : x(x), y(y), width(width), height(height) {}

    void Show() const override
    {
        cout << "Rectangle: [" << x << ", " << y << "], width = " << width << ", height = " << height << endl;
    }

    void Save(ofstream& out) const override
    {
        out << "Rectangle " << x << " " << y << " " << width << " " << height << endl;
    }

    void Load(ifstream& in) override
    {
        in >> x >> y >> width >> height;
    }
};

class Circle : public Shape
{
private:
    int x, y;
    int radius;

public:
    Circle(int x = 0, int y = 0, int radius = 0) : x(x), y(y), radius(radius) {}

    void Show() const override
    {
        cout << "Circle: center = [" << x << ", " << y << "], radius = " << radius << endl;
    }

    void Save(ofstream& out) const override
    {
        out << "Circle " << x << " " << y << " " << radius << endl;
    }

    void Load(ifstream& in) override
    {
        in >> x >> y >> radius;
    }
};

class Ellipse : public Shape
{
private:
    int x, y;
    int width, height;

public:
    Ellipse(int x = 0, int y = 0, int width = 0, int height = 0)
        : x(x), y(y), width(width), height(height) {}

    void Show() const override
    {
        cout << "Ellipse: bounding box = [" << x << ", " << y << "], width = " << width << ", height = " << height << endl;
    }

    void Save(ofstream& out) const override
    {
        out << "Ellipse " << x << " " << y << " " << width << " " << height << endl;
    }

    void Load(ifstream& in) override
    {
        in >> x >> y >> width >> height;
    }
};

void SaveShapes(const vector<shared_ptr<Shape>>& shapes, const string& filename)
{
    ofstream out(filename);
    for (const auto& shape : shapes)
    {
        shape->Save(out);
    }
    out.close();
}

void LoadShapes(vector<shared_ptr<Shape>>& shapes, const string& filename)
{
    ifstream in(filename);
    string shapeType;
    while (in >> shapeType)
    {
        if (shapeType == "Square")
        {
            auto shape = make_shared<Square>();
            shape->Load(in);
            shapes.push_back(shape);
        }
        else if (shapeType == "Rectangle")
        {
            auto shape = make_shared<Rectangle>();
            shape->Load(in);
            shapes.push_back(shape);
        }
        else if (shapeType == "Circle")
        {
            auto shape = make_shared<Circle>();
            shape->Load(in);
            shapes.push_back(shape);
        }
        else if (shapeType == "Ellipse")
        {
            auto shape = make_shared<Ellipse>();
            shape->Load(in);
            shapes.push_back(shape);
        }
    }
    in.close();
}

int main()
{
    vector<shared_ptr<Shape>> shapes;

    shapes.push_back(make_shared<Square>(0, 0, 10));
    shapes.push_back(make_shared<Rectangle>(10, 10, 20, 30));
    shapes.push_back(make_shared<Circle>(5, 5, 15));
    shapes.push_back(make_shared<Ellipse>(2, 2, 40, 20));

    SaveShapes(shapes, "shapes.txt");

    vector<shared_ptr<Shape>> loadedShapes;
    LoadShapes(loadedShapes, "shapes.txt");

    for (const auto& shape : loadedShapes)
    {
        shape->Show();
    }

    return 0;
}
