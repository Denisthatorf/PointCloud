#ifndef SPHERE_HPP
#define SPHERE_HPP

#include <mwTPoint3d.hpp>
#include "cuboid.hpp"

class Sphere
{
public:
    Sphere(double radius);

    bool IsBelong(const cadcam::mwTPoint3d<double>& point);
    Cuboid GetSphereInCuboid();

    inline void SetCenterPosition(cadcam::mwTPoint3d<double> point) 
        { mCenterPos = point; } 

    inline const cadcam::mwTPoint3d<double>& GetCenterPosition() 
        { return mCenterPos; } 

    inline const double& GetRadius()
        {return mRadius;}

private:
    const double mRadius;
	cadcam::mwTPoint3d<double> mCenterPos;
};

#endif