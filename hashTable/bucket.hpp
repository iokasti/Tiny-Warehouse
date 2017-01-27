#ifndef BUCKET_HPP_
#define BUCKET_HPP_

#include "../entitiesList/list.hpp"

struct bucketNode{
	int customerid;
	ListNode* ListNodeptr;
};

class Bucket{
private:
	bucketNode *bucketNodes;
	Bucket *overflow;
	int maxNodes;
	int currentNodes;		// number of entries in the current bucket (overflows NOT included)
	int numberOfEntries;	// number of entries in all the buckets (overflows included)
public:
	Bucket(int);
	~Bucket();

	void insertNode(int, ListNode*);

	bucketNode* getAllEntries();	// returns an array with all the bucketNodes of the Bucket
	int getNumberOfEntries();
	void emptyBucket();		// bucketNodes point to NULL and have no data, overflow buckets deleted.

	ListNode* searchNode(long);


	void print();

};



#endif /* BUCKET_HPP_ */
