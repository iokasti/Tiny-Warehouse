#include "list.hpp"
#include <iostream>

using namespace std;

List::List() {
	head = NULL;
	size = 0;
}

List::~List() {
	ListNode *temp = head;
	while (head->next != NULL) {
		temp = head->next;
		delete head->rec;	// diagrafi tou record pou dimiourgithike stin insert tou twa
		delete head;
		head = temp;
	}
	delete head->rec;	// diagrafi tou record pou dimiourgithike stin insert tou twa
	delete head;
}

ListNode* List::addSorted(MyRecord* record) {
	ListNode* newNode = new ListNode();
	newNode->position = size + 1;
	if (head == NULL) {
		newNode->rec = record;
		newNode->next = NULL;
		newNode->previous = NULL;
		head = newNode;
		size++;
	} else if (record->amount >= head->rec->amount) {
		newNode->rec = record;
		newNode->next = head;
		newNode->previous = NULL;
		head->previous = newNode;  // head->next remains as is
		head = newNode;
		size++;
	} else {
		ListNode* temp = head;
		while ((temp->next != NULL)
				&& (temp->next->rec->amount > record->amount)) {
			temp = temp->next;
		}
		newNode->rec = record;
		newNode->next = temp->next;
		newNode->previous = temp;
		//newNode->previous = temp->previous;
		if (temp->next != NULL) {   // last node
			temp->next->previous = newNode;
		}
		temp->next = newNode;
		size++;
	}
	return newNode;	// return the node we just created
}

void List::printList() {
	if (head != NULL) {
		ListNode* temp = head;
		while (temp != NULL) {
			cout << "Customer ID: " << temp->rec->custid << " , ";
			cout << "Fist Name: " << temp->rec->FirstName << " , ";
			cout << "Last Name: " << temp->rec->LastName << " , ";
			cout << "City: " << temp->rec->City << " , ";
			cout << "Street: " << temp->rec->Street << " , ";
			cout << "House ID: " << temp->rec->HouseID << " , ";
			cout << "Post Code: " << temp->rec->postcode << " , ";
			cout << "Amount: " << temp->rec->amount << endl;
			temp = temp->next;
		}
	}
}

void List::topk(int kappa) {
	ListNode* temp = head;
	int i = 0;
	while ((temp != NULL) && i < kappa) {
		cout << "Customer ID: " << temp->rec->custid << " , ";
		cout << "Fist Name: " << temp->rec->FirstName << " , ";
		cout << "Last Name: " << temp->rec->LastName << " , ";
		cout << "City: " << temp->rec->City << " , ";
		cout << "Street: " << temp->rec->Street << " , ";
		cout << "House ID: " << temp->rec->HouseID << " , ";
		cout << "Post Code: " << temp->rec->postcode << " , ";
		cout << "Amount: " << temp->rec->amount << endl;
		temp = temp->next;
		i++;
	}
}

void List::bottomk(int kappa) {
	ListNode* temp = head;
	int i = 0;
	while (temp->next != NULL) {
		temp = temp->next;
	}
	while ((temp != NULL) && (i < kappa)) {
		cout << "Customer ID: " << temp->rec->custid << " , ";
		cout << "Fist Name: " << temp->rec->FirstName << " , ";
		cout << "Last Name: " << temp->rec->LastName << " , ";
		cout << "City: " << temp->rec->City << " , ";
		cout << "Street: " << temp->rec->Street << " , ";
		cout << "House ID: " << temp->rec->HouseID << " , ";
		cout << "Post Code: " << temp->rec->postcode << " , ";
		cout << "Amount: " << temp->rec->amount << endl;
		temp = temp->previous;
		i++;
	}
}

void List::average() {
	ListNode* temp = head;
	float avg;
	float money = 0;
	while (temp != NULL) {
		money += temp->rec->amount;
		temp = temp->next;
	}
	avg = money / (float) size;
	cout << "Average amount spent by: " << size << " customers is: " << avg
			<< endl;
}

void List::range(ListNode* N1, ListNode* N2) {
	ListNode* temp;
	if ((N1->rec->amount) < (N2->rec->amount)) {	// sygrinoume orismata kata poso oste na einai sosti i ektyposi
		temp = N1;
		while (temp->rec->custid != N2->rec->custid) {
			cout << "Customer ID: " << temp->rec->custid << " , ";
			cout << "Fist Name: " << temp->rec->FirstName << " , ";
			cout << "Last Name: " << temp->rec->LastName << " , ";
			cout << "City: " << temp->rec->City << " , ";
			cout << "Street: " << temp->rec->Street << " , ";
			cout << "House ID: " << temp->rec->HouseID << " , ";
			cout << "Post Code: " << temp->rec->postcode << " , ";
			cout << "Amount: " << temp->rec->amount << endl;
			temp = temp->previous;
		}
		cout << "Customer ID: " << temp->rec->custid << " , ";
		cout << "Fist Name: " << temp->rec->FirstName << " , ";
		cout << "Last Name: " << temp->rec->LastName << " , ";
		cout << "City: " << temp->rec->City << " , ";
		cout << "Street: " << temp->rec->Street << " , ";
		cout << "House ID: " << temp->rec->HouseID << " , ";
		cout << "Post Code: " << temp->rec->postcode << " , ";
		cout << "Amount: " << temp->rec->amount << endl;
	} else {
		temp = N2;
		while (temp->rec->custid != N1->rec->custid) {
			cout << "Customer ID: " << temp->rec->custid << " , ";
			cout << "Fist Name: " << temp->rec->FirstName << " , ";
			cout << "Last Name: " << temp->rec->LastName << " , ";
			cout << "City: " << temp->rec->City << " , ";
			cout << "Street: " << temp->rec->Street << " , ";
			cout << "House ID: " << temp->rec->HouseID << " , ";
			cout << "Post Code: " << temp->rec->postcode << " , ";
			cout << "Amount: " << temp->rec->amount << endl;
			temp = temp->previous;
		}
		cout << "Customer ID: " << temp->rec->custid << " , ";
		cout << "Fist Name: " << temp->rec->FirstName << " , ";
		cout << "Last Name: " << temp->rec->LastName << " , ";
		cout << "City: " << temp->rec->City << " , ";
		cout << "Street: " << temp->rec->Street << " , ";
		cout << "House ID: " << temp->rec->HouseID << " , ";
		cout << "Post Code: " << temp->rec->postcode << " , ";
		cout << "Amount: " << temp->rec->amount << endl;

	}

}

void List::percentile(ListNode* Node) {
	if (Node != NULL) {
		double per = ((size - (Node->position)) / (double) size);
		per *= 100;
		cout << "Percentile for customer with the id: " << Node->rec->custid
				<< " according to amount, is: " << per << "%" << endl;
	}
}

