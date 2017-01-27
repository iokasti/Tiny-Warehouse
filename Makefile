all: list.o bucket.o hash.o tinyWarehouse.o main.o
	g++ -o TWA list.o bucket.o hash.o tinyWarehouse.o main.o


list.o: entitiesList/list.cpp entitiesList/list.hpp
	g++ -c entitiesList/list.cpp 


bucket.o: hashTable/bucket.cpp hashTable/bucket.hpp
	g++ -c hashTable/bucket.cpp 


hash.o: hashTable/hash.cpp hashTable/hash.hpp
	g++ -c hashTable/hash.cpp 


tinyWarehouse.o: tinyWarehouse/tinyWarehouse.cpp tinyWarehouse/tinyWarehouse.hpp
	g++ -c tinyWarehouse/tinyWarehouse.cpp 


main.o: main.cpp
	g++ -c main.cpp

clean:
	rm -f *.o TWA



