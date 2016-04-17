all:cmp cat cp wc 
cmp:src/cmp.cpp
	g++ -o cmp src/cmp.cpp
cat:src/cat.cpp
	g++ -o cat src/cat.cpp
cp:src/cp.cpp
	g++ -o cp src/cp.cpp
wc:src/wc.cpp
	g++ -o wc src/wc.cpp
clean:
	rm *.o