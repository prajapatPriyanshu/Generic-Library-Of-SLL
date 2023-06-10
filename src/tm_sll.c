#ifndef __TM_SLL__C
#define __TM_SLL__C 123
#include<stdlib.h>
#include<tm_sll.h>
SinglyLinkedList *createSinglyLinkedList(bool *success)							// CREATE   SPELLING MISS.
{
if(success) *success=false;
SinglyLinkedList *singlyLinkedList;
singlyLinkedList=(SinglyLinkedList *)malloc(sizeof(SinglyLinkedList));
if(singlyLinkedList==NULL) return NULL;
singlyLinkedList->start=NULL;
singlyLinkedList->end=NULL;
singlyLinkedList->size=0;
if(success) *success=true;
return singlyLinkedList;
}
void destroySinglyLinkedList(SinglyLinkedList *singlyLinkedList)						// DESTROY
{
if(singlyLinkedList==NULL) return;
clearSinglyLinkedList(singlyLinkedList);
free(singlyLinkedList);
}
int getSizeOfSinglyLinkedList(SinglyLinkedList * singlyLinkedList)
{
if(singlyLinkedList==NULL) return 0;
return singlyLinkedList->size;
}
void clearSinglyLinkedList(SinglyLinkedList * singlyLinkedList)						// CLEAR
{
if(singlyLinkedList==NULL) return;
SinglyLinkedListNode *node;
node=singlyLinkedList->start;
while(singlyLinkedList->start!=NULL) {
node=singlyLinkedList->start;
singlyLinkedList->start=singlyLinkedList->start->next;
free(node);
}
singlyLinkedList->size=0;
}

void addToSinglyLinkedList(SinglyLinkedList *singlyLinkedList,void *ptr,bool *success)						// ADD 
{
if(success) *success=false;
if(singlyLinkedList==NULL) return;
SinglyLinkedListNode *node;
node=(SinglyLinkedListNode*)malloc(sizeof(SinglyLinkedListNode));
if(node==NULL) return;
node->ptr=ptr;
node->next=NULL;
if(singlyLinkedList->start==NULL)
{
singlyLinkedList->start=node;
singlyLinkedList->end=node;
}else{
singlyLinkedList->end->next=node;
singlyLinkedList->end=node;
}
singlyLinkedList->size++;
if(success) *success=true;
}

void insertIntoSinglyLinkedList(SinglyLinkedList *singlyLinkedList,int index,void *ptr,bool *success)					// INSERT
{
if(success) *success=false;
if(singlyLinkedList==NULL) return;
SinglyLinkedListNode *node,*p1,*p2;
int x;
if(index<0||index>singlyLinkedList->size) return;
if(index==singlyLinkedList->size)
{
addToSinglyLinkedList(singlyLinkedList,ptr,success);
return;
}
node=(SinglyLinkedListNode*)malloc(sizeof(SinglyLinkedListNode));
if(node==NULL) return;
node->ptr=ptr;
node->next=NULL;
if(index==0)
{
node->next=singlyLinkedList->start;
singlyLinkedList->start=node;
singlyLinkedList->size++;
if(success)*success=true;
return;
}
p1=singlyLinkedList->start;
x=0;
while(x<index)
{
p2=p1;
p1=p1->next;
x++;
}
node->next=p1;
p2->next=node;
singlyLinkedList->size++;
if(success) *success=true;
}
void * removeFromSinglyLinkedList(SinglyLinkedList *singlyLinkedList,int index,boolean* success)			// REMOVE_FROM SLL
{
if(success) *success=false;
if(singlyLinkedList==NULL) return NULL;
void *ptr;
int x;
SinglyLinkedListNode *node,*p1,*p2;
if(0>index||index>=singlyLinkedList->size) return NULL;
p1=singlyLinkedList->start;
x=0;
while(x<index)
{
p2=p1;
p1=p1->next;
x++;
}
ptr=p1->ptr;
if(p1==singlyLinkedList->start&&p1==singlyLinkedList->end)
{
singlyLinkedList->start=NULL;
singlyLinkedList->end=NULL;
}else if(singlyLinkedList->start==p1)
{
singlyLinkedList->start=singlyLinkedList->start->next;
}else if(singlyLinkedList->end==p1)
{
singlyLinkedList->end=p2;
singlyLinkedList->end->next=NULL;
}else 
{
p2->next=p1->next;
}
free(p1);
singlyLinkedList->size--;
if(success) *success=true;
return ptr;
}

void appendToSinglyLinkedList(SinglyLinkedList * targetSinglyLinkedList,SinglyLinkedList *sourceSinglyLinkedList,bool*success)			// 	APPEND
{
if(success) *success=false;
SinglyLinkedListNode *s,*e,*t,*node;
s=NULL;
e=NULL;
bool done;
//done=true;
if(targetSinglyLinkedList==NULL)return; 
if(sourceSinglyLinkedList==NULL||sourceSinglyLinkedList->size==0) 
{
if(success) *success=true;
return;
}
t=sourceSinglyLinkedList->start;
while(t!=NULL)
{
node=(SinglyLinkedListNode*)malloc(sizeof(SinglyLinkedListNode));
if(node==NULL)
{
done=false;
break;
}
node->ptr=t->ptr;
node->next=NULL;
if(s==NULL)
{
s=node;
e=node;
}else
{
e->next=node;
e=node;
}
t=t->next;
}
if(done==false)
{
while(s!=NULL)
{
node=s;
s=s->next;
free(node);
}
return;
}
if(targetSinglyLinkedList->start==NULL)  // ye cond. try krna hai [if(tSLL->size==0)]
{
targetSinglyLinkedList->start=s;
targetSinglyLinkedList->end=e;
targetSinglyLinkedList->size=sourceSinglyLinkedList->size;
}else
{
targetSinglyLinkedList->end->next=s;
targetSinglyLinkedList->end=e;
targetSinglyLinkedList->size+=sourceSinglyLinkedList->size;
}
if(success) *success=true;

} // append fun. complete


void * getFromSinglyLinkedList(SinglyLinkedList *singlyLinkedList,int index,bool*success)					// GET_FROM_SLL
{
int x=0;
if(success) *success==false;
if(singlyLinkedList==NULL) return NULL;
SinglyLinkedListNode *node;
if(index<0||index>=singlyLinkedList->size) return NULL;
node=singlyLinkedList->start;
while(x<index)
{
node=node->next;
x++;
}
if(success) *success=true;
return node->ptr;
}


SinglyLinkedListIterator getSinglyLinkedListIterator(SinglyLinkedList *singlyLinkedList,bool *success)
{
SinglyLinkedListIterator  sll;
sll.node=NULL;
if(success) *success=false;
if(singlyLinkedList==NULL) return sll;
if(singlyLinkedList->start==NULL)
{
if(success) *success=true;
return sll;
}
if(success) *success=true;
sll.node=singlyLinkedList->start;
return sll;
}

bool hasNextInSinglyLinkedList(SinglyLinkedListIterator *sll)
{
if(sll==NULL) return false;
if(sll->node==NULL) return false;
return true;
}
void * getNextElementFromSinglyLinkedList(SinglyLinkedListIterator * sll,bool *success)
{
void *ptr;
if(success) *success=false;
if(sll==NULL || sll->node==NULL) return ptr;
ptr=sll->node->ptr;
sll->node=sll->node->next;
if(success) * success=true;
return ptr;
}


#endif


