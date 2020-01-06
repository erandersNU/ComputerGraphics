#include "Lab.h"

#include "BasicWidget.h"

Lab0::Lab0(QWidget* parent) : QMainWindow(parent)
{
  buildGui();
}

Lab0::~Lab0()
{}

void Lab0::buildGui()
{
  // A simple menubar.
  QMenuBar* menu = menuBar();
  QMenu* file = menu->addMenu("File");
  QAction* exit = file->addAction("Quit", [this]() {close();});

  // Our basic widget.
  BasicWidget* widget = new BasicWidget(this);
  widget->setBackgroundColor(QColor(255, 0, 0, 0));
  setCentralWidget(widget);
}
