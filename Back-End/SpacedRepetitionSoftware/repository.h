MYSQL * OpenConnection()
{
    MYSQL *con = mysql_init(NULL);

    if (mysql_real_connect(con, "127.0.0.1", "root", "lexos2009","spacedrepetition", 0, NULL, 0) == NULL) finish_with_error(con);

    return con;
}

MYSQL_RES * ExecQueryCommand(MYSQL *con, char * command )
{
     if (mysql_query(con,command))
            finish_with_error(con);

        MYSQL_RES *result = mysql_store_result(con);

        if (result == NULL)  finish_with_error(con);

    return result;
}

void ExecCommand(MYSQL *con, char * command)
{
    if (mysql_query(con, command))
    {
         finish_with_error(con);
    }
}

