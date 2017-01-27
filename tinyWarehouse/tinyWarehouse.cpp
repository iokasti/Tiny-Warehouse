#include <iostream>
#include <fstream>
#include <sstream>
#include "tinyWarehouse.hpp"

using namespace std;

Twa::Twa(int initialBuckets, int Bucketentries, double LoadFactor) {
	orderedStructure = new List();
	hashTable = new Hash(initialBuckets, Bucketentries, LoadFactor);
}

Twa::~Twa() {
	delete orderedStructure;
	delete hashTable;
}

void Twa::load(string DataFile) {
	ifstream file(DataFile.c_str());
	long custid;
	string fName;
	string lName;
	string street;
	int houseID;
	string city;
	string postCode;
	float amount;
	while (file >> custid >> lName >> fName >> street >> houseID >> city
			>> postCode >> amount) {	// diavazei apo to file grammi grammi kai ta dinei stin insert
		insert(custid, fName, lName, street, houseID, city, postCode, amount);
	}
	file.close();
}

void Twa::insert(long custid, string fName, string lName, string street,
		int houseID, string city, string postCode, float amount) {
	MyRecord* rec = new MyRecord();		// dimiourgei neo record
	ListNode* Node;
	rec->City = city;
	rec->FirstName = fName;
	rec->HouseID = houseID;
	rec->LastName = lName;
	rec->Street = street;
	rec->amount = amount;
	rec->custid = custid;
	rec->postcode = postCode;
	Node = orderedStructure->addSorted(rec); // apothikevei to record sti lista, sto node apothikevetai o deiktis ston antistoiho komvo tis listas
	hashTable->insertData(custid, Node);	// eisagei sto hash table to id kai ton deikti ston antistoiho komvo tis listas

}

void Twa::query(long custid) {
	ListNode* customer;
	customer = hashTable->query(custid);
	cout << "Customer ID: " << customer->rec->custid << " , ";
	cout << "Fist Name: " << customer->rec->FirstName << " , ";
	cout << "Last Name: " << customer->rec->LastName << " , ";
	cout << "City: " << customer->rec->City << " , ";
	cout << "Street: " << customer->rec->Street << " , ";
	cout << "House ID: " << customer->rec->HouseID << " , ";
	cout << "Post Code: " << customer->rec->postcode << " , ";
	cout << "Amount: " << customer->rec->amount << endl;
}

void Twa::top(int k) {
	orderedStructure->topk(k);
}

void Twa::bottom(int k) {
	orderedStructure->bottomk(k);
}

void Twa::average() {
	orderedStructure->average();
}

void Twa::range(long custid1, long custid2) {
	ListNode* Node1 = hashTable->query(custid1);	// custid1;
	ListNode* Node2 = hashTable->query(custid2);	// custid2;
	if ((Node1 == NULL) || (Node2 == NULL)) {
		cout << "Error! At least one of the given IDs doesn't exist!" << endl;
	} else {
		orderedStructure->range(Node1, Node2);
	}
}

void Twa::percentile(long custid) {
	orderedStructure->percentile(hashTable->query(custid));
}

bool Twa::runOperations(string opFile) {
	ifstream file(opFile.c_str());
	string line;
	while (getline(file, line)) {
		istringstream iss(line);
		string word;
		iss >> word;
		if (word == "l") {
			iss >> word;
			load(word);
		} else if (word == "i") {
			long custid;
			string fName;
			string lName;
			string street;
			int houseID;
			string city;
			string postCode;
			float amount;
			iss >> custid >> lName >> fName >> street >> houseID >> city
					>> postCode >> amount;
			insert(custid, fName, lName, street, houseID, city, postCode,
					amount);
		} else if (word == "q") {
			long custid;
			iss >> custid;
			query(custid);
		} else if (word == "t") {
			int k;
			iss >> k;
			top(k);
		} else if (word == "b") {
			int k;
			iss >> k;
			bottom(k);
		} else if (word == "a") {
			average();
		} else if (word == "r") {
			long custid1;
			long custid2;
			iss >> custid1 >> custid2;
			range(custid1, custid2);
		} else if (word == "p") {
			long custid;
			iss >> custid;
			percentile(custid);
		} else if (word == "e") {
			cout << "Terminated!" << endl;
			return true;
		}
	}
	return false;
}

void Twa::printlist() {
	orderedStructure->printList();
}
