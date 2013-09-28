#include "tux_sqlite.h"

Tux_sqlite::Tux_sqlite()
{
  db = NULL;
  result = new QSqlQuery();
  error  = new QSqlError();
}

Tux_sqlite::~Tux_sqlite()
{
  if(db != NULL)
  {
    close();
  }
  delete result;
  delete error;
}

int Tux_sqlite::open(const char *dbtype, const char *hostname, const char *dbname, const char *user, const char *pass, const char *conn_name)
{
  // See here to eliminate bug:
  // QSqlDatabasePrivate::addDatabase: duplicate connection name 'qt_sql_default_connection', old connection removed.
  // http://www.qtcentre.org/threads/26441-SOLVED-addDatabase-with-connectionName-problem
  if(db != NULL) return -1;
  db = new QSqlDatabase;
  QString qconn_name=conn_name;

  if(!db->contains(qconn_name)){
        *db = QSqlDatabase::addDatabase(dbtype,qconn_name);
        db->setHostName(hostname);
        db->setDatabaseName(dbname);
        db->setUserName(user);
        db->setPassword(pass);
        //printf("new connection: %s\n",conn_name);
    }
    else{
        *db=QSqlDatabase::database(qconn_name,true);
        //printf("re-using connection: %s\n",conn_name);
    }

  if(db->open())
  {
    return 0;
  }
  else
  {
    delete db;
    db = NULL;
    return -1;
  }
}

int Tux_sqlite::close()
{
  if(db == NULL)
  {
    return -1;
  }
  if(db->isOpen()){
     db->close();
   }
   delete db;
   db = NULL;
   return 0;
}

int Tux_sqlite::query(const char *sqlcommand)
//int Tux_sqlite::query(PARAM *p, const char *sqlcommand)
{
  if(db == NULL) return -1;
  QString qsqlcommand = QString::fromUtf8(sqlcommand);
  *result = db->exec(qsqlcommand);
  *error = db->lastError();
  if(error->isValid())
  {
    QString e = error->databaseText();
    printf("Tux_sqlite::query ERROR: %s\n", (const char *) e.toUtf8());
//    pvStatusMessage(p,255,0,0,"ERROR: Tux_sqlite::query(%s) %s", sqlcommand, (const char *) e.toUtf8());
    return -1;
  }
//  else
//      result->next();
//      printf("resultado 2: %s\n",(const char *) result->value(0).toString().toUtf8());
  return 0;
}

const char *Tux_sqlite::recordFieldValue(int x)
//const char *Tux_sqlite::recordFieldValue(PARAM *p, int x)
{
  QSqlRecord record = result->record();
  if(record.isEmpty())
  {
    //pvStatusMessage(p,255,0,0,"ERROR: Tux_sqlite::recordFieldValue(%d) record is empty", x);
    return "ERROR:";
  }
  QSqlField f = record.field(x);
  if(f.isValid())
  {
    QVariant v = f.value();
    return v.toString().toUtf8();
  }
  else
  {
   //pvStatusMessage(p,255,0,0,"ERROR: Tux_sqlite::recordFieldValue(%d) field is invalid", x);
    return "ERROR:";
  }
}

int Tux_sqlite::nextRecord()
{
  result->next();
  QSqlRecord record = result->record();
  if(record.isEmpty()) return -1;
  return 0;
}

/*
int Tux_sqlite::populateTable(int id)
//int Tux_sqlite::populateTable(PARAM *p, int id)
{
  int x,y,xmax,ymax;

  if(db == NULL)
  {
    //pvStatusMessage(p,255,0,0,"ERROR: Tux_sqlite::populateTable() db==NULL");
    return -1;
  }

  // set table dimension
  xmax = result->record().count();
  //
  // Using SQLITE a user from our forum found an issue
  // getting ymax.
  // With SQLITE numRowsAffected() does not return the correct value.
  // Other database systems do.
  //
  if(db->driverName() == "QSQLITE")
  {
    result->last();
    ymax = result->at()+1;
    result->first();
    printf("SQLITE ymax = %d \n",ymax);
  }
  else
  {
    ymax = result->numRowsAffected();
    //printf("no SQLITE, ymax = %d \n",ymax);
  }
  //pvSetNumRows(p,id,ymax);
  //pvSetNumCols(p,id,xmax);

  // populate table
  QSqlRecord record = result->record();
  if(record.isEmpty())
  {
    //pvStatusMessage(p,255,0,0,"ERROR: Tux_sqlite::populateTable() record is empty");
    return -1;
  }

  for(x=0; x<xmax; x++)
  { // write name of fields
    //pvSetTableText(p, id, x, -1, (const char *) record.fieldName(x).toUtf8());
  }

  for(y=0; y<ymax; y++)
  { // write fields
    result->next();
    QSqlRecord record = result->record();
    for(x=0; x<xmax; x++)
    {
      QSqlField f = record.field(x);
      if(f.isValid())
      {
        QVariant v = f.value();
        //pvSetTableText(p, id, x, y, (const char *) v.toString().toUtf8());
      }
      else
      {
        //pvSetTableText(p, id, x, y, "ERROR:");
      }
    }
    //result->next();
  }

  return 0;
}
*/
