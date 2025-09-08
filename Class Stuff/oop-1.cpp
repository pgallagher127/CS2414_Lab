#include <iostream>

using namespace std;

template <class DT>
class Point {
    public:
        DT x;
        DT y;
        Point();
        Point (DT a, DT b);
        Point (const Point<DT>& p);
        Point& operator=(const Point<DT>& p);
        Point operator+(const Point<DT>& p);
        Point operator+(const int i);
        friend ostream& operator<<(ostream& os, const Point<DT>& p) {
            os << "Point coordinates: (" << p.x << ", " << p.y << ")" << endl;
            return os;
        }
        void display();
        ~Point();
};

template <class DT>
class colorPoint: virtual public Point<DT> {
    public:
        int color;
        colorPoint();
        colorPoint(DT a, DT b, int c);
};

template <class DT>
Point<DT>::Point () {
    x = 0;
    y = 0;
}

template <class DT>
Point<DT>::Point (DT a, DT b) {
    x = a;
    y = b;
}

template <class DT>
Point<DT>::Point (const Point<DT>& p) {
    x = p.x;
    y = p.y;
}

template <class DT>
Point<DT>& Point<DT>::operator=(const Point<DT>& p) {
    if (this != &p) {
        x = p.x;
        y = p.y;
    }
    return *this;
}

template <class DT>
Point<DT> Point<DT>::operator+(const int i) {
    return Point<DT>(x + i, y + i);
}

template <class DT>
Point<DT> Point<DT>::operator+(const Point<DT>& p) {
    return Point<DT>(x + p.x, y + p.y);
}

template <class DT>
void Point<DT>::display() {
    cout << "Point coordinates: (" << x << ", " << y << ")" << endl;
}

template <class DT>
Point<DT>::~Point() {
    cout << "The Point {" << x << ", " << y << "} was destroyed" << endl;
}

template <class DT>
Point<DT>* getAPoint () {
    Point<DT>* aPoint = new Point<DT>();
    return aPoint;
}

template <class DT>
colorPoint<DT>::colorPoint() : Point<DT>() {
    color = 0;
}

template <class DT>
colorPoint<DT>::colorPoint(DT a, DT b, int c) : Point<DT>(a, b) {
    color = c;
}

int main() {
    Point<int> p;
    Point<int>* q = new Point<int>(10, 20);
    Point<int> r(30, 40);
    r = r + 10;
    p = r + *q;

    p.display();
    (*q).display();
    
    cout << (*q) << endl;

    Point<int>* z = getAPoint<int>();
    z->x = 100;
    z->y = 100;
    z->display();

    delete q;
    delete z;
    return 0;
}