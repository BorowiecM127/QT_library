#ifndef LIBRARYDBMANAGER_H
#define LIBRARYDBMANAGER_H
#include <QSqlDatabase>
#include "book.h"
#include "client.h"

class librarydbmanager
{
public:
    librarydbmanager(const QString& path);
    QVector<book> GetAvailableBooks();
    void AddBook(book b);
    void RemoveBook(int ID);
    QVector<book> GetLendedBooks();
    QPair<book, client> LendedBookDetails(int BookID);
    QVector<client> GetClients();
    void AddClient(client C);
    void RemoveClient(int ID);
    void RemoveClientCommits(int ID);
    void LendBook(int BookID, int ClientID);
    void ReturnBook(int BookID);

private:
    QSqlDatabase db;
};

#endif // LIBRARYDBMANAGER_H
