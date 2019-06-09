#include <QGLWidget>

#include <limits>

#include "QAxis.h"
#include "QPlot3D.h"

namespace
{
	void Draw3DPlane(QVector3D topLeft, QVector3D bottomRight, QColor color)
	{
		QVector3D normal = QVector3D::crossProduct(topLeft, bottomRight);
		glNormal3f(normal.x(), normal.y(), normal.z());
		glColor4f(color.redF(), color.greenF(), color.blueF(), color.alphaF());

		glBegin(GL_QUADS);
			glVertex3f(topLeft.x(), topLeft.y(), topLeft.z());
			glVertex3f(bottomRight.x(), topLeft.y(), bottomRight.z());
			glVertex3f(bottomRight.x(), bottomRight.y(), bottomRight.z());
			glVertex3f(topLeft.x(), bottomRight.y(), topLeft.z());
		glEnd();
	}
}

QAxis::QAxis()
	: mPlot(nullptr)
	, mRange(std::numeric_limits<double>::max(), -std::numeric_limits<double>::max())
	, mAxis(X_AXIS)
	, mAdjustPlaneView(true)
	, mShowPlane(true)
	, mShowGrid(true)
	, mShowAxis(true)
	, mShowLabel(true)
	, mShowAxisBox(false)
	, mXLabel("X")
	, mYLabel("Y")
	, mPlaneColor(230, 230, 242)
	, mGridColor(128, 128, 128)
	, mLabelColor(0, 0, 0)
	, mShowLowerTicks(false)
	, mShowUpperTicks(false)
	, mShowLeftTicks(false)
	, mShowRightTicks(false)
	, mTranslate(0.0)
	, mScale(5.0)
	, mLabelFont("Helvetica", 12)
	, mTicksFont("Helvetica", 10)
{
}

void QAxis::setRange(const QRange& range)
{
	mRange = range;

	if (mAxis == X_AXIS)
	{
		mXTicks = getTicks(mRange.min.x(), mRange.max.x());
		mYTicks = getTicks(mRange.min.y(), mRange.max.y());
		mZTicks = getTicks(mRange.min.z(), mRange.max.z());
		mShowUpperTicks = true;
		mShowRightTicks = true;
	}
	else if (mAxis == Y_AXIS)
	{
		mXTicks = getTicks(mRange.min.y(), mRange.max.y());
		mYTicks = getTicks(mRange.min.z(), mRange.max.z());
		mZTicks = getTicks(mRange.min.x(), mRange.max.x());
	}
	else
	{
		mXTicks = getTicks(mRange.min.z(), mRange.max.z());
		mYTicks = getTicks(mRange.min.x(), mRange.max.x());
		mZTicks = getTicks(mRange.min.y(), mRange.max.y());
		mShowUpperTicks = true;
	}

	mTranslate = mZTicks[0];
}

void QAxis::setAxis(const Axis& axis)
{
	mAxis = axis;
}

void QAxis::setAdjustPlaneView(bool value)
{
	mAdjustPlaneView = value;
}

void QAxis::setShowPlane(bool value)
{
	mShowPlane = value;
}

void QAxis::setShowGrid(bool value)
{
	mShowGrid = value;
}

void QAxis::setShowAxis(bool value)
{
	mShowAxis = value;
}

void QAxis::setShowLabel(bool value)
{
	mShowLabel = value;
}

void QAxis::setShowAxisBox(bool value)
{
	mShowAxisBox = value;
}

void QAxis::setPlaneColor(const QColor& color)
{
	mPlaneColor = color;
}

void QAxis::setGridColor(const QColor& color)
{
	mGridColor = color;
}

void QAxis::setLabelColor(const QColor& color)
{
	mLabelColor = color;
}

void QAxis::setLabelFont(const QFont& font)
{
	mLabelFont = font;
}
void QAxis::setTicksFont(const QFont& font)
{
	mTicksFont = font;
}

const QRange& QAxis::range() const
{
	return mRange;
}

bool QAxis::showPlane() const
{
	return mShowPlane;
}

bool QAxis::showGrid() const
{
	return mShowGrid;
}

bool QAxis::showAxis() const
{
	return mShowAxis;
}

bool QAxis::showLabel() const
{
	return mShowLabel;
}

const QString& QAxis::xLabel() const
{
	return mXLabel;
}

const QString QAxis::yLabel() const
{
	return mYLabel;
}

