#include "mainwindow.h"

MainWindow::MainWindow()
{
    tuneWindow();
    createActions();
    setCurrentFile(QString());
}

void MainWindow::loadFile(const QString &file_name)
{
    QFile file(file_name);
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this, tr("Application"),
                           tr("Cannot read file %1:\n%2.")
                           .arg(QDir::toNativeSeparators(file_name), file.errorString()));
        return;
    }
    QTextStream in(&file);
    QString line;
    QStringList temp_list;
    for(int i = 0; in.readLineInto(&line); ++i) temp_list.append(line);
    list->setStringList(temp_list);
    setCurrentFile(file_name);
    file.close();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (changesSaved())
    {
        event->accept();
    } else {
        event->ignore();
    }
}

void MainWindow::open()
{
    if (changesSaved())
    {
        QString fileName = QFileDialog::getOpenFileName(this);
        if (!fileName.isEmpty()) loadFile(fileName);
    }
}

bool MainWindow::save()
{
    if (cur_file.isEmpty())
    {
        return saveAs();
    } else {
        return saveFile(cur_file);
    }
}

bool MainWindow::saveAs()
{
    QFileDialog dialog(this);
    dialog.setWindowModality(Qt::WindowModal);
    dialog.setAcceptMode(QFileDialog::AcceptSave);
    if (dialog.exec() != QDialog::Accepted) return false;
    return saveFile(dialog.selectedFiles().first());
}

void MainWindow::createActions()
{
    QMenu *fileMenu = menuBar()->addMenu(tr("&File"));

    QAction *openAct = new QAction(tr("&Open"), this);
    openAct->setShortcuts(QKeySequence::Open);
    openAct->setStatusTip(tr("Open an existing file"));
    connect(openAct, &QAction::triggered, this, &MainWindow::open);
    fileMenu->addAction(openAct);

    QAction *saveAct = new QAction(tr("&Save"), this);
    openAct->setShortcuts(QKeySequence::Save);
    openAct->setStatusTip(tr("Save current file"));
    connect(saveAct, &QAction::triggered, this, &MainWindow::save);
    fileMenu->addAction(saveAct);

    QAction *saveAsAct = new QAction(tr("&Save as..."), this);
    openAct->setShortcuts(QKeySequence::SaveAs);
    openAct->setStatusTip(tr("Save current file as..."));
    connect(saveAsAct, &QAction::triggered, this, &MainWindow::saveAs);
    fileMenu->addAction(saveAsAct);
}

void MainWindow::tuneWindow()
{
    QFrame *frame = new QFrame;
    QHBoxLayout *frameLayout = new QHBoxLayout(frame);
    list_view = new QListView();
    list = new QStringListModel(this);
    list_view->setModel(list);
    frameLayout->addWidget(list_view);
    setCentralWidget(frame);
    setMinimumSize(400, 500);

    connect(list, SIGNAL(dataChanged(QModelIndex,QModelIndex,QVector<int>)), this, SLOT(save()));
}

bool MainWindow::changesSaved()
{
    return true;
}

bool MainWindow::saveFile(const QString &file_name)
{
    QFile file(file_name);
    if (!file.open(QFile::WriteOnly | QFile::Text))
    {
        QMessageBox::warning(this, tr("Application"),
                            tr("Cannot write file %1:\n%2.")
                            .arg(QDir::toNativeSeparators(file_name),
                            file.errorString()));
        return false;
    }

    QTextStream out(&file);
    QString out_string;
    for(int i = 0; i != list->rowCount(); ++i)
    {
        QModelIndex ind = list->index(i);
        out_string.append(list->data(ind, Qt::EditRole).toString()+"\n");
    }
    out << out_string;
    setCurrentFile(file_name);
    file.close();
    return true;
}

void MainWindow::setCurrentFile(const QString &file_name)
{
    cur_file = file_name;
    setWindowModified(false);
    QString shownName = cur_file;
    if (cur_file.isEmpty()) shownName = "untitled.txt";
    setWindowFilePath(shownName);
}
