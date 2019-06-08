#include <QVector3D>
#include <QVector2D>

#include <QMenu>
#include <QAction>

#include <QQuaternion>
#include <QMouseEvent>

#include "QPlot3D.h"

namespace
{
	void Draw2DPlane(QVector2D topLeft, QVector2D bottomRight, QColor color)
	{
		glColor4f(color.redF(), color.greenF(), color.blueF(), color.alphaF());
		glBegin(GL_QUADS);
		glVertex2f(topLeft.x(), topLeft.y());
		glVertex2f(bottomRight.x(), topLeft.y());
		glVertex2f(bottomRight.x(), bottomRight.y());
		glVertex2f(topLeft.x(), bottomRight.y());
		glEnd();
	}

	void Draw2DLine(QVector2D from, QVector2D to, int lineWidth, QColor color)
	{
		glColor4f(color.redF(), color.greenF(), color.blueF(), color.alphaF());
		glLineWidth(lineWidth);
		glBegin(GL_LINES);
		glVertex2f(from.x(), from.y());
		glVertex2f(to.x(), to.y());
		glEnd();
	}
}


QPlot3D::QPlot3D(QWidget* parent) :
	QGLWidget(QGLFormat(QGL::SampleBuffers), parent),
	mBackgroundColor(Qt::white),
	mTranslate(0, 0, -20),
	mRotation(0, 0, 0),
	mShowAzimuthElevation(true),
	mShowLegend(true),
	mAxisEqual(false),
	mLegendFont("Helvetica", 12)
{
	setAzimuth(130);
	setElevation(30);

	mXAxis.setAxis(QAxis::X_AXIS);
	mXAxis.setPlot(this);
	setXLabel("X");

	mYAxis.setAxis(QAxis::Y_AXIS);
	mYAxis.setPlot(this);
	setYLabel("Y");

	mZAxis.setAxis(QAxis::Z_AXIS);
	mZAxis.setPlot(this);
	setZLabel("Z");

	setFont(QFont("Helvetica"));

	setContextMenuPolicy(Qt::CustomContextMenu);
	connect(this, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(showContextMenu(const QPoint&)));
}

QPlot3D::~QPlot3D() = default;

void QPlot3D::showContextMenu(const QPoint& pos)
{
	if (mCurves.isEmpty())
		return;

	QPoint globalPos = this->mapToGlobal(pos);

	QMenu tMenu;

	QAction* a1 = new QAction("Toggle Plane", this);
	connect(a1, SIGNAL(triggered()),&mXAxis, SLOT(togglePlane()));
	connect(a1, SIGNAL(triggered()),&mYAxis, SLOT(togglePlane()));
	connect(a1, SIGNAL(triggered()),&mZAxis, SLOT(togglePlane()));
	tMenu.addAction(a1);

	QAction* a2 = new QAction("Toggle Grid", this);
	connect(a2, SIGNAL(triggered()),&mXAxis, SLOT(toggleGrid()));
	connect(a2, SIGNAL(triggered()),&mYAxis, SLOT(toggleGrid()));
	connect(a2, SIGNAL(triggered()),&mZAxis, SLOT(toggleGrid()));
	tMenu.addAction(a2);

	QAction* a3 = new QAction("Toggle Axis", this);
	connect(a3, SIGNAL(triggered()),&mXAxis, SLOT(toggleAxis()));
	connect(a3, SIGNAL(triggered()),&mYAxis, SLOT(toggleAxis()));
	connect(a3, SIGNAL(triggered()),&mZAxis, SLOT(toggleAxis()));
	tMenu.addAction(a3);

	QAction* a4 = new QAction("Toggle Label", this);
	connect(a4, SIGNAL(triggered()),&mXAxis, SLOT(toggleLabel()));
	connect(a4, SIGNAL(triggered()),&mYAxis, SLOT(toggleLabel()));
	connect(a4, SIGNAL(triggered()),&mZAxis, SLOT(toggleLabel()));
	tMenu.addAction(a4);

	QAction* a5 = new QAction("Toggle Axis Box", this);
	connect(a5, SIGNAL(triggered()),&mXAxis, SLOT(toggleAxisBox()));
	connect(a5, SIGNAL(triggered()),&mYAxis, SLOT(toggleAxisBox()));
	connect(a5, SIGNAL(triggered()),&mZAxis, SLOT(toggleAxisBox()));
	tMenu.addAction(a5);

	QAction* a6 = new QAction("Toggle Adjust Plane View", this);
	connect(a6, SIGNAL(triggered()),&mXAxis, SLOT(toggleAdjustView()));
	connect(a6, SIGNAL(triggered()),&mYAxis, SLOT(toggleAdjustView()));
	connect(a6, SIGNAL(triggered()),&mZAxis, SLOT(toggleAdjustView()));
	tMenu.addAction(a6);

	QAction* a7 = new QAction("Toggle Axis Equal", this);
	connect(a7, SIGNAL(triggered()), this, SLOT(toggleAxisEqual()));
	tMenu.addAction(a7);

	tMenu.exec(globalPos);
	update();
}

