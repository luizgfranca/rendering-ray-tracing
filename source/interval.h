#pragma once

#include "common.h"
#include <cmath>

class Interval {
public:
    Interval(): m_min(INFINITY), m_max(-INFINITY) {}
    Interval(double min, double max): m_min(min), m_max(max) {}

    double size() const {
        return m_max - m_min;
    }

    bool contains(double x) const {
        return x >= m_min && x <= m_max;
    }

    bool surrounds(double x) const {
        return x > m_min && x < m_max;
    }

    void set_min(double new_min) {
        m_min = new_min;
    }

    void set_max(double new_max) {
        m_max = new_max;
    }

    static const Interval EMPTY, UNIVERSE;

private:
    double m_min;
    double m_max;
};

inline const Interval Interval::EMPTY = Interval();
inline const Interval Interval::UNIVERSE = Interval(-INFINITY, INFINITY);