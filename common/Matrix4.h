//
// Matrix4.h
//

#include "Vec3f.h"

class Matrix4
{
public:
    
    //
    // Math properties
    //
    Matrix4 Transpose() const;
    
    //
    // Vector transforms
    //
    inline Vec3f TransformPoint(const Vec3f &point) const
    {
        float w = point.x * _Entries[0][3] + point.y * _Entries[1][3] + point.z * _Entries[2][3] + _Entries[3][3];
        if(w)
        {
            const float invW = 1.0f / w;
            return Vec3f( (point.x * _Entries[0][0] + point.y * _Entries[1][0] + point.z * _Entries[2][0] + _Entries[3][0]) * invW,
                          (point.x * _Entries[0][1] + point.y * _Entries[1][1] + point.z * _Entries[2][1] + _Entries[3][1]) * invW,
                          (point.x * _Entries[0][2] + point.y * _Entries[1][2] + point.z * _Entries[2][2] + _Entries[3][2]) * invW);
        }
        else
        {
            return Vec3f(0.0f, 0.0f, 0.0f);
        }
    }

    inline Vec3f TransformPointNoProjection(const Vec3f &point) const
    {
        return Vec3f( (point.x * _Entries[0][0] + point.y * _Entries[1][0] + point.z * _Entries[2][0] + _Entries[3][0]),
                      (point.x * _Entries[0][1] + point.y * _Entries[1][1] + point.z * _Entries[2][1] + _Entries[3][1]),
                      (point.x * _Entries[0][2] + point.y * _Entries[1][2] + point.z * _Entries[2][2] + _Entries[3][2]));
    }
    
    inline Vec3f TransformNormal(const Vec3f &normal) const
    {
        return Vec3f(normal.x * _Entries[0][0] + normal.y * _Entries[1][0] + normal.z * _Entries[2][0],
                     normal.x * _Entries[0][1] + normal.y * _Entries[1][1] + normal.z * _Entries[2][1],
                     normal.x * _Entries[0][2] + normal.y * _Entries[1][2] + normal.z * _Entries[2][2]);
    }

    //
    // Accessors
    //
    float* operator [] (int Row)
    {
        return _Entries[Row];
    }
    const float* operator [] (int Row) const
    {
        return _Entries[Row];
    }
    
    //
    // Transformation matrices
    //
    static Matrix4 Identity();
    static Matrix4 Scaling(const Vec3f &ScaleFactors);
    static Matrix4 Scaling(float ScaleFactor)
    {
        return Scaling(Vec3f(ScaleFactor, ScaleFactor, ScaleFactor));
    }
    static Matrix4 Translation(const Vec3f &Pos);
    static Matrix4 Rotation(const Vec3f &Axis, float Angle, const Vec3f &Center);
    static Matrix4 Rotation(const Vec3f &Axis, float Angle);
    static Matrix4 RotationX(float Theta);
    static Matrix4 RotationY(float Theta);
    static Matrix4 RotationZ(float Theta);
    static Matrix4 Camera(const Vec3f &Eye, const Vec3f &Look, const Vec3f &Up, const Vec3f &Right);
    static Matrix4 PerspectiveFov(float FOV, float Aspect, float ZNear, float ZFar);

private:
    float _Entries[4][4];
};

Matrix4 operator * (const Matrix4 &Left, const Matrix4 &Right);

//Vec4f operator * (const Vec4f &Right, const Matrix4 &Left)
//{
//    return Vec4f(Right.x * Left[0][0] + Right.y * Left[1][0] + Right.z * Left[2][0] + Right.w * Left[3][0],
//                Right.x * Left[0][1] + Right.y * Left[1][1] + Right.z * Left[2][1] + Right.w * Left[3][1],
//                Right.x * Left[0][2] + Right.y * Left[1][2] + Right.z * Left[2][2] + Right.w * Left[3][2],
//                Right.x * Left[0][3] + Right.y * Left[1][3] + Right.z * Left[2][3] + Right.w * Left[3][3]);
//}
