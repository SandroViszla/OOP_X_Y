#include <iostream>

using namespace std;
class Line;
class Dot
        {
    friend class Line;
    friend istream& operator >> (istream&, Dot&);
    friend ostream& operator<< (ostream&, Dot&);
private:
            float X;
            float Y;
public:
            Dot(float xx = 0.0, float yy = 0.0): X(xx), Y(yy) {};
            float getx(){return X;};
            float gety(){return Y;};
            Dot symx() {return Dot(-X, Y);};
            Dot symy() {return Dot(X,-Y);};
        };
class Line
        {
private:
            Dot p1;
            Dot p2;
public:
            Line(Dot& p, Dot& q): p1(p), p2(q){};
            Line(float x1, float y1, float x2, float y2): p1(x1,y1) ,p2(x2,y2) {};
            Dot clipx();
            Dot clipy();
        };
Dot Line::clipx()
{
    float dx = p2.X - p1.X;
    float dy = p1.Y - p2.Y;
    float x0 = (p2.Y * dx) / dy + p2.X;
    return Dot(x0, 0.0);
}
Dot Line::clipy()
{
    float dx = p2.X - p1.X;
    float dy = p1.Y - p2.Y;
    float y0 = (p2.Y * dy) / dx + p2.X;
    return Dot(0.0,y0);
}
istream& operator >> (istream& input, Dot& p)
{
    char semicolon = ';';
    input >> p.X >> semicolon >> p.Y;
    return input;
}
ostream& operator << (ostream& output, Dot& p)
{
    char semicolon = ';';
    output << p.X << semicolon << p.Y;
    return output;
}
int main()
{
    Dot A, B, _A, _B, C;
    float xa, ya, xb, yb, _x, _y;
    cout << "Input xa;ya xb;yb or exit" << endl;
    while (cin >> A >> B)
    {
        ya = A.gety();
        yb = B.gety();
        _A = (ya * yb) > 0 ? A.symy() : A;
        Line lx (_A, B);
        C = lx.clipx();
        cout << C << endl;
        xa = A.getx();
        xb = B.getx();
        _x = (xa * xb) > 0 ? -xb : xb;
        Line ly(xa, ya, _x, yb);
        C = ly.clipy();
        cout << C << endl;
        cout << "Input xa;ya xb;yb or exit" << endl;
    }
    return 0;
}