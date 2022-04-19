#include "librarydbmanager.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>

librarydbmanager::librarydbmanager(const QString& path)
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(path);

    if (!db.open())
    {
            QMessageBox messageBox;
            messageBox.critical(0,"Error","Error: connection with database failed");
            messageBox.setFixedSize(500,200);
    }
}

QVector<book> librarydbmanager::GetAvailableBooks()
{
    QVector<book> books;
    QSqlQuery query("SELECT * FROM books WHERE ClientID IS NULL ORDER BY Author");
    if(query.isActive())
    {
        while (query.next()) {
            books.push_back(book(query.value(0).toInt(),
                                 query.value(1).toString(),
                                 query.value(2).toString(),
                                 query.value(3).toString()));
        }
    }
    else
    {
        QMessageBox messageBox;
        messageBox.critical(0,"Error","GetAvailableBooks error: " + query.lastError().text());
        messageBox.setFixedSize(500,200);
    }

    return books;
}

void librarydbmanager::AddBook(book B)
{
    QSqlQuery query;
    query.prepare("INSERT INTO books (Author, Name, Genre) VALUES (:Author, :Name, :Genre)");
    query.bindValue(":Author", B.Author);
    query.bindValue(":Name", B.Name);
    query.bindValue(":Genre", B.Genre);

    if (!query.exec()) {
        QMessageBox messageBox;
        messageBox.critical(0,"Error","AddBook error: " + query.lastError().text());
        messageBox.setFixedSize(500,200);
    }
}

void librarydbmanager::RemoveBook(int ID)
{
    QSqlQuery query;
    query.prepare("DELETE FROM books WHERE BookID = (:id)");
    query.bindValue(":id", ID);

    if (!query.exec()) {
        QMessageBox messageBox;
        messageBox.critical(0,"Error","RemoveBook error: " + query.lastError().text());
        messageBox.setFixedSize(500,200);
    }
}

QVector<book> librarydbmanager::GetLendedBooks()
{
    QVector<book> books;
    QSqlQuery query("SELECT * FROM books WHERE ClientID IS NOT NULL");
    if(query.isActive())
    {
        while (query.next()) {
            books.push_back(book(query.value(0).toInt(),
                                 query.value(1).toString(),
                                 query.value(2).toString(),
                                 query.value(3).toString()));
        }
    }
    else
    {
        QMessageBox messageBox;
        messageBox.critical(0,"Error","GetLendedBooks error: " + query.lastError().text());
        messageBox.setFixedSize(500,200);
    }

    return books;
}

QPair<book, client> librarydbmanager::LendedBookDetails(int BookID)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM books WHERE BookID = (:BookID)");
    query.bindValue(":BookID", BookID);

    if (query.exec()) {
        if (query.next()) {
            book Book(query.value(0).toInt(),
                      query.value(1).toString(),
                      query.value(2).toString(),
                      query.value(3).toString());
            int ClientID = query.value(4).toInt();

            QSqlQuery client_query;
            client_query.prepare("SELECT * FROM clients WHERE ClientID = (:ClientID)");
            client_query.bindValue(":ClientID", ClientID);
            if (client_query.exec()) {
                if (client_query.next()) {
                    client Client(client_query.value(0).toInt(),
                                  client_query.value(1).toString(),
                                  client_query.value(2).toString(),
                                  client_query.value(3).toString());

                    return qMakePair(Book, Client);
                }
            }
            else
            {
                QMessageBox messageBox;
                messageBox.critical(0,"Error","LendedBookDetails Client error: " + query.lastError().text());
                messageBox.setFixedSize(500,200);
            }
        }
    }
    else
    {
        QMessageBox messageBox;
        messageBox.critical(0,"Error","LendedBookDetails Book error: " + query.lastError().text());
        messageBox.setFixedSize(500,200);
    }
}

QVector<client> librarydbmanager::GetClients()
{
    QVector<client> clients;
    QSqlQuery query("SELECT * FROM clients");

    if(query.isActive())
    {
        while (query.next())
        {
            clients.push_back(
                client(
                    query.value(0).toInt(),
                    query.value(1).toString(),
                    query.value(2).toString(),
                    query.value(3).toString()
                    ));
        }
    }
    else
    {
        QMessageBox messageBox;
        messageBox.critical(0,"Error","GetClients error: " + query.lastError().text());
        messageBox.setFixedSize(500,200);
    }

    return clients;
}

void librarydbmanager::AddClient(client C)
{
    QSqlQuery query;
    query.prepare("INSERT INTO clients (Lastname, Name, Address) VALUES (:Lastname, :Name, :Address)");
    query.bindValue(":Lastname", C.Lastname);
    query.bindValue(":Name", C.Name);
    query.bindValue(":Address", C.Address);

    if(!query.exec())
    {
        QMessageBox messageBox;
        messageBox.critical(0,"Error","AddClient error: " + query.lastError().text());
        messageBox.setFixedSize(500,200);
    }
}

void librarydbmanager::RemoveClient(int ID)
{
    QSqlQuery query;
    query.prepare("DELETE FROM clients WHERE ClientID = (:id)");
    query.bindValue(":id", ID);

    if(!query.exec())
    {
        QMessageBox messageBox;
        messageBox.critical(0,"Error","RemoveClient error: " + query.lastError().text());
        messageBox.setFixedSize(500,200);
    }
}

void librarydbmanager::RemoveClientCommits(int ID)
{
    QSqlQuery query;
    query.prepare("UPDATE books SET ClientID = NULL WHERE ClientID = (:id)");
    query.bindValue(":id", ID);

    if(!query.exec())
    {
        QMessageBox messageBox;
        messageBox.critical(0,"Error","RemoveClientCommits error: " + query.lastError().text());
        messageBox.setFixedSize(500,200);
    }
}

void librarydbmanager::LendBook(int BookID, int ClientID)
{
    QSqlQuery query;
    query.prepare("UPDATE books SET ClientID = (:ClientID) WHERE BookID = (:BookID)");
    query.bindValue(":ClientID", ClientID);
    query.bindValue(":BookID", BookID);

    if(!query.exec())
    {
        QMessageBox messageBox;
        messageBox.critical(0,"Error","LendBook error: " + query.lastError().text());
        messageBox.setFixedSize(500,200);
    }
}

void librarydbmanager::ReturnBook(int BookID)
{
    QSqlQuery query;
    query.prepare("UPDATE books SET ClientID = NULL WHERE BookID = (:BookID)");
    query.bindValue(":BookID", BookID);

    if(!query.exec())
    {
        QMessageBox messageBox;
        messageBox.critical(0,"Error","ReturnBook error: " + query.lastError().text());
        messageBox.setFixedSize(500,200);
    }
}
