#include <QCoreApplication>
//#include <signal.h>
//#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//#include <ctype.h>
//#include "TuxEip.h"
#include "rlthread.h"
//#include "rlinifile.h"
//#include "rlspreadsheet.h"
//#include "rldataacquisitionprovider.h"
//#include "rlmailbox.h"
//#include "rlsocket.h"
#include "tux_sqlite.h"

char *get_int(char *source, int *nro);
char *get_float(char *source, float *nro);
char *get_time(char *source, char *dest);
char *get_date(char *source, char *dest);

int main(int argc, char *argv[])
{
    int ret,i;
    char queue_data[120]="01/10/2013,11:01:26,196,6566,148,71,1171";
    int via=1;
    char *rest;
    char fecha_str[11], hora_str[9];
    float peso, float_value;
    int plato;

    // LO QUE FALTA:
    // Abrir la base de datos de configuracion (c:\\automation\\config\\config.db)
    // obtener de la tabla de 'variadad_procesada' el nombre de la actual a partir
    // del último registro y utilizarla por default.

    char query_str[120];
    Tux_sqlite db;
    rlMutex dbmutex;
    QCoreApplication a(argc, argv);

    rest=NULL;

    ret = db.open("QSQLITE","localhost","c:\\automation\\datos\\produccion.db","","");
    printf("db.open ret=%d\n", ret);

    dbmutex.lock();
    ret = db.query("SELECT * FROM produccion;");
    if(ret==0){
        printf("db.query=listar todos los registros de tabla 'produccion' ret=%d\n", ret);
/*
        for(i=0; i<2; i++){
            db.result->next();
            printf("resultado: %s\n",db.result->value(0).toString().toUtf8().data());
            printf("resultado: %s\n",db.result->value(1).toString().toUtf8().data());
        }
*/
        dbmutex.unlock();
        }
    else{
        printf("no pudo abrir la base de datos\n");
        dbmutex.unlock();
        rlsleep(3000);
        return -1;
      }
    i=0;
    while(i==0){ //<1000
        rest=get_date(queue_data,fecha_str);
        rest=get_time(rest,hora_str);
        rest=get_float(rest,&peso);
        rest=get_int(rest,&plato);
        rest=get_float(rest,&float_value);
        sprintf(query_str, "INSERT INTO produccion(FECHA,HORA,VIA,PLATO,PESO) VALUES ('%s','%s',%d,%d,%f);",fecha_str,hora_str,via,plato,peso);
        dbmutex.lock();
        ret = db.query(query_str);
        dbmutex.unlock();
        if(ret==0){
            printf("db.query %d succeded query= %s\n", i,query_str);
            i++;
            rlsleep(100);
            printf("\n");
         }
//        else{
//              printf("db.query %d fail, query=%s\n", i,query_str);
//            }
    }
    printf("fin del programa\n");
    return a.exec();
}

char *get_int(char *source, int *nro)
{
    char *rest, dest[10];
    int p;

    rest=strchr(source,',');
    if(rest!=NULL){
        p=rest-source;
        strncpy(dest,source,p);
        dest[p]=0;
        *nro=atoi(dest);
        return (rest+1);
    }
    else{
        *nro=0;
        return NULL;
    }
}

char *get_float(char *source, float *nro)
{
    char *rest, dest[20];
    int p, q;
    // float format received: xxxx,yyyyy
    // return xxxx.yyyy

    rest=strchr(source,',');
    if(rest!=NULL){
        p=rest-source;
        strncpy(dest,source,p);
        dest[p]='.';
        source=rest+1;
        rest=strchr(source,',');
        if(rest==NULL) q=strlen(source);
        else q=rest-source;
        strncpy(dest+p+1,source,q);
        dest[p+q+1]=0;
        *nro=atof(dest);
        if (rest+1==NULL)
            return NULL;
        else{
            return (rest+1);
        }
    }
    else{
        *nro=0.0;
        return NULL;
    }
}

char *get_time(char *source, char *dest)
{
    char *rest;
    int p;

    rest=strchr(source,',');
    if(rest!=NULL){
        p=rest-source;
        strncpy(dest,source,p);
        dest[p]=0;
        return (rest+1);
    }
    else{
        dest[0]=0;
        return NULL;
    }
}

char *get_date(char *source, char *dest)
{
    char yy_str[5], mm_str[3], dd_str[3];
    int p, yy, mm, dd;
    char *head,*rest;

    // formato deseado de fecha YYYY-MM-DD
    // formato actual de fecha DD/MM/YYYY
    head=source;
    rest=strchr(head,'/');
    if(rest!=NULL){
        p=rest-head;
        strncpy(dd_str, head, p);
        dd_str[p]=0;
        dd=atoi(dd_str);    // dia
    }
    else
        return NULL;

    head=rest+1;
    rest=strchr(head,'/');
    if(rest!=NULL){
        p=rest-head;
        strncpy(mm_str, head, p);
        mm_str[p]=0;
        mm=atoi(mm_str);    // mes
    }
    else
        return NULL;

    head=rest+1;
    rest=strchr(head,',');
    if(rest!=NULL){
        p=rest-head;
        strncpy(yy_str, head, p);
        yy_str[p]=0;
        yy=atoi(yy_str);    // año
    }
    else
        return NULL;

    // validar fecha
    sprintf(dest,"%04d-%02d-%02d",yy,mm,dd);
    return (rest+1);
}
