//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section A - Linked List Questions
Purpose: Implementing the required functions for Question 7 */

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////////

typedef struct _listnode
{
	int item;
	struct _listnode *next;
} ListNode;			// You should not change the definition of ListNode

typedef struct _linkedlist
{
	int size;
	ListNode *head;
} LinkedList;			// You should not change the definition of LinkedList


//////////////////////// function prototypes /////////////////////////////////////

// You should not change the prototype of this function
void RecursiveReverse(ListNode **ptrHead);

void printList(LinkedList *ll);
void removeAllItems(LinkedList *ll);
ListNode * findNode(LinkedList *ll, int index);
int insertNode(LinkedList *ll, int index, int value);
int removeNode(LinkedList *ll, int index);


//////////////////////////// main() //////////////////////////////////////////////

int main()
{
	LinkedList ll;
	int c, i, j;
	c = 1;
	//Initialize the linked list 1 as an empty linked list
	ll.head = NULL;
	ll.size = 0;


	printf("1: Insert an integer to the linked list:\n");
	printf("2: Reversed the linked list:\n");
	printf("0: Quit:\n");

	while (c != 0)
	{
		printf("Please input your choice(1/2/0): ");
		scanf("%d", &c);

		switch (c)
		{
		case 1:
			printf("Input an integer that you want to add to the linked list: ");
			scanf("%d", &i);
			j = insertNode(&ll, ll.size, i);
			printf("The resulting linked list is: ");
			printList(&ll);
			break;
		case 2:
			RecursiveReverse(&(ll.head)); // You need to code this function
			printf("The resulting linked list after reversed the given linked list is: ");
			printList(&ll);
			removeAllItems(&ll);
			break;
		case 0:
			removeAllItems(&ll);
			break;
		default:
			printf("Choice unknown;\n");
			break;
		}
	}
	return 0;
}

////////////////////////////////////////////////////////////////////////

// 재귀적으로 링크드 리스트를 뒤집는 함수
void RecursiveReverse(ListNode **ptrHead)
{
    ListNode *first; // 현재 서브리스트의 첫 번째 노드를 가리키는 포인터
    ListNode *rest;  // 현재 서브리스트의 '나머지' 부분을 가리키는 포인터 (first 다음 노드부터)

    // 기본 케이스 (Base Case):
    // 1. 리스트가 비어있거나 (*ptrHead == NULL)
    // 2. 리스트에 노드가 하나뿐인 경우 ((*ptrHead)->next == NULL)
    // 이 두 경우에는 더 이상 뒤집을 필요가 없으므로 함수를 종료합니다.
    if (*ptrHead == NULL || (*ptrHead)->next == NULL) {
        return;
    }

    // 단계 1: 현재 서브리스트의 첫 번째 노드를 'first'에 할당합니다.
    first = *ptrHead;

    // 단계 2: 'first' 다음 노드를 'rest'에 할당합니다. 이 'rest'가 이제 재귀 호출될 서브리스트의 시작이 됩니다.
    rest = first->next;	

    // 단계 3: 'rest'부터 시작하는 나머지 서브리스트에 대해 재귀적으로 RecursiveReverse 함수를 호출합니다.
    // 이 재귀 호출이 완료되면, 'rest' 포인터는 뒤집힌 서브리스트의 새로운 헤드를 가리키게 됩니다.
    // 예: 원래 1->2->3 에서 first=1, rest=2 였다면, 이 호출 후 rest는 3을 가리키고 3->2 가 연결됩니다.
    RecursiveReverse(&rest);

    // 단계 4: 재귀 호출이 반환된 후, 'rest'는 이제 뒤집힌 서브리스트의 새로운 헤드를 가리킵니다.
    // 이제 'first' 노드를 뒤집힌 'rest' 서브리스트의 맨 끝에 연결해야 합니다.
    // 'first->next' (원래 'first' 다음 노드, 예: 2)는 이제 뒤집힌 서브리스트의 마지막 노드가 됩니다.
    // 따라서 'first->next'가 가리키는 노드(예: 2)의 'next' 포인터가 'first'를 가리키도록 연결합니다.
    // 이렇게 하면 '...' -> 3 -> 2 -> 1 과 같은 연결이 형성됩니다.
    first->next->next = first;

    // 단계 5: 'first' 노드(원래 헤드 노드였던)는 이제 전체 뒤집힌 리스트의 마지막 노드가 되므로,
    // 이 노드의 'next' 포인터를 NULL로 설정하여 리스트의 끝을 표시합니다.
    first->next = NULL;

    // 단계 6: 마지막으로, 전체 리스트의 실제 헤드 포인터를 업데이트합니다.
    // 재귀 호출을 통해 'rest'는 이미 완전히 뒤집힌 리스트의 새로운 헤드를 가리키고 있으므로,
    // 'ptrHead'가 'rest'를 가리키도록 합니다.
    *ptrHead = rest;
}

//////////////////////////////////////////////////////////////////////////////////

void printList(LinkedList *ll){

	ListNode *cur;
	if (ll == NULL)
		return;
	cur = ll->head;

	if (cur == NULL)
		printf("Empty");
	while (cur != NULL)
	{
		printf("%d ", cur->item);
		cur = cur->next;
	}
	printf("\n");
}

ListNode * findNode(LinkedList *ll, int index){

	ListNode *temp;

	if (ll == NULL || index < 0 || index >= ll->size)
		return NULL;

	temp = ll->head;

	if (temp == NULL || index < 0)
		return NULL;

	while (index > 0){
		temp = temp->next;
		if (temp == NULL)
			return NULL;
		index--;
	}

	return temp;
}

int insertNode(LinkedList *ll, int index, int value){

	ListNode *pre, *cur;

	if (ll == NULL || index < 0 || index > ll->size + 1)
		return -1;

	// If empty list or inserting first node, need to update head pointer
	if (ll->head == NULL || index == 0){
		cur = ll->head;
		ll->head = malloc(sizeof(ListNode));
		ll->head->item = value;
		ll->head->next = cur;
		ll->size++;
		return 0;
	}


	// Find the nodes before and at the target position
	// Create a new node and reconnect the links
	if ((pre = findNode(ll, index - 1)) != NULL){
		cur = pre->next;
		pre->next = malloc(sizeof(ListNode));
		pre->next->item = value;
		pre->next->next = cur;
		ll->size++;
		return 0;
	}

	return -1;
}


int removeNode(LinkedList *ll, int index){

	ListNode *pre, *cur;

	// Highest index we can remove is size-1
	if (ll == NULL || index < 0 || index >= ll->size)
		return -1;

	// If removing first node, need to update head pointer
	if (index == 0){
		cur = ll->head->next;
		free(ll->head);
		ll->head = cur;
		ll->size--;

		return 0;
	}

	// Find the nodes before and after the target position
	// Free the target node and reconnect the links
	if ((pre = findNode(ll, index - 1)) != NULL){

		if (pre->next == NULL)
			return -1;

		cur = pre->next;
		pre->next = cur->next;
		free(cur);
		ll->size--;
		return 0;
	}

	return -1;
}

void removeAllItems(LinkedList *ll)
{
	ListNode *cur = ll->head;
	ListNode *tmp;

	while (cur != NULL){
		tmp = cur->next;
		free(cur);
		cur = tmp;
	}
	ll->head = NULL;
	ll->size = 0;
}
