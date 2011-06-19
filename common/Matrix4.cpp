//
// Matrix4.cpp
//

#include "Matrix4.h"

Matrix4 Matrix4::Transpose() const
{
    Matrix4 Result;
    for(unsigned int i = 0; i < 4; i++)
    {
        for(unsigned int i2 = 0; i2 < 4; i2++)
        {
            Result[i2][i] = _entries[i][i2];
        }
    }
    return Result;
}

Matrix4 Matrix4::Identity()
{
    Matrix4 Result;
    for(unsigned int i = 0; i < 4; i++)
    {
        for(unsigned int i2 = 0; i2 < 4; i2++)
        {
            if(i == i2)
            {
                Result[i][i2] = 1.0f;
            }
            else
            {
                Result[i][i2] = 0.0f;
            }
        }
    }
    return Result;
}

Matrix4 Matrix4::Camera(const Vec3f &Eye, const Vec3f &_Look, const Vec3f &_Up, const Vec3f &_Right)
{
    Vec3f Look = Vec3f::Normalize(_Look);
    Vec3f Up = Vec3f::Normalize(_Up);
    Vec3f Right = Vec3f::Normalize(_Right);

    Matrix4 Result;
    Result[0][0] = Right.x;
    Result[1][0] = Right.y;
    Result[2][0] = Right.z;
    Result[3][0] = -Vec3f::Dot(Right, Eye);

    Result[0][1] = Up.x;
    Result[1][1] = Up.y;
    Result[2][1] = Up.z;
    Result[3][1] = -Vec3f::Dot(Up, Eye);

    Result[0][2] = Look.x;
    Result[1][2] = Look.y;
    Result[2][2] = Look.z;
    Result[3][2] = -Vec3f::Dot(Look, Eye);

    Result[0][3] = 0.0f;
    Result[1][3] = 0.0f;
    Result[2][3] = 0.0f;
    Result[3][3] = 1.0f;
    return Result;
}

Matrix4 Matrix4::PerspectiveFov(float FOV, float Aspect, float ZNear, float ZFar)
{
    float Width = 1.0f / tanf(FOV/2.0f), Height = Aspect / tanf(FOV/2.0f);

    Matrix4 Result;
    Result[0][0] = Width;
    Result[1][0] = 0.0f;
    Result[2][0] = 0.0f;
    Result[3][0] = 0.0f;

    Result[0][1] = 0.0f;
    Result[1][1] = Height;
    Result[2][1] = 0.0f;
    Result[3][1] = 0.0f;

    Result[0][2] = 0.0f;
    Result[1][2] = 0.0f;
    Result[2][2] = ZFar / (ZNear - ZFar);
    Result[3][2] = ZFar * ZNear / (ZNear - ZFar);

    Result[0][3] = 0.0f;
    Result[1][3] = 0.0f;
    Result[2][3] = -1.0f;
    Result[3][3] = 0.0f;
    return Result;
}

Matrix4 Matrix4::Rotation(const Vec3f &Axis, float Angle)
{
    float c = cosf(Angle);
    float s = sinf(Angle);
    float t = 1.0f - c;

    Vec3f NormalizedAxis = Vec3f::Normalize(Axis);
    float x = NormalizedAxis.x;
    float y = NormalizedAxis.y;
    float z = NormalizedAxis.z;

    Matrix4 Result;
    Result[0][0] = 1 + t*(x*x-1);
    Result[0][1] = z*s+t*x*y;
    Result[0][2] = -y*s+t*x*z;
    Result[0][3] = 0.0f;

    Result[1][0] = -z*s+t*x*y;
    Result[1][1] = 1+t*(y*y-1);
    Result[1][2] = x*s+t*y*z;
    Result[1][3] = 0.0f;

    Result[2][0] = y*s+t*x*z;
    Result[2][1] = -x*s+t*y*z;
    Result[2][2] = 1+t*(z*z-1);
    Result[2][3] = 0.0f;

    Result[3][0] = 0.0f;
    Result[3][1] = 0.0f;
    Result[3][2] = 0.0f;
    Result[3][3] = 1.0f;
    return Result;
}

