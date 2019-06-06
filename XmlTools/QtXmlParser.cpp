#include <QFile>
#include <QXmlStreamReader>

#include "QtXmlParser.h"

using namespace XmlTools;

struct QtXmlParser::Impl
{
	Impl(const std::string& fileName)
		: fileName(fileName)
	{
	}

	const std::string fileName;
};

QtXmlParser::QtXmlParser(const std::string& fileName)
	: m_impl(std::make_unique<Impl>(fileName))
{
}

QtXmlParser::~QtXmlParser() = default;

bool QtXmlParser::Parse()
{
	QFile xmlFile(QString::fromStdString(m_impl->fileName));

	if (!xmlFile.open(QIODevice::ReadOnly | QIODevice::Text))
		return false;

	QXmlStreamReader  xmlReader(&xmlFile);

	while (!xmlReader.atEnd())
	{
		xmlReader.readNext();

		if (!xmlReader.isStartElement())
			continue;		
		
		const auto name = xmlReader.name().toString().toStdString();
		const auto elementParseFunction = GetElementParseFunction(name);

		if (!elementParseFunction)
			continue;

		std::vector<std::pair<std::string, std::string>> attributes;

		{
			const auto atrList = xmlReader.attributes();

			attributes.reserve(atrList.size());

			std::transform(atrList.cbegin(), atrList.cend(), std::back_inserter(attributes), [](const auto& atr)
			{
				return std::make_pair(atr.name().toString().toStdString(), atr.value().toString().toStdString());
			});
		}
					
		if (xmlReader.name() == "Root") //@todo
			continue;

		std::string elementText;
		elementText = xmlReader.readElementText().toStdString();

		if (!elementParseFunction(attributes, elementText))
		{
			assert(!"Unable to parse item");
			return false;
		}			
	}

	if (xmlReader.hasError()) 
		return false;

	return true;
}
