# R Benchmarking Project

This project provides a simple and easy way to benchmark R code performance on different machines using a Docker container or Singularity.

## Usage

### Docker

1. Pull the Docker image from DockerHub: `docker pull kuangda/simple-benchmark`
2. Run the Docker container and mount your current working directory as a volume: `docker run --rm kuangda/simple-benchmark`

### Singularity

1. Pull the Docker image as a Singularity image: `singularity pull docker://kuangda/simple-benchmark`
2. Run the Singularity container and bind your current working directory as a volume: `singularity exec simple-benchmark_latest.sif Rscript /benchmark.R`

## Output

The summary of the benchmark results will be printed in the terminal.
