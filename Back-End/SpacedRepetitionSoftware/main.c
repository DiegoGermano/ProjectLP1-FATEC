#include <stdio.h>
#include <mysql.h>

int main(int argc, char *argv[])
{
	int i;
	printf("Content-type: text/plain\n\n");

	printf("DIEGO GERMANO 2");

	for(i=1; i<argc; i++)
	{
		if(argv[i] != '\0')
			printf("Saida: %s \n", argv[i]);
	}
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
