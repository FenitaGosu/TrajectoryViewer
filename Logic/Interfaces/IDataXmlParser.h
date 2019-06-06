#pragma once

namespace Logic 
{
	class Trajectory;
	class Model;

	class IDataXmlParser
	{
	public:
		virtual bool ParseData(Trajectory& trajectory, Model& model) = 0;
	};
}