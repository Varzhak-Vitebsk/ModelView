#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>
//#include "mystringlistmodel.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT    

public:
      MainWindow();
      void loadFile(const QString &file_name);

  protected:
      void closeEvent(QCloseEvent *event) Q_DECL_OVERRIDE;

  private slots:      
      void open();
      bool save();
      bool saveAs();

  private:
      void createActions();
      void tuneWindow();
      bool changesSaved();
      bool saveFile(const QString &file_name);
      void setCurrentFile(const QString &file_name);

      QFrame *frame;
      QHBoxLayout *frameLayout;
      QListView *list_view;
      //MyStringListModel * my_list;
      QStringListModel * list;
      QString cur_file;
};

#endif // MAINWINDOW_H
