#ifndef CYLINDER_HPP
#define CYLINDER_HPP

#include <cmath>
#include <mwTPoint3d.hpp>

#include "cuboid.hpp"

struct Cylinder
{
    Cylinder() = default;

    inline Cylinder(double radius) 
        : radius(radius)
    {}

    inline bool IsBelong(cadcam::mwTPoint3d<double> point)
    {
        //Check if point lies between the planes of the cylinder
        auto cylinderVector = top_position - base_position;
        if( (point - base_position) *  cylinderVector >= 0 &&
            (point - top_position) * cylinderVector <= 0)
        {
            //Check if point lies inside cylinder
            auto result = ~((point - base_position) % cylinderVector) / ~cylinderVector;
            return result <= radius;
        }
        return false;
    }

    inline Cuboid GetCylinderInCuboid()
    {
        cadcam::mwTPoint3d<double> start = 
            {
                (base_position.x() < top_position.x() ? base_position.x() : top_position.x()) - radius, 
                (base_position.y() < top_position.y() ? base_position.y() : top_position.y()) - radius,
                (base_position.z() < top_position.z() ? base_position.z() : top_position.z()) - radius 
            };
        cadcam::mwTPoint3d<double> end = 
            {
                (base_position.x() > top_position.x() ? base_position.x() : top_position.x()) + radius, 
                (base_position.y() > top_position.y() ? base_position.y() : top_position.y()) + radius,
                (base_position.z() > top_position.z() ? base_position.z() : top_position.z()) + radius 
            };

        return Cuboid(start, end);
    }

    cadcam::mwTPoint3d<double> base_position;
    cadcam::mwTPoint3d<double> top_position;
    double radius;
};

#endif