const QColor& QAxis::planeColor() const
{
	return mPlaneColor;
}

const QColor& QAxis::gridColor() const
{
	return mGridColor;
}

const QColor& QAxis::labelColor() const
{
	return mLabelColor;
}

const QFont& QAxis::labelFont() const
{
	return mLabelFont;
}

const QFont& QAxis::ticksFont() const
{
	return mTicksFont;
}

QVector<double> QAxis::getTicks(double minValue, double maxValue) const
{
	QVector<double> tTicks;
	double step = (maxValue - minValue) / mScale;
	double factor = pow(10.0, floor((log(step) / log(10.0))));

	double tmp = step / factor;
	if (tmp < mScale)
	{
		step = (int)(tmp * 2) / 2.0 * factor;
	}
	else
	{
		step = (int)(tmp * 0.5) / 2.0 * factor;
	}
	int firstStep = floor(minValue / step);
	int lastStep = ceil(maxValue / step);
	int tickCount = lastStep - firstStep + 1;

	for (int i = 0; i < tickCount; i++)
	{
		tTicks.push_back((firstStep + i) * step);
	}
	return tTicks;
}

void QAxis::drawXTickLabel(const QVector3D& start, const QVector3D& stop, const QString& string) const
{
	QRect textSize = mPlot->textSize(string);

	const QVector3D tmpStart = mPlot->toScreenCoordinates(start.x(), start.y(), 0.0);
	const QVector3D tmpStop = mPlot->toScreenCoordinates(stop.x(), stop.y(), 0.0);
	const QVector2D tStart(tmpStart.x(), tmpStart.y());
	const QVector2D tStop(tmpStop.x(), tmpStop.y());

	QVector2D r = tStop - tStart;
	QVector2D v = tStop;
	if (r.x() < 0)
	{
		v - QVector2D(textSize.width(), 0.0);
		v += QVector2D(-textSize.width(), 0.5 * textSize.height());
	}
	else
	{
		v += QVector2D(0, 0.5 * textSize.height());
	}

	glColor4f(mLabelColor.redF(), mLabelColor.greenF(), mLabelColor.blueF(), mLabelColor.alphaF());
	mPlot->renderTextAtScreenCoordinates(v.x(), v.y(), string, mTicksFont);
}

bool QAxis::isEmpty() const
{
	return mXTicks.isEmpty() || mYTicks.isEmpty() || mZTicks.isEmpty();
}

