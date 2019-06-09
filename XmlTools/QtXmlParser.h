#pragma once

#include <memory>

#include "BaseXmlParser.h"

namespace XmlTools
{

class QtXmlParser : public BaseXmlParser
{
public:
	QtXmlParser(const std::string& fileName);
	~QtXmlParser();

protected:
	bool Parse() override final;

private:
	struct Impl;
	std::unique_ptr<Impl> m_impl;
};

}
