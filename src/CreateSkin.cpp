#include "CreateSkin.hpp"

#include <climits>
#include <functional>

#include "log.hpp"
#include "timer.hpp"

#include "mwTPoint3d.hpp"
#include <mwException.hpp>

#include "pointCloud.hpp"
#include "sphere.hpp"
#include "cylinder.hpp"
#include "cuboid.hpp"

void CreateSkin( const cadcam::mwTPoint3d<double> refPoint, 
				const unsigned long nx, 
				const unsigned long ny, 
				const unsigned long nz,
				const double sphereRad, 
				mwDiscreteFunction &func, const double deltaT, 
				const double delta, const std::string &skinFileName )
{
	PointCloud cloud(refPoint, nx, ny, nz, delta);
	Sphere sphere(sphereRad);	
	Cylinder cylinder(sphereRad);

	PointCloud::IterationFunc sphereFunc = [&](auto x, auto y, auto z) 
	{
		if(sphere.IsBelong(cloud.GetPoint(x, y, z)))
			cloud.MakePointInvisible(x, y, z);
	};

	PointCloud::IterationFunc cylinderFunc = [&](auto x, auto y, auto z) 
	{
		if(cylinder.IsBelong(cloud.GetPoint(x, y, z)))
			cloud.MakePointInvisible(x, y, z);
	};

	log_info("Start calculating");
	Timer mainTimer;

	double stepTime = 0;
	cadcam::mwTPoint3d<double> previousPoint = func.Evaluate(stepTime);
	cadcam::mwTPoint3d<double> firstPoint = previousPoint;
	stepTime += deltaT;

	while(true)
	{
		try
		{
			auto point = func.Evaluate(stepTime);

			sphere.SetCenterPosition(previousPoint);
			cylinder.base_position = previousPoint;
			cylinder.top_position = point;

			//Also can make DoOnIteration use GetPointSector inside 
			//But in this way it more clearer what we do

			//Check collision with sphere
			auto sphereSector = cloud.GetPointSector(
				sphere.GetSphereInCuboid(), sphere.GetRadius());
			PointCloud::DoOnIteration(sphereFunc, sphereSector);

			//Check collision with cylinder
			auto cylinderSector = cloud.GetPointSector(
				cylinder.GetCylinderInCuboid(), sphere.GetRadius());
			PointCloud::DoOnIteration(cylinderFunc, cylinderSector);

			previousPoint = point;
			stepTime += deltaT;
		}
		catch(misc::mwException ex)
		{
			//Make last connection between last and first point
			sphere.SetCenterPosition(previousPoint);
			cylinder.base_position = previousPoint;
			cylinder.top_position = firstPoint;

			auto sphereSector = cloud.GetPointSector(
				sphere.GetSphereInCuboid(), sphere.GetRadius());
			PointCloud::DoOnIteration(sphereFunc, sphereSector);

			//Check collision with cylinder
			auto cylinderSector = cloud.GetPointSector(
				cylinder.GetCylinderInCuboid(), sphere.GetRadius());
			PointCloud::DoOnIteration(cylinderFunc, cylinderSector);

			break;	
		}
	}

	mainTimer.Finish();
	log_info("End calculation (duration - %ld)",
				mainTimer.GetDurationMicroseconds());

	log_info("Start serializing");
	Timer serializeTimer;

	cloud.Serialize(skinFileName);

	serializeTimer.Finish();
	log_info("End serializing (duration - %ld)", 
				serializeTimer.GetDurationMicroseconds());
}