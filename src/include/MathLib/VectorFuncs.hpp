#pragma once

#include "pvector.hpp"
#include "Vector4.hpp"
#include "AddMath.hpp"

float dot(vec3 a, vec3 b){ return a.x * b.x + a.y * b.y + a.z * b.z; }
float len(vec3 v) { return sqrt(v.x * v.x + v.y * v.y + v.z * v.z); }
float dist(vec3 a, vec3 b){ return sqrtf(pow(b.x - a.x, 2) + pow(b.y - a.y, 2) + pow(b.z - a.z, 2)); }
float dist(vec2 a, vec2 b){ return sqrtf(pow(b.x - a.x, 2) + pow(b.y - a.y, 2)); }

vec3 abs(vec3 v){ return {std::abs(v.x), std::abs(v.y), std::abs(v.z)};}
vec3 norm(vec3 a){ return len(a) != 0 ? a / len(a): vec3(0, 0, 0); }
vec3 clamp(float a, float b, vec3 v){ return {clamp(a, b, v.x), clamp(a, b, v.y), clamp(a, b, v.z)}; }
vec3 cross(vec3 a, vec3 b){ return { a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x }; }
vec3 lerp(vec3 a, vec3 b, vec3 f){ return {lerp(a.x, b.x, f.x), lerp(a.y, b.y, f.y), lerp(a.z, b.z, f.z)};}

vec2 lerp(vec2 a, vec2 b, vec2 f){ return {lerp(a.x, b.x, f.x), lerp(a.y, b.y, f.y)};}
vec2 abs(vec2 v){ return {std::abs(v.x), std::abs(v.y)};}
vec2 clamp(float a, float b, vec2 v){ return {clamp(a, b, v.x), clamp(a, b, v.y)}; }

vec3 sign(vec3 const& v) { return vec3(sign(v.x), sign(v.y), sign(v.z)); }
vec3 step(vec3 const& edge, vec3 v) { return vec3(step(edge.x, v.x), step(edge.y, v.y), step(edge.z, v.z)); }

bool getInterPoint(pvector a, pvector b, vec2& intersectionPoint) {
    float A1 = a.y2 - a.y1;
    float B1 = a.x1 - a.x2;
    float C1 = A1 * a.x1 + B1 * a.y1;

    float A2 = b.y2 - b.y1;
    float B2 = b.x1 - b.x2;
    float C2 = A2 * b.x1 + B2 * b.y1;

    float det = A1 * B2 - A2 * B1;
    if (det == 0) {
        return false; // Отрезки параллельны
    } else {
        intersectionPoint.x = (B2 * C1 - B1 * C2) / det;
        intersectionPoint.y = (A1 * C2 - A2 * C1) / det;

        // Проверка, что точка пересечения лежит внутри обоих отрезков
        float t1 = (a.x2 - a.x1) != 0 ? (intersectionPoint.x - a.x1) / (a.x2 - a.x1) : 0.5;
        float t2 = (b.x2 - b.x1) != 0 ? (intersectionPoint.x - b.x1) / (b.x2 - b.x1) : 0.5;

        float u1 = (a.y2 - a.y1) != 0 ? (intersectionPoint.y - a.y1) / (a.y2 - a.y1) : 0.5;
        float u2 = (b.y2 - b.y1) != 0 ? (intersectionPoint.y - b.y1) / (b.y2 - b.y1) : 0.5;

        if (t1 >= 0 && t1 <= 1 && t2 >= 0 && t2 <= 1 && u1 >= 0 && u1 <= 1 && u2 >= 0 && u2 <= 1) {
            return true;
        } else {
            return false;
        }
    }
}

bool isPointOnVector(pvector a, vec2 point) {
    float t = (a.x2 - a.x1) != 0 ? (point.x - a.x1) / (a.x2 - a.x1) : 0.5;
    float u = (a.y2 - a.y1) != 0 ? (point.y - a.y1) / (a.y2 - a.y1) : 0.5;

    return (t >= 0 && t <= 1 && u >= 0 && u <= 1);
}

bool isIntersected(pvector a, pvector b){
    vec2 intersectionPoint;

    float A1 = a.y2 - a.y1;
    float B1 = a.x1 - a.x2;
    float C1 = A1 * a.x1 + B1 * a.y1;

    float A2 = b.y2 - b.y1;
    float B2 = b.x1 - b.x2;
    float C2 = A2 * b.x1 + B2 * b.y1;

    float det = A1 * B2 - A2 * B1;
    if (det == 0) {
        return false; // Отрезки параллельны
    } else {
        intersectionPoint.x = (B2 * C1 - B1 * C2) / det;
        intersectionPoint.y = (A1 * C2 - A2 * C1) / det;

        // Проверка, что точка пересечения лежит внутри обоих отрезков
        float t1 = (a.x2 - a.x1) != 0 ? (intersectionPoint.x - a.x1) / (a.x2 - a.x1) : 0.5;
        float t2 = (b.x2 - b.x1) != 0 ? (intersectionPoint.x - b.x1) / (b.x2 - b.x1) : 0.5;

        float u1 = (a.y2 - a.y1) != 0 ? (intersectionPoint.y - a.y1) / (a.y2 - a.y1) : 0.5;
        float u2 = (b.y2 - b.y1) != 0 ? (intersectionPoint.y - b.y1) / (b.y2 - b.y1) : 0.5;

        if (t1 >= 0 && t1 <= 1 && t2 >= 0 && t2 <= 1 && u1 >= 0 && u1 <= 1 && u2 >= 0 && u2 <= 1) {
            return true;
        } else {
            return false;
        }
    }
}