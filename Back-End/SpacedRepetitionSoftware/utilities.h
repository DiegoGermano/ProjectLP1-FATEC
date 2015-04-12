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
