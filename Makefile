rsa: rsa.o
	g++ -std=c++14 -g -Wall -o rsa rsa.o

rsa.o: rsa.cpp
	g++ -c rsa.cpp

debug:
	g++ -std=c++14 -g3 rsa.cpp -o rsa_debug

clean:
	rm *.o rsa rsa_debug