AddTarget(EXECUTABLE
	NAME TrajectoryViewer
	SOURCE_DIR TrajectoryViewer/
	SRC *.cpp *.h
	QT_USE Core Widgets OpenGL
	UI_FILES *.ui
	SUBDIRS
	Controller
	DEPS
	GraphicsViewers
	Geometry
	Logic
	XmlTools
	FileWatcher
	)
