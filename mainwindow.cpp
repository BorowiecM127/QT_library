#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
      , ui(new Ui::MainWindow)
      , lib_db("../Biblioteka/library.db")
{
    ui->setupUi(this);

    connect(ui->AddBookButton, SIGNAL(clicked()), this, SLOT(AddBook()));
    connect(ui->RemoveBookButton, SIGNAL(clicked()), this, SLOT(RemoveBook()));
    connect(ui->AddClientButton, SIGNAL(clicked()), this, SLOT(AddClient()));
    connect(ui->RemoveClientButton, SIGNAL(clicked()), this, SLOT(RemoveClient()));
    connect(ui->LendBookButton, SIGNAL(clicked()), this, SLOT(LendBook()));
    connect(ui->ReturnBookButton, SIGNAL(clicked()), this, SLOT(ReturnBook()));
    connect(ui->LendedBookList, SIGNAL(currentRowChanged(int)), this, SLOT(BookDetails()));

    LoadAllData();
}

MainWindow::~MainWindow()
{
    delete ui;
}



////////////////////////////////////////////////////////
//SLOTS:

void MainWindow::AddBook()
{
    if (!ui->BookAuthorEdit->document()->isEmpty()
        && !ui->BookTitleEdit->document()->isEmpty()
        && !ui->BookGenreEdit->document()->isEmpty())
    {
        QString Author = ui->BookAuthorEdit->toPlainText();
        QString Name = ui->BookTitleEdit->toPlainText();
        QString Genre = ui->BookGenreEdit->toPlainText();
        book b(Author, Name, Genre);
        lib_db.AddBook(b);
        LoadAvailableBooks();
        ui->BookAuthorEdit->clear();
        ui->BookTitleEdit->clear();
        ui->BookGenreEdit->clear();
    }
}

void MainWindow::RemoveBook()
{
    if(ui->AvailableBookList->currentItem())
    {
        QString Row = ui->AvailableBookList->currentItem()->text();
        int Selected = Row.split(" ")[0].toInt();

        lib_db.RemoveBook(Selected);
        LoadAvailableBooks();
        LoadLendedBooks();
    }
}

void MainWindow::AddClient()
{
    if (!ui->ClientLastnameEdit->document()->isEmpty()
        && !ui->ClientNameEdit->document()->isEmpty()
        && !ui->ClientAddressEdit->document()->isEmpty())
    {
        QString Lastname = ui->ClientLastnameEdit->toPlainText();
        QString Name = ui->ClientNameEdit->toPlainText();
        QString Address = ui->ClientAddressEdit->toPlainText();
        client c(Lastname, Name, Address);
        lib_db.AddClient(c);
        LoadClients();
        ui->ClientLastnameEdit->clear();
        ui->ClientNameEdit->clear();
        ui->ClientAddressEdit->clear();
    }
}

void MainWindow::RemoveClient()
{
    if(ui->ClientsList->currentItem())
    {
        QString Row = ui->ClientsList->currentItem()->text();
        int Selected = Row.split(" ")[0].toInt();
        lib_db.RemoveClient(Selected);
        lib_db.RemoveClientCommits(Selected);
        LoadAllData();
    }
}

void MainWindow::LendBook()
{
    if (ui->ClientListToLend->currentItem() && ui->BookListToLend->currentItem()) {
        ui->LendedBookDetails->clear();
        QString Row = ui->ClientListToLend->currentItem()->text();
        int SelectedClient = Row.split(" ")[0].toInt();
        Row = ui->BookListToLend->currentItem()->text();
        int SelectedBook = Row.split(" ")[0].toInt();

        lib_db.LendBook(SelectedBook, SelectedClient);
        LoadAllData();
    }
}

void MainWindow::ReturnBook()
{
    if(ui->LendedBookList->currentItem())
    {
        QString Row = ui->LendedBookList->currentItem()->text();
        int Selected = Row.split(" ")[0].toInt();

        lib_db.ReturnBook(Selected);
        LoadAvailableBooks();
        LoadLendedBooks();
    }
}

void MainWindow::BookDetails()
{
    if(ui->LendedBookList->currentItem())
    {
        QString Row = ui->LendedBookList->currentItem()->text();
        int ID = Row.split(" ")[0].toInt();
        QPair<book, client> Details = lib_db.LendedBookDetails(ID);
        ui->LendedBookDetails->clear();

        QStringList DetailsList;
        DetailsList << "KSIĄŻKA"
                    << "Autor: " + Details.first.Author
                    << "Tytuł: " + Details.first.Name
                    << "Gatunek: " + Details.first.Genre + "\n"
                    << "WYPOŻYCZONA PRZEZ: "
                    << "Imię: " + Details.second.Name
                    << "Nazwisko: " + Details.second.Lastname
                    << "Adres: " + Details.second.Address;

        ui->LendedBookDetails->addItems(DetailsList);
    }
}



///////////////////////////////////////////////////////
//FUNCTIONS

void MainWindow::LoadAllData()
{
    LoadAvailableBooks();
    LoadLendedBooks();
    LoadClients();
}

void MainWindow::LoadAvailableBooks()
{
    QVector<book> AvailableBooks = lib_db.GetAvailableBooks();
    ui->AvailableBookList->clear();
    ui->BookListToLend->clear();

    for (unsigned int i = 0; i < AvailableBooks.length(); ++i) {
        ui->AvailableBookList->addItem(QString::number(AvailableBooks[i].ID) + " " + AvailableBooks[i].Author + " "
                                       + AvailableBooks[i].Name + " " + AvailableBooks[i].Genre);
        ui->BookListToLend->addItem(QString::number(AvailableBooks[i].ID) + " " + AvailableBooks[i].Author + " "
                                    + AvailableBooks[i].Name + " " + AvailableBooks[i].Genre);
    }
}

void MainWindow::LoadLendedBooks()
{
    QVector<book> LendedBooks = lib_db.GetLendedBooks();
    ui->LendedBookDetails->clear();
    ui->LendedBookList->clear();

    for (unsigned int i = 0; i < LendedBooks.length(); ++i) {
        ui->LendedBookList->addItem(QString::number(LendedBooks[i].ID) + " " + LendedBooks[i].Author + " "
                                    + LendedBooks[i].Name + " " + LendedBooks[i].Genre);
    }
}

void MainWindow::LoadClients()
{
    QVector<client> Clients = lib_db.GetClients();
    ui->ClientsList->clear();
    ui->ClientListToLend->clear();

    for (unsigned int i = 0; i < Clients.length(); ++i) {
        ui->ClientsList->addItem(QString::number(Clients[i].ID) + " " + Clients[i].Lastname + " "
                                 + Clients[i].Name + " " + Clients[i].Address);
        ui->ClientListToLend->addItem(QString::number(Clients[i].ID) + " " + Clients[i].Lastname + " "
                                      + Clients[i].Name + " " + Clients[i].Address);
    }
}
