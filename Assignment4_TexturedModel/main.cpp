/**
 * Support code written by Erik W. Anderson
 */

#include <QtCore>
#include <QtGui>
#include <QtOpenGL>

// TODO:  you have to include whatever application-specific code there is here.  This should be
// a subclass of QMainWindow!

int main(int argc, char** argv) {
  QApplication a(argc, argv);
  QString appDir = a.applicationDirPath();
  QDir::setCurrent(appDir);

  QSurfaceFormat fmt;
  fmt.setDepthBufferSize(24);
  fmt.setStencilBufferSize(8);
  fmt.setVersion(3,3);
  fmt.setProfile(QSurfaceFormat::CoreProfile);
  QSurfaceFormat::setDefaultFormat(fmt);

  // TODO:  Replace the following 3 lines with whatever you need to create, show, and execute your application
  //Application app;
  //app.show();
  //return QApplication::exec();
}
