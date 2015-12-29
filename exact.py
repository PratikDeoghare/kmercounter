

import sys 
from collections import Counter


def kmerize(line, k):
    for i in range(len(line) - k):
        yield line[i : i + k] 

def stream_kmers(filename, k):
    i = 0
    with open(filename) as f:
        for line in f:
            if i % 4 == 1:
                for kmer in kmerize(line, k):
                    yield kmer 
            i = i + 1


def main(): 
    filename = sys.argv[1] 
    k = int(sys.argv[2])
    n = int(sys.argv[3]) 

    c = Counter()

    for kmer in stream_kmers(filename, k):
        c.update([kmer]) 

    print len(c) 

    for kmer in c.most_common(n):
        print kmer 

if __name__ == '__main__':
    main()
