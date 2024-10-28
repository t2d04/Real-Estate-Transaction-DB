#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include "mysql.h"

#pragma comment(lib, "libmysql.lib")

const char* host = "localhost"; // change if necessary
const char* user = "root";      // change if necessary
const char* pw = "#wldbsEl0204";       // change if necessary
const char* db = "proj";      // 데이터베이스 이름

#define MAX_LEN 13000

// menu를 표시하는 함수
void menu();
// 쿼리를 실행하게 하는 함수
void execute_query(MYSQL* connection, const char* query);

// 사용자의 input을 관리하는 함수
void input(MYSQL* connection);

// 각 쿼리 및 서브쿼리를 실행하는 함수
// 서브쿼리에 대해 추가적인 함수를 두지 않았음 (서브쿼리도 쿼리함수에서 실행)
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
        printf("Error: Query failed: %s\n", mysql_error(connection)); // 오류 내용 출력
    }
}

// 사용자로부터 input을 받아 그에 맞게 쿼리 함수를 실행시킴
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

// 1. 마포구 매물 찾기
// 1-1. 그 중에서 10억과 15억 사이인 매물 찾기
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
        "WHERE district_g = '마포구'";
    execute_query(connection, query1);

    if (FLAG1) {
        const char* query1_1 = "SELECT estate_name, district_g, district_d, street, building_num "
            "FROM ("
            "    SELECT E.* "
            "    FROM Estate E "
            "    LEFT JOIN Contract C ON E.post_ID = C.post_ID "
            "    WHERE C.post_ID IS NULL"
            ") AS Temp "
            "WHERE district_g = '마포구' "
            "AND p_lump BETWEEN 100000 AND 150000";
        execute_query(connection, query1_1);
    }
}

// 2. 8학군에 있는 매물 찾기
// 2-1. 그 중에서 침실 4개, 화장실 2개 이상인 매물 찾기
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
        const char* query1_1 = "SELECT estate_name, district_g, district_d, street, building_num, p_lump FROM Estate WHERE district_g = '마포구' AND p_lump BETWEEN 100000 AND 150000";
        execute_query(connection, query1_1);
    }
}

// 3. 2022년에 가장 높은 수익을 올린 공인중개사 찾기
// 3-1. 2023년에 가장 높은 수익을 올린 순으로 k명의 공인중개사 찾기
// 3-2. 2021년에 가장 낮은 수익을 올린 하위 10% 공인중개사 찾기
void Q3(MYSQL* connection) {


}

// 4. 각 공인중개사 별로 2022년에 성사시킨 매물의 평균금액, 시장에 있었던 기간 찾기
// 4-1. 각 공인중개사 별로 2023년에 판매한 가장 비싼 매물의 가격 찾기
// 4-2. 각 공인중개사 별로 매물이 시장에 가장 오래 있었던 기간 찾기
void Q4(MYSQL* connection) {


}

// 5. 가장 비싼 studio, one-bed, multi-bed apt, detached의 사진 각각 보여주기
void Q5(MYSQL* connection) {


}

// 6. 이미 판매된 매물의 가격, 구매자, 공인중개사, 날짜 찾기
void Q6(MYSQL* connection) {


}

// 7. 새로운 공인중개사를 데이터베이스에 추가하기
void Q7(MYSQL* connection) {

    printf("**************************\n");
    

}

