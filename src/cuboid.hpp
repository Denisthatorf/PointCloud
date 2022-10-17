#ifndef CUBOID_HPP
#define CUBOID_HPP

#include <mwTPoint3d.hpp>

struct Cuboid
{
    inline Cuboid(
        cadcam::mwTPoint3d<double> startPos, 
        cadcam::mwTPoint3d<double> endPos)
    : startPosition (startPos), endPosition(endPos)
    {}

    cadcam::mwTPoint3d<double> startPosition;
    cadcam::mwTPoint3d<double> endPosition;
};

#endif