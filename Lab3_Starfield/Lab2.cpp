#include "Lab2.h"

#include "BasicWidget.h"

Lab2::Lab2(QWidget* parent) : QMainWindow(parent)
{
  buildGui();
}

Lab2::~Lab2()
{}

void Lab2::buildGui()
{
  // A simple menubar.
  QMenuBar* menu = menuBar();
  QMenu* file = menu->addMenu("File");
  QAction* exit = file->addAction("Quit", [this]() {close();});

  // Our basic widget.
  BasicWidget* widget = new BasicWidget(this);
  setCentralWidget(widget);
}