void QPlot3D::initializeGL()
{
	qglClearColor(mBackgroundColor);

	glShadeModel(GL_SMOOTH);

	glEnable(GL_MULTISAMPLE);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

}

void QPlot3D::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glTranslatef(mTranslate.x(), mTranslate.y(), mTranslate.z());

	glRotatef(mRotation.x() - 90, 1.0, 0.0, 0.0);
	glRotatef(mRotation.y(), 0.0, 1.0, 0.0);
	glRotatef(mRotation.z(), 0.0, 0.0, 1.0);

	glScalef(mScale.x(), mScale.y(), mScale.z());

	QVector3D tCenter = mXAxis.range().center();
	glTranslatef(-tCenter.x(), -tCenter.y(), -tCenter.z());

	// DRAW AXIS
	mXAxis.draw();
	mYAxis.draw();
	mZAxis.draw();

	// DRAW CURVES
	const int nCurves = mCurves.size();
	for (int i = 0; i < nCurves; i++)
	{
		mCurves[i]->draw();
	}

	// DRAW AXIS BOX
	mXAxis.drawAxisBox();
	mYAxis.drawAxisBox();
	mZAxis.drawAxisBox();

	// DRAW LEGEND
	if (mShowLegend)
	{
		drawLegend();
	}

	// DRAW ELEVATION AZIMUTH TEXT BOX
	if (mShowAzimuthElevation)
	{
		drawTextBox(10, height() - 15, QString("Az: %1 El: %2").arg(azimuth(), 3, 'f', 1).arg(elevation(), 3, 'f', 1));
	}


}

void QPlot3D::drawLegend()
{
	if (mCurves.isEmpty())
		return;

	double textWidth = 0;
	double textHeight = 0;
	int nrCurves = mCurves.size();
	for (int i = 0; i < nrCurves; i++)
	{
		QString string = mCurves[i]->name();
		if (fontMetrics().width(string) > textWidth) textWidth = fontMetrics().width(string);
		if (fontMetrics().height() > textHeight) textHeight = fontMetrics().height();
	}


	double tWidth = 5 + 20 + 5 + textWidth + 5;
	double tHeight = 5 + nrCurves * textHeight + 5;
	double x0 = width() - tWidth - 5;
	double y0 = 5;

	enable2D();
	glEnable(GL_BLEND);
	// Draw box
	Draw2DPlane(QVector2D(x0, y0), QVector2D(x0 + tWidth, y0 + tHeight), QColor(204, 204, 217, 128));
	// Draw contour lines
	Draw2DLine(QVector2D(x0, y0), QVector2D(x0 + tWidth, y0), 1, QColor(0, 0, 0, 255));
	Draw2DLine(QVector2D(x0 + tWidth, y0), QVector2D(x0 + tWidth, y0 + tHeight), 1, QColor(0, 0, 0, 255));
	Draw2DLine(QVector2D(x0 + tWidth, y0 + tHeight), QVector2D(x0, y0 + tHeight), 1, QColor(0, 0, 0, 255));
	Draw2DLine(QVector2D(x0, y0 + tHeight), QVector2D(x0, y0), 1, QColor(0, 0, 0, 255));
	glDisable(GL_BLEND);
	disable2D();

	y0 = 10;

	for (int i = 0; i < nrCurves; i++)
	{

		x0 = width() - tWidth - 5;

		enable2D();
		Draw2DLine(QVector2D(x0 + 5, y0 + 0.5 * textHeight),
			QVector2D(x0 + 5 + 20, y0 + 0.5 * textHeight),
			mCurves[i]->lineWidth(),
			mCurves[i]->color());
		disable2D();

		x0 += 30;
		glColor4f(0, 0, 0, 1);
		y0 += textHeight;
		renderTextAtScreenCoordinates((int)x0, (int)y0, mCurves[i]->name(), mLegendFont);
	}


}

void QPlot3D::drawTextBox(int x, int y, QString string, QFont font)
{
	const double textWidth = fontMetrics().width(string);
	const double textHeight = fontMetrics().height();

	glEnable(GL_BLEND);
	enable2D();
	Draw2DPlane(QVector2D(x - 5, y + 5), QVector2D(x + 10 + textWidth, y - textHeight - 5), QColor(204, 204, 217, 128));
	disable2D();
	glDisable(GL_BLEND);

	glColor4f(0, 0, 0, 1);
	renderTextAtScreenCoordinates(x, y, string, font);
}


void QPlot3D::enable2D()
{
	glPushMatrix();

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, width(), height(), 0, 0.01, -10000.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

}

