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

private:
  QString vertexShaderString() const;
  QString fragmentShaderString() const;
  void createShader();
  QOpenGLVertexArrayObject vao_;

  QMatrix4x4 model_;
  QMatrix4x4 view_;
  QMatrix4x4 projection_;
  
protected:
  // Required interaction overrides
  void keyReleaseEvent(QKeyEvent* keyEvent) override;

  // Required overrides form QOpenGLWidget
  void initializeGL() override;
  void resizeGL(int w, int h) override;
  void paintGL() override;

  QOpenGLBuffer vbo_;
  QOpenGLBuffer ibo_;
  // TODO:  Remove the cbo_!
  QOpenGLBuffer cbo_;
  // END TODO
  QOpenGLShaderProgram shaderProgram_;
  QOpenGLDebugLogger logger_;
  
public:
  BasicWidget(QWidget* parent=nullptr);
  virtual ~BasicWidget();
  
  // Make sure we have some size that makes sense.
  QSize sizeHint() const {return QSize(800,600);}
};
