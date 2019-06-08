#pragma once

#include <QObject>
#include <QVector3D>
#include <QVector>
#include <QColor>
#include <QString>
#include <QGLWidget>

#include "QRange.h"

class QPlot3D;

class QCurve3D : public QObject
{
	Q_OBJECT

	friend class QPlot3D;

public:
	QCurve3D();
	QCurve3D(const QCurve3D& rhs);
	QCurve3D(QString name);

	QColor color() const { return mColor; }
	double lineWidth() const { return mLineWidth; }
	QVector3D& value(int index) { return mVertices[index]; }
	const QVector3D& value(int index) const { return mVertices[index]; }
	QRange range() const { return mRange; }
	QString name() const { return mName; }

	void setColor(QColor color) { mColor = color; }
	void setLineWidth(int value) { mLineWidth = value; }
	void setName(QString name) { mName = name; }

	void addData(const double& x, const double& y, const double& z);
	void addData(const QVector<double>& x, const QVector<double>& y, const QVector<double>& z);
	void addData(const QVector<QVector3D>& data);
	void addData(const QVector3D& data);
	void clear() { mVertices.clear(); }
	int size() const { return mVertices.size(); }

	QVector3D& operator[](int i);
	const QVector3D& operator[](int i) const;

protected:
	void draw() const;

private:
	QString mName;
	QColor mColor;
	int mLineWidth;

	QVector<QVector3D> mVertices;
	QVector<GLushort> mFaces;
	QRange mRange;
};
