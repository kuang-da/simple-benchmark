# Benchmark Result (ms)

MacBook with Apple Silicon in x86 container
```
❯ docker run --rm  kuangda/simple-benchmark
WARNING: The requested image's platform (linux/amd64) does not match the detected host platform (linux/arm64/v8) and no specific platform was requested
             expr      min       lq     mean  median       uq      max neval
1 test_function() 1348.919 1364.993 1380.693 1372.19 1388.345 1632.335   100
```

MacBook with Apple Silicon
```
> print(summary(benchmark_results))
             expr      min       lq     mean  median      uq      max neval
1 test_function() 147.7881 150.7482 155.9405 152.451 163.079 182.8134   100
```

kimclust 35
```
$ singularity exec simple-benchmark_latest.sif Rscript /benchmark.R

             expr      min       lq     mean   median       uq      max neval
1 test_function() 299.1577 305.2054 324.9583 309.6009 353.7972 382.4457   100
```

kimclust36
```
$ singularity exec simple-benchmark_latest.sif Rscript /benchmark.R

             expr      min       lq     mean   median       uq     max neval
1 test_function() 300.3512 303.6467 321.3429 306.8774 348.6059 386.408   100
```

kimclust37
```
$ singularity exec simple-benchmark_latest.sif Rscript /benchmark.R
             expr     min       lq     mean   median       uq     max neval
1 test_function() 296.536 305.1491 322.0647 307.0868 351.2231 380.037   100
```

kimclust50
```
$ singularity exec simple-benchmark_latest.sif Rscript /benchmark.R
             expr      min       lq     mean   median       uq      max neval
1 test_function() 432.3623 440.0316 492.6002 481.7329 521.3995 649.4701   100
```

kimclust51: NA

kimclust52
```
$ singularity exec simple-benchmark_latest.sif Rscript /benchmark.R
             expr      min       lq     mean   median       uq      max neval
1 test_function() 614.1188 617.9856 636.3686 621.5955 651.3181 769.4068   100
```

kimclust53
```
$ singularity exec simple-benchmark_latest.sif Rscript /benchmark.R

             expr      min       lq     mean   median       uq      max neval
1 test_function() 605.2142 610.1963 628.1052 615.7402 643.9346 763.9945   100
```

kimclust54
```
$ singularity exec simple-benchmark_latest.sif Rscript /benchmark.R
             expr      min       lq     mean   median      uq      max neval
1 test_function() 344.3678 596.9761 619.6061 606.8272 649.238 933.9229   100
```

kimclust55: NA