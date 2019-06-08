AddTarget(
	NAME FileWatcher
	SOURCE_DIR FileWatcher/
	SRC *.cpp *.h
	QT_USE Core
	SUBDIRS
	Interfaces
	QtFileWtcher
	)