void QAxis::drawAxisPlane() const
{
	if (isEmpty())
		return;

	double minX = mXTicks[0];
	double maxX = mXTicks[mXTicks.size() - 1];
	double minY = mYTicks[0];
	double maxY = mYTicks[mYTicks.size() - 1];

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glEnable(GL_POLYGON_OFFSET_FILL);
	glPolygonOffset(1.0f, 1.0f);

	// Plane
	if (mShowPlane)
	{
		Draw3DPlane(QVector3D(minX, minY, 0), QVector3D(maxX, maxY, 0), mPlaneColor);
	}

	double deltaX = mXTicks[1] - mXTicks[0];
	double deltaY = mYTicks[1] - mYTicks[0];

	// Grid
	for (int i = 0; i < mXTicks.size(); i++)
	{
		if (mShowGrid)
		{
			mPlot->draw3DLine(QVector3D(mXTicks[i], minY, 0), QVector3D(mXTicks[i], maxY, 0), 2, mGridColor);
		}
		if (mShowAxis && mShowLowerTicks)
		{
			mPlot->draw3DLine(QVector3D(mXTicks[i], minY, 0), QVector3D(mXTicks[i], minY - 0.2 * deltaY, 0), 2, mLabelColor);
			drawXTickLabel(QVector3D(mXTicks[i], minY, 0), QVector3D(mXTicks[i], minY - 0.5 * deltaY, 0), QString("%1").arg(mXTicks[i], 3, 'f', 1));
		}
		if (mShowAxis && mShowUpperTicks)
		{
			mPlot->draw3DLine(QVector3D(mXTicks[i], maxY, 0), QVector3D(mXTicks[i], maxY + 0.2 * deltaY, 0), 2, mLabelColor);
			drawXTickLabel(QVector3D(mXTicks[i], maxY, 0), QVector3D(mXTicks[i], maxY + 0.5 * deltaY, 0), QString("%1").arg(mXTicks[i], 3, 'f', 1));
		}
	}

	for (int i = 1; i < mYTicks.size(); i++)
		{
		if (mShowGrid)
		{
			mPlot->draw3DLine(QVector3D(minX, mYTicks[i], 0), QVector3D(maxX, mYTicks[i], 0), 2, mGridColor);
		}
		if (mShowAxis && mShowLeftTicks)
		{
			mPlot->draw3DLine(QVector3D(minX, mYTicks[i], 0), QVector3D(minX - 0.2 * deltaX, mYTicks[i], 0), 2, mLabelColor);
			drawXTickLabel(QVector3D(minX, mYTicks[i], 0), QVector3D(minX - 0.5 * deltaX, mYTicks[i], 0), QString("%1").arg(mYTicks[i], 3, 'f', 1));
		}
		if (mShowAxis && mShowRightTicks)
		{
			mPlot->draw3DLine(QVector3D(maxX, mYTicks[i], 0), QVector3D(maxX + 0.2 * deltaX, mYTicks[i], 0), 2, mLabelColor);
			drawXTickLabel(QVector3D(maxX, mYTicks[i], 0.0), QVector3D(maxX + 0.5 * deltaX, mYTicks[i], 0), QString("%1").arg(mYTicks[i], 3, 'f', 1));
		}
	}

	if (mShowAxis && mShowLowerTicks)
	{
		mPlot->draw3DLine(QVector3D(minX, minY, 0), QVector3D(maxX + 0.5 * deltaX, minY, 0), 3, mLabelColor);
	}
	if (mShowLabel && mShowLowerTicks)
	{
		mPlot->renderTextAtWorldCoordinates(QVector3D(0.5 * (maxX + minX), minY - 1.5 * deltaY, 0), mXLabel, mLabelFont);
	}
	if (mShowAxis && mShowUpperTicks)
	{
		mPlot->draw3DLine(QVector3D(minX, maxY, 0), QVector3D(maxX + 0.5 * deltaX, maxY, 0), 3, mLabelColor);
	}
	if (mShowLabel && mShowUpperTicks)
	{
		mPlot->renderTextAtWorldCoordinates(QVector3D(0.5 * (maxX + minX), maxY + 1.5 * deltaY, 0), mXLabel, mLabelFont);
	}
	if (mShowAxis && mShowLeftTicks)
	{
		mPlot->draw3DLine(QVector3D(minX, minY, 0), QVector3D(minX, maxY + 0.5 * deltaY, 0), 3, mLabelColor);
	}
	if (mShowLabel && mShowLeftTicks)
	{
		mPlot->renderTextAtWorldCoordinates(QVector3D(minX - 1.5 * deltaX, 0.5 * (maxY + minY), 0), mYLabel, mLabelFont);
	}
	if (mShowAxis && mShowRightTicks)
	{
		mPlot->draw3DLine(QVector3D(maxX, minY, 0), QVector3D(maxX, maxY + 0.5 * deltaY, 0), 3, mLabelColor);
	}
	if (mShowLabel && mShowRightTicks)
	{
		mPlot->renderTextAtWorldCoordinates(QVector3D(maxX + 1.5 * deltaX, 0.5 * (maxY + minY), 0), mYLabel, mLabelFont);
	}

	glDisable(GL_POLYGON_OFFSET_FILL);
}

