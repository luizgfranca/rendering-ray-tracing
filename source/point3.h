#pragma once

#include "vec3.h"

class Point3 : public Vec3 {
public:
    Point3(): Vec3() {};
    Point3(double x, double y, double z): Vec3(x, y, z) {};

    double x() const { return data[0]; }
    double y() const { return data[1]; }
    double z() const { return data[2]; }
};