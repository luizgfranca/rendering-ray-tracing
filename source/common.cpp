#include "common.h"
#include <iostream>
#include <random>

std::default_random_engine engine;

double get_random() {   
    return double(rand()) / double(RAND_MAX - 1);
}

double get_random(double min, double max) {
    std::uniform_real_distribution<double> dist(min, max);
    
    auto value = dist(engine);
    return value;
}