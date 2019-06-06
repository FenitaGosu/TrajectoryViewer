#pragma once

#include <string>

#include "XmlTools/QtXmlParser.h"

#include "Interfaces/IDataXmlParser.h"

namespace Logic 
{
	class Model;
	class Trajectory;

	class DataXmlParser 
		: public IDataXmlParser
		, public XmlTools::QtXmlParser
	{
	public:
		DataXmlParser(const std::string& fileName);

		bool ParseData(Trajectory& trajectory, Model& model) override;
	};
}