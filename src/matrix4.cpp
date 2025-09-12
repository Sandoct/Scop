#include "matrix4.hpp"

// Constructor -> identity
Matrix4::Matrix4() {
    for (int i = 0; i < 16; i++)
        m[i] = (i % 5 == 0) ? 1.0f : 0.0f;
}

Matrix4 Matrix4::identity() { return Matrix4(); }

Matrix4 Matrix4::multiply(const Matrix4& a, const Matrix4& b) {
    Matrix4 r{};
    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 4; col++) {
            r.m[col*4 + row] =
                a.m[0*4 + row] * b.m[col*4 + 0] +
                a.m[1*4 + row] * b.m[col*4 + 1] +
                a.m[2*4 + row] * b.m[col*4 + 2] +
                a.m[3*4 + row] * b.m[col*4 + 3];
        }
    }
    return r;
}

Matrix4 Matrix4::translate(float x, float y, float z) {
    Matrix4 r = identity();
    r.m[12] = x; r.m[13] = y; r.m[14] = z;
    return r;
}

Matrix4 Matrix4::rotateY(float angle) {
    Matrix4 r = identity();
    float c = std::cos(angle);
    float s = std::sin(angle);
    r.m[0] = c; r.m[2] = s;
    r.m[8] = -s; r.m[10] = c;
    return r;
}

Matrix4 Matrix4::rotateX(float angle) {
    Matrix4 r = identity();
    float c = std::cos(angle);
    float s = std::sin(angle);
    r.m[5] = c; r.m[6] = -s;
    r.m[9] = s; r.m[10] = c;
    return r;
}

Matrix4 Matrix4::rotateZ(float angle) {
    Matrix4 r = identity();
    float c = std::cos(angle);
    float s = std::sin(angle);
    r.m[0] = c; r.m[1] = -s;
    r.m[4] = s; r.m[5] = c;
    return r;
}

Matrix4 Matrix4::perspective(float fov, float aspect, float near, float far) {
    Matrix4 r{};
    float t = std::tan(fov * 0.5f);
    r.m[0] = 1.0f / (aspect * t);
    r.m[5] = 1.0f / t;
    r.m[10] = -(far + near) / (far - near);
    r.m[11] = -1.0f;
    r.m[14] = -(2.0f * far * near) / (far - near);
    return r;
}