void QPlot3D::disable2D()
{
	glPopMatrix();
	resizeGL(width(), height());
}

void QPlot3D::resizeGL(int width, int height)
{
	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	double zNear = 0.01;
	double zFar = 10000.0;
	double aspect = (double)width / (double)height;
	double fW = tan(25 * 3.141592 / 180.0) * zNear;
	double fH = fW / aspect;
	glFrustum(-fW, fW, -fH, fH, zNear, zFar);

	glMatrixMode(GL_MODELVIEW);
}

void QPlot3D::mousePressEvent(QMouseEvent * event)
{
	mLastMousePos = event->pos();
}

void QPlot3D::mouseMoveEvent(QMouseEvent* event)
{
	int dx = event->x() - mLastMousePos.x();
	int dy = event->y() - mLastMousePos.y();

	if (event->buttons()& Qt::LeftButton)
	{

		if (event->modifiers() == Qt::ControlModifier)
		{
			setPitch(pitch() + dx);
		}
		else
		{
			if ((roll() + dy < 90)&& (roll() + dy > -90))
				setRoll(roll() + dy);
			setYaw(yaw() + dx);
		}
	}
	else
	{
		setPan(pan() + QVector3D(dx / 32.0, -dy / 32.0, 0.0));
	}

	mLastMousePos = event->pos();

	mXAxis.adjustPlaneView();
	mYAxis.adjustPlaneView();
	mZAxis.adjustPlaneView();
}

void QPlot3D::mouseDoubleClickEvent(QMouseEvent * event)
{
	event->accept();
	mAxisEqual = !mAxisEqual;
	rescaleAxis();
}

void QPlot3D::wheelEvent(QWheelEvent * event)
{
	event->accept();
	setZoom(zoom() + (double)event->delta() / 32);

	mXAxis.adjustPlaneView();
	mYAxis.adjustPlaneView();
	mZAxis.adjustPlaneView();
}

void QPlot3D::addCurve(QCurve3D * curve)
{
	mCurves.push_back(curve);
	rescaleAxis();
	updateGL();
}

void QPlot3D::setBackgroundColor(QColor color)
{
	mBackgroundColor = color;
	makeCurrent();
	qglClearColor(mBackgroundColor);
}

void QPlot3D::rescaleAxis()
{
	if (mCurves.isEmpty())
		return;

	QRange tRange = mXAxis.range();
	int tSize = mCurves.size();
	for (int i = 0; i < tSize; i++)
	{
		tRange.setIfMin(mCurves[i]->range());
		tRange.setIfMax(mCurves[i]->range());
	}
	mXAxis.setRange(tRange);
	mYAxis.setRange(tRange);
	mZAxis.setRange(tRange);

	if (mAxisEqual)
		axisEqual();
	else
		axisTight();

	mXAxis.adjustPlaneView();
	mYAxis.adjustPlaneView();
	mZAxis.adjustPlaneView();
}

void QPlot3D::axisEqual()
{
	QVector3D delta = mXAxis.range().delta();
	double k = std::max(delta.x(), std::max(delta.y(), delta.z()));
	mScale.setX(10.0 / k);
	mScale.setY(10.0 / k);
	mScale.setZ(10.0 / k);
	updateGL();
}

void QPlot3D::axisTight()
{
	QVector3D delta = mXAxis.range().delta();
	mScale.setX(10.0 / delta.x());
	mScale.setY(10.0 / delta.y());
	mScale.setZ(10.0 / delta.z());
	updateGL();
}

QVector3D QPlot3D::cameraPositionInWorldCoordinates() const
{

	QVector3D tObjectCenter = mXAxis.range().center();

	QQuaternion q1 = QQuaternion::fromAxisAndAngle(1.0, 0.0, 0.0, (mRotation.x() - 90));
	QQuaternion q2 = QQuaternion::fromAxisAndAngle(0.0, 1.0, 0.0, mRotation.y());
	QQuaternion q3 = QQuaternion::fromAxisAndAngle(0.0, 0.0, 1.0, mRotation.z());
	QQuaternion q = (q1 * q2 * q3).conjugate();

	return tObjectCenter + q.rotatedVector(-QVector3D(mTranslate.x() / mScale.x(), mTranslate.y() / mScale.y(), mTranslate.z() / mScale.z()));
}

void QPlot3D::renderTextAtWorldCoordinates(const QVector3D& vec, QString str, QFont font)
{
	QVector3D sVec = toScreenCoordinates(vec);
	renderTextAtScreenCoordinates(sVec.x(), sVec.y(), str, font);
}

void QPlot3D::renderTextAtScreenCoordinates(int x, int y, QString str, QFont font)
{
	setFont(font);
	renderText(x, y, str);
}

