//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section A - Linked List Questions
Purpose: Implementing the required functions for Question 6 */

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
int moveMaxToFront(ListNode **ptrHead);

void printList(LinkedList *ll);
void removeAllItems(LinkedList *ll);
ListNode * findNode(LinkedList *ll, int index);
int insertNode(LinkedList *ll, int index, int value);
int removeNode(LinkedList *ll, int index);


//////////////////////////// main() //////////////////////////////////////////////

int main()
{
	int c, i, j;
	c = 1;

	LinkedList ll;
	//Initialize the linked list 1 as an empty linked list
	ll.head = NULL;
	ll.size = 0;


	printf("1: Insert an integer to the linked list:\n");
	printf("2: Move the largest stored value to the front of the list:\n");
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
			j=insertNode(&ll, ll.size, i);
			printf("The resulting linked list is: ");
			printList(&ll);
			break;
		case 2:
			moveMaxToFront(&(ll.head));  // You need to code this function
			printf("The resulting linked list after moving largest stored value to the front of the list is: ");
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

int moveMaxToFront(ListNode **ptrHead)
{
    if (*ptrHead == NULL) return -1;

	// 탐색을 위한 변수들 설정
    ListNode *maxNode = *ptrHead;      // 현재까지 찾은 최댓값 노드 (일단 첫 번째 노드라고 가정)
    ListNode *prevMax = NULL;          // 최댓값 노드의 '이전' 노드
    ListNode *current = *ptrHead;      // 현재 탐색 중인 노드
    ListNode *prev = NULL;             // 현재 노드의 '이전' 노드
    int maxValue = (*ptrHead)->item;   // 현재까지 찾은 최댓값 (일단 첫 번째 노드의 값이라고 가정)

    // 리스트를 끝까지 순회합니다.
    while (current != NULL) {
        // 만약 현재 노드의 값이 지금까지의 최댓값보다 크다면?
        if (current->item > maxValue) {
            // '대장'을 교체합니다!
            maxValue = current->item; // 최댓값 갱신
            maxNode = current;        // 최댓값 노드 갱신
            prevMax = prev;           // 최댓값 노드의 '이전' 노드도 갱신
        }
        // 다음 노드로 이동하기 위해 현재 노드를 '이전' 노드로 만들고
        prev = current;
        // 한 칸 앞으로 전진합니다.
        current = current->next;
    }

	// 최댓값 노드가 이미 맨 앞이 아니라면 (prevMax가 NULL이 아님)
    if (prevMax != NULL) {
        // 1. 최댓값 노드를 리스트에서 분리합니다.
        // prevMax의 다음을 maxNode의 다음으로 연결하여 maxNode를 건너뜁니다.
        // (20의 next가 40을 가리키게 됨)
        prevMax->next = maxNode->next;

        // 2. 최댓값 노드를 맨 앞에 삽입합니다.
        // (50의 next가 기존의 head였던 10을 가리키게 됨)
        maxNode->next = *ptrHead;
        // (이제 새로운 head는 50이 됨)
        *ptrHead = maxNode;
    }
    // 만약 최댓값이 이미 맨 앞에 있었다면 (prevMax == NULL),
    // 아무것도 할 필요가 없으므로 이 로직은 실행되지 않습니다.
	
    return 0; // 성공적으로 완료!
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
