#include <stdio.h>
#include <mysql.h>
#include <string.h>
#include <time.h>
#include "repository.h"
#include "utilities.h"
#include "builders.h"
#include "serviceCreate.h"
#include "serviceUpdate.h"
#include "serviceDelete.h"
#include "serviceRead.h"
#include "serviceLogin.h"

char current_token[500];

int main(int argc, char *argv[])
{
    // remember to take out some characters

    printf("Content-type: text/plain\n\n");


    //Split parameters to get token and data

    int c = 0;
    char * pch;
	int number_of_values = (count_characters(argv[1], '&')*2);

    if(number_of_values > 0)
    {
        part fieldsValues[number_of_values];

        pch = strtok (argv[1],"&");
        while (pch != NULL)    {
            strcpy(fieldsValues[c].value, pch);
            pch = strtok (NULL, "&");
            c++;
        }

        strcpy(current_token, fieldsValues[1].value);
        argv[1] = fieldsValues[0].value;
    }

    if(strlen(current_token) > 0)
    {
        //validar token
    }
    else
    {

        if((strstr(argv[1], "log/logi/") == NULL) &&  (strstr(argv[1], "cre/user/") == NULL) && (strstr(argv[1], "cre/cont/") == NULL))
        {
            //printf("Access denied 0x45678558");
            //return;
        }

    }


    //some tests
   /* printf("qury : %s\n", getenv("HOME"));
    printf("HOME : %s\n", getenv("HOME"));
    printf("ROOT : %s\n", getenv("ROOT"));
    printf("HTTP_X_MY_HEADER : %s\n", getenv("HTTP_X_MY_HEADER"));
    printf("HTTP_ACCEPT_ENCODING : %s\n", getenv("HTTP_ACCEPT_ENCODING"));
    printf("AUTH_TYPE : %s\n", getenv("AUTH_TYPE"));
    printf("REMOTE_USER : %s\n", getenv("REMOTE_USER"));
    printf("REMOTE_IDENT  : %s\n", getenv("REMOTE_IDENT"));
    printf("REMOTE_USER : %s\n", getenv("REMOTE_USER"));
    printf("REQUEST_METHOD : %s\n", getenv("REQUEST_METHOD"));
    printf("SCRIPT_NAME : %s\n", getenv("SCRIPT_NAME"));
    printf("CONTENT_TYPE  : %s\n", getenv("CONTENT_TYPE"));
    printf("SERVER_SOFTWARE : %s\n", getenv("SERVER_SOFTWARE"));
    printf("REMOTE_HOST : %s\n", getenv("REMOTE_HOST")); */

    if(argc <= 1 || strlen(argv[1]) < 9)
    {
        printf("Error invalid argument! 00001");
        return 0;
    }

    //ROTAS        CRE/UPD/DEL/READ

    if(argv[1][0] == 'c' && argv[1][1] == 'r' && argv[1][2] == 'e' && argv[1][3] == '/')
    {
        Create(argv[1]);
    }
    else if(argv[1][0] == 'u' && argv[1][1] == 'p' && argv[1][2] == 'd' && argv[1][3] == '/')
    {
        Update(argv[1]);
    }
    else if(argv[1][0] == 'd' && argv[1][1] == 'e' && argv[1][2] == 'l' && argv[1][3] == '/')
    {
        Delete(argv[1]);
    }
    else if(argv[1][0] == 'r' && argv[1][1] == 'e' && argv[1][2] == 'a' && argv[1][3] == '/')
    {
        Read(argv[1]);
    }
    else if(argv[1][0] == 'l' && argv[1][1] == 'o' && argv[1][2] == 'g' && argv[1][3] == '/')
    {
        Login(argv[1]);
    }
    else
    {
        printf("Error invalid argument! 00002");
    }

    return 0;

    //http://zetcode.com/db/mysqlc/
    //http://hypeshell.com/index.php/articles/14-sql/59-mysql-c-api-programming-tutorial


	return 0;
}

/*
#include <windows.h>
#include <mysql.h>
#include <stdio.h>

int main(int argc, char *argv[])
{

     MYSQL *conn;
     MYSQL_RES *res;
     MYSQL_ROW row;
     char *server = "localhost";
     char *user = "root";
     char *password = "lexos2009";
     char *database = "test";
     conn = mysql_init(NULL);
     // Connect to database
     if (!mysql_real_connect(conn, server,
         user, password, database, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    // send SQL query
    if (mysql_query(conn, "show tables")) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }
    res = mysql_use_result(conn);

    // output table name
    printf("MySQL Tables in mysql database:\n");
    while ((row = mysql_fetch_row(res)) != NULL)
        printf("%s \n", row[0]);

    // close connection
    mysql_free_result(res);
    mysql_close(conn);

    return 0;
}
*/
