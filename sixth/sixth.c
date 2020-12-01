#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>

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


// adds alphabetically to a linked list (for original array adj list)
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

struct graphNode* pqInsert(struct graphNode* head, char val[21], int weight)
{
	if (head == 0)
	{
		struct graphNode* temp = createNode(val, weight);
		return temp;
	}

	else
	{
		struct graphNode* temphead = head;

		if (weight < head->distance)
		{
			head = createNode(val, weight);
			head->next = temphead;
			return head;
		}
		
		while ((head->next != 0) && (head->next->distance < weight)) 
		{	
			head = head->next;
		}
		struct graphNode* temp = createNode(val, weight);
		temp->next = head->next;
		head->next = temp;
		return temphead;
	}
}

struct graphNode* dequeue(struct graphNode* head)
{
	struct graphNode* temp = head;
	head = head -> next;
	free(temp);
	return head;
}


int* dijkstra(struct graphNode** arr, int num, char origin[21])
{
	int* visited = malloc(num*sizeof(int));
	for (int x = 0; x < num; x++)
	{
		visited[x] = 0;
	}

	int* distances = malloc(num*sizeof(int));
	for (int x = 0; x < num; x++)
	{
		distances[x] = INT_MAX;
	}

	distances[returnPos(arr, num, origin)] = 0;
	
	struct graphNode* pqHead = 0;
	pqHead = pqInsert(pqHead, origin, 0);
	
	while (pqHead != 0)
	{
		int index = returnPos(arr, num, pqHead->name);
		pqHead = dequeue(pqHead);
		visited[index] = 1;
		struct graphNode* ptr = arr[index];
		
		while (ptr != 0)
		{
			if (visited[returnPos(arr, num, ptr->name)] == 1)
			{
				ptr = ptr -> next;
				continue;
			}
			int newDist = distances[index] + ptr->distance;
			if (newDist < distances[returnPos(arr, num, ptr->name)])
			{
				distances[returnPos(arr, num, ptr->name)] = newDist;
				pqHead = pqInsert(pqHead, ptr->name, newDist);
			}
			
			ptr = ptr -> next;
		}	
	}
	while (pqHead != 0)
	{
		struct graphNode* temp = pqHead;
		pqHead = pqHead -> next;
		free(temp);
	}

	// MUST FREE DISTANCES IN MAIN, THEN FREE pqHEAD LINKED LIST
	free(visited);
	return distances;
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

	FILE* f2 = fopen(argv[2], "r");
	
	char origin[21];
	while(fscanf(f2, "%s\n", origin) != EOF)
	{
		int* distances = dijkstra(arr, num, origin);	
		
		for (int x = 0; x < num; x++)
		{
			if (distances[x] == INT_MAX)
				printf("%s INF\n", arr[x] -> name);
			else
				printf("%s %d\n", arr[x] -> name, distances[x]);
		}
		
		free(distances);
		printf("\n");
	}

	freeAll(num, arr);
	free(arr);
	fclose(f1);
	return EXIT_SUCCESS;
}