void QAxis::draw() const
{
	if (isEmpty())
		return;

	glPushMatrix();

	if (mAxis == X_AXIS)
	{
		// do nothing
	}
	else if (mAxis == Y_AXIS)
	{
		glRotatef(90, 1, 0, 0);
		glRotatef(90, 0, 1, 0);
	}
	else
{
		glRotatef(90, 1, 0, 0);
		glRotatef(180, 0, 1, 0);
		glRotatef(90, 0, 0, 1);
	}

	glTranslatef(0, 0, mTranslate);
	drawAxisPlane();

	glPopMatrix();
}
void QAxis::drawAxisBox() const
{
	if (isEmpty())
		return;

	glPushMatrix();

	if (mShowAxisBox)
	{
		if (mAxis == X_AXIS)
		{
			// do nothing
		}
		else if (mAxis == Y_AXIS)
		{
			glRotatef(90, 1, 0, 0);
			glRotatef(90, 0, 1, 0);
		}
		else
		{
			glRotatef(90, 1, 0, 0);
			glRotatef(180, 0, 1, 0);
			glRotatef(90, 0, 0, 1);
		}

		// glTranslatef(0,0,-mTranslate);
		mPlot->draw3DLine(QVector3D(mXTicks[0], mYTicks[0], mZTicks[0]), QVector3D(mXTicks[mXTicks.size() - 1], mYTicks[0], mZTicks[0]), 2, mLabelColor);
		mPlot->draw3DLine(QVector3D(mXTicks[mXTicks.size() - 1], mYTicks[0], mZTicks[0]), QVector3D(mXTicks[mXTicks.size() - 1], mYTicks[mYTicks.size() - 1], mZTicks[0]), 2, mLabelColor);
		mPlot->draw3DLine(QVector3D(mXTicks[mXTicks.size() - 1], mYTicks[mYTicks.size() - 1], mZTicks[0]), QVector3D(mXTicks[0], mYTicks[mYTicks.size() - 1], mZTicks[0]), 2, mLabelColor);
		mPlot->draw3DLine(QVector3D(mXTicks[0], mYTicks[mYTicks.size() - 1], mZTicks[0]), QVector3D(mXTicks[0], mYTicks[0], mZTicks[0]), 2, mLabelColor);

		mPlot->draw3DLine(QVector3D(mXTicks[0], mYTicks[0], mZTicks[mZTicks.size() - 1]), QVector3D(mXTicks[mXTicks.size() - 1], mYTicks[0], mZTicks[mZTicks.size() - 1]), 2, mLabelColor);
		mPlot->draw3DLine(QVector3D(mXTicks[mXTicks.size() - 1], mYTicks[0], mZTicks[mZTicks.size() - 1]), QVector3D(mXTicks[mXTicks.size() - 1], mYTicks[mYTicks.size() - 1], mZTicks[mZTicks.size() - 1]), 2, mLabelColor);
		mPlot->draw3DLine(QVector3D(mXTicks[mXTicks.size() - 1], mYTicks[mYTicks.size() - 1], mZTicks[mZTicks.size() - 1]), QVector3D(mXTicks[0], mYTicks[mYTicks.size() - 1], mZTicks[mZTicks.size() - 1]), 2, mLabelColor);
		mPlot->draw3DLine(QVector3D(mXTicks[0], mYTicks[mYTicks.size() - 1], mZTicks[mZTicks.size() - 1]), QVector3D(mXTicks[0], mYTicks[0], mZTicks[mZTicks.size() - 1]), 2, mLabelColor);
	}
	glPopMatrix();
}

void QAxis::setPlot(QPlot3D* plot)
{
	mPlot = plot;
}

void QAxis::setXLabel(const QString& label)
{
	mXLabel = label;
}

void QAxis::setYLabel(const QString& label)
{
	mYLabel = label;
}

void QAxis::setVisibleTicks(bool lower, bool right, bool upper, bool left)
{
	mShowLeftTicks = left;
	mShowRightTicks = right;
	mShowLowerTicks = lower;
	mShowUpperTicks = upper;
}

