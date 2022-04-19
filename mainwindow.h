#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "librarydbmanager.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void AddBook();
    void RemoveBook();
    void AddClient();
    void RemoveClient();
    void LendBook();
    void ReturnBook();
    void BookDetails();

private:
    Ui::MainWindow *ui;
    librarydbmanager lib_db;
    void LoadAllData();
    void LoadAvailableBooks();
    void LoadLendedBooks();
    void LoadClients();
};
#endif // MAINWINDOW_H
