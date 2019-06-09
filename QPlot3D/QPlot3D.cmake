# fork https://github.com/pstrom77/QPlot3D

AddTarget(
	NAME QPlot3D
	SOURCE_DIR QPlot3D/
	SRC *.cpp *.h
	QT_USE Core Widgets OpenGL
	DEPS
	opengl32.lib
	)
