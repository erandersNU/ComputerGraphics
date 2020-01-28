#pragma once

#include <QtGui>
#include <QtWidgets>
#include <QtOpenGL>

#include "ScanBuffer.h"
#include "Matrix4f.h"
#include "Vertex.h"

/**
 * This is just a basic OpenGL widget that will allow a change of background color.
 */
class BasicWidget : public QWidget
{
  Q_OBJECT

protected:
  QColor backgroundColor_;
  ScanBuffer buffer_;
  qint64 prevTicks_;
  float yAxisRotation_;
  Matrix4f translation_;
  Matrix4f rotation_;
  Matrix4f transform_;
  Matrix4f projection_;
  Vertex minYVert_;
  Vertex midYVert_;
  Vertex maxYVert_;
  
  // Paint our image.
  void paintEvent(QPaintEvent* event) Q_DECL_OVERRIDE;
  void resizeEvent(QResizeEvent* event) Q_DECL_OVERRIDE;

public:
  BasicWidget(QWidget* parent=nullptr);
  virtual ~BasicWidget();

  // Make sure we have some size that makes sense.
  QSize sizeHint() const {return QSize(800,600);}

};
