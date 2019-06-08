#pragma once

#include <memory>

namespace Logic {
	class IDataSource;
}

class Controller
{
public:
	Controller(std::unique_ptr<Logic::IDataSource>&& dataSource);
	~Controller();

	void Draw();

private:
	struct Impl;
	std::unique_ptr<Impl> m_impl;
};
