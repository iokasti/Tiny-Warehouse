#include <iostream>
#include "hash.hpp"
#include <cmath>

using namespace std;

Hash::Hash(int initialBuckets, int Bucketentries, double loadfactor) {
	m = initialBuckets;	// menei stathero sto programma
	bucketEntries = Bucketentries;
	i = 0;
	p = 0;
	hashSize = m;	// allazei stin poreia
	numberOfEntries = 0;
	hashTable = new Bucket*[m];
	for (int j = 0; j < m; j++) {
		hashTable[j] = new Bucket(bucketEntries);
	}
	LoadFactor = loadfactor;
}

Hash::~Hash() {
	for (int j = 0; j < hashSize; j++) {
		delete hashTable[j];
	}
	delete[] hashTable;
}

int Hash::HashFunc(int hashFuncNo, long ID) {//	hashFuncNo technically the round number
	int pos;
	double x = pow(2.0, (double) hashFuncNo);
	pos = ID % ((int) x * m);
	return pos;
}

bool Hash::checkLoadFactor() {
	double var = (double) ((double) numberOfEntries
			/ (double) (hashSize * bucketEntries));
	if (var > LoadFactor) {
		return false;
	} else {
		return true;
	}
}

void Hash::insertData(long ID, ListNode* ListNodePtr) {
	int pos = HashFunc(i, ID); 	// kaloume tin hash function me i tou gyrou p eimaste
	if (pos < p) {
		pos = HashFunc(i + 1, ID); // kaloume tin hash function me i tou epomenou gyrou
	}
	hashTable[pos]->insertNode(ID, ListNodePtr);
	numberOfEntries++;

	if (checkLoadFactor() == false) { // eimaste pano apo to loadfactor ara theloume na megalosoume to hashtable
		int toBeSplit = p;	// to p deihnei poio bucket tha ginei split meta
		addNewBucket();
		split(toBeSplit);
	}
}

void Hash::insertDataFromSplit(long ID, ListNode* ListNodePtr) {
	// omoia me insert data, alla ksanahasharoume yparhousa timi gia pithani allagi thesis
	int pos = HashFunc(i, ID);
	if (pos < p) {
		pos = HashFunc(i + 1, ID);
	}
	hashTable[pos]->insertNode(ID, ListNodePtr);
}

void Hash::addNewBucket() {
	Bucket** extendedHashTable;
	int extHashSize;
	extHashSize = hashSize + 1;

	extendedHashTable = new Bucket*[extHashSize]; // neos pinakas me deiktes se buckets
	for (int j = 0; j < hashSize; j++) {
		extendedHashTable[j] = hashTable[j]; // metafora ton deikton tou arhikou hash table sto extended hash table
	}
	extendedHashTable[hashSize] = new Bucket(bucketEntries);

	delete[] hashTable;	// diagrafi tou arhikou pinaka hash table
						// den diagrafontai oi deiktes sta buckets
						// kaleitai o destructor tou bucket gia ton pinaka kai oxi gia tous deiktes pou vriskontai mesa se afton

	hashSize++;
	hashTable = extendedHashTable;
	if ((pow(2, i) * m) == hashSize / m) {
		// an ehoume diplasiasmo tote gyrname sto 0
		p = 0;
		i++; // epomenos gyros
	} else {
		p++;
	}
}

void Hash::split(int toBeSplit) {
	bucketNode* temp = hashTable[toBeSplit]->getAllEntries();
	if (temp == NULL) { // bucket had no entries
		return;
	}
	int sizeOfTemp = hashTable[toBeSplit]->getNumberOfEntries();
	hashTable[toBeSplit]->emptyBucket();

	for (int j = 0; j < sizeOfTemp; j++) { // prospelasi tou temp kai rehash ton timon tou
		if (temp[j].customerid != -1) {
			insertDataFromSplit(temp[j].customerid, temp[j].ListNodeptr);
		}
	}
	delete[] temp; // diagrafoume ton pinaka temp, eihe dimiourgithei stin getAllEntries tou Bucket
}

void Hash::print() {
	for (int j = 0; j < hashSize; j++) {
		if (j == p)
			cout << "p->";
		hashTable[j]->print();
	}
}

ListNode* Hash::query(long ID) {
	int pos = HashFunc(i, ID);
	if (pos < p) {
		pos = HashFunc(i + 1, ID);
	}
	return hashTable[pos]->searchNode(ID);

}
