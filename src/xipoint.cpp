////////////////////////////////////////////////////////////////////////////////
// Module Name: xipoint.h/cpp
// Authors: Sergey Shershakov
// Version: 0.2.1
// Date: 08.09.2017
//
// This is a part of the course "Algorithms and Data Structures"
// provided by the School of Software Engineering of the Faculty
// of Computer Science at the Higher School of Economics.
////////////////////////////////////////////////////////////////////////////////

#include "xipoint.h"
#include <algorithm>
#include <cmath>

namespace xi
{
    Point::Point(int x, int y)
    {
        _x = x;
        _y = y;
    }
    void Point::shift(int shf)
    {
        _x += shf;
        _y += shf;
    }
    void Point::shift(int xSh, int ySh)
    {
        _x += xSh;
        _y += ySh;
    }
    void Point::shift(const Point& pt)
    {
        _x += pt._x;
        _y += pt._y;
    }
    double Point::dist(const Point& other) const
    {
        return sqrt(pow(_x - other._x, 2) + pow(_y - other._y, 2));
    }
    int Point::getX() const
    {
        return _x;
    }
    int Point::getY() const
    {
        return _y;
    }
    void Point::setX(int x)
    {
        _x = x;
    }
    void Point::setY(int y)
    {
        _y = y;
    }
    typedef unsigned int Uint;
    PointArray::PointArray()
    {
        _arr = nullptr;
        _size = 0;
    }
    PointArray::PointArray(const Point points[], Uint n)
    {
        _arr = new Point[n];
        _size = n;
        for (int i = 0; i < n; i++)
        {
            _arr[i] = points[i];
        }
    }
    PointArray::PointArray(const PointArray& pv)
    {
        _size = pv.getSize();
        _arr = new Point[getSize()];
        for (int i = 0; i < _size; i++)
        {
            _arr[i] = *pv.get(i);
        }
    }
    PointArray::~PointArray()
    {
        delete[] _arr;
        _size = 0;
    }
    void PointArray::append(const Point& pt)
    {
        resize(getSize() + 1);
        _arr[getSize() - 1] = pt;
    }
    void PointArray::insert(const Point& pt, Uint pos)
    {
        if (pos >= getSize())
        {
            append(pt);
        }
        else
        {
            resize(getSize() + 1);
            for (int i = getSize() - 1; i > pos; i--)
            {
                _arr[i] = _arr[i - 1];
            }
            _arr[pos] = pt;
        }
    }
    void PointArray::remove(Uint pos)
    {
        if (pos < getSize())
        {
            for (int i = pos; i < getSize() - 1; i++)
            {
                _arr[i] = _arr[i + 1];
            }
            resize(getSize() - 1);
        }
    }
    void PointArray::clear()
    {
        delete[] _arr;
        _size = 0;
        _arr = nullptr;
    }
    double PointArray::computePath() const
    {
        double sum = 0;
        for (int i = 1; i < getSize(); i++)
        {
            sum += _arr[i].dist(_arr[i - 1]);
        }
        return sum;
    }
    Uint PointArray::getSize() const
    {
        return _size;
    }
    Point* PointArray::get(Uint pos)
    {
        if (pos < getSize() && pos >= 0)
        {
            return &_arr[pos];
        }
    }
    const Point* PointArray::get(Uint pos) const
    {
        if (pos < getSize() && pos >= 0)
        {
            return &_arr[pos];
        }
    }
    void PointArray::resize(Uint n) {
        if (n == 0)
        {
            clear();
        }
        else
        {
            Point* newArr = new Point[n];
            for (int i = 0; i < std::min(getSize(), n); i++) {
                newArr[i] = *get(i);
            }
            delete[] _arr;
            _arr = new Point[n];
            _size = n;
            for (int i = 0; i < n; i++) {
                _arr[i] = newArr[i];
            }
            delete[] newArr;
        }
    }
}
