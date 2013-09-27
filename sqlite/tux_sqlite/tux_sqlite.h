#ifndef TUX_SQLITE_H
#define TUX_SQLITE_H

#include "tux_sqlite_global.h"
#include <stdio.h>
#include <stdlib.h>
#include <QSqlDatabase>
#include <QSqlRecord>
#include <QSqlField>
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <qstring.h>
//#include "processviewserver.h"

class TUX_SQLITESHARED_EXPORT Tux_sqlite
{
public:
    Tux_sqlite();
    ~Tux_sqlite();
    int open(const char *dbtype, const char *hostname, const char *dbname, const char *user, const char *pass);
    int close();
    //int query(PARAM *p, const char *sqlcommand);
    int query(const char *sqlcommand);
    //int populateTable(PARAM *p, int id);
    int populateTable(int id);
    //const char *recordFieldValue(PARAM *p, int x);
    const char *recordFieldValue(int x);
    int nextRecord();

  QSqlDatabase *db;
  QSqlQuery    *result;
  QSqlError    *error;
};

#endif // TUX_SQLITE_H
