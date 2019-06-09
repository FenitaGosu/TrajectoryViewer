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
	ClearElementParseFunctions();

	const auto parseTrajectory = [&trajectory](const std::map<std::string, std::string>& atributes, const std::string& data)
	{
		const auto it = atributes.find(TRAJECTORY_SIZE_ATR);

		if (it == atributes.cend())
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

	const auto parseModel = [&model](const std::map<std::string, std::string>& atributes, const std::string& data)
	{

#define PARSE_ATR(ATR, NAME, PARSE_FUNCTION)		\
		{											\
			const auto it = atributes.find(NAME);	\
			if (it == atributes.cend())				\
				return false;						\
			PARSE_FUNCTION(it->second, &ATR);		\
		}											\

		double hSize;
		PARSE_ATR(hSize, MODEL_H_SIZE_ATR, ParseDoubleAtr)

		double vSize;
		PARSE_ATR(vSize, MODEL_V_SIZE_ATR, ParseDoubleAtr)

		double hOffset;
		PARSE_ATR(hOffset, MODEL_H_OFFSET_ATR, ParseDoubleAtr)

		double vOffset;
		PARSE_ATR(vOffset, MODEL_V_OFFSET_ATR, ParseDoubleAtr)

		int hResolution;
		PARSE_ATR(hResolution, MODEL_H_RESOLUTION_ATR, ParseIntAtr)

		int vResolution;
		PARSE_ATR(vResolution, MODEL_V_RESOLUTION_ATR, ParseIntAtr)

		double depth;
		PARSE_ATR(depth, MODEL_DEPH_ATR, ParseDoubleAtr)

		double angle1X;
		PARSE_ATR(angle1X, MODEL_ANGLE_1_X_ATR, ParseDoubleAtr)

		double angle2Z;
		PARSE_ATR(angle2Z, MODEL_ANGLE_2_Z_ATR, ParseDoubleAtr)

		double angle3X;
		PARSE_ATR(angle3X, MODEL_ANGLE_3_X_ATR, ParseDoubleAtr)

#undef PARSE_ATR

		std::istringstream stream(data);

		std::vector<std::vector<double>>  distributionXZ;
		distributionXZ.reserve(vResolution);

		for (int i = 0; i < vResolution; ++i)
		{
			std::vector<double> row;
			row.reserve(hResolution);

			for (int j = 0; j < hResolution; ++j)
			{
				double value;
				stream >> value;
				row.push_back(value);
			}

			distributionXZ.push_back(row);
		}

		model = Model(hSize, vSize, hOffset, vOffset, hResolution, vResolution, depth, angle1X, angle2Z, angle3X, std::move(distributionXZ));

		return true;
	};

	AddElementParseFunction(TRAJECTORY_NAME, parseTrajectory);
	AddElementParseFunction(MODEL_NAME, parseModel);

	return Parse();
}
