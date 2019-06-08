AddTarget(
	NAME Logic
	SOURCE_DIR Logic/
	SRC *.cpp *.h
	QT_USE Core
	SUBDIRS
	Data
	DataXmlParser
	DataSourceXml
	DEPS
	XmlTools
	)
