#include "BasicWidget.h"

//////////////////////////////////////////////////////////////////////
// Publics
#if USE_QT_OPENGL
  BasicWidget::BasicWidget(QWidget* parent) : QOpenGLWidget(parent), vbo_(QOpenGLBuffer::VertexBuffer), cbo_(QOpenGLBuffer::VertexBuffer), ibo_(QOpenGLBuffer::IndexBuffer)
#else
  BasicWidget::BasicWidget(QWidget* parent) : QOpenGLWidget(parent)
#endif
{
  setFocusPolicy(Qt::StrongFocus);
}

BasicWidget::~BasicWidget()
{
#if USE_QT_OPENGL
  vbo_.release();
  vbo_.destroy();
  ibo_.release();
  ibo_.destroy();
  cbo_.release();
  cbo_.destroy();
  vao_.release();
  vao_.destroy();
#else
  glDeleteProgram(shaderID_);
  glDeleteBuffers(1, &vboID_);
  glDeleteBuffers(1, &cboID_);
  glDeleteBuffers(1, &iboID_);
#endif
}

//////////////////////////////////////////////////////////////////////
// Privates
QString BasicWidget::vertexShaderString() const
{
  QString str =
	"#version 330\n"
	"layout(location = 0) in vec3 position;\n"
    "layout(location = 1) in vec4 color;\n"
    "out vec4 vertColor;\n"
	"void main()\n"
	"{\n"
	"  gl_Position = vec4(position, 1.0);\n"
    "  vertColor = color;\n"
    "}\n";
  return str;
}

QString BasicWidget::fragmentShaderString() const
{
  QString str =
	"#version 330\n"
    "in vec4 vertColor;\n"
	"out vec4 color;\n"
	"void main()\n"
	"{\n"
	"  color = vertColor;\n"
	"}\n";
  return str;
}

#if USE_QT_OPENGL
void BasicWidget::createShader()
{
  QOpenGLShader vert(QOpenGLShader::Vertex);
  vert.compileSourceCode(vertexShaderString());
  QOpenGLShader frag(QOpenGLShader::Fragment);
  frag.compileSourceCode(fragmentShaderString());
  bool ok = shaderProgram_.addShader(&vert);
  if(!ok) {
	qDebug() << shaderProgram_.log();
  }
  ok = shaderProgram_.addShader(&frag);
  if(!ok) {
	qDebug() << shaderProgram_.log();
  }
  ok = shaderProgram_.link();
  if(!ok) {
	qDebug() << shaderProgram_.log();
  }
}
#else
void BasicWidget::createShader()
{
  unsigned int prog = glCreateProgram();
  unsigned int vert = compileShader(GL_VERTEX_SHADER, vertexShaderString());
  unsigned int frag = compileShader(GL_FRAGMENT_SHADER, fragmentShaderString());
  glAttachShader(prog, vert);
  glAttachShader(prog, frag);
  glLinkProgram(prog);
  glValidateProgram(prog);

  // The shaders are build and ready to use.  We can now detach the individual shaders and destroy them
  glDetachShader(prog, vert);
  glDetachShader(prog, frag);
  glDeleteShader(vert);
  glDeleteShader(frag);

  // Assign here in case there are failures we need to bail on - This has not yet been implemented, though.
  shaderID_ = prog;
}

