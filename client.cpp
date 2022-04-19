#include "client.h"

client::client(int ID, QString Lastname, QString Name, QString Address):
      ID(ID),
      Lastname(Lastname),
      Name(Name),
      Address(Address)
{}

client::client(QString Lastname, QString Name, QString Address):
      Lastname(Lastname),
      Name(Name),
      Address(Address)
{}
