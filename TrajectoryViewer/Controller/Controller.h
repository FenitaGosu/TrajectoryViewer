#pragma once

#include <memory>

namespace Logic {
	class IDataSource;
}

namespace TrajectoryViewer {

class I2DView;
class I3DView;

class Controller
{
public:
	Controller(std::unique_ptr<Logic::IDataSource>&& dataSource, I3DView* view3d, I2DView* view2d);
	~Controller();

	void Draw();

private:
	struct Impl;
	std::unique_ptr<Impl> m_impl;
};

}
