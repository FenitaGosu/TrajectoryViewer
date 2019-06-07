#include <sstream>

#include "Data/Model.h"
#include "Data/Trajectory.h"

#include "DataXmlParser.h"

using namespace Logic;

namespace {
	const std::string TRAJECTORY_NAME	= "Trajectory";
	const std::string MODEL_NAME		= "Model";

	const std::string TRAJECTORY_SIZE_ATR	= "size";

	const std::string MODEL_H_SIZE_ATR			= "hsize";
	const std::string MODEL_V_SIZE_ATR			= "vsize";
	const std::string MODEL_H_OFFSET_ATR		= "hoffset";
	const std::string MODEL_V_OFFSET_ATR		= "voffset";
	const std::string MODEL_H_RESOLUTION_ATR	= "hresolution";
	const std::string MODEL_V_RESOLUTION_ATR	= "vresolution";
	const std::string MODEL_DEPH_ATR			= "mdepth";
	const std::string MODEL_ANGLE_1_X_ATR		= "angle1X";
	const std::string MODEL_ANGLE_2_Z_ATR		= "angle2Z";
	const std::string MODEL_ANGLE_3_X_ATR		= "angle3X";

	void ParseIntAtr(const std::string& str, int* data)
	{
		*data = std::stoi(str);
	}

	void ParseDoubleAtr(const std::string& str, double* data)
	{
		*data = std::stod(str);
	}
}

DataXmlParser::DataXmlParser(const std::string& fileName)
	: QtXmlParser(fileName)
{
}

bool DataXmlParser::ParseData(Trajectory& trajectory, Model& model)
{
	const auto parseTrajectory = [&trajectory, &model](const std::map<std::string, std::string>& attributes, const std::string& data)
	{
		const auto it = attributes.find(TRAJECTORY_SIZE_ATR);

		if (it == attributes.cend())
			return false;

		size_t size = static_cast<size_t>(std::stoi(it->second));
		trajectory.Reserve(size);

		std::istringstream stream(data);

		for (size_t i = 0; i < size; ++i)
		{
			Trajectory::Data data;

			stream >> data.depth;
			stream >> data.azimuth;
			stream >> data.inclination;
			stream >> data.x;
			stream >> data.y;
			stream >> data.z;

			trajectory.AddNewData(std::move(data));
		}

		return true;
	};

	const auto parseModel = [&trajectory, &model](const std::map<std::string, std::string>& atributes, const std::string& data)
	{
		return true;
	};

	AddElementParseFunction(TRAJECTORY_NAME, parseTrajectory);
	AddElementParseFunction(MODEL_NAME, parseTrajectory);

	return Parse();
}
