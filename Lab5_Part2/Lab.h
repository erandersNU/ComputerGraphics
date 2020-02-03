/**
 * The primary application code.
 */

#include <QtGui>
#include <QtCore>
#include <QtWidgets>

class Lab : public QMainWindow
{
  Q_OBJECT

public:
  Lab(QWidget* parent=0);
  virtual ~Lab();
  
signals:

public slots:

private:
  void buildGui();
};
