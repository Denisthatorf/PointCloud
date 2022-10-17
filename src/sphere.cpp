#include "sphere.hpp"
#include "cuboid.hpp"
#include "mwTPoint3d.hpp"

Sphere::Sphere(double radius)
    :mRadius(radius)
{}

bool Sphere::IsBelong(const cadcam::mwTPoint3d<double>& point)
{
    //Also can
    //cadcam::mwTPoint3d<double> vector_to_center = mCenterPos - point;
    //double distanceToCenter =  vector_to_center * vector_to_center;
    //return distanceToCenter < mRadius;
    //or use squere length

    // (x−cx)^2+(y−cy)^2+(z−cz)^2<r2.
    double xd = point.x() - mCenterPos.x();
    double yd = point.y() - mCenterPos.y();
    double zd = point.z() - mCenterPos.z();

    return xd*xd + yd*yd + zd*zd < mRadius * mRadius;
}

Cuboid Sphere::GetSphereInCuboid()
{
    cadcam::mwTPoint3d<double> radiusVector = { this->GetRadius(), this->GetRadius(), this->GetRadius() };
    return Cuboid(
        this->GetCenterPosition() - radiusVector,
        this->GetCenterPosition() + radiusVector);

}