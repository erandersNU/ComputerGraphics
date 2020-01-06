/**
 * The primary application code.
 */

#include <QtGui>
#include <QtCore>
#include <QtWidgets>

class Lab0 : public QMainWindow
{
  Q_OBJECT

public:
  Lab0(QWidget* parent=0);
  virtual ~Lab0();
  
signals:

public slots:

private:
  void buildGui();
};
