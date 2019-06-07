#include <map>
#include <cassert>

#include "BaseXmlParser.h"

using namespace XmlTools;

struct BaseXmlParser::Impl
{
	std::map<std::string, ElementParseFunction> elementsParsers;
};

BaseXmlParser::BaseXmlParser()
	: m_impl(std::make_unique<Impl>())
{
}

BaseXmlParser::~BaseXmlParser() = default;

void BaseXmlParser::AddElementParseFunction(const std::string& name, ElementParseFunction func)
{
	const auto res = m_impl->elementsParsers.emplace(name, func);
	assert(res.second);
}

BaseXmlParser::ElementParseFunction BaseXmlParser::GetElementParseFunction(const std::string& name) const
{
	const auto it = m_impl->elementsParsers.find(name);	
	return it == m_impl->elementsParsers.cend() ? ElementParseFunction() : it->second;
}

void BaseXmlParser::ClearElementParseFunctions()
{
	m_impl->elementsParsers.clear();
}
