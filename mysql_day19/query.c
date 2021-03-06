#include <func.h>

int main(int argc, char ** argv)
{
    ARGS_CHECK(argc, 2);

    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    char* server = "localhost";
    char* user = "root";
    char* password = "456456";
    char* database = "Course";//the database which will be accessed
    char query[300] = "select * from ";
    sprintf(query, "%s%s", query, argv[1]);
    //strcpy(query, "select * from student");
    puts(query);
    int t, r;
    conn = mysql_init(NULL);
    if (!mysql_real_connect \
        (conn, server, user, password, database, 0, NULL, 0)) {
            printf("Error connecting to database:%s\n", mysql_error(conn));
            return -1;
    } else {
        printf("Connected...\n");
    }
    t = mysql_query(conn, query);
    if (t)
    {
        printf("Error making query:%s\n", mysql_error(conn));
    } else {
        //printf("Query made...\n");
        res = mysql_use_result(conn);
        if (res) {
            while (NULL != (row = mysql_fetch_row(res))) {
                //printf("num = %d\n", mysql_num_fields(res));//the num of col
                for (t = 0; t < mysql_num_fields(res); t++) {
                    printf("%8s", row[t]);
                }
                printf("\n");
            }
        } else {
            printf("Don't find data\n");
        }
        mysql_free_result(res);
    }
    mysql_close(conn);

    return 0;
}

