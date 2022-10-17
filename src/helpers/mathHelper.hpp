#ifndef MATH_HELPER_HPP
#define MATH_HELPER_HPP
#include <mwTPoint3d.hpp>

//In this case is no need to make full implementation
template<typename T>
class Matrix2D
{
public:
    inline Matrix2D(unsigned long nx, unsigned long ny)
        : mNx(nx), mNy(ny)
    { mMatrix = new T[nx*ny]; }

    inline ~Matrix2D() 
        { delete [] mMatrix;}

public:
    inline T& GetElement(unsigned long x, unsigned long y)
    {
        //unsigned long givenIndex = x * mNy + y;
        //if(givenIndex >= mNx * mNy)
        //    throw misc::mwIdxRangeException(mSize, givenIndex);
        return *( mMatrix + x * mNy + y);
    }

    inline T& GetElement(unsigned long index)
    {
        //unsigned long givenIndex = x * mNy + y;
        //if(givenIndex >= mNx * mNy)
        //    throw misc::mwIdxRangeException(mSize, givenIndex);
        return *(mMatrix + index);
    }

    inline unsigned long GetSize()
        { return  mNx * mNy; }
    
private:
    T* mMatrix;
    unsigned long mNx;
    unsigned long mNy;

};

inline unsigned long roundInMin(double x)
{
    int ix = (int)x;
    return ix;
}

inline unsigned int roundInBig(double x)
{
    int ix = (int)x;
    ix += 1;

    return ix;
}

#endif