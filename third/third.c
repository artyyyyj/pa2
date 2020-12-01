#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct graphNode
{
	char name[21];
	struct graphNode* next;
};

struct graphNode* createNode(char str[21])
{
	struct graphNode* temp = (struct graphNode*) malloc(sizeof(struct graphNode));
	strcpy(temp -> name, str);
	temp -> next = 0;
	return temp;
}

struct graphNode* enqueue(struct graphNode* head, char name[21])
{
	if (head == 0)
	{
		struct graphNode* lastNode = createNode(name);
		return lastNode;
	}
	
	else
	{
		struct graphNode* temp = head;
		
		while(head->next != 0)
		{
			head = head->next;
		}
		struct graphNode* lastNode = createNode(name);
		head->next = lastNode;
		return temp;
	}
}

struct graphNode* pop(struct graphNode* head)
{	
	struct graphNode* temp = head;

	if (temp == 0)
	{
		return 0;
	}

	if (temp->next == 0)
	{
		free(head);
		return 0;
	}

	temp = head->next;
	head->next = 0;
	free(head);
	return temp;
}


struct graphNode* insertNode(struct graphNode* head, char str[21])
{
	struct graphNode* temp = head;
	
	if (head -> next == 0)
	{
		struct graphNode* nextNode = createNode(str);
		head -> next = nextNode;
		return head;
	}
	
	if (strcmp(str, head->next->name) < 0)
	{
		struct graphNode* t = head->next;
		struct graphNode* nextNode = createNode(str);
		head -> next = nextNode;
		nextNode -> next = t;
		return temp;
	}

	head = head -> next;

	while (head -> next != 0)
	{
		if (head -> next == 0)
		{
			struct graphNode* nextNode = createNode(str);
			head -> next  = nextNode;
			return temp;
		}

		else if (strcmp(str, head->next->name) < 0 && strcmp(str, head->name) > 0)
		{
			struct graphNode* nextNode = createNode(str);
			struct graphNode* f = head ->next;
			head -> next = nextNode;
			nextNode ->next = f;
			return temp;
		}
		head = head->next;
	}
	
	if (head ->next == 0)
	{
		struct graphNode* nextNode = createNode(str);
		head ->next = nextNode;
	}

	return temp;
}

struct graphNode* alphNode(struct graphNode* head, char str[21])
{

	if (head == 0)
	{
		struct graphNode* newNode = createNode(str);
		return newNode;
	}

	if (head -> next == 0)
	{
		struct graphNode* newNode = createNode(str);
		head -> next = newNode;
		return head;
	}

	if (strcmp(str, head->name) < 0)
	{
		struct graphNode* newNode = createNode(str);
		newNode -> next = head;
		return newNode;
	}

	struct graphNode* temp = head; 
	// head = head -> next;

	while (head -> next != 0)
	{

		if (strcmp(str, head->next->name) < 0 && strcmp(str, head->name) > 0)
		{
			struct graphNode* nextNode = createNode(str);
			struct graphNode* f = head ->next;
			head -> next = nextNode;
			nextNode ->next = f;
			return temp;
		}
		head = head->next;
	}
	
	if (head ->next == 0)
	{
		struct graphNode* nextNode = createNode(str);
		head ->next = nextNode;
	}

	return temp;
}

			
void freeAll(int size, struct graphNode** arr)
{
	struct graphNode* temp;

	for (int x = 0; x < size; x++)
	{
		temp = arr[x];
		struct graphNode* temp2;

		while(temp != 0)
		{
			temp2 = temp;
			temp = temp -> next;
		       	free(temp2);
	 	}		
	}	 	
}

int returnPos(struct graphNode** arr, int num, char str[21])
{
	for (int x = 0; x < num; x++)
	{
		if (strcmp(arr[x] -> name, str) == 0)
		{
			return x;
		}
	}

	return 0;
}

// returns 0 if not found, 1 if found
int search(struct graphNode* head, char value[21])
{
	if (head == 0)
	{
		return 0;
	}
	
	struct graphNode* temp = head;
	while (temp != 0)
	{
		if (strcmp(temp->name, value) == 0)
		{
			return 1;
		}
		
		temp = temp -> next;
		
	}
	return 0;
}

int isEmpty(struct graphNode* head)
{
	if (head == 0)
	{
		return 1;
	}

	return 0;
}

void bfs(struct graphNode** arr, int num, char name[21])
{
	// Creates Queue w/ first node
	struct graphNode* qHead = 0;
	qHead = enqueue(qHead, name);

	// Creates Visited LL w/ first node
	struct graphNode* vHead = 0;
	

	while (isEmpty(qHead) == 0)
	{
		// finds position of first in queue in array 
		int pos = returnPos(arr, num, qHead->name);
		struct graphNode* temp = arr[pos];
		qHead = pop(qHead);
		

		// sets a pointer to neighbors
		struct graphNode* neighbors = temp;
			
		while (neighbors != 0)
		{
			if (search(vHead, neighbors->name) == 0)
			{
				qHead = enqueue(qHead, neighbors->name);
				vHead = enqueue(vHead, neighbors->name);
				printf("%s ", neighbors->name);
			}
			neighbors = neighbors -> next;
		}
		
	}

	free(qHead);
	while (vHead != 0)
	{
		struct graphNode* temp = vHead;
		vHead = vHead -> next;
		free(temp);
	}
	printf("\n");	
}

int main(int argc, char* argv[argc + 1])
{
	FILE* f1 = fopen(argv[1], "r");
	
	if (f1 == 0)
	{
		printf("error\n");
		return EXIT_SUCCESS;
	}

	// READS THE FIRST GRAPH FILE, CREATES GRAPH HEADS
	
	int num;
	fscanf(f1, "%d\n", &num);
	char name[21];
	struct graphNode** arr = malloc(num * sizeof(struct graphNode));
	struct graphNode* tempList = 0;	

	for (int x = 0; x < num; x++)
	{
		fscanf(f1, "%s\n", name);	
		tempList = alphNode(tempList, name);
	}

	int c = 0;
	struct graphNode* tempListPointer = tempList;
	while (tempListPointer != 0)
	{
		arr[c] = createNode(tempListPointer -> name);
		c++;
		tempListPointer = tempListPointer -> next;
	}

	while (tempList != 0)
	{
		struct graphNode* temp = tempList;
		tempList = tempList -> next;
		free(temp);
	}	
	
	
	// READS FIRST GRAPH FILE, CREATES GRAPH EDGES
	char s1[21];
	char s2[21];
	int count;

	while (fscanf(f1, "%s %s\n", s1, s2) != EOF)
	{
		for (int x = 0; x < num; x++)
		{
			if (strcmp(arr[x] -> name, s1) == 0)
			{
				count = x;
				break;
			}
		}

		arr[count] = insertNode(arr[count], s2);

		for (int x = 0; x < num; x++)
		{
			
			if (strcmp(arr[x] -> name, s2) == 0)
			{
				count = x;
				break;
			}
		}

		arr[count] = insertNode(arr[count], s1);
	}

	
	// PARSE SECOND FILE
	FILE* f2 = fopen(argv[2], "r");
	char toBeSearched[21];

	while (fscanf(f2, "%s\n", toBeSearched) != EOF)
	{
		bfs(arr, num, toBeSearched);						 
	}


	freeAll(num, arr);
	free(arr);
	return EXIT_SUCCESS;
}


