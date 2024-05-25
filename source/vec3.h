#pragma once
#include "common.h"

class Vec3 {
public:
    double data[3];

    Vec3(): data{0, 0, 0} {};

    Vec3(double v0, double v1, double v2): data{v0, v1, v2} {};

    double x() const { return data[0]; }
    double y() const { return data[1]; }
    double z() const { return data[2]; }

    Vec3 operator-() const { 
        return Vec3(-data[0], -data[1], -data[2]);
    }

    double operator[](int i) const { return data[i]; }
    double& operator[](int i) { return data[i]; }

    Vec3& operator+=(const Vec3& v) {
        data[0] += v[0];
        data[0] += v[1];
        data[0] += v[2];

        return *this;
    }

    Vec3& operator*=(double k) {
        data[0] *= k;
        data[0] *= k;
        data[0] *= k;

        return *this;
    }

    Vec3& operator/=(double k) {
        return *this *= 1/k;
    }

    double length_squared() const {
        return data[0]*data[0] + data[1]*data[1] + data[2]*data[2];
    }

    double length() const {
        return std::sqrt(length_squared());
    }
};


inline std::ostream& operator<<(std::ostream& out, const Vec3& v) {
    return out << v.data[0] << ' ' << v.data[1] << ' ' << v.data[2];
}

inline Vec3 operator+(const Vec3& u, const Vec3& v) {
    return Vec3(u.data[0] + v.data[0], u.data[1] + v.data[1], u.data[2] + v.data[2]);
}

inline Vec3 operator-(const Vec3& u, const Vec3& v) {
    return Vec3(u.data[0] - v.data[0], u.data[1] - v.data[1], u.data[2] - v.data[2]);
}

inline Vec3 operator*(const Vec3& u, const Vec3& v) {
    return Vec3(u.data[0] * v.data[0], u.data[1] * v.data[1], u.data[2] * v.data[2]);
}

inline Vec3 operator*(double t, const Vec3& v) {
    return Vec3(t*v.data[0], t*v.data[1], t*v.data[2]);
}

inline Vec3 operator*(const Vec3& v, double k) {
    return k * v;
}


inline Vec3 operator/(const Vec3& v, double k) {
    return (1/k) * v;
}


namespace vec_op {
    inline double dot(const Vec3& v, const Vec3& u) {
        return v[0] * u[0] + v[1] * u[1] + v[2] * u[2];
    }


    inline Vec3 cross(const Vec3& v, const Vec3& u) {
        return Vec3(
            v[1] * u[2] - v[2] * u[1],
            v[0] * u[2] - v[2] * u[0],
            v[0] * u[1] - v[1] * u[0]
        );
    }

    inline Vec3 unit_vector(const Vec3& v) {
        return v / v.length();
    }
}
