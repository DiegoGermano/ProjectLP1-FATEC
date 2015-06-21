void DeleteDeck(char *str)
{
   int i, j =0;

    char newValue[100], Query[100];

	for(i=9; i<= strlen(str)  ; i++)
	{
        newValue[j] = str[i];
        j++;
	}

    sprintf(Query,"DELETE FROM Deck where id = (%s)",newValue) ;

    printf("DECKDELETED = %s", Query);

    MYSQL *con = OpenConnection();

    ExecCommand(con, Query);
}

void Delete(char *str)
{
    //ROTAS DECK/WROD/USER
    if(str[4] == 'd' && str[5] == 'e' && str[6] == 'c' && str[7] == 'k' && str[8] == '/')
    {
        DeleteDeck(str);
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
