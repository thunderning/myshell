all:bin/cmp bin/cat bin/cp bin/wc 
bin/cmp:src/cmp.cpp
	g++ -o bin/cmp src/cmp.cpp
bin/cat:src/cat.cpp
	g++ -o bin/cat src/cat.cpp
bin/cp:src/cp.cpp
	g++ -o bin/cp src/cp.cpp
bin/wc:src/wc.cpp
	g++ -o bin/wc src/wc.cpp
clean:
	rm *.o