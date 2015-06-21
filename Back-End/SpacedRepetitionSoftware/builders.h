
char password[500];


typedef struct part
{
   char * value[500];

}part;
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

	for(i=9; i<= strlen(value)  ; i++)
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


