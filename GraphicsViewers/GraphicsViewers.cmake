AddTarget(
	NAME GraphicsViewers
	SOURCE_DIR GraphicsViewers/
	SRC *.cpp *.h
	QT_USE Core Widgets OpenGL Charts
	SUBDIRS
	Interfaces
	GraphicsViewers
	DEPS
	Geometry
	QPlot3D
	)
