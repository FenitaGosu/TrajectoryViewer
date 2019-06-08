#pragma once

#include <QVector3D>

struct QRange
{
	QRange();
	QRange(double _min, double _max);

	QVector3D center() const;
	QVector3D delta() const;

	void setIfMin(const QVector3D& in);
	void setIfMax(const QVector3D& in);
	void setIfMin(const QRange& in);
	void setIfMax(const QRange& in);

	QVector3D min;
	QVector3D max;
};
