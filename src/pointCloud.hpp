#ifndef POINT_CLOUD_HPP
#define POINT_CLOUD_HPP

#include <functional>

#include <mwTPoint3d.hpp>
#include <mwIdxRangeException.hpp>

#include "cuboid.hpp"
#include <mathHelper.hpp>
#include <vector>

struct Sector
{
    inline Sector(
        unsigned long start_x, unsigned long start_y, unsigned long start_z,
        unsigned long end_x, unsigned long end_y, unsigned long end_z
    )
        : s_x(start_x), s_y(start_y), s_z(start_z),
        e_x(end_x), e_y(end_y), e_z(end_z)
    {}

    unsigned long s_x;
    unsigned long s_y;
    unsigned long s_z;

    unsigned long e_x;
    unsigned long e_y;
    unsigned long e_z;
};

class PointCloud
{
public:
    using IterationFunc = std::function<void(unsigned long x, unsigned long y, unsigned long z)>;

public:
    PointCloud( cadcam::mwTPoint3d<double> refPoint,
                unsigned long nx, 
                unsigned long ny,
                unsigned long nz,
                double delta);

    PointCloud(const PointCloud&) = delete;
    PointCloud &operator=( const PointCloud&) = delete;

    Sector GetPointSector(Cuboid cuboid, unsigned long sectorSize);

    static void DoOnIteration( IterationFunc& func, Sector sector);
    void Serialize(const std::string& path);

public:
    inline unsigned long GetSize() const
        { return mNx * mNy * mNz; }

    inline void MakePointInvisible(
        unsigned long x, unsigned long y, unsigned long z)
    {
        mIsVisible.at(x * mNy * mNz + y * mNz + z) = false;
    }

    inline bool IsPointVisible(
        unsigned long x, unsigned long y, unsigned long z) const
    {
        return mIsVisible.at(x * mNy * mNz + y * mNz + z);
    }

    inline const cadcam::mwTPoint3d<double>& GetPoint (
        unsigned long x, unsigned long y, unsigned long z) const
    {
        return mPointsArray.at(x * mNy * mNz + y * mNz + z); 
    }

    inline void SetPoint(
        unsigned long x, unsigned long y, unsigned long z,
        cadcam::mwTPoint3d<double> point)
    {
        mPointsArray.at(x * mNy * mNz + y * mNz + z) = point;
    }

private:
    const Matrix2D<cadcam::mwTPoint3d<double>> GetTopLayer();
    void SetSecotorInRange(Sector& sector);

private:
    unsigned long mNx;
    unsigned long mNy;
    unsigned long mNz;
    double mDelta;

    std::vector<bool> mIsVisible;
    std::vector<cadcam::mwTPoint3d<double>> mPointsArray;
};

#endif