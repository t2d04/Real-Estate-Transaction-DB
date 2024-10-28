#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include "mysql.h"

#pragma comment(lib, "libmysql.lib")

const char* host = "localhost"; // change if necessary
const char* user = "root";      // change if necessary
const char* pw = "#wldbsEl0204";       // change if necessary
const char* db = "proj";      // �����ͺ��̽� �̸�

#define MAX_LEN 13000

// menu�� ǥ���ϴ� �Լ�
void menu();
// ������ �����ϰ� �ϴ� �Լ�
void execute_query(MYSQL* connection, const char* query);

// ������� input�� �����ϴ� �Լ�
void input(MYSQL* connection);

// �� ���� �� ���������� �����ϴ� �Լ�
// ���������� ���� �߰����� �Լ��� ���� �ʾ��� (���������� �����Լ����� ����)
void Q1(MYSQL* connection);
void Q2(MYSQL* connection);
void Q3(MYSQL* connection);
void Q4(MYSQL* connection);
void Q5(MYSQL* connection);
void Q6(MYSQL* connection);
void Q7(MYSQL* connection);

int main(void) {
    MYSQL* connection = NULL;
    MYSQL conn;
    FILE* fp = fopen("CRUD.txt", "rt");    // open CRUD file.
    char line[MAX_LEN];

    if (mysql_init(&conn) == NULL)
        printf("mysql_init() error!");

    connection = mysql_real_connect(&conn, host, user, pw, NULL, 3306, (const char*)NULL, 0);
    if (connection == NULL) {
        printf("%d ERROR : %s\n", mysql_errno(&conn), mysql_error(&conn));
        return 1;
    }
    else {
        printf("Connection Succeed\n\n");

        // Create and use the database
        while (fgets(line, sizeof(line), fp) != NULL) {
            if (!strcmp(line, "$$$\n")) // read lines from CRUD file, '$$$' separates CREATE / DELETE parts.
                break;
            mysql_query(connection, line);
        }

        if (mysql_select_db(&conn, db)) {
            printf("%d ERROR : %s\n", mysql_errno(&conn), mysql_error(&conn));
            return 1;
        }

        input(connection);

        // Clean up and close connection
        while (fgets(line, sizeof(line), fp) != NULL)
            mysql_query(connection, line); // these are DELETEs & DROPs.

        mysql_close(connection);
    }

    return 0;
}

// Function to print menu options
void menu() {
    printf("**************************\n");
    printf("    Select Query Types    \n");
    printf("1. TYPE 1:                \n");
    printf("2. TYPE 2:                \n");
    printf("3. TYPE 3:                \n");
    printf("4. TYPE 4:                \n");
    printf("5. TYPE 5:                \n");
    printf("6. TYPE 6:                \n");
    printf("7. TYPE 7:                \n");
    printf("0. TYPE 0: Quit           \n\n");
}

// Function to execute a query and print the result
void execute_query(MYSQL* connection, const char* query) {
    MYSQL_RES* sql_result;
    MYSQL_ROW sql_row;
    int state = mysql_query(connection, query);

    if (state == 0) {
        sql_result = mysql_store_result(connection);
        if (sql_result) {
            int num_fields = mysql_num_fields(sql_result);
            while ((sql_row = mysql_fetch_row(sql_result)) != NULL) {
                for (int i = 0; i < num_fields; i++) {
                    printf("%s\t", sql_row[i] ? sql_row[i] : "NULL");
                }
                printf("\n");
            }
            mysql_free_result(sql_result);
        }
        else {
            if (mysql_field_count(connection) != 0) {
                printf("Error: Invalid Result Set\n");
            }
        }
    }
    else {
        printf("Error: Query failed: %s\n", mysql_error(connection)); // ���� ���� ���
    }
}

