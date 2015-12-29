
topkmers: topkmers.cc stream_summary.o
	g++ -std=c++11 -O3 topkmers.cc stream_summary.o -o topkmers

stream_summary.o: stream_summary.cc stream_summary.h doubly_linked_list.o 
	g++ -std=c++11 -O3 -c stream_summary.cc 

doubly_linked_list.o: doubly_linked_list.cc doubly_linked_list.h 
	g++ -std=c++11 -O3 -c doubly_linked_list.cc 

clean:
	rm *.o topkmers
