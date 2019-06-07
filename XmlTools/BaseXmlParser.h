#pragma once

#include <memory>
#include <functional>
#include <map>
#include <string>

namespace XmlTools
{
	class BaseXmlParser
	{
	public:
		BaseXmlParser();
		virtual ~BaseXmlParser();	

	protected:
		using ElementParseFunction = std::function<bool(const std::map<std::string, std::string>&, const std::string&)>;

		virtual bool Parse() = 0;

		void AddElementParseFunction(const std::string& name, ElementParseFunction func);
		ElementParseFunction GetElementParseFunction(const std::string& name) const;
		void ClearElementParseFunctions();

	private:
		struct Impl;
		std::unique_ptr<Impl> m_impl;
	};
}