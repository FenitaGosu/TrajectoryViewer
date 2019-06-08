#include "Interfaces/IDataSource.h"

#include "Controller.h"

struct Controller::Impl
{
	Impl(std::unique_ptr<Logic::IDataSource>&& dataSource)
		: dataSource(std::move(dataSource))
	{
	}

	std::unique_ptr<Logic::IDataSource> dataSource;
};

Controller::Controller(std::unique_ptr<Logic::IDataSource>&& dataSource)
	: m_impl(std::make_unique<Impl>(std::move(dataSource)))
{
}

Controller::~Controller() = default;

void Controller::Draw()
{
	m_impl->dataSource->Refresh();
}
