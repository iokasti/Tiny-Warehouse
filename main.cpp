#include <iostream>
#include <cstring>
#include <cstdlib>
#include <string>
#include <sstream>
#include "tinyWarehouse/tinyWarehouse.hpp"

#define INITIAL_BUCKETS 2

using namespace std;

int main(int argc, char **argv) {
	/************ reading command line arguments ***************/
	if (argc < 3) {
		cout << "Error!We need more arguments to continue!" << endl;
		return 1;
	}
	string DataFile = "";
	int BucketEntries = 0;
	double LoadFactor = 0.0;
	string OperationsFile = "";
	string configFile = "";
	for (int i = 1; i < argc; i = i + 2) {
		if (strncmp(argv[i], "-l", 2) == 0) {
			DataFile = argv[i + 1];
		} else if (strncmp(argv[i], "-p", 2) == 0) {
			OperationsFile = argv[i + 1];
		} else if (strncmp(argv[i], "-f", 2) == 0) {
			LoadFactor = atof(argv[i + 1]);
		} else if (strncmp(argv[i], "-b", 2) == 0) {
			BucketEntries = atoi(argv[i + 1]);
		} else if (strncmp(argv[i], "-c", 2) == 0) {
			configFile = argv[i + 1];
		}
	}
	if (BucketEntries == 0 || LoadFactor == 0.0) {
		cout << "Wrong arguments given." << endl;
		return 1;
	}
	/********************************************************/
	Twa *tWhouse = new Twa(INITIAL_BUCKETS, BucketEntries, LoadFactor);
	if (DataFile != "") {
		cout << "Loading data file.." << endl;
		tWhouse->load(DataFile);
	}
	if (OperationsFile != "") {
		cout << "Running according to requested operations.." << endl;
		bool opResult = tWhouse->runOperations(OperationsFile);
		if (opResult == true) {		// sto operation file ehoume end command
			delete tWhouse;
			return 0;
		}
	}
	string line;
	while (1) {		// main loop
		cout << "Please type your request" << endl;
		getline(cin, line);		// read command from user
		istringstream iss(line);	// pername to line sto iss
		string word;
		iss >> word;	// pairnoume tin proti leksi apo to iss
		if (word == "l") {
			// load file
			iss >> word;
			tWhouse->load(word);
			//tWhouse->printlist();
		} else if (word == "i") {
			// insert record
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
			tWhouse->insert(custid, fName, lName, street, houseID, city,
					postCode, amount);
		} else if (word == "q") {
			// query
			long custid;
			iss >> custid;
			tWhouse->query(custid);
		} else if (word == "t") {
			// find top k
			int k;
			iss >> k;
			tWhouse->top(k);
		} else if (word == "b") {
			// find bottom k
			int k;
			iss >> k;
			tWhouse->bottom(k);
		} else if (word == "a") {
			// average
			tWhouse->average();
		} else if (word == "r") {
			// range of two ids
			long custid1;
			long custid2;
			iss >> custid1 >> custid2;
			tWhouse->range(custid1, custid2);
		} else if (word == "p") {
			// percentile
			long custid;
			iss >> custid;
			tWhouse->percentile(custid);
		} else if (word == "e") {
			// terminate
			delete tWhouse;
			cout << "Terminated!" << endl;
			return 0;
		}
	}

	return 0;
}
