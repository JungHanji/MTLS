#pragma once
#include "VectorFuncs.hpp"

class pvector{
    public:
    float x1, x2, y1, y2;
    pvector(vec2 a, vec2 b){x1 = a.x; x2 = b.x; y1 = a.y; y2 = b.y;}
    pvector(){;}
    
    vec2 getCenter(){
        return {x1+abs(x2-x1)/2.f, y1+abs(y2-y1)/2.f};
    }
    vec2 getPointA(){
        return {x1, y1};
    }

    vec2 getPointB(){
        return {x2, y2};
    }

    float getLen(){
        return sqrtf(pow(x2 - x1, 2) + pow(y2 - y1, 2));
    }
    
    void print(){cout<<"{("<<x1<<","<<y1<<"), ("<<x2<<","<<y2<<")}\n";}
};

void operator*=(pvector &a, float b){ a.x2 += (a.x2 - a.x1) * b;  a.y2 += (a.y2 - a.y1) * b;}
void operator*=(pvector &a, pvector b){ a.x2 *= b.getLen(); a.y2 *= b.getLen(); }

bool operator==(pvector a, pvector b){return a.getPointA()==b.getPointA() && a.getPointB()==b.getPointB();}