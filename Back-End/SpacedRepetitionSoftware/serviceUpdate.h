void UpdateDeck(char *str)
{
    char *cmdUpdate = buildCmdUpdate(str , "Deck");

    printf("DECKUPDATED %s", cmdUpdate);
    MYSQL *con = OpenConnection();

    ExecCommand(con, cmdUpdate);
}


void Update(char *str)
{
    //ROTAS DECK/WROD/USER
    if(str[4] == 'd' && str[5] == 'e' && str[6] == 'c' && str[7] == 'k' && str[8] == '/')
    {
       UpdateDeck(str);
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
