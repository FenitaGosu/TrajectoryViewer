AddTarget(EXECUTABLE
	NAME TrajectoryViewer
	SOURCE_DIR TrajectoryViewer/
	SRC *.cpp *.h
	QT_USE Core Widgets
	UI_FILES *.ui GraphicsViewers/*.ui
	SUBDIRS
	Interfaces
	Controller
	GraphicsViewers
	DEPS
	Logic
	XmlTools
	FileWatcher
	)
