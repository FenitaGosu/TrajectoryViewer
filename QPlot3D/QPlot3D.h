#pragma once

#include <QtCore>
#include <QGLWidget>
#include <QVector3D>

#include "QRange.h"
#include "QCurve3D.h"
#include "QAxis.h"

class QPlot3D: public QGLWidget
{
	Q_OBJECT

friend class QAxis;

public:
	QPlot3D(QWidget* parent = nullptr);
	~QPlot3D();

	void addCurve(QCurve3D* curve);
	bool removeCurve(QCurve3D* curve);
	void clear() { mCurves.clear(); }
	void setBackgroundColor(QColor color);
	void setLegendFont(QFont font) { mLegendFont = font; }
	QFont legendFont() const { return mLegendFont; }

	double    zoom()  const { return mTranslate.z(); }
	QVector3D pan()   const { return mTranslate;     }
	QColor    background() const { return mBackgroundColor; }
	double    azimuth() const
	{
		double tAzimuth = -mRotation.z();
		return tAzimuth - floor(tAzimuth/360.0)*360.0;
	}
	double    elevation() const
	{
	  if (mRotation.x() > 180)
	    return  mRotation.x() - floor(mRotation.x()/90.0)*90.0;
	  if (mRotation.x() < -180)
	    return  mRotation.x() - floor(mRotation.x()/90.0)*90.0;
	  return mRotation.x();
	}
	QAxis&    xAxis() { return mXAxis; }
	QAxis&    yAxis() { return mYAxis; }
	QAxis&    zAxis() { return mZAxis; }

public slots:
	void setZoom(double value)   { if(value < 0.0) mTranslate.setZ(value); updateGL(); }
	void setPan(QVector3D value) { mTranslate = value;     updateGL(); }
	void setShowAzimuthElevation(bool value) { mShowAzimuthElevation = value; }
	void setAzimuth(double value)   { mRotation.setZ(-value); }
	void setElevation(double value) { mRotation.setX(value); }
	void setShowLegend(bool value)  { mShowLegend = value; }
	void setAxisEqual(bool value)   { mAxisEqual = value; rescaleAxis();}
	void setShowAxis(bool value);
	void setShowAxisBox(bool value);
	void setShowGrid(bool value);
	void setXLabel(QString str) { mXAxis.setXLabel(str); mZAxis.setYLabel(str);}
	void setYLabel(QString str) { mYAxis.setXLabel(str); mXAxis.setYLabel(str);}
	void setZLabel(QString str) { mZAxis.setXLabel(str); mYAxis.setYLabel(str);}
	void setAdjustPlaneView(bool value) { mXAxis.setAdjustPlaneView(value);mYAxis.setAdjustPlaneView(value), mZAxis.setAdjustPlaneView(value);}
	void showContextMenu(const QPoint&);
	void toggleAxisEqual() {setAxisEqual(!mAxisEqual);}
	void replot() {updateGL();}

private:
	double roll()  const { return mRotation.x();  }
	double pitch() const { return mRotation.y();  }
	double yaw()   const { return mRotation.z();  }
	void   drawLegend();
	void   enable2D();
	void   disable2D();
	void   draw3DLine(QVector3D from, QVector3D to, double lineWidth, QColor color);

private slots:
	void setRoll(double value)   { mRotation.setX(value);  updateGL(); }
	void setPitch(double value)  { mRotation.setY(value);  updateGL(); }
	void setYaw(double value)    { mRotation.setZ(value);  updateGL(); }
	void rescaleAxis();
	void axisEqual();
	void axisTight();
	
protected:
	void initializeGL() override;
	void paintGL() override;
	void resizeGL(int width, int height) override;
	void mousePressEvent(QMouseEvent* event);
	void mouseMoveEvent(QMouseEvent* event);
	void mouseDoubleClickEvent(QMouseEvent* event);
	void wheelEvent(QWheelEvent* event);
	QRect textSize(QString) const;
	QVector3D toScreenCoordinates(const QVector3D& worldCoord) const ;
	QVector3D toScreenCoordinates(double worldX, double worldY, double worldZ) const ;
	void      renderTextAtWorldCoordinates(const QVector3D& vec, QString string, QFont font = QFont("Helvetica"));
	void      renderTextAtScreenCoordinates(int x, int y, QString string, QFont font = QFont("Helvetica"));
	QVector3D cameraPositionInWorldCoordinates() const;
	void   drawTextBox(int x, int y, QString string, QFont font = QFont("Helvetica"));

private:
	QList<QCurve3D*> mCurves;
	QPoint mLastMousePos;
	QColor mBackgroundColor;
	
	QVector3D mTranslate;
	QVector3D mRotation;
	QVector3D mScale;
	
	bool mShowAzimuthElevation, mShowLegend, mAxisEqual;
	QAxis mXAxis, mYAxis, mZAxis;
	QFont mLegendFont;
};
