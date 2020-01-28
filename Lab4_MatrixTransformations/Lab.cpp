#include "Lab.h"

#include "BasicWidget.h"

Lab::Lab(QWidget* parent) : QMainWindow(parent)
{
  buildGui();
}

Lab::~Lab()
{}

void Lab::buildGui()
{
  // A simple menubar.
  QMenuBar* menu = menuBar();
  QMenu* file = menu->addMenu("File");
  QAction* exit = file->addAction("Quit", [this]() {close();});

  // Our basic widget.
  BasicWidget* widget = new BasicWidget(this);
  setCentralWidget(widget);
}
