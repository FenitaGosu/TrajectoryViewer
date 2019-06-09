#pragma once

namespace Logic {

class Model;
class Trajectory;

class IDataSource
{
public:
	virtual ~IDataSource() = default;

	virtual void Refresh() = 0;

	virtual const Model& GetModel() const = 0;
	virtual const Trajectory& GetTrajectory() const = 0;
};

}
