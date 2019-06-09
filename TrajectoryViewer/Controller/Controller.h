#pragma once

#include <memory>

namespace Logic {
	class IDataSource;
}

namespace GraphicsViewers {
	class I2DView;
	class I3DView;
}
namespace TrajectoryViewer {

class Controller
{
public:
	Controller(std::unique_ptr<Logic::IDataSource>&& dataSource, GraphicsViewers::I3DView* view3d, GraphicsViewers::I2DView* view2d);
	~Controller();

	void Draw();

private:
	struct Impl;
	std::unique_ptr<Impl> m_impl;
};

}
