#include "pointCloud.hpp"
#include "cuboid.hpp"
#include "mwTPoint3d.hpp"

#include "sphere.hpp"
#include "mathHelper.hpp"

#include <cstring>
#include <fstream>
#include <limits>

PointCloud::PointCloud (cadcam::mwTPoint3d<double> refPoint,
                        unsigned long nx, 
                        unsigned long ny,
                        unsigned long nz,
                        double delta)
    : mNx(nx), mNy (ny), mNz(nz),
    mIsVisible(nx * ny * nz), mPointsArray(nx * ny * nz)
{
    mDelta = delta;

    for(unsigned long i = 0; i < nx * ny * nz; i++)
        mIsVisible[i] = true;

    for(unsigned long x = 0; x < nx; x++)
    {
        for(unsigned long y = 0; y < ny; y++)
        {
            for(unsigned long z = 0; z < nz; z++)
            {
                cadcam::mwTPoint3d<double> point (delta*x, delta*y, delta*z);
                this->SetPoint(x, y, z, point + refPoint);
            }
        }
    }
}

void PointCloud::DoOnIteration(IterationFunc& func, Sector sector)
{
    for (unsigned long x = sector.s_x; x < sector.e_x; x++)
		for (unsigned long y = sector.s_y; y < sector.e_y; y++)
			for (unsigned long z = sector.s_z; z < sector.e_z; z++)
                func(x, y, z);
}

Sector PointCloud::GetPointSector(Cuboid cuboid, unsigned long sectorSize)
{
    // Get Sector in which ball placed
    // and multiply it my sectorSize => get all points that program need to check

    auto mSectorSizeIn3D = sectorSize * mDelta;

    Sector result (
        roundInMin(cuboid.startPosition.x() / mSectorSizeIn3D) * sectorSize,
        roundInMin(cuboid.startPosition.y() / mSectorSizeIn3D) * sectorSize,
        roundInMin(cuboid.startPosition.z() / mSectorSizeIn3D) * sectorSize,
        roundInBig(cuboid.endPosition.x() / mSectorSizeIn3D) * sectorSize,
        roundInBig(cuboid.endPosition.y() / mSectorSizeIn3D) * sectorSize,
        roundInBig(cuboid.endPosition.z() / mSectorSizeIn3D) * sectorSize
    );

    //Check is sector is in mN_ if no change it
    SetSecotorInRange(result);

    return result;
}

void PointCloud::SetSecotorInRange(Sector& sector)
{
    if(sector.e_x > mNx) sector.e_x = mNx;
    if(sector.e_y > mNy) sector.e_y = mNy;
    if(sector.e_z > mNz) sector.e_z = mNz;
}

const Matrix2D<cadcam::mwTPoint3d<double>> PointCloud::GetTopLayer()
{
    Matrix2D<cadcam::mwTPoint3d<double>> result(mNx, mNy);

    const double lowest_double = -std::numeric_limits<double>::max();
    for (unsigned int x = 0; x < mNx; x++)
    {
        for (unsigned int y = 0; y < mNy; y++)
        {
            result.GetElement(x, y) = {lowest_double, lowest_double, lowest_double };
        }
    }

    for(unsigned long x = 0; x < mNx; x++)
    {
        for(unsigned long y = 0; y < mNy; y++)
        {
            for(unsigned long z = 0; z < mNz; z++)
            {
                if(this->IsPointVisible(x, y, z)
                    && this->GetPoint(x, y, z).z() > result.GetElement(x, y).z())
                {
                    result.GetElement(x,y) = this->GetPoint(x, y, z);
                }
            }
        }
    }

    return result;
}

void PointCloud::Serialize(const std::string& path)
{
    std::ofstream stream;
    stream.open(path);

    auto matrix = this->GetTopLayer();

    for(unsigned long i = 0; i < matrix.GetSize(); i++)
    {
        stream <<matrix.GetElement(i).x() << " ";
        stream <<matrix.GetElement(i).y() << " ";
        stream <<matrix.GetElement(i).z() << "\n";
    }

    stream.close();
}