#ifndef TINYWAREHOUSE_HPP_
#define TINYWAREHOUSE_HPP_

#include <string>
#include "../hashTable/hash.hpp"

class Twa {
private:
	List* orderedStructure;
	Hash* hashTable;
public:
	Twa(int, int, double);
	~Twa();

	void load(std::string);
	void insert(long, std::string, std::string, std::string, int, std::string,
			std::string, float);
	void query(long);
	void top(int);
	void bottom(int);
	void average();
	void range(long, long);
	void percentile(long);
	bool runOperations(std::string);
	void printlist();
};

#endif /* TINYWAREHOUSE_HPP_ */