unsigned int BasicWidget::compileShader(unsigned int type, const QString& shaderSrc)
{
  unsigned int id = glCreateShader(type);
  // Make sure we can create the shader
  if(id == 0) {
	return 0;
  }
  QByteArray ba = shaderSrc.toLocal8Bit();
  const char* src = ba.data();
  // Set the source
  glShaderSource(id, 1, &src, nullptr);
  // Compile
  glCompileShader(id);
  // Retrieve the result of our compilation
  int result;
  glGetShaderiv(id, GL_COMPILE_STATUS, &result);
  if(result == GL_FALSE){
	int length;
	glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
	char* errorMessages = new char[length]; // Could also use alloca here.
	glGetShaderInfoLog(id, length, &length, errorMessages);
	if(type == GL_VERTEX_SHADER){
	  qDebug() << "ERROR: GL_VERTEX_SHADER compilation failed!\n" << errorMessages << "\n";
	}else if(type == GL_FRAGMENT_SHADER){
	  qDebug() << "ERROR: GL_FRAGMENT_SHADER compilation failed!\n" << errorMessages << "\n";
	}
	// Reclaim our memory
	delete[] errorMessages;
	// Delete our broken shader
	glDeleteShader(id);
	return 0;
  }

  return id;
}
#endif
///////////////////////////////////////////////////////////////////////
// Protected
void BasicWidget::keyReleaseEvent(QKeyEvent* keyEvent)
{
  // TODO
  // Handle key events here.
  if (keyEvent->key() == Qt::Key_Left) {
    qDebug() << "Left Arrow Pressed";
    update();  // We call update after we handle a key press to trigger a redraw when we are ready
  } else if (keyEvent->key() == Qt::Key_Right) {
    qDebug() << "Right Arrow Pressed";
    update();  // We call update after we handle a key press to trigger a redraw when we are ready
  } else {
    qDebug() << "You Pressed an unsupported Key!";
  }
  // ENDTODO
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

  // Set up our shaders.
  createShader();

  // TODO:  Add vertex and index data to draw two triangles
  // Define our verts
  static const GLfloat verts[12] =
  {
	-0.8f, -0.8f, 0.0f, // Left vertex position
	0.8f, -0.8f, 0.0f,  // right vertex position
	-0.8f,  0.8f, 0.0f,  // Top vertex position
    0.8f, 0.8f, 0.0f
  };
  // Define our vert colors
  static const GLfloat colors[16] =
  {
      1.0f, 0.0f, 0.0f, 1.0f, // red
      0.0f, 1.0f, 0.0f, 1.0f, // green
      0.0f, 0.0f, 1.0f, 1.0f, // blue
      1.0f, 1.0f, 0.0f, 1.0f  // yellow
  };
  // Define our indices
  static const GLuint idx[6] =
  {
      0, 1, 2, 2, 1, 3
  };
  // ENDTODO
  // Set up our buffers and our vao
#if USE_QT_OPENGL
  // Temporary bind of our shader.
  shaderProgram_.bind();
  // Create and prepare a vbo
  vbo_.setUsagePattern(QOpenGLBuffer::StaticDraw);
  vbo_.create();
  // Bind our vbo inside our vao
  vbo_.bind();
  vbo_.allocate(verts, 12 * sizeof(GL_FLOAT));

  // TODO:  Generate our color buffer
  // ENDTODO
  // TODO:  Generate our index buffer
  // ENDTODO

  // Create a VAO to keep track of things for us.
  vao_.create();
  vao_.bind();
  vbo_.bind();
  shaderProgram_.enableAttributeArray(0);
  shaderProgram_.setAttributeBuffer(0, GL_FLOAT, 0, 3);
  cbo_.bind();
  shaderProgram_.enableAttributeArray(1);
  shaderProgram_.setAttributeBuffer(1, GL_FLOAT, 0, 4);
  ibo_.bind();
  // Releae the vao THEN the vbo
  vao_.release();
  shaderProgram_.release();
#else
  vao_.create();
  vao_.bind();

  glGenBuffers(1, &vboID_);
  glBindBuffer(GL_ARRAY_BUFFER, vboID_);
  glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(GL_FLOAT), verts, GL_STATIC_DRAW);

  // TODO:  Generate our color buffer
  // ENDTODO
  // TODO:  Generate our index buffer
  // ENDTODO

  vao_.release();
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
#endif
  glViewport(0, 0, width(), height());
}

void BasicWidget::resizeGL(int w, int h)
{
  glViewport(0, 0, w, h);
}

void BasicWidget::paintGL()
{
  glDisable(GL_DEPTH_TEST);
  glDisable(GL_CULL_FACE);

  glClearColor(0.f, 0.f, 0.f, 1.f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

#if USE_QT_OPENGL
  shaderProgram_.bind();
  vao_.bind();
  // TODO: Change number of indices drawn
  glDrawElements(GL_TRIANGLES, ??, GL_UNSIGNED_INT, 0);
  // ENDTODO
  vao_.release();
  shaderProgram_.release();
#else
  glUseProgram(shaderID_);
  glEnableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, vboID_);
  glVertexAttribPointer(0,        // Attribute 0 matches our layout for vertex positions
      3,        // Size
      GL_FLOAT, // Type
      GL_FALSE, // Not normalized
      0,        // Stride - no interleaving
      (void*)0  // nullptr
  );
  glEnableVertexAttribArray(1);
  glBindBuffer(GL_ARRAY_BUFFER, cboID_);
  glVertexAttribPointer(1,        // Attribute 0 matches our layout for vertex positions
      4,        // Size
      GL_FLOAT, // Type
      GL_FALSE, // Not normalized
      0,        // Stride - no interleaving
      (void*)0  // nullptr
  );
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboID_);
  // Render
  // TODO: Change number of indices drawn
  glDrawElements(GL_TRIANGLES, ??, GL_UNSIGNED_INT, nullptr);
  // ENDTODO
  // Unbind everything
  glDisableVertexAttribArray(0);
  glUseProgram(NULL);
#endif
}
