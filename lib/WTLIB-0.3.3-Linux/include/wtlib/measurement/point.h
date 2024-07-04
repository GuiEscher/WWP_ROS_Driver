#ifndef WTL_POINT_H
#define WTL_POINT_H

#include <compare>

namespace wtl {

class Point
{
public:
    Point();
    Point(int x, int y);

    int x() const;
    int y() const;

    void setX(int x);
    void setY(int y);

    auto operator<=>(const Point& other) const = default;

    bool isValid() const;

private:
    int m_x, m_y;
};

} // namespace wtl

#endif // WTL_POINT_H
