#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h> 
#include <string>
#include <iostream>
#include <cstring>
#include "helpers.h"

using namespace std;

static int callback(void *NotUsed, int argc, char **argv, char **azColName){
    int i;
    for(i=0; i<argc; i++)
    {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}

/*char* myToLower(char *temp)
{
    int x;
    for(x = 0; x < strlen(temp); x++)
    {
        temp[x] = tolower(temp[x]);
    }
    return temp;
}*/

int main(int argc, char* argv[])
{
    char *command = (char*)malloc(sizeof(char) * 1000);

    while(true)
    {
        int x = 0;
        cout<<"Enter a command. Supported commands are:\nCreate"<<endl<<endl;
        cin>>command;

        helpers *helper = new helpers();
        //command = helper->myToLower(command);
        helper->myToLower(command);
        sqlite3 *db;
        
        if (strcmp(command, "create") == 0)
        {
            char *zErrMsg = 0;
            int  rc;
            char *sql = (char*)malloc(sizeof(char) * 1000);
            char *input = (char*)malloc(sizeof(char) * 100);

            /* Open database */
            rc = sqlite3_open("test.db", &db);
            if( rc )
            {
                fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
                return(0);
            }else
            {
                fprintf(stdout, "Opened database successfully\n");
            }

            cout<<"Enter a name for the table"<<endl;
            cin >> input;

            /* Create SQL statement */
            strcpy(sql, "CREATE TABLE ");
            strcat(sql, input);
            cout<<sql<<endl;

            strcat(sql, " (ID INT PRIMARY KEY  NOT NULL," \
                    "NAME           TEXT       NOT NULL," \
                    "DIFFICULTY     INT        NOT NULL,"\
                    "TIME           INT,       NOT NULL"\
                    "INSTRUCTIONS   CHAR[5000] NOT NULL);");

            /* Execute SQL statement */
            rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
            if( rc != SQLITE_OK )
            {
                fprintf(stderr, "SQL error: %s\n", zErrMsg);
                sqlite3_free(zErrMsg);
            }else
            {
                fprintf(stdout, "Table created successfully\n");
            }

            free(input);
            free(sql);

        }

        else if(strcmp(command,"close") == 0 || strcmp(command,"exit") == 0 || strcmp(command,"quit") == 0)
        {
//            sqlite3_close(db);
            return 0;
        } 
        else
            cout<<"You entered ["<<command<<"] which is not currently a valid command"<<endl;

    }

}
