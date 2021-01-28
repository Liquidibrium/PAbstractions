#include "flattenlist.h"


bool allDownsAreNull(ListNode * head){
	ListNode * gadamyoli = head;
	while(gadamyoli!=NULL){
		if(gadamyoli->down!=NULL){
			return false;
		}
		gadamyoli=gadamyoli->next;
	}
	return true;
}


void amoigePirveliDown(ListNode *& head){
	ListNode * ravi = head;
	while(ravi->down==NULL){
		ravi=ravi->next;
		if(ravi==NULL)
			break;
	}
	if(ravi!=NULL){
		ListNode * aiimagas = ravi->next;
		ravi->next=ravi->down;
		ravi->down = NULL;
		ravi->next->next=aiimagas;
	}
}

ListNode * flattenList(ListNode * head) {
	while(!allDownsAreNull(head)){
		amoigePirveliDown(head);
	}
	return head;
}

