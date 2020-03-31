#include "BasicWidget.h"

#include "TerrainQuad.h"
#include "UnitQuad.h"

//////////////////////////////////////////////////////////////////////
// Publics
BasicWidget::BasicWidget(QWidget* parent) : QOpenGLWidget(parent), logger_(this), isFilled_(true)
{
  setFocusPolicy(Qt::StrongFocus);
  camera_.setPosition(QVector3D(0.5, 0.5, -0.5));
  camera_.setLookAt(QVector3D(0.5, 0.5, 0.0));
  world_.setToIdentity();
}

BasicWidget::~BasicWidget()
{
    for (auto renderable : renderables_) {
        delete renderable;
    }
    renderables_.clear();
}

//////////////////////////////////////////////////////////////////////
// Privates
///////////////////////////////////////////////////////////////////////
// Protected
void BasicWidget::keyReleaseEvent(QKeyEvent* keyEvent)
{
  // Handle key events here.
  if (keyEvent->key() == Qt::Key_Left) {
    qDebug() << "Left Arrow Pressed";
    update();  // We call update after we handle a key press to trigger a redraw when we are ready
  } else if (keyEvent->key() == Qt::Key_Right) {
    qDebug() << "Right Arrow Pressed";
    update();  // We call update after we handle a key press to trigger a redraw when we are ready
  } else if (keyEvent->key() == Qt::Key_R) {
    camera_.setPosition(QVector3D(0.5, 0.5, -2.0));
    camera_.setLookAt(QVector3D(0.5, 0.5, 0.0));
    update();
  } else {
    qDebug() << "You Pressed an unsupported Key!";
  }
}

void BasicWidget::mousePressEvent(QMouseEvent* mouseEvent)
{
  if (mouseEvent->button() == Qt::LeftButton) {
    mouseAction_ = Rotate;
  } else if (mouseEvent->button() == Qt::RightButton) {
    mouseAction_ = Zoom;
  }
  lastMouseLoc_ = mouseEvent->pos();
}

void BasicWidget::mouseMoveEvent(QMouseEvent* mouseEvent)
{
  if (mouseAction_ == NoAction) {
    return;
  }
  QPoint delta = mouseEvent->pos() - lastMouseLoc_;
  lastMouseLoc_ = mouseEvent->pos();
  if (mouseAction_ == Rotate) {
    // TODO:  Implement rotating the camera
  } else if (mouseAction_ == Zoom) {
    // TODO:  Implement zoom by moving the camera
    // Zooming is moving along the gaze direction by some amount.
  } 
  update();
}

void BasicWidget::mouseReleaseEvent(QMouseEvent* mouseEvent)
{
    mouseAction_ = NoAction;
}

void BasicWidget::initializeGL()
{
  makeCurrent();
  initializeOpenGLFunctions();

  qDebug() << QDir::currentPath();
  // TODO:  You may have to change these paths.
  QString terrainTex = "../../colormap.ppm";

  TerrainQuad* terrain = new TerrainQuad();
  terrain->init(terrainTex);
  QMatrix4x4 floorXform;
  floorXform.setToIdentity();
  floorXform.translate(-0.5, 0.0, 0.5);
  floorXform.scale(2.0, 2.0, 2.0);
  terrain->setModelMatrix(floorXform);
  renderables_.push_back(terrain);

  glViewport(0, 0, width(), height());
  frameTimer_.start();
}

void BasicWidget::resizeGL(int w, int h)
{
    if (!logger_.isLogging()) {
        logger_.initialize();
        // Setup the logger for real-time messaging
        connect(&logger_, &QOpenGLDebugLogger::messageLogged, [=]() {
            const QList<QOpenGLDebugMessage> messages = logger_.loggedMessages();
            for (auto msg : messages) {
                qDebug() << msg;
            }
            });
        logger_.startLogging();
    }
  glViewport(0, 0, w, h);

  camera_.setPerspective(70.f, (float)w / (float)h, 0.001, 1000.0);
  glViewport(0, 0, w, h);
}

void BasicWidget::paintGL()
{
  qint64 msSinceRestart = frameTimer_.restart();
  glDisable(GL_DEPTH_TEST);
  glDisable(GL_CULL_FACE);

  glClearColor(0.f, 0.f, 0.f, 1.f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glEnable(GL_DEPTH_TEST);

  for (auto renderable : renderables_) {
      renderable->update(msSinceRestart);
      // TODO:  Understand that the camera is now governing the view and projection matrices
      renderable->draw(world_, camera_.getViewMatrix(), camera_.getProjectionMatrix());
  }
  update();
}
