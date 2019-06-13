#include <cassert>

#include "DataSourceXml.h"
#include "Interfaces/IDataXmlParser.h"

#include "Data/Model.h"
#include "Data/Trajectory.h"

#include "DataSourceXml.h"

using namespace Data;

struct DataSourceXml::Impl
{
	Impl(std::unique_ptr<IDataXmlParser>&& xmlParser)
		: xmlParser(std::move(xmlParser))
	{
	}

	std::unique_ptr<Model> model;
	std::unique_ptr<Trajectory> trajectory;

	std::unique_ptr<IDataXmlParser> xmlParser;
};

DataSourceXml::DataSourceXml(std::unique_ptr<IDataXmlParser>&& xmlParser)
	: m_impl(std::make_unique<Impl>(std::move(xmlParser)))
{
}

DataSourceXml::~DataSourceXml() = default;

bool DataSourceXml::Refresh()
{
	m_impl->trajectory	= std::make_unique<Trajectory>();
	m_impl->model		= std::make_unique<Model>();

	bool isSuccess = m_impl->xmlParser->ParseData(*m_impl->trajectory, *m_impl->model);
	assert(isSuccess);

	return isSuccess;
}

const Model& DataSourceXml::GetModel() const
{
	assert(m_impl->model);
	return *m_impl->model;
}

const Trajectory& DataSourceXml::GetTrajectory() const
{
	assert(m_impl->trajectory);
	return *m_impl->trajectory;
}
