#pragma once

#include <QObject>
#include <QString>
#include <QColor>
#include <QFont>
#include <QVector>
#include <QVector2D>

#include "QRange.h"

class QPlot3D;

class QAxis : public QObject
{
	Q_OBJECT

	friend class QPlot3D;

public:
	enum Axis
	{
		X_AXIS = 0,
		Y_AXIS = 1,
		Z_AXIS = 2
	};

public:
	QAxis();

	void setRange(const QRange& range);
	void setAxis(const Axis& axis);
	void setAdjustPlaneView(bool value);
	void setShowPlane(bool value);
	void setShowGrid(bool value);
	void setShowAxis(bool value);
	void setShowLabel(bool value);
	void setShowAxisBox(bool value);
	void setPlaneColor(const QColor& color);
	void setGridColor(const QColor& color);
	void setLabelColor(const QColor& color);
	void setLabelFont(const QFont& font);
	void setTicksFont(const QFont& font);

	const QRange& range() const { return mRange; }
	bool   showPlane() const { return mShowPlane; }
	bool   showGrid()  const { return mShowGrid; }
	bool   showAxis()  const { return mShowAxis; }
	bool   showLabel()  const { return mShowLabel; }
	const QString& xLabel() const { return mXLabel; }
	const QString yLabel() const { return mYLabel; }
	const QColor& planeColor() const { return mPlaneColor; }
	const QColor& gridColor() const { return mGridColor; }
	const QColor& labelColor() const { return mLabelColor; }
	const QFont& labelFont() const { return mLabelFont; }
	const QFont& ticksFont() const { return mTicksFont; }

public slots:
	void adjustPlaneView();

	void togglePlane();
	void toggleGrid();
	void toggleAxis();
	void toggleLabel();
	void toggleAxisBox();
	void toggleAdjustView();

protected:
	void draw() const;
	void drawAxisBox() const;
	void setPlot(QPlot3D* plot) { mPlot = plot; }
	void setXLabel(const QString& label) { mXLabel = label; }
	void setYLabel(const QString& label) { mYLabel = label; }
	double mScale;

private:
	void drawAxisPlane() const;
	QVector<double> getTicks(double min, double max) const;
	void setVisibleTicks(bool lower, bool right, bool upper, bool left);
	void drawXTickLabel(QVector3D start, QVector3D stop, const QString& string) const;
	bool isEmpty() const;

private:
	QPlot3D* mPlot;
	QRange mRange;
	Axis  mAxis;
	bool mAdjustPlaneView, mShowPlane, mShowGrid, mShowAxis, mShowLabel, mShowAxisBox;
	QString mXLabel, mYLabel;
	QColor mPlaneColor, mGridColor, mLabelColor;
	QVector<double> mXTicks, mYTicks, mZTicks;
	bool  mShowLowerTicks, mShowUpperTicks, mShowLeftTicks, mShowRightTicks;
	double mTranslate;
	QFont mLabelFont, mTicksFont;
};