// ����ڷκ��� input�� �޾� �׿� �°� ���� �Լ��� �����Ŵ
void input(MYSQL* connection) {
    int choice;

    while (1) {
        menu();
        printf("Enter your choice (0-7): ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
        case 1:
            Q1(connection);
            break;
        case 2:
            Q2(connection);
            break;
        case 3:
            Q3(connection);
            break;
        case 4:
            Q4(connection);
            break;
        case 5:
            Q5(connection);
            break;
        case 6:
            Q6(connection);
            break;
        case 7:
            Q7(connection);
            break;
        case 0:
            return;
        default:
            printf("Invalid choice. Please try again.\n");
        }
    }
}

// 1. ������ �Ź� ã��
// 1-1. �� �߿��� 10��� 15�� ������ �Ź� ã��
void Q1(MYSQL* connection) {

    int subchoice = 0;
    char FLAG1 = 0;

    printf("**************************\n");
    printf("    Select Query Types    \n");
    printf("1. TYPE 1-1:              \n\n");

    printf("Enter your choice: ");
    scanf("%d", &subchoice);
    getchar();

    if (subchoice == 1) {
        FLAG1 = 1;
    }

    const char* query1 = "SELECT estate_name, district_g, district_d, street, building_num "
        "FROM ("
        "    SELECT E.* "
        "    FROM Estate E "
        "    LEFT JOIN Contract C ON E.post_ID = C.post_ID "
        "    WHERE C.post_ID IS NULL"
        ") AS Temp "
        "WHERE district_g = '������'";
    execute_query(connection, query1);

    if (FLAG1) {
        const char* query1_1 = "SELECT estate_name, district_g, district_d, street, building_num "
            "FROM ("
            "    SELECT E.* "
            "    FROM Estate E "
            "    LEFT JOIN Contract C ON E.post_ID = C.post_ID "
            "    WHERE C.post_ID IS NULL"
            ") AS Temp "
            "WHERE district_g = '������' "
            "AND p_lump BETWEEN 100000 AND 150000";
        execute_query(connection, query1_1);
    }
}

// 2. 8�б��� �ִ� �Ź� ã��
// 2-1. �� �߿��� ħ�� 4��, ȭ��� 2�� �̻��� �Ź� ã��
void Q2(MYSQL* connection) {

    int subchoice = 0;
    char FLAG1 = 0;

    printf("**************************\n");
    printf("    Select Query Types    \n");
    printf("1. TYPE 2-1:              \n\n");

    printf("Enter your choice: ");
    scanf("%d", &subchoice);
    getchar();

    if (subchoice == 1) {
        FLAG1 = 1;
    }

    const char* query1 = "";
    execute_query(connection, query1);

    if (FLAG1) {
        const char* query1_1 = "SELECT estate_name, district_g, district_d, street, building_num, p_lump FROM Estate WHERE district_g = '������' AND p_lump BETWEEN 100000 AND 150000";
        execute_query(connection, query1_1);
    }
}

// 3. 2022�⿡ ���� ���� ������ �ø� �����߰��� ã��
// 3-1. 2023�⿡ ���� ���� ������ �ø� ������ k���� �����߰��� ã��
// 3-2. 2021�⿡ ���� ���� ������ �ø� ���� 10% �����߰��� ã��
void Q3(MYSQL* connection) {


}

// 4. �� �����߰��� ���� 2022�⿡ �����Ų �Ź��� ��ձݾ�, ���忡 �־��� �Ⱓ ã��
// 4-1. �� �����߰��� ���� 2023�⿡ �Ǹ��� ���� ��� �Ź��� ���� ã��
// 4-2. �� �����߰��� ���� �Ź��� ���忡 ���� ���� �־��� �Ⱓ ã��
void Q4(MYSQL* connection) {


}

// 5. ���� ��� studio, one-bed, multi-bed apt, detached�� ���� ���� �����ֱ�
void Q5(MYSQL* connection) {


}

// 6. �̹� �Ǹŵ� �Ź��� ����, ������, �����߰���, ��¥ ã��
void Q6(MYSQL* connection) {


}

// 7. ���ο� �����߰��縦 �����ͺ��̽��� �߰��ϱ�
void Q7(MYSQL* connection) {

    printf("**************************\n");
    

}

