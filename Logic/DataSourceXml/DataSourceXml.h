#pragma once

#include <memory>

#include "Interfaces/IDataSource.h"

namespace Logic
{
	class IDataXmlParser;

	class DataSourceXml : public IDataSource
	{
	public:
		DataSourceXml(std::unique_ptr<IDataXmlParser>&& xmlParser);
		~DataSourceXml();

		void Refresh() override;

		const Model& GetModel() const override;
		const Trajectory& GetTrajectory() const override;

	private:
		struct Impl;
		std::unique_ptr<Impl> m_impl;
	};
}