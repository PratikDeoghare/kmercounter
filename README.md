# kmercounter
An implementation of SpaceSaving algorithm and StreamSummary data structure [1]. 

This can be used to count the most frequent k-mers from a fastq file. With few modifications this can be used to count frequent things in any stream of things (if you can check those things for equality). Valgrind shows no memory leaks but the implementation can be improved. 

The StreamSummary implementation has the same time and space complexity as in the paper. 



To build the program:

     make 

Usage: 

    ./kmercounter <filename.fastq> <kmer length> <top n> [number of counters m]

To get 25 most frequent 30-mers from file.fastq  

    ./kmercounter file.fastq 30 25 
    

To improve accuracy of the results try bigger values of m. Default value of m =
70000. Program should work fine for much smaller values of m. 

To improve space complexity try with smaller values of m. 


[1] Metwally, Ahmed, Divyakant Agrawal, and Amr El Abbadi. "Efficient computation of frequent and top-k elements in data streams." Database Theory-ICDT 2005. Springer Berlin Heidelberg, 2005. 398-412.

