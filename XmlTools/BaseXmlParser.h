#pragma once

#include <memory>
#include <functional>
#include <vector>
#include <string>

namespace XmlTools
{
	class BaseXmlParser
	{
	public:
		BaseXmlParser();
		virtual ~BaseXmlParser();

		virtual bool Parse() = 0;

	protected:
		using ElementParseFunction = std::function<bool(const std::vector<std::pair<std::string, std::string>>&, const std::string&)>;

		void AddElementParseFunction(const std::string name, ElementParseFunction func);

	private:
		struct Impl;
		std::unique_ptr<Impl> m_impl;
	};
}