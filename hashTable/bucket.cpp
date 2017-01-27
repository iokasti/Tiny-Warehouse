#include "bucket.hpp"
#include <iostream>

using namespace std;

Bucket::Bucket(int Bucketentries) {
	bucketNodes = new bucketNode[Bucketentries];
	for (int i = 0; i < Bucketentries; i++) {
		bucketNodes[i].customerid = -1;
		bucketNodes[i].ListNodeptr = NULL;
	}
	overflow = NULL;
	maxNodes = Bucketentries;
	currentNodes = 0;
	numberOfEntries = 0;
}

Bucket::~Bucket() {
	if (overflow != NULL) {
		// anadromiki diagrafi olwn twn overflow buckets.
		delete overflow;
		overflow = NULL;
	}
	delete[] bucketNodes;
}

void Bucket::insertNode(int ID, ListNode* ListNode) {
	numberOfEntries++;
	if (currentNodes < maxNodes) {
		bucketNodes[currentNodes].customerid = ID;
		bucketNodes[currentNodes].ListNodeptr = ListNode;
		currentNodes++;
	} else {
		if (overflow == NULL) { // den yparhei overflow bucket ara to dimiourgoume
			overflow = new Bucket(maxNodes);
		}
		overflow->insertNode(ID, ListNode); // eisagoume sto overflow bucket
	}
}

bucketNode* Bucket::getAllEntries() {
	if (numberOfEntries == 0)
		return NULL;
	bucketNode* entries = new bucketNode[numberOfEntries];		// new array
	for (int i = 0; i < numberOfEntries; i++) {		// arhikopoihsh tou array
		entries[i].customerid = -1;
		entries[i].ListNodeptr = NULL;
	}

	int j = 0;

	for (int i = 0; i < maxNodes; i++) {		// prospelasi tou arhikou bucket eggrafi tou kathe stoiheiou ston pinaka entries
		if (bucketNodes[i].customerid != -1) {
			entries[j].customerid = bucketNodes[i].customerid;
			entries[j].ListNodeptr = bucketNodes[i].ListNodeptr;
			j++;
		}
	}

	Bucket *temp = overflow;
	while (temp != NULL && j < numberOfEntries) {		// prospelasi ton overflow buckets kai apothikefsi  ton stoiheion tous ston entries
		for (int i = 0; i < temp->maxNodes; i++) {
			if (temp->bucketNodes[i].customerid != -1) {
				entries[j].customerid = temp->bucketNodes[i].customerid;
				entries[j].ListNodeptr = temp->bucketNodes[i].ListNodeptr;
				j++;
			}
		}
		temp = temp->overflow;		// pame sto overflow tou proigoumenou overflow
	}

	return entries;
}

int Bucket::getNumberOfEntries() {
	return numberOfEntries;
}

void Bucket::emptyBucket() {
	for (int i = 0; i < maxNodes; i++) {
		bucketNodes[i].customerid = -1;
		bucketNodes[i].ListNodeptr = NULL;
	}
	numberOfEntries = 0;
	currentNodes = 0;
	delete overflow; // delete to overflow bucket (ola ta pithana overflows tou overflow tha diagrafoun sto destructor)
	overflow = NULL;
}

ListNode* Bucket::searchNode(long ID) {
	for (int i = 0; i < currentNodes; i++) {
		if (bucketNodes[i].customerid == ID) {
			return bucketNodes[i].ListNodeptr;
		}
	}
	if (overflow != NULL) {
		return overflow->searchNode(ID);
	}
	return NULL; // no data with that ID
}

void Bucket::print() {
	cout << "|";
	for (int i = 0; i < maxNodes; i++) {
		cout << bucketNodes[i].customerid << "|";
	}
	if (overflow != NULL) {
		cout << "->";
		overflow->print();
	}
	cout << endl;
}
