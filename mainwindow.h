#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>
#include "mystringlistmodel.h"

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
      void documentWasModified();

  private:
      void createActions();      
      bool changesSaved();
      bool saveFile(const QString &file_name);
      void setCurrentFile(const QString &file_name);

      QFrame *frame;
      QHBoxLayout *frameLayout;
      QStringList lst;
      QListView *list_view_1, *list_view_2;
      MyStringListModel * my_list;
      QStringListModel * list;
      QString cur_file;
};

#endif // MAINWINDOW_H