Matrix4 Matrix4::Rotation(const Vec3f &Axis, float Angle, const Vec3f &Center)
{
    return Translation(-Center) * Rotation(Axis, Angle) * Translation(Center);
}

Matrix4 Matrix4::RotationX(float Theta)
{
    float CosT = cosf(Theta);
    float SinT = sinf(Theta);

    Matrix4 Result = Identity();
    Result[1][1] = CosT;
    Result[1][2] = SinT;
    Result[2][1] = -SinT;
    Result[2][2] = CosT;
    return Result;
}

Matrix4 Matrix4::RotationY(float Theta)
{
    float CosT = cosf(Theta);
    float SinT = sinf(Theta);

    Matrix4 Result = Identity();
    Result[0][0] = CosT;
    Result[0][2] = SinT;
    Result[2][0] = -SinT;
    Result[2][2] = CosT;
    return Result;
}

Matrix4 Matrix4::RotationZ(float Theta)
{
    float CosT = cosf(Theta);
    float SinT = sinf(Theta);

    Matrix4 Result = Identity();
    Result[0][0] = CosT;
    Result[0][1] = SinT;
    Result[1][0] = -SinT;
    Result[1][1] = CosT;
    return Result;
}

Matrix4 Matrix4::Scaling(const Vec3f &ScaleFactors)
{
    Matrix4 Result;
    Result[0][0] = ScaleFactors.x;
    Result[1][0] = 0.0f;
    Result[2][0] = 0.0f;
    Result[3][0] = 0.0f;

    Result[0][1] = 0.0f;
    Result[1][1] = ScaleFactors.y;
    Result[2][1] = 0.0f;
    Result[3][1] = 0.0f;

    Result[0][2] = 0.0f;
    Result[1][2] = 0.0f;
    Result[2][2] = ScaleFactors.z;
    Result[3][2] = 0.0f;

    Result[0][3] = 0.0f;
    Result[1][3] = 0.0f;
    Result[2][3] = 0.0f;
    Result[3][3] = 1.0f;
    return Result;
}

Matrix4 Matrix4::Translation(const Vec3f &Pos)
{
    Matrix4 Result;
    Result[0][0] = 1.0f;
    Result[1][0] = 0.0f;
    Result[2][0] = 0.0f;
    Result[3][0] = Pos.x;

    Result[0][1] = 0.0f;
    Result[1][1] = 1.0f;
    Result[2][1] = 0.0f;
    Result[3][1] = Pos.y;

    Result[0][2] = 0.0f;
    Result[1][2] = 0.0f;
    Result[2][2] = 1.0f;
    Result[3][2] = Pos.z;

    Result[0][3] = 0.0f;
    Result[1][3] = 0.0f;
    Result[2][3] = 0.0f;
    Result[3][3] = 1.0f;
    return Result;
}

Matrix4 operator * (const Matrix4 &Left, const Matrix4 &Right)
{
    Matrix4 Result;
    for(unsigned int i = 0; i < 4; i++)
    {
        for(unsigned int i2 = 0; i2 < 4; i2++)
        {
            float Total = 0.0f;
            for(unsigned int i3 = 0; i3 < 4; i3++)
            {
                Total += Left[i][i3] * Right[i3][i2];
            }
            Result[i][i2] = Total;
        }
    }
    return Result;
}

Matrix4 Matrix4::BoundingBoxToUnitSphere(const Vec3f &boundingBoxMin, const Vec3f &boundingBoxMax)
{
    Vec3f center = (boundingBoxMin + boundingBoxMax) * 0.5f;
    Vec3f variance = boundingBoxMax - center;

    return Matrix4::Translation(-center) * Matrix4::Scaling(1.0f / variance.Length());
}