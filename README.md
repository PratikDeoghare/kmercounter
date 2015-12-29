# kmercounter
An implementation of SpaceSaving algorithm and StreamSummary data structure [1]. 

This can be used to count the most frequent k-mers from a fastq file. With few modifications this can be used to count frequent things in any stream of things (if you can check those things for equality). Valgrind shows no memory leaks but the implementation can be improved. 

The StreamSummary implementation has the same time and space complexity as in the paper. 

[1] Metwally, Ahmed, Divyakant Agrawal, and Amr El Abbadi. "Efficient computation of frequent and top-k elements in data streams." Database Theory-ICDT 2005. Springer Berlin Heidelberg, 2005. 398-412.

