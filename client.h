#ifndef CLIENT_H
#define CLIENT_H

#include <QString>

struct client
{
    explicit client(int ID, QString Lastname, QString Name, QString Address);
    explicit client(QString Lastname, QString Name, QString Address);

    int ID;
    QString Lastname;
    QString Name;
    QString Address;
};

#endif // CLIENT_H
