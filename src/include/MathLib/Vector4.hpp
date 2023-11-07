#pragma once
#include "Vector3.hpp"

class vec4{
    public:

    float x, y, z, w = 1;
    vec4(float a){x = a; y = a; z = a;}
    vec4(vec2 v, float a){x = v.x; y = v.y; z = a;}
    vec4(float a, vec2 v){x = a; y = v.x; z = v.y;}
    vec4(float x_, float y_, float z_, float w_ = 1){x = x_; y = y_; z = z_; w = w_;}
    vec4(vec3 v3, float w_ = 1){x = v3.x; y = v3.y; z = v3.z; w = w_;}
    std::string str(){return "{"+std::to_string(x)+", "+std::to_string(y)+", "+std::to_string(z)+", "+std::to_string(w)+"}";}
    vec4(){};

    //void operator=(vec4 b){x = b.x; y = b.y; z = b.z; w = b.w;}
};

vec4 operator+(vec4 a, vec4 b){ return { a.x + b.x, a.y + b.y, a.z + b.z, a.w}; }
vec4 operator-(vec4 a, vec4 b){ return { a.x - b.x, a.y - b.y, a.z - b.z, a.w}; }
vec4 operator/(vec4 a, vec4 b){ return { a.x / b.x, a.y / b.y, a.z / b.z, a.w}; }
vec4 operator*(vec4 a, vec4 b){ return { a.x * b.x, a.y * b.y, a.z * b.z, a.w}; }

void operator+=(vec4 &a, vec4 b){a.x += b.x; a.y += b.y; a.z += b.z; }
void operator-=(vec4 &a, vec4 b){a.x -= b.x; a.y -= b.y; a.z -= b.z; }
void operator/=(vec4 &a, vec4 b){a.x /= b.x; a.y /= b.y; a.z /= b.z; }
void operator*=(vec4 &a, vec4 b){a.x *= b.x; a.y *= b.y; a.z *= b.z; }

vec4 operator+(vec4 a, float b){ return { a.x + b, a.y + b, a.z + b, a.w}; }
vec4 operator-(vec4 a, float b){ return { a.x - b, a.y - b, a.z - b, a.w}; }
vec4 operator/(vec4 a, float b){ return { a.x / b, a.y / b, a.z / b, a.w}; }
vec4 operator*(vec4 a, float b){ return { a.x * b, a.y * b, a.z * b, a.w}; }

vec4 operator+(float b, vec4 a){ return { b + a.x, b + a.y, b + a.z, a.w}; }
vec4 operator-(float b, vec4 a){ return { b - a.x, b - a.y, b - a.z, a.w}; }
vec4 operator/(float b, vec4 a){ return { b / a.x, b / a.y, b / a.z, a.w}; }
vec4 operator*(float b, vec4 a){ return { b * a.x, b * a.y, b * a.z, a.w}; }

void operator+=(vec4 &a, float b){a.x += b; a.y += b; a.z += b; }
void operator-=(vec4 &a, float b){a.x -= b; a.y -= b; a.z -= b; }
void operator/=(vec4 &a, float b){a.x /= b; a.y /= b; a.z /= b; }
void operator*=(vec4 &a, float b){a.x *= b; a.y *= b; a.z *= b; }

bool operator==(vec4 a, vec4 b){ return a.x == b.x && a.y == b.y && a.z == b.z; }
bool operator!=(vec4 a, vec4 b){ return !(a == b);}
vec4 operator-(vec4 a){ return {-a.x, -a.y, -a.z}; }