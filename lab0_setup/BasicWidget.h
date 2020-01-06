#pragma once

#include <QtGui>
#include <QtWidgets>
#include <QtOpenGL>

/**
 * This is just a basic OpenGL widget that will allow a change of background color.
 */
class BasicWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
  Q_OBJECT

protected:
  virtual void initializeGL() override;
  virtual void resizeGL(int w, int h) override;
  virtual void paintGL() override;

  QColor backgroundColor_;

public:
  BasicWidget(QWidget* parent=nullptr);
  virtual ~BasicWidget();

  // Make sure we have some size that makes sense.
  QSize sizeHint() const {return QSize(800,600);}

  void setBackgroundColor(const QColor& color);
  
};
