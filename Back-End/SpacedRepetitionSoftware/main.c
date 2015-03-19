#include <stdio.h>
#include <mysql.h>
#include <string.h>
#include <time.h>

char password[500];
char current_token[500];

//##############     Auxiliary functions ###################################################

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

int count_characters(const char *str, char character)
{
    const char *p = str;
    int count = 0;

    do {
        if (*p == character)
            count++;
    } while (*(p++));

    return count;
}

int random_number(int min_num, int max_num)
{
    int result=0,low_num=0,hi_num=0;
    if(min_num<max_num)
    {
        low_num=min_num;
        hi_num=max_num+1; // this is done to include max_num in output.
    }else{
        low_num=max_num+1;// this is done to include max_num in output.
        hi_num=min_num;
    }
    srand(time(NULL));
    result = (rand()%(hi_num-low_num))+low_num;
    return result;
}
//##########################################################################################


typedef struct part
{
   char * value[500];

}part;

char *  GenarateToken()
{
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    //printf("now: %d-%d-%d %d:%d:%d\n%d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec, tm.tm_isdst);

    int i;
    char randstuff[50] = {'6','t','9','1', '2', '3', '4','5','6', '7', '8', '9','a','b', 'c', 'd', 'f','g','h', 'i', 'j', 'k','l','m','n','l','p','r','i','z','x','t','9','1', '2', '3', '4','5','6', '7', '8', '9','a','b', 'c', 'd', 'f','g','h', 'i', 'j', 'k','l','m','n','l','p','r','i','z','x'};
    char token[25];

    for(i = 0; i <= 25; i++)
    {
        token[i] = randstuff[rand() % 50];
    }

    return token;
}

char * buildCmdSelectLogin(char *value)
{
    int i, j =0,c = 0;
    char sqlQuery[500];
    char * pch;
    char newValue[strlen(value)];

	for(i=11; i<= strlen(value) ; i++){
        newValue[j] = value[i];
        j++;
	}
	int number_of_values = (count_characters(value, ':') * 2);

    part fieldsValues[number_of_values];

    pch = strtok (newValue,":,");
    while (pch != NULL)    {
        strcpy(fieldsValues[c].value, pch);
        pch = strtok (NULL, ":,");
        c++;
    }

    strcpy(sqlQuery, "SELECT Name, Password, id FROM User WHERE Email =  '");
    remove_all_chars(fieldsValues[1].value, '"');
    remove_all_chars(fieldsValues[3].value, '"');
    remove_all_chars(fieldsValues[3].value, '\\');
    remove_all_chars(fieldsValues[3].value, '}');

    strcat(sqlQuery, fieldsValues[1].value);
    strcpy(password, fieldsValues[3].value);
    return strcat(sqlQuery, "'");

}

char * buildCmdInsert(char *value, char *table)
{
    int i, j =0;

    char newValue[strlen(value)];

	for(i=11; i<= strlen(value) ; i++)
	{
        newValue[j] = value[i];
        j++;
	}

	remove_all_chars(newValue, '}');
	remove_all_chars(newValue, '\\');

	int number_of_values = (count_characters(value, ':') * 2);

    part fieldsValues[number_of_values];

    char * pch;
    int c = 0;

    pch = strtok (newValue,":,");
    while (pch != NULL)
    {

        strcpy(fieldsValues[c].value, pch);
        pch = strtok (NULL, ":,");

        c++;
    }

     char fields[strlen(value)];
     char values[strlen(value)];
     char sqlInsert[strlen(value) + 100];

     strcpy(fields, "(");
     strcpy(values, "(");

     strcpy(sqlInsert, "INSERT INTO  ");
     strcat(sqlInsert, table);
     strcat(sqlInsert, " ");

     int isFieldInvalid = 1;

     for(i = 0; i < number_of_values; i++)
     {
         if (strstr(fieldsValues[i].value, "$$hashKey") != NULL)
            isFieldInvalid = 0;

         if(i % 2 == 0 && isFieldInvalid)
         {
            strcat(fields, fieldsValues[i].value);
            strcat(fields, ",");
         }
         else if(i % 2 == 1)
         {
             if(isFieldInvalid)
             {
                 strcat(values, fieldsValues[i].value);
                 strcat(values, ",");
             }
             else
             {
                 isFieldInvalid= 1;
             }
         }
     }

	remove_all_chars(fields, '"'); // REMOVE ASPAS DOS CAMPOS

    fields[strlen(fields)-1] = '\0';   //|
    values[strlen(values)-1] = '\0'; //|  REMOVE ULTIMA VIRGULA DOS CAMPOS E DOS VALORES

    strcat(fields, ")");  //
    strcat(values, ")"); // FECHA VALORES E CAMPOS

    strcat(sqlInsert, fields);      //|
    strcat(sqlInsert, " VALUES ");  //| MONTA SQL INSERT
    strcat(sqlInsert, values);     //|

    return sqlInsert;
}

