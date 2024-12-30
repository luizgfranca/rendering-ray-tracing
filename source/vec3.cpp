#include "vec3.h"

double Vec3::length_squared() const {
    return data[0]*data[0] + data[1]*data[1] + data[2]*data[2];
}
double Vec3::length() const {
    return std::sqrt(length_squared());
}

double Vec3::dot(const Vec3& v, const Vec3& u) {
    return v.data[0] * u.data[0] + v.data[1] * u.data[1] + v.data[2] * u.data[2];
}

Vec3 Vec3::cross(const Vec3& v, const Vec3& u) {
    return Vec3(
        v.data[1] * u.data[2] - v.data[2] * u.data[1],
        v.data[0] * u.data[2] - v.data[2] * u.data[0],
        v.data[0] * u.data[1] - v.data[1] * u.data[0]
    );
}

Vec3 Vec3::unit_vector(const Vec3& v) {
    return v / v.length();
}

Vec3 Vec3::random() { return Vec3(get_random(), get_random(), get_random()); }

Vec3 Vec3::random(double min, double max) { 
    return Vec3(
        get_random(min, max), 
        get_random(min, max), 
        get_random(min, max)
    ); 
}

Vec3 Vec3::unit_sphere_random() {
    Vec3 candidate;

    do {
        candidate = Vec3::random(-1, 1);
    } while(candidate.length_squared() >= 1);

    return candidate;
}

Vec3 Vec3::unit_random() {
    return Vec3::unit_vector(unit_sphere_random());
}

Vec3 Vec3::unit_random_in_another_vector_hemisphere(const Vec3 &another_vector) {
    auto random = Vec3::unit_random();
    return (Vec3::dot(random, another_vector) > 0) ? random : -random;
}

Vec3 Vec3::reflect(Vec3 vector, Vec3 surface_normal) {
    return vector - (2 * Vec3::dot(vector, surface_normal) * surface_normal);
}