# Benchmarking Project

This project offers a straightforward method to benchmark computational performance across different machines using either a Docker container or Singularity.

## Usage

Follow the instructions below to execute the benchmark on your computing nodes. 

- On kimclust, you should use Singularity. On personal devices, it's recommended to use Docker. 
- Replace `<node-id>` with the name of your machine. If you're using kimclust, please use one of the following: 
  - kimclust35, kimclust36, kimclust37
  - kimclust50, kimclust51 (NA), kimclust52, kimclust53, kimclust54, kimclust55 (NA)
- Tip: You can check your node id by running `hostname -s`.
- On personal devices, you can use your own `<node-id>` to represent your device. 
  - For instance, `Apple-silicon`, `Apple-silicon-rosetta2`.

### Singularity

#### Preparation
1. Clone the repository from GitHub.
2. Convert the Docker image to a Singularity image: `singularity pull docker://kuangda/simple-benchmark`.

#### Running the R Test
1. Execute the Singularity container `singularity exec simple-benchmark_latest.sif Rscript /benchmark.R <node-id> <sqlite-file> <debug-flg>`.
   - By default Singularity bind your current working directory as a volume.

Example command for R:

```bash
singularity exec simple-benchmark_latest.sif Rscript simple-benchmark/benchmark.R $(hostname -s) /home/kuangda/simple-benchmark-test/benchmark_results.sqlite False
```

#### Running the C Test

Navigate to the test directory and compile the C code:

```bash
cd simple-benchmark-test/simple-benchmark
singularity exec simple-benchmark_latest.sif bash
Singularity> gcc -o benchmark benchmark.c -lm -lsqlite3
```

Then, execute the benchmark:

```bash
Singularity> ./benchmark $(hostname -s) /home/kuangda/simple-benchmark-test/benchmark_results.sqlite FALSE
```

### Docker

#### Preparation

1. Clone the repository from GitHub.
2. Pull the Docker image from DockerHub: `docker pull kuangda/simple-benchmark`

#### Running the R Test

1. Execute the Docker container and mount your current working directory as a volume: 

```bash
docker run --rm \
-v /Users/kuangda/Developer/1-projects/simple-benchmark:/simple-benchmark \
kuangda/simple-benchmark \
Rscript /benchmark.R <node_id> False
```

#### Running the C Test

```bash
docker run -it --rm \
-v /Users/kuangda/Developer/1-projects/simple-benchmark:/simple-benchmark \
kuangda/simple-benchmark \
bash

Singularity> cd /simple-benchmark
Singularity> gcc -o benchmark benchmark.c -lm -lsqlite3
Singularity> ./benchmark $(hostname -s) benchmark_results.sqlite FALSE
```

## Output

The summary of the benchmark results will be printed in the terminal and also written to a SQLite file (benchmark_results.sqlite).
