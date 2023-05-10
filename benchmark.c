#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <sqlite3.h>
#include <string.h>

void matrix_multiplication() {
    int n = 100;
    double a[n][n], b[n][n], result[n][n];
    
    srand(time(0));
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < n; ++j) {
            a[i][j] = (double)rand() / RAND_MAX;
            b[i][j] = (double)rand() / RAND_MAX;
            result[i][j] = 0;
        }
    }

    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < n; ++j) {
            for(int k = 0; k < n; ++k) {
                result[i][j] += a[i][k] * b[k][j];
            }
        }
    }
}

void sum_of_squares_iterative(int n) {
    long long sum_of_squares = 0;
    for (int i = 1; i <= n; i++) {
        sum_of_squares += i * i;
    }
}

int main(int argc, char *argv[]) {
    // Get command line arguments
    char *node_id = argv[1];
    char *sql_file = argv[2];
    int debug_flag = atoi(argv[3]);

    if (debug_flag) {
        node_id = "Thelio";
        sql_file = "benchmark_results.sqlite";
    }

    printf("Start benchmarking...\n");
    printf("node_id: %s\n", node_id);
    printf("sql_file: %s\n", sql_file);

    int times = 100;
    struct timespec start, end;
    double elapsed_mat_mul, elapsed_sum_of_square;

    // Benchmark matrix multiplication
    clock_gettime(CLOCK_MONOTONIC, &start);
    for (int i = 0; i < times; i++) {
        matrix_multiplication();
    }
    clock_gettime(CLOCK_MONOTONIC, &end);
    // Elaps in miliseconds
    elapsed_mat_mul = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1000000000.0 * 1000;

    // Benchmark sum of squares iterative
    clock_gettime(CLOCK_MONOTONIC, &start);
    for (int i = 0; i < times; i++) {
        sum_of_squares_iterative(1000000);
    }
    clock_gettime(CLOCK_MONOTONIC, &end);
    // Elaps in miliseconds
    elapsed_sum_of_square = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1000000000.0 * 1000;

    // Calculate the overall time
    double elapsed_total = elapsed_mat_mul + elapsed_sum_of_square;

    // Open the SQLite connection
    sqlite3 *db;
    int rc = sqlite3_open(sql_file, &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    // Create the C_benchmark_result table if it doesn't exist
    char *sql = "CREATE TABLE IF NOT EXISTS C_benchmark_result ("
                "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                "node_id TEXT, "
                "expr TEXT, "
                "median REAL, "
                "neval INTEGER, "
                "timestamp TEXT);";
    char *err_msg = 0;
    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
    }

    // Insert the benchmark results into the table, including the overall time
    char insert_sql[384];
    snprintf(insert_sql, sizeof(insert_sql), "INSERT INTO C_benchmark_result (node_id, expr, median, neval, timestamp) "
                                             "VALUES ('%s', 'mat_mul', %f, %d, datetime('now', 'localtime')), "
                                             "('%s', 'sum_of_square', %f, %d, datetime('now', 'localtime')), "
                                             "('%s', 'total', %f, %d, datetime('now', 'localtime'));",
             node_id, elapsed_mat_mul, times, node_id, elapsed_sum_of_square, times, node_id, elapsed_total, times);
    rc = sqlite3_exec(db, insert_sql, 0, 0, &err_msg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
    }

    // Print the summary of the benchmark results
    printf("\nBenchmark results:\n");
    printf("Node ID: %s\n", node_id);
    printf("Matrix Multiplication: Median Time (ms) = %f, Iterations = %d\n", elapsed_mat_mul, times);
    printf("Sum of Squares Iterative: Median Time (ms) = %f, Iterations = %d\n", elapsed_sum_of_square, times);
    printf("Total: Median Time (ms) = %f, Iterations = %d\n", elapsed_total, times);

    // Close the SQLite connection
    sqlite3_close(db);

    return 0;
}
