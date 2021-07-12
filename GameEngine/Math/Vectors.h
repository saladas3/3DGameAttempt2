//
// Created by lucai on 10.07.2021.
//

#pragma once

#ifndef INC_3DGAME_VECTORS_H
#define INC_3DGAME_VECTORS_H

class Vector2D {
public:
    Vector2D() : m_x(0), m_y(0) {}

    Vector2D(float x, float y) : m_x(x), m_y(y) {}

    Vector2D(const Vector2D &vector) : m_x(vector.m_x), m_y(vector.m_y) {}

    Vector2D operator*(float num) const {
        return Vector2D(m_x * num, m_y * num);
    }

    Vector2D operator+(const Vector2D &vec) const {
        return Vector2D(m_x + vec.m_x, m_y + vec.m_y);
    }

    Vector2D operator-(const Vector2D &vec) const {
        return Vector2D(m_x - vec.m_x, m_y - vec.m_y);
    }

    ~Vector2D() = default;

public:
    float m_x, m_y;
};

class Vector3D {
public:
    Vector3D() : m_x(0), m_y(0), m_z(0) {}

    Vector3D(float x, float y, float z) : m_x(x), m_y(y), m_z(z) {}

    Vector3D(const Vector3D &vector) : m_x(vector.m_x), m_y(vector.m_y), m_z(vector.m_z) {}

    static Vector3D lerp(const Vector3D &start, const Vector3D &end, float delta) {
        Vector3D v;
        v.m_x = start.m_x * (1.0f - delta) + end.m_x * (delta);
        v.m_y = start.m_y * (1.0f - delta) + end.m_y * (delta);
        v.m_z = start.m_z * (1.0f - delta) + end.m_z * (delta);
        return v;
    }

    Vector3D operator*(float num) const {
        return Vector3D(m_x * num, m_y * num, m_z * num);
    }

    Vector3D operator+(const Vector3D &vec) const {
        return Vector3D(m_x + vec.m_x, m_y + vec.m_y, m_z + vec.m_z);
    }

    Vector3D operator-(const Vector3D &vec) const {
        return Vector3D(m_x - vec.m_x, m_y - vec.m_y, m_z - vec.m_z);
    }

    bool operator!=(const Vector3D &vec) const {
        return m_x != vec.m_x && m_y != vec.m_y && m_z != vec.m_z;
    }

    static Vector3D normalize(const Vector3D &vec) {
        Vector3D res;
        float len = sqrt((vec.m_x * vec.m_x) + (vec.m_y * vec.m_y) + (vec.m_z * vec.m_z));

        if (len == 0)
            return Vector3D();

        res.m_x = vec.m_x / len;
        res.m_y = vec.m_y / len;
        res.m_z = vec.m_z / len;

        return res;
    }

    static Vector3D cross(const Vector3D &v1, const Vector3D &v2) {
        Vector3D res;
        res.m_x = (v1.m_y * v2.m_z) - (v1.m_z * v2.m_y);
        res.m_y = (v1.m_z * v2.m_x) - (v1.m_x * v2.m_z);
        res.m_z = (v1.m_x * v2.m_y) - (v1.m_y * v2.m_x);
        return res;
    }

    // Calculates the distance between two vectors
    //  by passing only the difference between them
    //  because sqrt is expensive
    static float calculateDistance(const Vector3D &diff) {
        return sqrt(diff.m_x * diff.m_x + diff.m_y * diff.m_y + diff.m_z * diff.m_z);
    }

    static Vector3D calculateMin(const Vector3D &vec, float radius) {
        return Vector3D(vec.m_x - radius, vec.m_y - radius, vec.m_z - radius);
    }

    static Vector3D calculateMax(const Vector3D &vec, float radius) {
        return Vector3D(vec.m_x + radius, vec.m_y + radius, vec.m_z + radius);
    }

    ~Vector3D() = default;

public:
    float m_x, m_y, m_z;
};

class Vector4D {
public:
    Vector4D() : m_x(0), m_y(0), m_z(0), m_w(0) {}

    Vector4D(float x, float y, float z, float w) : m_x(x), m_y(y), m_z(z), m_w(w) {}

    Vector4D(const Vector4D &vector) : m_x(vector.m_x), m_y(vector.m_y), m_z(vector.m_z), m_w(vector.m_w) {}

    explicit Vector4D(const Vector3D &vector) : m_x(vector.m_x), m_y(vector.m_y), m_z(vector.m_z), m_w(1.0) {}

    void cross(Vector4D &v1, Vector4D &v2, Vector4D &v3) {
        this->m_x = v1.m_y * (v2.m_z * v3.m_w - v3.m_z * v2.m_w) - v1.m_z * (v2.m_y * v3.m_w - v3.m_y * v2.m_w) +
                    v1.m_w * (v2.m_y * v3.m_z - v2.m_z * v3.m_y);
        this->m_y = -(v1.m_x * (v2.m_z * v3.m_w - v3.m_z * v2.m_w) - v1.m_z * (v2.m_x * v3.m_w - v3.m_x * v2.m_w) +
                      v1.m_w * (v2.m_x * v3.m_z - v3.m_x * v2.m_z));
        this->m_z = v1.m_x * (v2.m_y * v3.m_w - v3.m_y * v2.m_w) - v1.m_y * (v2.m_x * v3.m_w - v3.m_x * v2.m_w) +
                    v1.m_w * (v2.m_x * v3.m_y - v3.m_x * v2.m_y);
        this->m_w = -(v1.m_x * (v2.m_y * v3.m_z - v3.m_y * v2.m_z) - v1.m_y * (v2.m_x * v3.m_z - v3.m_x * v2.m_z) +
                      v1.m_z * (v2.m_x * v3.m_y - v3.m_x * v2.m_y));
    }

    ~Vector4D() = default;

public:
    float m_x, m_y, m_z, m_w;
};

#endif //INC_3DGAME_VECTORS_H
