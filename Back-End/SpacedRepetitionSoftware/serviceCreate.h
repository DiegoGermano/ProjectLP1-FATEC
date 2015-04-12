
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
