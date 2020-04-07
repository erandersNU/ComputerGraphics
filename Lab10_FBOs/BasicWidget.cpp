#include "BasicWidget.h"

#include "TerrainQuad.h"
#include "UnitQuad.h"

//////////////////////////////////////////////////////////////////////
// Publics
BasicWidget::BasicWidget(QWidget* parent) : QOpenGLWidget(parent), logger_(this), isFilled_(true), vbo_(QOpenGLBuffer::VertexBuffer), ibo_(QOpenGLBuffer::IndexBuffer)
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
	// Make sure to clean up.
    vbo_.release();
    vbo_.destroy();
    ibo_.release();
    ibo_.destroy();
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

// This is just a Unit Quad that will not ever get lit or have anything to do with normals!
void BasicWidget::setupViewQuad()
{
    // Create a screen-aligned quad vbo.  
    // The unit quad goes from 0.0 to 1.0 in each dimension.
    // But we only need pos and texture coords
    QVector<QVector3D> pos;
    QVector<QVector2D> texCoord;
    QVector<unsigned int> idx;
    // unit positions.
    pos << QVector3D(0.0, 0.0, 0.0);
    pos << QVector3D(1.0, 0.0, 0.0);
    pos << QVector3D(0.0, 1.0, 0.0);
    pos << QVector3D(1.0, 1.0, 0.0);
    // Add in the texcoords
    texCoord << QVector2D(0.0, 0.0);
    texCoord << QVector2D(1.0, 0.0);
    texCoord << QVector2D(0.0, 1.0);
    texCoord << QVector2D(1.0, 1.0);
    idx << 0 << 1 << 2 << 3;
    int vSize = 3 + 2;  // pos + texcoord sizes
    float* data = new float[4 * vSize];
    for (int i = 0; i < 4; ++i) {
        data[i * vSize + 0] = pos.at(i).x();
        data[i * vSize + 1] = pos.at(i).y();
        data[i * vSize + 2] = pos.at(i).z();
        data[i * vSize + 3] = texCoord.at(i).x();
        data[i * vSize + 4] = texCoord.at(i).y();
    }
    vbo_.create();
    vbo_.bind();
    vbo_.setUsagePattern(QOpenGLBuffer::DynamicDraw);
    vbo_.allocate(data, 4 * vSize * sizeof(float));
    vbo_.release();
    delete[] data;

    // Create our ibo
    unsigned int* idAr = new unsigned int[4];
    for (int i = 0; i < 4; ++i) {
        idAr[i] = idx.at(i);
    }
    ibo_.create();
    ibo_.bind();
    ibo_.setUsagePattern(QOpenGLBuffer::StaticDraw);
    ibo_.allocate(idAr, 4 * sizeof(unsigned int));
    ibo_.release();
    delete[] idAr;

}

// We need to set up different shaders for our post-processing step. 
void BasicWidget::setupShaders()
{
    // TODO:  You may need to change these paths based on how/where you choose to build
    QString vertexFilename = "../../FBOVert.glsl";
    bool ok = shader_.addShaderFromSourceFile(QOpenGLShader::Vertex, vertexFilename);
    if (!ok) {
        qDebug() << shader_.log();
    }
    QString fragmentFilename = "../../FBOFrag.glsl";
    ok = shader_.addShaderFromSourceFile(QOpenGLShader::Fragment, fragmentFilename);
    if (!ok) {
        qDebug() << shader_.log();
    }
    ok = shader_.link();
    if (!ok) {
        qDebug() << shader_.log();
    }
    shader_.release();

    // Create our VAO now
    vao_.create();
    vao_.bind();
    vbo_.bind();
    ibo_.bind();
    shader_.bind();
    // Make sure we setup our shader inputs properly
    int vertexSize = 3 + 2; // positions + texCoords
    shader_.enableAttributeArray(0);
    shader_.setAttributeBuffer(0, GL_FLOAT, 0, 3, vertexSize * sizeof(float));
    shader_.enableAttributeArray(1);
    shader_.setAttributeBuffer(1, GL_FLOAT, 3 * sizeof(float), 2, vertexSize * sizeof(float));
    vao_.release();
    vbo_.release();
    ibo_.release();
    shader_.release();
}

void BasicWidget::initializeGL()
{
  makeCurrent();
  initializeOpenGLFunctions();

  // Create our quad
  setupViewQuad();

  // Create our shaders and our vao.
  setupShaders();

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
  camera_.setPerspective(70.f, (float)w / (float)h, 0.001, 1000.0);
  glViewport(0, 0, w, h);
}

void BasicWidget::paintGL()
{
  qint64 msSinceRestart = frameTimer_.restart();

  // Create an FBO the same size as our window.
  // TODO:  This is wasteful -- do we really NEED to create a new FBO every frame?!
  QOpenGLFramebufferObject fbo(size(), QOpenGLFramebufferObject::CombinedDepthStencil);

  // Bind our FBO.
  // This make our current render target the framebuffer that we have bound.  We will not
  // be seeing any imagery from now on!
  fbo.bind();

  glDisable(GL_DEPTH_TEST);
  glDisable(GL_CULL_FACE);

  glClearColor(0.f, 0.f, 0.f, 1.f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glEnable(GL_DEPTH_TEST);


  // When we draw, we are now rendering into our FBO
  for (auto renderable : renderables_) {
      renderable->update(msSinceRestart);
      // TODO:  Understand that the camera is now governing the view and projection matrices
      renderable->draw(world_, camera_.getViewMatrix(), camera_.getProjectionMatrix());
  }

  // Release our FBO.
  fbo.release();

  // Reset our context so we can draw the offscreen rendered scene
  // From now on, we are drawing to the "normal" framebuffer.  We will see in our window
  // whatever gets drawn here.
  makeCurrent();

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // At this point, our FBO has our rendered scene in it.
  // We now want to do the second render pass to paste it onto a quad as if it were a
  // normal texture.
  // TODO -- Note, Qt doesn't expose the textures an QOpenGLFrameBufferObject stores directly
  // instead, it provides a method to get the textureID that it used to render to.
  // We now want to bind it and use it to render our screen-sized quad
  GLuint fboTextureId = fbo.texture();
  shader_.bind();
  // Our scene is very simple... we just set all of our matrices to identity
  QMatrix4x4 id;
  id.setToIdentity();
  // Except our projection.  Our projection we set up to be the same size (and coordinates) as
  // the quad we built
  QMatrix4x4 proj;
  proj.ortho(0.0, 1.0, 0.0, 1.0, 0.0, 1.0);
  shader_.setUniformValue("modelMatrix", id);
  shader_.setUniformValue("viewMatrix", id);
  shader_.setUniformValue("projectionMatrix", proj);

  // Now we simply render our quad using the fbo texture.
  vao_.bind();
  glBindTexture(GL_TEXTURE_2D, fboTextureId);
  glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_INT, 0);
  glBindTexture(GL_TEXTURE_2D, 0);
  vao_.release();
  shader_.release();

  // We can also save out the contents of our framebuffer object without ever actually rendering
  // it to the screen!  Qt provides some VERY easy ways of doing this.  Please note that this is
  // a pretty expensive process, though.  Memory transfers from GPU->CPU are extremely expensive.
  //QImage fboImage = fbo.toImage();
  //fboImage.save("fbo.png");
  update();
}
