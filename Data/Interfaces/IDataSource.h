#pragma once

namespace Data {

class Model;
class Trajectory;

class IDataSource
{
public:
	virtual ~IDataSource() = default;

	virtual bool Refresh() = 0;

	virtual const Model& GetModel() const = 0;
	virtual const Trajectory& GetTrajectory() const = 0;
};

}
