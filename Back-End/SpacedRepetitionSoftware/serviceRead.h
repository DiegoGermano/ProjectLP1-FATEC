

void ReadDecksFromUser()
{
  char cmdSelect[150] = "select CONCAT(\"[\", GROUP_CONCAT(Id, deck, Language,amountWord, amountStudy,  daysLastStudy, PercentYield), \"]\") as Json from view_deck";

    MYSQL *con = OpenConnection();
    MYSQL_RES *result = ExecQueryCommand(con, cmdSelect);

    int num_fields = mysql_num_fields(result);
    int i, j;
    MYSQL_ROW row;

    while ((row = mysql_fetch_row(result)))
    {
      for(i = 0; i < num_fields; i++)
      {
          printf("%s",row[0]);
      }
    }

}


void Read(char *str)
{
    //ROTAS DECK/WROD/USER
    if(str[4] == 'd' && str[5] == 'e' && str[6] == 'c' && str[7] == 'k' && str[8] == '/')
    {
       ReadDecksFromUser();
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
