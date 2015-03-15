#include <stdio.h>
#include <mysql.h>
#include <string.h>


void remove_all_chars(char* str, char c) {

    char *pr = str, *pw = str;

    while (*pr) {
        *pw = *pr++;
        pw += (*pw != c);
    }
    *pw = '\0';

}

void finish_with_error(MYSQL *con)
{
  fprintf(stderr, "%s\n", mysql_error(con));
  mysql_close(con);
  exit(1);
}


void CreateDeck(char *str)
{
    //cre/deck/\{"descricao":"maroto","dificuldade":"hard","idioma":"ingles"\}

    printf("%s", str);

    return 0;

      MYSQL *con = mysql_init(NULL);

      if (con == NULL)
      {
          fprintf(stderr, "mysql_init() failed\n");
          exit(1);
      }

      if (mysql_real_connect(con, "127.0.0.1", "root", "lexos2009","spacedrepetition", 0, NULL, 0) == NULL) finish_with_error(con);



      if (mysql_query(con, "insert into deck (dificuldade, modifiedOn, CreatedOn, Ativado, descricao, Deck_Id) values (1,NOW(),NOW(),1,'uhUuuuuuuuuUUuuUuu',5)")) finish_with_error(con);


       printf("Congratilations one deck was created :)");
}

void Create(char *str)
{
    //ROTAS DECK/WROD/USER
    if(str[4] == 'd' && str[5] == 'e' && str[6] == 'c' && str[7] == 'k' && str[8] == '/')
    {
       CreateDeck(str);
    }
    else if(str[4] == 'w' && str[5] == 'o' && str[6] == 'r' && str[7] == 'd' && str[8] == '/')
    {
       printf("Create word");
    }
    else if(str[4] == 'u' && str[5] == 's' && str[6] == 'e' && str[7] == 'r' && str[8] == '/')
    {
       printf("Create usuario");
    }
    else
    {
        printf("Error invalid argument! 00003");
        return 0;
    }
}

void Update(char *str)
{
    //ROTAS DECK/WROD/USER
    if(str[4] == 'd' && str[5] == 'e' && str[6] == 'c' && str[7] == 'k' && str[8] == '/')
    {
       printf("Update deck");
    }
    else if(str[4] == 'w' && str[5] == 'o' && str[6] == 'r' && str[7] == 'd' && str[8] == '/')
    {
       printf("Update word");
    }
    else if(str[4] == 'u' && str[5] == 's' && str[6] == 'e' && str[7] == 'r' && str[8] == '/')
    {
       printf("Update usuario");
    }
    else
    {
        printf("Error invalid argument! 00004");
        return 0;
    }
}

void Delete(char *str)
{
    //ROTAS DECK/WROD/USER
    if(str[4] == 'd' && str[5] == 'e' && str[6] == 'c' && str[7] == 'k' && str[8] == '/')
    {
       printf("Delete deck");
    }
    else if(str[4] == 'w' && str[5] == 'o' && str[6] == 'r' && str[7] == 'd' && str[8] == '/')
    {
       printf("Delete word");
    }
    else if(str[4] == 'u' && str[5] == 's' && str[6] == 'e' && str[7] == 'r' && str[8] == '/')
    {
       printf("Delete usuario");
    }
    else
    {
        printf("Error invalid argument! 00005");
        return 0;
    }
}

void Read(char *str)
{
    //ROTAS DECK/WROD/USER
    if(str[4] == 'd' && str[5] == 'e' && str[6] == 'c' && str[7] == 'k' && str[8] == '/')
    {
       printf("Read deck");
    }
    else if(str[4] == 'w' && str[5] == 'o' && str[6] == 'r' && str[7] == 'd' && str[8] == '/')
    {
       printf("Read word");
    }
    else if(str[4] == 'u' && str[5] == 's' && str[6] == 'e' && str[7] == 'r' && str[8] == '/')
    {
       printf("Read usuario");
    }
    else
    {
        printf("Error invalid argument! 00006");
        return 0;
    }
}


int main(int argc, char *argv[])
{

    //find solution to build where

	int i, j =0, c = 0;
    printf("Content-type: text/plain\n\n");

    char* value = "cre/deck/\{\"descricao\":\"maroto\",\"dificuldade\":\"hard\",\"idioma\":\"ingles\"\}";
    char saida[strlen(value)-10];

    char campos[150];

	for(i=10; i< strlen(value); i++)
	{
        saida[j] = value[i];
        j++;


	}

	 remove_all_chars(saida, '"');

    printf("Saida: %s \n", saida);

    return 0;

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
    else
    {
        printf("Error invalid argument! 00002");
    }

    return 0;

    /*
	int i;

	//char *stat  = '\{"descricao":"english","dificuldade":"hard","idioma":"english"\}'

	//

	printf("Content-type: text/plain\n\n");



	for(i=1; i<argc; i++)
	{
		if(argv[i] != '\0')
            printf("Saida: %s \n", argv[i]);
	}


    char s[200]="\{\"descricao\":\"english\",\"dificuldade\":\"hard\",\"idioma\":\"english\"\}";

    printf("%s\n",s);

    remove_all_chars(s, '\\');


    printf("%s\n",s);*/


    /* segundo testes tetornado uma lista de

    printf("Content-type: text/plain\n\n");

    printf("%s \n", argv[1]);
    printf("%s \n", argv[2]);
    printf("%s \n", argv[3]);
       printf("%s ", argv[0]);

    return 0;

     MYSQL *con = mysql_init(NULL);

      if (con == NULL)
      {
          fprintf(stderr, "mysql_init() failed\n");
          exit(1);
      }

     if (mysql_real_connect(con, "127.0.0.1", "root", "lexos2009","spacedrepetition", 0, NULL, 0) == NULL)
      {
          finish_with_error(con);
      }



        remove_all_chars(argv[1], '\\');
        remove_all_chars(argv[1], '\'');

      if (mysql_query(con, argv[1]))
      {
          finish_with_error(con);
      }

      MYSQL_RES *result = mysql_store_result(con);

       if (result == NULL)
      {
          finish_with_error(con);
      }

       int num_fields = mysql_num_fields(result);
       int i=0;
          MYSQL_ROW row;

          while ((row = mysql_fetch_row(result)))
          {
              for(i = 0; i < num_fields; i++)
              {
                  printf("%s ", row[i] ? row[i] : "NULL");
              }
                  printf("\n");
          }

          mysql_free_result(result);
          mysql_close(con);

          */


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
