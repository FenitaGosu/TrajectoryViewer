#include <QVector3D>
#include <QVector>

#include "QCurve3D.h"

QCurve3D::QCurve3D() :
	mName(""),
	mColor(0, 0, 255),
	mLineWidth(1),
	mRange(std::numeric_limits<double>::max(), -std::numeric_limits<double>::max())
{
}

QCurve3D::QCurve3D(const QCurve3D& rhs)
	: mName(rhs.mName)
	, mColor(rhs.mColor)
	, mLineWidth(rhs.mLineWidth)
	, mRange(rhs.mRange)
{
}

QCurve3D::QCurve3D(QString name) :
	mName(name),
	mColor(0, 0, 255),
	mLineWidth(1),
	mRange(std::numeric_limits<double>::max(), -std::numeric_limits<double>::max())
{
}

void QCurve3D::addData(const double& x, const double& y, const double& z) {
	addData(QVector3D(x, y, z));
}

void QCurve3D::addData(const QVector<double>& x, const QVector<double>& y, const QVector<double>& z) {
	int tSize = x.size();
	for (int i = 0; i < tSize; i++) {
		addData(x[i], y[i], z[i]);
	}
}

void QCurve3D::addData(const QVector<QVector3D>& data) {
	int tSize = data.size();
	for (int i = 0; i < tSize; i++) {
		addData(data[i]);
	}
}

void QCurve3D::addData(const QVector3D& data) {
	mRange.setIfMin(data);
	mRange.setIfMax(data);

	mVertices.push_back(data);
	mFaces.push_back(mVertices.size() - 1);
}

QVector3D& QCurve3D::operator[](int i) {
	return value(i);
}

const QVector3D& QCurve3D::operator[](int i) const {
	return value(i);
}

void QCurve3D::draw() const {
	glVertexPointer(3, GL_FLOAT, 0, mVertices.constData());

	glLineWidth(mLineWidth);
	glColor3f(mColor.red() / 255.0, mColor.green() / 255.0, mColor.blue() / 255.0);
	glEnableClientState(GL_VERTEX_ARRAY);
	glDrawElements(GL_LINE_STRIP, mFaces.count(), GL_UNSIGNED_SHORT, (GLushort*)mFaces.constData());
	glDisableClientState(GL_VERTEX_ARRAY);
	glLineWidth(1);
}
