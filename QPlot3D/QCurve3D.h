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
	QCurve3D(const QString& name);

	const QColor& color() const;
	double lineWidth() const;
	QVector3D& value(int index);
	const QVector3D& value(int index) const;
	const QRange& range() const;
	const QString& name() const;

	void setColor(const QColor& color);
	void setLineWidth(int value);
	void setName(const QString& name);

	void addData(const double& x, const double& y, const double& z);
	void addData(const QVector<double>& x, const QVector<double>& y, const QVector<double>& z);
	void addData(const QVector<QVector3D>& data);
	void addData(const QVector3D& data);
	void clear();
	int size() const;

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
