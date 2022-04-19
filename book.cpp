#include "book.h"

book::book(int ID, QString Author, QString Name, QString Genre):
      ID(ID),
      Author(Author),
      Name(Name),
      Genre(Genre)
{}
book::book(QString Author, QString Name, QString Genre):
      Author(Author),
      Name(Name),
      Genre(Genre)
{}
