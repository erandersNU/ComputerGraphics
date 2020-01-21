/**
 * The primary application code.
 */

#include <QtGui>
#include <QtCore>
#include <QtWidgets>

class Lab2 : public QMainWindow
{
  Q_OBJECT

public:
  Lab2(QWidget* parent=0);
  virtual ~Lab2();
  
signals:

public slots:

private:
  void buildGui();
};
