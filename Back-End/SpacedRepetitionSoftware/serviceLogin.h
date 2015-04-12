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
