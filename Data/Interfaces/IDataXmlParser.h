#pragma once

namespace Data {

class Trajectory;
class Model;

class IDataXmlParser
{
public:
	virtual ~IDataXmlParser() = default;

	virtual bool ParseData(Trajectory& trajectory, Model& model) = 0;
};

}
