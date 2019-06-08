#include "QRange.h"

QRange::QRange()
	: min(-1.0, -1.0, -1.0)
	, max(1.0, 1.0, 1.0)
{
}

QRange::QRange(double _min, double _max)
	: min(_min, _min, _min)
	, max(_max, _max, _max)
{
}

QVector3D QRange::center() const
{
	return 0.5 * (max + min);
}

QVector3D QRange::delta() const
{
	return max - min;
}

void QRange::setIfMin(const QVector3D& vec)
{
	if (vec.x() < min.x()) min.setX(vec.x());
	if (vec.y() < min.y()) min.setY(vec.y());
	if (vec.z() < min.z()) min.setZ(vec.z());
}

void QRange::setIfMax(const QVector3D& vec)
{
	if (vec.x() > max.x()) max.setX(vec.x());
	if (vec.y() > max.y()) max.setY(vec.y());
	if (vec.z() > max.z()) max.setZ(vec.z());
}

void QRange::setIfMin(const QRange& in)
{
	setIfMin(in.min);
}

void QRange::setIfMax(const QRange& in)
{
	setIfMax(in.max);
}