QVector3D QPlot3D::toScreenCoordinates(double worldX, double worldY, double worldZ) const
{
	return toScreenCoordinates(QVector3D(worldX, worldY, worldZ));
}

QVector3D QPlot3D::toScreenCoordinates(const QVector3D& vec) const
{
	// v' = P*M*v
	GLdouble m[16];
	GLdouble p[16];

	glGetDoublev(GL_MODELVIEW_MATRIX,&m[0]);
	glGetDoublev(GL_PROJECTION_MATRIX,&p[0]);

	GLint viewPort[4];
	viewPort[0] = 0;
	viewPort[1] = 0;
	viewPort[2] = width();
	viewPort[3] = height();

	// M*v
	const double f1 = m[0] * vec.x() + m[4] * vec.y() + m[8] * vec.z() + m[12];
	const double f2 = m[1] * vec.x() + m[5] * vec.y() + m[9] * vec.z() + m[13];
	const double f3 = m[2] * vec.x() + m[6] * vec.y() + m[10] * vec.z() + m[14];
	const double f4 = m[3] * vec.x() + m[7] * vec.y() + m[11] * vec.z() + m[15];

	// P*M*v
	double g1 = p[0] * f1 + p[4] * f2 + p[8] * f3 + p[12] * f4;
	double g2 = p[1] * f1 + p[5] * f2 + p[9] * f3 + p[13] * f4;
	double g3 = p[2] * f1 + p[6] * f2 + p[10] * f3 + p[14] * f4;
	double g4 = -f3;

	if (g4 == 0.0) return QVector3D(0.0, 0.0, 0.0);
	g1 /= g4;
	g2 /= g4;
	g3 /= g4;

	return QVector3D((g1 * 0.5 + 0.5) * viewPort[2] + viewPort[0],
		height() - ((g2 * 0.5 + 0.5) * viewPort[3] + viewPort[1]),
		(1.0 + g3) * 0.5);
}

void QPlot3D::setShowAxis(bool value)
{
	mXAxis.setShowAxis(value);
	mXAxis.setShowLabel(value);

	mYAxis.setShowAxis(value);
	mYAxis.setShowLabel(value);

	mZAxis.setShowAxis(value);
	mZAxis.setShowLabel(value);
}

void QPlot3D::setShowAxisBox(bool value)
{
	mXAxis.setShowAxisBox(value);
	mYAxis.setShowAxisBox(value);
	mZAxis.setShowAxisBox(value);
}

void QPlot3D::setShowGrid(bool value)
{
	mXAxis.setShowPlane(value);
	mXAxis.setShowGrid(value);

	mYAxis.setShowPlane(value);
	mYAxis.setShowGrid(value);

	mZAxis.setShowPlane(value);
	mZAxis.setShowGrid(value);
}

void QPlot3D::draw3DLine(QVector3D from, QVector3D to, double lineWidth, QColor color)
{
	const QVector3D tFrom = toScreenCoordinates(from);
	const QVector3D tTo = toScreenCoordinates(to);

	const QVector3D v = tTo - tFrom;
	const QVector3D n1 = QVector3D::crossProduct(tTo, tFrom);
	const QVector3D n = QVector3D::crossProduct(v, n1).normalized();

	enable2D();
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	const QVector3D d = 0.5 * lineWidth * n;
	const QVector3D v1 = tFrom - d;
	const QVector3D v2 = tTo - d;
	const QVector3D v3 = tFrom;
	const QVector3D v4 = tTo;
	const QVector3D v5 = tFrom + d;
	const QVector3D v6 = tTo + d;

	float vertexVec[] =
	{
		v1.x(),v1.y(),v1.z(),
		v2.x(),v2.y(),v2.z(),
		v3.x(),v3.y(),v3.z(),
		v4.x(),v4.y(),v4.z(),
		v5.x(),v5.y(),v5.z(),
		v6.x(),v6.y(),v6.z()
	};

	float colorVec[] =
	{
		color.redF(), color.greenF(), color.blueF(), 0.0,
		color.redF(), color.greenF(), color.blueF(), 0.0,
		color.redF(), color.greenF(), color.blueF(), 1.0,
		color.redF(), color.greenF(), color.blueF(), 1.0,
		color.redF(), color.greenF(), color.blueF(), 0.0,
		color.redF(), color.greenF(), color.blueF(), 0.0,
	};

	glVertexPointer(3, GL_FLOAT, 0, vertexVec);
	glColorPointer(4, GL_FLOAT, 0, colorVec);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 6);
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);

	glDisable(GL_BLEND);
	disable2D();
}

QRect QPlot3D::textSize(QString string) const
{
	return QRect(0.0, 0.0, fontMetrics().width(string), fontMetrics().height());
}

bool QPlot3D::removeCurve(QCurve3D * curve)
{
	return mCurves.removeOne(curve);
}
