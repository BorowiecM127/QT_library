#ifndef BOOK_H
#define BOOK_H

#include <QString>

struct book
{
    explicit book(int ID, QString Author, QString Name, QString Genre);
    explicit book(QString Author, QString Name, QString Genre);

    int ID;
    QString Author;
    QString Name;
    QString Genre;
};

#endif // BOOK_H
