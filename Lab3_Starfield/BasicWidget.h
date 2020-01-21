#pragma once

#include <QtGui>
#include <QtWidgets>
#include <QtOpenGL>

#include "StarList.h"

/**
 * This is just a basic OpenGL widget that will allow a change of background color.
 */
class BasicWidget : public QWidget
{
  Q_OBJECT

protected:
  QColor backgroundColor_;
  QImage image_;
  StarList stars_;

  // Paint our image.
  void paintEvent(QPaintEvent* event) Q_DECL_OVERRIDE;
  void resizeEvent(QResizeEvent* event) Q_DECL_OVERRIDE;

public:
  BasicWidget(QWidget* parent=nullptr);
  virtual ~BasicWidget();

  // Make sure we have some size that makes sense.
  QSize sizeHint() const {return QSize(800,600);}

};
