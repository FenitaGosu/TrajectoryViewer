#include <map>
#include <cassert>

#include "BaseXmlParser.h"

using namespace XmlTools;

struct BaseXmlParser::Impl
{
	Impl(const std::string & fileName)
		: fileName(fileName)
	{
	}

	const std::string fileName;
	std::map<std::string, ElementParseFunction> elementsParsers;
};

BaseXmlParser::BaseXmlParser(const std::string& fileName)
	: m_impl(std::make_unique<Impl>(fileName))
{
}

XmlTools::BaseXmlParser::~BaseXmlParser() = default;

void BaseXmlParser::AddElementParseFunction(const std::string name, ElementParseFunction func)
{
	const auto res = m_impl->elementsParsers.emplace(name, func);
	assert(res.second);
}