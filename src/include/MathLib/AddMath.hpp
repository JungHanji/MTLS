#pragma once

#include <vector>
#include <cmath>

float clamp(float a, float b, float v){return std::min(std::max(v, a), b);}
float sign(float a) { return (0 < a) - (a < 0); }
float step(float edge, float x) { return x > edge; }
float lerp(float a, float b, float f){return a + f * (b - a);}
float aproximate_to_zero(float n, float speed, float border = 0.1){if(n<-border){n+=speed; } else if(n>border){n-=speed; } else if(n<=border && n >= -border){n=0;}}

template<typename T>
T min(T v) {
    return v;
}

template<typename T, typename... Args>
T min(T first, Args... args) {
    return std::min(first, min(args...));
}