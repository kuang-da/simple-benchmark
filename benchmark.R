# Load necessary libraries
library(microbenchmark)
library(DBI)

TABLE_NAME <- "R_benchmark_results"

# Get command line arguments
args <- commandArgs(trailingOnly = TRUE)
node_id <- args[1]
sqlfile_path <- args[2]
debug_flg <- as.logical(args[3])
if (debug_flg) {
  node_id <- "Thelio"
  sqlfile_path <- "benchmark_results.sqlite"
}
print("Start benchmarking...")
print(paste("node_id:", node_id))
print(paste("sqlfile_path:", sqlfile_path))

# Define the test function
test_function_matrix_mul <- function() {
  set.seed(42)
  a <- matrix(runif(10000), nrow = 100, ncol = 100)
  b <- matrix(runif(10000), nrow = 100, ncol = 100)
  a %*% b
}

test_function_iterative <- function(n=10^6) {
  sum_of_squares <- 0
  for (i in 1:n) {
    sum_of_squares <- sum_of_squares + i^2
  }
}

test_function_lm <- function() {
  set.seed(42)
  n <- 10000
  p <- 100
  X <- matrix(rnorm(n*p), n, p)
  y <- X %*% rnorm(p) + rnorm(100)
  lm(y ~ X + 0)
}

r_test <- function() {
  test_function_matrix_mul()
  test_function_iterative()
  test_function_lm()
}

benchmark_results <- microbenchmark(r_test(), times = 100, unit = "ms")

# Add node_id and timestamp to res_df
res_df <- as.data.frame(summary(benchmark_results))
res_df$node_id <- node_id
res_df$timestamp <- format(Sys.time(), format = "%Y-%m-%d %H:%M:%S")

# Move node_id to the first column
res_df <- res_df[, c("node_id", "expr", "median", "neval", "min", "lq", "mean", "uq", "max", "timestamp")]

# Save benchmark results to SQLite file
conn <- dbConnect(RSQLite::SQLite(), dbname = sqlfile_path)

# Check if the "benchmark_results" table exists; if not, create it
if (!dbExistsTable(conn, TABLE_NAME)) {
  dbWriteTable(conn, TABLE_NAME, res_df, overwrite = TRUE)
} else {
  dbAppendTable(conn, TABLE_NAME, res_df)
}

# Close the SQLite connection
dbDisconnect(conn)

# Print the summary of the benchmark results
print(res_df)
