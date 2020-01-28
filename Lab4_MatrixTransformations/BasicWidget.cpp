#include "BasicWidget.h"

BasicWidget::BasicWidget(QWidget* parent) : QWidget(parent), buffer_(800, 600), minYVert_(-1, -1, 0), midYVert_(0, 1, 0), maxYVert_(1, -1, 0)
{
  prevTicks_ = QDateTime::currentMSecsSinceEpoch();
  yAxisRotation_ = 0.0f;
  projection_.InitPerspective(90.0f, 800./600., 0.1f, 1000.0f);
}

BasicWidget::~BasicWidget()
{}

void BasicWidget::resizeEvent(QResizeEvent* event)
{
  QWidget::resizeEvent(event);
  buffer_.setSize(size());
  projection_.InitPerspective(90.0f, width() / height(), 0.1, 1000.0);
}

void BasicWidget::paintEvent(QPaintEvent* event)
{
  Q_UNUSED(event);

  qint64 curTicks = QDateTime::currentMSecsSinceEpoch();
  float delta = (float)((curTicks - prevTicks_) / 1000.0);

  yAxisRotation_ += delta;

  // We have some transformations now.  Construct them
  translation_.InitTranslation(0.0, 0.0, 3.0);
  rotation_.InitRotation(0.0, yAxisRotation_, 0.0);

  // TODO:  Make sure our transform is correct! (Apply our transforms)
  transform_ = transform_;

  buffer_.clearImage();
  Vertex v0 = maxYVert_.Transform(transform_);
  Vertex v1 = midYVert_.Transform(transform_);
  Vertex v2 = minYVert_.Transform(transform_);
  buffer_.FillTriangle(v0, v1, v2);

  QPainter painter(this);
  QImage image = buffer_.image();
  QPixmap pixmap = QPixmap::fromImage(image);
  painter.drawPixmap(0, 0, pixmap);
  prevTicks_ = curTicks;
  update();
}
