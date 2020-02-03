/**
 * Support code written by Erik W. Anderson
 */

#include <QtCore>
#include <QtGui>
#include <QtOpenGL>

// Lab application
#include "Lab.h"

int main(int argc, char** argv) {
  QApplication a(argc, argv);
  QString appDir = a.applicationDirPath();
  QDir::setCurrent(appDir);

  //QSurfaceFormat fmt;
  //fmt.setDepthBufferSize(24);
  //fmt.setStencilBufferSize(8);
  //fmt.setVersion(3,3);
  //fmt.setProfile(QSurfaceFormat::CoreProfile);
  //QSurfaceFormat::setDefaultFormat(fmt);
  
  Lab app;
  app.show();
  return QApplication::exec();
}
