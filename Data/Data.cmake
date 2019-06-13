AddTarget(
	NAME Data
	SOURCE_DIR Data/
	SRC *.cpp *.h
	QT_USE Core
	SUBDIRS
	Data
	DataXmlParser
	DataSourceXml
	DEPS
	XmlTools
	)
