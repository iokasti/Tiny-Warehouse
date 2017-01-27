#ifndef HASH_HPP_
#define HASH_HPP_

#include "../entitiesList/list.hpp"
#include "bucket.hpp"

class Hash {
private:
	int m;	//	initial buckets
	int i;	//	round
	int p;	//	points bucket to be split
	int hashSize;	//	hash table size
	int numberOfEntries;	// Number of all entries given
	int bucketEntries; // max size of each bucket
	double LoadFactor;
	Bucket** hashTable;	//	hash table apoteloumeno apo typou bucket entries
public:
	Hash(int, int, double);
	~Hash();

	int HashFunc(int, long);
	bool checkLoadFactor();

	void insertData(long, ListNode*);
	void insertDataFromSplit(long, ListNode*);
	void split(int);
	void addNewBucket();
	ListNode* query(long);
	void print();
};

#endif /* HASH_HPP_ */
