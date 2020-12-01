#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct graphNode
{
	char name[21];
	int distance;
	struct graphNode* next;
};

struct graphNode* createNode(char str[21], int dist)
{
	struct graphNode* temp = (struct graphNode*) malloc(sizeof(struct graphNode));
	strcpy(temp -> name, str);
	temp -> next = 0;
	temp -> distance = dist;
	return temp;
}

struct graphNode* insertNode(struct graphNode* head, char str[21], int dist)
{
	struct graphNode* temp = head;
	
	if (head -> next == 0)
	{
		struct graphNode* nextNode = createNode(str, dist);
		head -> next = nextNode;
		return head;
	}
	
	if (strcmp(str, head->next->name) < 0)
	{
		struct graphNode* t = head->next;
		struct graphNode* nextNode = createNode(str, dist);
		head -> next = nextNode;
		nextNode -> next = t;
		return temp;
	}

	head = head -> next;

	while (head -> next != 0)
	{
		if (head -> next == 0)
		{
			struct graphNode* nextNode = createNode(str, dist);
			head -> next  = nextNode;
			return temp;
		}

		else if (strcmp(str, head->next->name) < 0 && strcmp(str, head->name) > 0)
		{
			struct graphNode* nextNode = createNode(str, dist);
			struct graphNode* f = head ->next;
			head -> next = nextNode;
			nextNode ->next = f;
			return temp;
		}
		head = head->next;
	}
	
	if (head ->next == 0)
	{
		struct graphNode* nextNode = createNode(str, dist);
		head ->next = nextNode;
	}

	return temp;
}

struct graphNode* alphNode(struct graphNode* head, char str[21])
{

	if (head == 0)
	{
		struct graphNode* newNode = createNode(str, 0);
		return newNode;
	}

	if (head -> next == 0)
	{
		struct graphNode* newNode = createNode(str, 0);
		head -> next = newNode;
		return head;
	}

	if (strcmp(str, head->name) < 0)
	{
		struct graphNode* newNode = createNode(str, 0);
		newNode -> next = head;
		return newNode;
	}

	struct graphNode* temp = head; 
	// head = head -> next;

	while (head -> next != 0)
	{

		if (strcmp(str, head->next->name) < 0 && strcmp(str, head->name) > 0)
		{
			struct graphNode* nextNode = createNode(str, 0);
			struct graphNode* f = head ->next;
			head -> next = nextNode;
			nextNode ->next = f;
			return temp;
		}
		head = head->next;
	}
	
	if (head ->next == 0)
	{
		struct graphNode* nextNode = createNode(str, 0);
		head ->next = nextNode;
	}

	return temp;
}

	

struct graphNode* enqueue(struct graphNode* head, char name[21], int dist)
{
	if (head == 0)
	{
		struct graphNode* lastNode = createNode(name, dist);
		return lastNode;
	}
	
	else
	{
		struct graphNode* temp = head;
		
		while(head->next != 0)
		{
			head = head->next;
		}
		struct graphNode* lastNode = createNode(name, dist);
		head->next = lastNode;
		return temp;
	}
}
	
// returns position of head in array
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


struct graphNode* dfs(struct graphNode** arr, char name[21], int num, struct graphNode* vHead)
{
	if (search(vHead, name) == 1)
	{
		return vHead;
	}

	vHead = enqueue(vHead, name, 0);
	printf("%s ", name);
	int pos = returnPos(arr, num, name);
	struct graphNode* temp = arr[pos];

	while(temp->next != 0)
	{
		dfs(arr, temp->next->name, num, vHead);
		temp = temp->next;
	}

	return vHead;
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
		arr[c] = createNode(tempListPointer -> name, 0);
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
	int distance;
	
	while (fscanf(f1, "%s %s %d\n", s1, s2, &distance) != EOF)
	{
		for (int x = 0; x < num; x++)
		{
			if (strcmp(arr[x] -> name, s1) == 0)
			{
				count = x;
				break;
			}
		}

		arr[count] = insertNode(arr[count], s2, distance);
	}

	struct graphNode* vHead = 0;

	vHead =	dfs(arr, arr[0] -> name, num, vHead);

	for (int x = 0; x < num; x++)
	{
		if (search(vHead, arr[x]->name) == 0)
		{
			vHead = dfs(arr, arr[x]->name, num, vHead); 
		}
	}

	printf("\n");
	
	struct graphNode* temp;	
	while (vHead != 0)
	{
		temp = vHead;
		vHead = vHead->next;
		free(temp);
	}
	
	freeAll(num, arr);
	free(arr);
	fclose(f1);
	return EXIT_SUCCESS;
}

