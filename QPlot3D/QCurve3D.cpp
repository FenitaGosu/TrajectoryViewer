#include <QVector3D>
#include <QVector>

#include "QCurve3D.h"

QCurve3D::QCurve3D()
	: mName("")
	, mColor(0, 0, 255)
	, mLineWidth(1)
	, mRange(std::numeric_limits<double>::max(), -std::numeric_limits<double>::max())
{
}

QCurve3D::QCurve3D(const QCurve3D& rhs)
	: mName(rhs.mName)
	, mColor(rhs.mColor)
	, mLineWidth(rhs.mLineWidth)
	, mRange(rhs.mRange)
{
}

QCurve3D::QCurve3D(const QString& name)
	: mName(name)
	, mColor(0, 0, 255)
	, mLineWidth(1)
	, mRange(std::numeric_limits<double>::max(), -std::numeric_limits<double>::max())
{
}

const QColor& QCurve3D::color() const
{
	return mColor;
}

double QCurve3D::lineWidth() const
{
	return mLineWidth;
}

QVector3D& QCurve3D::value(int index)
{
	return mVertices[index];
}

const QVector3D& QCurve3D::value(int index) const
{
	return mVertices[index];
}

const QRange& QCurve3D::range() const
{
	return mRange;
}

const QString& QCurve3D::name() const
{
	return mName;
}

void QCurve3D::setColor(const QColor& color)
{
	mColor = color;
}

void QCurve3D::setLineWidth(int value)
{
	mLineWidth = value;
}

void QCurve3D::setName(const QString& name)
{
	mName = name;
}

void QCurve3D::addData(const double& x, const double& y, const double& z)
{
	addData(QVector3D(x, y, z));
}

void QCurve3D::addData(const QVector<double>& x, const QVector<double>& y, const QVector<double>& z)
{
	for (int i = 0, tSize = x.size(); i < tSize; i++)
		addData(x[i], y[i], z[i]);
}

void QCurve3D::addData(const QVector<QVector3D>& data)
{
	for (int i = 0, tSize = data.size(); i < tSize; i++)
		addData(data[i]);
}

void QCurve3D::addData(const QVector3D& data)
{
	mRange.setIfMin(data);
	mRange.setIfMax(data);

	mVertices.push_back(data);
	mFaces.push_back(mVertices.size() - 1);
}

void QCurve3D::clear() { mVertices.clear(); }

int QCurve3D::size() const { return mVertices.size(); }

QVector3D& QCurve3D::operator[](int i)
{
	return value(i);
}

const QVector3D& QCurve3D::operator[](int i) const
{
	return value(i);
}

void QCurve3D::draw() const
{
	glVertexPointer(3, GL_FLOAT, 0, mVertices.constData());

	glLineWidth(mLineWidth);
	glColor3f(mColor.red() / 255.0, mColor.green() / 255.0, mColor.blue() / 255.0);
	glEnableClientState(GL_VERTEX_ARRAY);
	glDrawElements(GL_LINE_STRIP, mFaces.count(), GL_UNSIGNED_SHORT, (GLushort*)mFaces.constData());
	glDisableClientState(GL_VERTEX_ARRAY);
	glLineWidth(1);
}
