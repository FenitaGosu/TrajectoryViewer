AddTarget(EXECUTABLE
	NAME TrajectoryViewer
	SOURCE_DIR TrajectoryViewer/
	SRC *.cpp *.h
	QT_USE Core Widgets OpenGL
	UI_FILES *.ui GraphicsViewers/*.ui
	SUBDIRS	
	Interfaces
	Controller
	GraphicsViewers
	DEPS
	QPlot3D
	Logic
	XmlTools
	FileWatcher
	)
