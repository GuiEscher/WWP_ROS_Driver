#ifndef WTL_RECTANGLE_H
#define WTL_RECTANGLE_H

namespace wtl {

class Point;

class Rectangle
{
public:
    Rectangle();
    Rectangle(int x, int y, int w, int h);
    Rectangle(Point topLeft, Point bottomRight);

    int x() const;
    int y() const;
    int width() const;
    int height() const;
    Point topLeft() const;
    Point topRight() const;
    Point bottomLeft() const;
    Point bottomRight() const;
    bool contains(const Point& point) const;
    bool isValid() const;

    void setX(int x);
    void setY(int y);
    void setWidth(int w);
    void setHeight(int h);

private:
    int m_x, m_y, m_w, m_h;
};

}

#endif // WTL_RECTANGLE_H