void QAxis::adjustPlaneView()
{
	if (!mAdjustPlaneView || mZTicks.isEmpty()) return;

	bool tFlipX = false;
	bool tFlipY = false;
	bool tFlipZ = false;

	// Translate the planes so that they are always in the background
	const QVector3D camPos = mPlot->cameraPositionInWorldCoordinates();
	if ((camPos - 0.5 * (QVector3D(mRange.max.x(), mRange.max.y(), mRange.max.z()) + QVector3D(mRange.min.x(), mRange.min.y(), mRange.max.z()))).length() >
		(camPos - 0.5 * (QVector3D(mRange.max.x(), mRange.max.y(), mRange.min.z()) + QVector3D(mRange.min.x(), mRange.min.y(), mRange.min.z()))).length())
		tFlipX = true;

	if ((camPos - 0.5 * (QVector3D(mRange.max.x(), mRange.max.y(), mRange.max.z()) + QVector3D(mRange.max.x(), mRange.min.y(), mRange.min.z()))).length() >
		(camPos - 0.5 * (QVector3D(mRange.min.x(), mRange.max.y(), mRange.max.z()) + QVector3D(mRange.min.x(), mRange.min.y(), mRange.min.z()))).length())
		tFlipY = true;

	if ((camPos - 0.5 * (QVector3D(mRange.max.x(), mRange.max.y(), mRange.max.z()) + QVector3D(mRange.min.x(), mRange.max.y(), mRange.min.z()))).length() >
		(camPos - 0.5 * (QVector3D(mRange.max.x(), mRange.min.y(), mRange.max.z()) + QVector3D(mRange.min.x(), mRange.min.y(), mRange.min.z()))).length())
		tFlipZ = true;

	// Default translation of the plane
	mTranslate = mZTicks[0];

	// If it was THIS plane that flipped move it to the back.
	if ((mAxis == X_AXIS && tFlipX) || (mAxis == Y_AXIS && tFlipY) || (mAxis == Z_AXIS && tFlipZ))
	{
		mTranslate = mZTicks[mZTicks.size() - 1];
	}

	// Default ticks

	if (0.0 <= mPlot->elevation() && 90.0 > mPlot->elevation())
	{
		if (0.0 <= mPlot->azimuth() && 90.0 > mPlot->azimuth())
		{
			if (mAxis == X_AXIS) setVisibleTicks(true, true, false, false);
			if (mAxis == Y_AXIS) setVisibleTicks(false, false, false, false);
			if (mAxis == Z_AXIS) setVisibleTicks(false, false, true, false);
		}

		if (90.0 <= mPlot->azimuth() && 180.0 > mPlot->azimuth())
		{
			if (mAxis == X_AXIS) setVisibleTicks(false, true, true, false);
			if (mAxis == Y_AXIS) setVisibleTicks(false, false, false, false);
			if (mAxis == Z_AXIS) setVisibleTicks(false, false, true, false);
		}

		if (180.0 <= mPlot->azimuth() && 270.0 > mPlot->azimuth())
		{
			if (mAxis == X_AXIS) setVisibleTicks(false, false, true, true);
			if (mAxis == Y_AXIS) setVisibleTicks(false, false, false, false);
			if (mAxis == Z_AXIS) setVisibleTicks(true, false, false, false);
		}

		if (270.0 <= mPlot->azimuth() && 360.0 > mPlot->azimuth())
		{
			if (mAxis == X_AXIS) setVisibleTicks(true, false, false, true);
			if (mAxis == Y_AXIS) setVisibleTicks(false, false, false, true);
			if (mAxis == Z_AXIS) setVisibleTicks(false, false, false, false);
		}
	}
	else
	{
		if (0.0 <= mPlot->azimuth() && 90.0 > mPlot->azimuth())
		{
			if (mAxis == X_AXIS) setVisibleTicks(false, false, false, false);
			if (mAxis == Y_AXIS) setVisibleTicks(true, false, false, false);
			if (mAxis == Z_AXIS) setVisibleTicks(false, false, true, true);
		}

		if (90.0 <= mPlot->azimuth() && 180.0 > mPlot->azimuth())
		{
			if (mAxis == X_AXIS) setVisibleTicks(false, false, false, false);
			if (mAxis == Y_AXIS) setVisibleTicks(true, false, false, false);
			if (mAxis == Z_AXIS) setVisibleTicks(false, false, true, true);
		}

		if (180.0 <= mPlot->azimuth() && 270.0 > mPlot->azimuth())
		{
			if (mAxis == X_AXIS) setVisibleTicks(false, false, false, false);
			if (mAxis == Y_AXIS) setVisibleTicks(true, false, false, false);
			if (mAxis == Z_AXIS) setVisibleTicks(true, false, false, true);
		}

		if (270.0 <= mPlot->azimuth() && 360.0 > mPlot->azimuth())
		{
			if (mAxis == X_AXIS) setVisibleTicks(false, false, false, false);
			if (mAxis == Y_AXIS) setVisibleTicks(true, false, false, false);
			if (mAxis == Z_AXIS) setVisibleTicks(true, false, false, true);
		}
	}
}

void QAxis::togglePlane()
{
	mShowPlane = !mShowPlane;
}

void QAxis::toggleGrid()
{
	mShowGrid = !mShowGrid;
}

void QAxis::toggleAxis()
{
	mShowAxis = !mShowAxis;
}

void QAxis::toggleLabel()
{
	mShowLabel = !mShowLabel;
}

void QAxis::toggleAxisBox()
{
	mShowAxisBox = !mShowAxisBox;
}

void QAxis::toggleAdjustView()
{
	mAdjustPlaneView = !mAdjustPlaneView;
}
