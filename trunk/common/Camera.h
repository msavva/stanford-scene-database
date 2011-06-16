//
// Camera.h
//

#include "Matrix4.h"

class Camera
{
public:
    void Reset(const Vec3f &eye, const Vec3f &worldUp, const Vec3f &lookAt);
    
    void Update();
    
    //
    // Movement
    //
    void LookUp(float Theta);
    void LookRight(float Theta);
    void Roll(float Theta);
    void Move(float Distance);
    void Jump(float Distance);
    void Strafe(float Distance);

    //
    // Accessors
    //
    Matrix4& Matrix()
    {
        return _matrix;
    }
    const Matrix4& Matrix() const
    {
        return _matrix;
    }
    Vec3f& VecEye()
    {
        return _eye;
    }
    const Vec3f& VecEye() const
    {
        return _eye;
    }
    Vec3f& VecLookDir()
    {
        return _look;
    }
    const Vec3f& VecLookDir() const
    {
        return _look;
    }
    Vec3f& VecUp()
    {
        return _up;
    }
    const Vec3f& VecUp() const
    {
        return _up;
    }
    Vec3f& VecRight()
    {
        return _right;
    }
    const Vec3f& VecRight() const
    {
        return _right;
    }
    Vec3f& AbsoluteUp()
    {
        return _worldUp;
    }
    const Vec3f& AbsoluteUp() const
    {
        return _worldUp;
    }

private:
    Vec3f _eye, _look, _up, _right, _worldUp;
    Matrix4 _matrix;
};
