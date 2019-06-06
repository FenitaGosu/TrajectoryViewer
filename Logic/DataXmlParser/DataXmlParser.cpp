#include "Data/Model.h"
#include "Data/Trajectory.h"

#include "DataXmlParser.h"

using namespace Logic;

DataXmlParser::DataXmlParser(const std::string& fileName)
	: QtXmlParser(fileName)
{
}

bool DataXmlParser::ParseData(Trajectory& trajectory, Model& model)
{
	/// @todo
	return Parse();
}
