#ifndef LIST_HPP_
#define LIST_HPP_

#include "../myRecordDef.hpp"

struct ListNode {
	MyRecord* rec;
	ListNode* next;
	ListNode* previous;
	int position;
};

class List {	// lista apothikefsis eggrafon
private:
	int size;
	ListNode* head;
public:
	List();
	~List();
	ListNode* addSorted(MyRecord*);
	void printList();
	void topk(int);
	void bottomk(int);
	void average();
	void range(ListNode*, ListNode*);
	void percentile(ListNode*);
};

#endif /* LIST_HPP_ */
