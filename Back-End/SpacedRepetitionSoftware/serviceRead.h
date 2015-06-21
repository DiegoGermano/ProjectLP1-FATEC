void ReadWordsFromDeck(char *str)
{
    int i, j=0;
    char newValue[strlen(str)];

    char cmdSelect[150] = "select CONCAT(\"[\",  GROUP_CONCAT(Id,Back, Front), \"]\") as Json from view_word where Deck_Id = ";

	for(i=9; i<= strlen(str) ; i++){
        newValue[j] = str[i];
        j++;
	}

	strcat(cmdSelect, newValue);

    MYSQL *con = OpenConnection();
    MYSQL_RES *result = ExecQueryCommand(con, cmdSelect);

    int num_fields = mysql_num_fields(result);
    MYSQL_ROW row;

    while ((row = mysql_fetch_row(result)))
    {
      for(i = 0; i < num_fields; i++)
      {
          printf("%s",row[0]);
      }
    }
}

void ReadDecksFromUser(char *str)
{
    int i, j=0;
    char newValue[strlen(str)];
    for(i=9; i<= strlen(str) ; i++){
        newValue[j] = str[i];
        j++;
	}

    char cmdSelect[250] = " select CONCAT(\"[\", GROUP_CONCAT(Id, deck, Language,amountWord, amountStudy,  daysLastStudy, PercentYield), \"]\") as Json from view_deck WHERE USER_id= ";

	strcat(cmdSelect, newValue);

    MYSQL *con = OpenConnection();
    MYSQL_RES *result = ExecQueryCommand(con, cmdSelect);

    int num_fields = mysql_num_fields(result);

    MYSQL_ROW row;

    while ((row = mysql_fetch_row(result)))
    {
      for(i = 0; i < num_fields; i++)
      {
          printf("%s",row[0]);
      }
    }

}

void ReadHistory(char *str)
{
    int i, j=0;
    char newValue[strlen(str)];

    char cmdSelect[250] = "select CONCAT(\"[\",  GROUP_CONCAT(date, value), \"]\") as Json from ( select  CONCAT('{\"date\":\\\"', DATE_FORMAT(CreatedOn,\"%d/%m\"), '\\\",') AS date, CONCAT('\"value\":',PercentYield, '}') as value, Deck_Id FROM  historydeck) as Cons where Deck_Id = ";

    for(i=9; i<= strlen(str) ; i++){
        newValue[j] = str[i];
        j++;
	}

	strcat(cmdSelect, newValue);


    MYSQL *con = OpenConnection();
    MYSQL_RES *result = ExecQueryCommand(con, cmdSelect);

    int num_fields = mysql_num_fields(result);
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
      ReadDecksFromUser(str);
    }
    else if(str[4] == 'w' && str[5] == 'o' && str[6] == 'r' && str[7] == 'd' && str[8] == '/')
    {
       ReadWordsFromDeck(str);
    }
    else if(str[4] == 'u' && str[5] == 's' && str[6] == 'e' && str[7] == 'r' && str[8] == '/')
    {
       printf("Read user");
    }
    else if(str[4] == 'h' && str[5] == 'i' && str[6] == 's' && str[7] == 't' && str[8] == '/')
    {
      ReadHistory(str);
    }
    else
    {
        printf("Error invalid argument! 00006 %s", str);
        return 0;
    }
}
