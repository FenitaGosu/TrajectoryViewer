AddTarget(EXECUTABLE
	NAME TrajectoryViewer
	SOURCE_DIR TrajectoryViewer/
	SRC *.cpp *.h
	QT_USE Core Widgets
	UI_FILES *.ui
	DEPS
	XmlTools
	)