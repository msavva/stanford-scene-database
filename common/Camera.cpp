//
// Camera.cpp
//

#include "Camera.h"

void Camera::Reset(const Vec3f &Eye, const Vec3f &Up, const Vec3f &VecLookAt)
{
    _eye = Eye;
    _worldUp = Up;
    _look = Vec3f::Normalize(_eye - VecLookAt);
    _right = Vec3f::Normalize(Vec3f::Cross(_worldUp, _look));
    _up = Vec3f::Normalize(Vec3f::Cross(_look, _right));

    Update();
}

void Camera::Update()
{
    _matrix = Matrix4::Camera(_eye, _look, _up, -_right);
}

void Camera::LookUp(float theta)
{
    Matrix4 Rotation = Matrix4::Rotation(_right, theta);
    _up = Rotation.TransformPoint(_up);
    _right = Rotation.TransformPoint(_right);
    _look = Rotation.TransformPoint(_look);
}

void Camera::LookRight(float theta)
{
    Matrix4 Rotation = Matrix4::Rotation(_worldUp, theta);
    _up = Rotation.TransformPoint(_up);
    _right = Rotation.TransformPoint(_right);
    _look = Rotation.TransformPoint(_look);
}

void Camera::Roll(float theta)
{
    Matrix4 Rotation = Matrix4::Rotation(_look, theta);
    _up = Rotation.TransformPoint(_up);
    _right = Rotation.TransformPoint(_right);
    _look = Rotation.TransformPoint(_look);
}

void Camera::Move(float distance)
{
    _eye += _look * distance;
}

void Camera::Strafe(float distance)
{
    _eye += _right * distance;
}
