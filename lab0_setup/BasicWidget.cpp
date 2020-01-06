#include "BasicWidget.h"

BasicWidget::BasicWidget(QWidget* parent) : QOpenGLWidget(parent)
{
  backgroundColor_ = QColor(0, 0, 0, 0);
  setFocusPolicy(Qt::StrongFocus);
}

BasicWidget::~BasicWidget()
{}

void BasicWidget::setBackgroundColor(const QColor& color)
{
  backgroundColor_ = color;
}

void BasicWidget::initializeGL()
{
  makeCurrent();
  initializeOpenGLFunctions();
  QOpenGLContext* curContext = this->context();
  qDebug() << "[BasicWidget]::initializeGL() -- Context Information:";
  qDebug() << "  Context Valid: " << std::string(curContext->isValid() ? "true" : "false").c_str();
  qDebug() << "  GL Version Used: " << curContext->format().majorVersion() << "." << curContext->format().minorVersion();
  qDebug() << "  Vendor: " << reinterpret_cast<const char*>(glGetString(GL_VENDOR));
  qDebug() << "  Renderer: " << reinterpret_cast<const char*>(glGetString(GL_RENDERER));
  qDebug() << "  Version: " << reinterpret_cast<const char*>(glGetString(GL_VERSION));
  qDebug() << "  GLSL Version: " << reinterpret_cast<const char*>(glGetString(GL_SHADING_LANGUAGE_VERSION));

  // Our default background color is white
  glClearColor(backgroundColor_.redF(), backgroundColor_.greenF(), backgroundColor_.blueF(), backgroundColor_.alphaF());
  // Set a generic viewport.
  glViewport(0, 0, width(), height());
}

void BasicWidget::resizeGL(int w, int h)
{
  // Reset our viewport
  glViewport(0,0,w, h);
  update();
}

void BasicWidget::paintGL()
{
  // Clear our contents.
  glClearColor(backgroundColor_.redF(), backgroundColor_.greenF(), backgroundColor_.blueF(), backgroundColor_.alphaF());
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
