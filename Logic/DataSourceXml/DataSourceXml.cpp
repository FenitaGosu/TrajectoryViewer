#include <cassert>

#include "DataSourceXml.h"
#include "Interfaces/IDataXmlParser.h"

#include "Data/Model.h"
#include "Data/Trajectory.h"

#include "DataSourceXml.h"

using namespace Logic;

struct DataSourceXml::Impl
{
	Impl(std::unique_ptr<IDataXmlParser>&& xmlParser)
		: xmlParser(std::move(xmlParser))
	{
	}

	Model model;
	Trajectory trajectory;

	std::unique_ptr<IDataXmlParser> xmlParser;
};

DataSourceXml::DataSourceXml(std::unique_ptr<IDataXmlParser>&& xmlParser)
	: m_impl(std::make_unique<Impl>(std::move(xmlParser)))
{
}

DataSourceXml::~DataSourceXml() = default;

void DataSourceXml::Refresh()
{
	[[maybe_unused]] bool isSuccess = m_impl->xmlParser->ParseData(m_impl->trajectory, m_impl->model);
	assert(isSuccess);
}

const Model& DataSourceXml::GetModel() const
{
	return m_impl->model;
}

const Trajectory& DataSourceXml::GetTrajectory() const
{
	return m_impl->trajectory;
}