char * buildCmdUpdate(char *value, char *table)
{
    int i, j =0;

    char newValue[strlen(value)];

	for(i=10; i<= strlen(value) ; i++)
	{
        newValue[j] = value[i];
        j++;
	}

	remove_all_chars(newValue, '}');

	int number_of_values = (count_characters(value, ':') * 2);

    part fieldsValues[number_of_values];

    char * pch;
    int c = 0;

    pch = strtok (newValue,":,");
    while (pch != NULL)
    {

        strcpy(fieldsValues[c].value, pch);
        pch = strtok (NULL, ":,");

        c++;
    }

     char fields[strlen(value)];
     char values[strlen(value)];
     char sqlUpdate[strlen(value) + 100];
     char predicate[50];

     strcpy(fields, "");
     strcpy(values, "");

     strcpy(sqlUpdate, "UPDATE ");
     strcat(sqlUpdate, table);
     strcat(sqlUpdate, " SET ");
     strcpy(predicate, " WHERE ID = ");

     for(i = 0; i < number_of_values; i++)
     {

         if(i % 2 == 0)
         {
            if(i != 0)
            {
                remove_all_chars(fieldsValues[i].value, '"');
                strcat(fields, fieldsValues[i].value);
                strcat(fields, " = ");
            }
         }
         else
         {
            if(i == 1)
            {
                remove_all_chars(fieldsValues[i].value, '"');
                strcat(predicate, fieldsValues[i].value);
            }
            else
            {
                strcat(fields, fieldsValues[i].value);
                strcat(fields, ",");
            }
         }

     }

    fields[strlen(fields)-1] = '\0';
    strcat(sqlUpdate, fields);
    strcat(sqlUpdate, predicate);

    return sqlUpdate;
}

char * buildCmdDelete(char *value, char *table)
{
    int i, j =0;

    char newValue[strlen(value)];

	for(i=10; i<= strlen(value)  ; i++)
	{
        newValue[j] = value[i];
        j++;
	}

    char sqlDelete[strlen(value) + 50];

     strcpy(sqlDelete, "DELETE FROM  ");
     strcat(sqlDelete, table);
     strcat(sqlDelete, " WHERE ID = ");
     strcat(sqlDelete,newValue);

    return sqlDelete;
}

char * buildCmdSelect(char *field, char *value, char *table)
{

    char sqlSelect[500];

     strcpy(sqlSelect, "SELECT * FROM  ");
     strcat(sqlSelect, table);
     strcat(sqlSelect, " WHERE ");
     strcat(sqlSelect, field);
     strcat(sqlSelect, " = ");
     strcat(sqlSelect, value);

    return sqlSelect;
}

