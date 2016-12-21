#ifndef COORD_H
#define COORD_H

template <typename T>
struct Coord
{
  T x, y;
  Coord(): x(0), y(0) {}
  Coord(T x, T y): x(x), y(y) {}
  Coord<T> operator-(const Coord<T>& p) const {
    return Coord<T>(x - p.x, y - p.y);
  }
  Coord<T> operator+(const Coord<T>& p) const {
    return Coord<T>(x + p.x, y + p.y);
  }
  Coord<T> operator*(const int p) const {
    return Coord<T>(x * p, y * p);
  }
  Coord<T>& operator+=(const Coord<T>& p) {
    return *this = *this + p;
  }
  Coord<T>& operator-=(const Coord<T>& p) {
    return *this = *this - p;
  }
  Coord<T>& operator*=(const int p) {
    return *this = *this * p;
  }
  Coord(const Coord& p): x(p.x), y(p.y) {}
};

#endif
