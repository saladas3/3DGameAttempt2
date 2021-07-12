//
// Created by lucai on 10.07.2021.
//

#ifndef INC_3DGAME_POINT_H
#define INC_3DGAME_POINT_H

#pragma once

class Point {
public:
    Point() : m_x(0), m_y(0) {

    }

    Point(int x, int y) : m_x(x), m_y(y) {

    }

    Point(const Point &point) : m_x(point.m_x), m_y(point.m_y) {

    }

    ~Point() = default;

public:
    int m_x = 0, m_y = 0;
};

#endif //INC_3DGAME_POINT_H
