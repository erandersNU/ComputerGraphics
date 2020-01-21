#pragma once

#include <QtCore/QVector>
#include <QtCore/QRandomGenerator>

#include <QtGui/QColor>
#include <QtGui/QImage>

struct Star
{
	float x, y, z;
	float speed;
	QColor color;
};

class StarList
{
public:
	StarList(unsigned int numStars, float spread, float maxSpeed);
	virtual ~StarList();

	// Update our stars and render them to our displayed image.
	void updateAndRender(QImage& image, float delta, const QSize& windowSize);
	void initStar(unsigned int idx);

private:
	QVector<Star> stars_;
	float spread_;
	float speed_;
	QRandomGenerator randomGen_;
};