void CreateDeck(char *str)
{
    char *result = buildCmdInsert(str , "Deck");

    printf("\n\n%s\n", result);

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

void CreateWord(char *str)
{
    char *result = buildCmdInsert(str , "Word");

    printf("\n\n%s\n", result);

    return 0;
}

void CreateUser(char *str)
{
    char *result = buildCmdInsert(str , "User");

    printf("666");

    return 0;
}

void CreateContact(char *str)
{
    char *result = buildCmdInsert(str , "Contact");

    printf("\n\n%s\n", result);

    return 0;
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
       CreateWord(str);
    }
    else if(str[4] == 'u' && str[5] == 's' && str[6] == 'e' && str[7] == 'r' && str[8] == '/')
    {
       CreateUser(str);
    }
    else if(str[4] == 'c' && str[5] == 'o' && str[6] == 'n' && str[7] == 't' && str[8] == '/')
    {
       CreateContact(str);
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

void Login(char *str)
{
    char * temp = buildCmdSelectLogin(str);
    char cmdSelect[500];
    int i;
    char user_id[20];

    for(i= 0; i <= strlen(temp) ; i++)
        cmdSelect[i] = temp[i];

    //ROTAS DECK/WROD/USER
    if(str[4] == 'l' && str[5] == 'o' && str[6] == 'g' && str[7] == 'i' && str[8] == '/')
    {

        MYSQL *con = mysql_init(NULL);

        if (mysql_real_connect(con, "127.0.0.1", "root", "lexos2009","spacedrepetition", 0, NULL, 0) == NULL) finish_with_error(con);

        if (mysql_query(con,cmdSelect))
            finish_with_error(con);


        MYSQL_RES *result = mysql_store_result(con);

        if (result == NULL)  finish_with_error(con);

        int num_fields = mysql_num_fields(result);
        int i, j;
        MYSQL_ROW row;

        if(mysql_num_rows(result) <= 0)
        {
            printf("access denied 0x542147");
            return;
        }

        while ((row = mysql_fetch_row(result)))
        {
          for(i = 0; i < num_fields; i++)
          {
              if(strlen(row[1]) != strlen(password))
              {
                  printf("access denied 0x14234");
                  return;
              }

              for(j=0; j< strlen(row[1]); j++)
                  if(row[1][j] != password[j])
                  {
                      printf("access denied 0x54562");
                      return;
                  }

               strcpy(user_id, row[2]);
               break;
          }

        }

        char cmdDelete[200] = "DELETE FROM AccessUser WHERE user_id = ";
        strcat(cmdDelete,user_id);

        if (mysql_query(con, cmdDelete)) finish_with_error(con);


        char * tokenTemp = GenarateToken();
        char token[50];

        for(i= 0; i <= strlen(tokenTemp) ; i++)
            token[i] = tokenTemp[i];

        remove_all_chars(token, '\'');

        char cmdInsert[1000] = "\n\nINSERT INTO AccessUser (Token, CreatedOn, User_Id) VALUES ('";
        strcat(cmdInsert,token);
        strcat(cmdInsert,"',");
        strcat(cmdInsert,"NOW(), ");
        strcat(cmdInsert,user_id);
        strcat(cmdInsert,")");

        if (mysql_query(con, cmdInsert)) finish_with_error(con);


        printf("\n\Without erros :)  %s", token);

         mysql_free_result(result);
        mysql_close(con);

    }
    else
    {
        printf("Error invalid argument! 00009");
        return 0;
    }
}

int main(int argc, char *argv[])
{
    // remember to take out some characters

    printf("Content-type: text/plain\n\n");

//######################### Split parameters to get token and data ######################### ######################### #########################
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

//#####################################################################################################################################################################

    if(strlen(current_token) > 0)
    {
        //validar token
    }
    else
    {
        if((strstr(argv[1], "log/logi/") == NULL) &&  (strstr(argv[1], "cre/user/") == NULL))
        {
            printf("Access denied 0x45678558")
            return;
        }

    }

    return;

    //SOME TESTS
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
