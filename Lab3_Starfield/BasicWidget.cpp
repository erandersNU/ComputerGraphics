#include "BasicWidget.h"

BasicWidget::BasicWidget(QWidget* parent) : QWidget(parent), image_(QSize(800,600), QImage::Format_RGB888), stars_(2400, 1.0, 1.5)
{
  backgroundColor_ = QColor(0, 0, 0, 0);
  image_.fill(QColor(0, 0, 0));
}

BasicWidget::~BasicWidget()
{}

void BasicWidget::resizeEvent(QResizeEvent* event)
{
    QWidget::resizeEvent(event);
}

void BasicWidget::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);
    QPainter painter(this);

    image_.fill(QColor(0, 0, 0));
    stars_.updateAndRender(image_, 0.001, QSize(800,600));
    QPixmap pixmap = QPixmap::fromImage(image_.scaled(size(), Qt::IgnoreAspectRatio));
    painter.drawPixmap(0, 0, pixmap);
    update();
}