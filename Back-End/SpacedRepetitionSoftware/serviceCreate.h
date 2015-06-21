
void CreateDeck(char *str)
{
    char *cmdInsert = buildCmdInsert(str ,"Deck");

    printf("DECKCREATED %s", cmdInsert);
    MYSQL *con = OpenConnection();

    ExecCommand(con, cmdInsert);
}

void CreateHistory(char *str)
{
    char *cmdInsert = buildCmdInsert(str , "historydeck");

    printf("HISTORYDECKCREATED %s", cmdInsert);

    MYSQL *con = OpenConnection();

    ExecCommand(con, cmdInsert);
}

void CreateWord(char *str)
{
    char *cmdInsert = buildCmdInsert(str , "Word");

    MYSQL *con = OpenConnection();

    ExecCommand(con, cmdInsert);

    printf("WORDCREATED");

    return 0;
}

void CreateUser(char *str)
{
    char *cmdInsert = buildCmdInsert(str , "User");
    MYSQL *con = OpenConnection();

    ExecCommand(con, cmdInsert);

    MYSQL_RES *result = ExecQueryCommand(con, "SELECT MAX(Id) from user");

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

    return 0;
}

void CreateContact(char *str)
{
    char *cmdInsert = buildCmdInsert(str , "Contact");

    MYSQL *con = OpenConnection();

    ExecCommand(con, cmdInsert);

    printf("CONTACTREGISTERED");

    return 0;
}


void Create(char *str)
{
    //ROTAS DECK/WROD/USER
    if(str[4] == 'd' && str[5] == 'e' && str[6] == 'c' && str[7] == 'k' && str[8] == '/')
    {
       CreateDeck(str);
    }
    else if(str[4] == 's' && str[5] == 't' && str[6] == 'u' && str[7] == 'y' && str[8] == '/')
    {
       CreateHistory(str);
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
