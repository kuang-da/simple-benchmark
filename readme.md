# R Benchmarking Project

This project provides a simple and easy way to benchmark R code performance on different machines using a Docker container or Singularity.

## Usage

Please use the following instructions to run the benchmark on the computing nodes. 

- On kimclust, one need to use Singularity and it is recommended to use Docker on personable devices. 
- `<node-id>` is the name of the machine. For kimclust, please using one of the following. 
    - kimclust35, kimclust36, kimclust37
    - kimclust50, kimclust51, kimclust52, kimclust53, kimclust54, kimclust55
    - Tips: node id can be checked by `hostname -s`.
- You can also use your own `<node-id>` represent your presonable device. 

### Singularity

1. Pull the repository from GitHub.
1. Pull the Docker image as a Singularity image: `singularity pull docker://kuangda/simple-benchmark`.
1. Run the Singularity container and bind your current working directory as a volume: `singularity exec simple-benchmark_latest.sif Rscript /benchmark.R <node-id> <sqlite-file> <debug-flg>`.

Example command for R:

```bash
singularity exec simple-benchmark_latest.sif Rscript simple-benchmark/benchmark.R $(hostname -s) /home/kuangda/simple-benchmark-test/benchmark_results.sqlite False
```

Example command for C:
```
# Compile
singularity exec simple-benchmark_latest.sif bash
Singularity> gcc -o benchmark benchmark.c -lm -lsqlite3

# Run: ./benchmark NODE_ID SQL_FILE DEBUG_FLAG
./benchmark $(hostname -s) /home/kuangda/simple-benchmark-test/benchmark_results.sqlite FALSE
```
### Docker

1. Pull the Docker image from DockerHub: `docker pull kuangda/simple-benchmark`
2. Run the Docker container and mount your current working directory as a volume: `docker run --rm kuangda/simple-benchmark Rscript /benchmark.R <node-id>`

## Output

The summary of the benchmark results will be printed in the terminal. The result will also write to the sqlite file (`benchmark_results.sqlite`).
