#pragma once

#include <random>
#include <vector>

std::random_device RANDOM_DEVICE;
std::mt19937 gen(RANDOM_DEVICE());

int randint(int a, int b){
    std::uniform_int_distribution<> dist(a,b);
    return dist(gen);
}

float uniform(float a, float b){
    std::uniform_int_distribution<> dist(a,b);
    return dist(gen);    
}

template<class T>
T choice(std::vector<T> vc){
    return vc[randint(0, vc.size()-1)];
}