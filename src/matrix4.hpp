#pragma once
#include <cmath>

struct {
	float	X = 0.0f;
	float	Y = 0.0f;
	float	Z = 0.0f;
	float	speed = 0.05f;

}pos;

class Matrix4 {
public:
    float m[16]; // column-major

    Matrix4(); // constructor -> identity

    static Matrix4 identity();
    static Matrix4 multiply(const Matrix4& a, const Matrix4& b);
    static Matrix4 translate(float x, float y, float z);
    static Matrix4 rotateY(float angle);
    static Matrix4 rotateX(float angle);
    static Matrix4 rotateZ(float angle);
    static Matrix4 perspective(float fov, float aspect, float near, float far);
};
