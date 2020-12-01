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


struct graphNode* pop(struct graphNode* head)
{
	if (head == 0)
	{
		return 0;
	}

	if (head -> next == 0)
	{
		free(head);
		return 0;
	}

	struct graphNode* temp = head;
	head = head->next;
	free(temp);
	return head;
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


int dfs(int i, char val[21], int* visited, struct graphNode** result, struct graphNode** arr, int num)
{
	int x = returnPos(arr, num, val);
	visited[x] = 1;
	
	struct graphNode* temp = arr[x] -> next;
	
	while (temp != 0)
	{
		if (visited[returnPos(arr, num, temp->name)] == 0)
			i = dfs(i, temp->name, visited, result, arr, num);

		temp = temp -> next;
	}

	result[i] = arr[returnPos(arr, num, val)];
	return i - 1;
}


struct graphNode** tsort(struct graphNode** arr, int num)
{
	int* visited = malloc(num*sizeof(int));
	for (int x = 0; x < num; x++)
	{
		visited[x] = 0;
	}

	struct graphNode** result = malloc(num*sizeof(struct graphNode));
	int i = num - 1;
	
	for (int x = 0; x < num; x++)
	{
		if (visited[x] == 0)
			i = dfs(i, arr[x] ->name, visited, result, arr, num);
	}
	
	free(visited);
	return result;	
}


int* spa(struct graphNode** arr, int num, char val[21], struct graphNode** tsort)
{
	int* distances = malloc(num*sizeof(int));
	for (int x = 0; x < num; x++)
	{
		distances[x] = INT_MAX;
	}
	
	distances[returnPos(arr, num, val)] = 0;
	
	for (int x = 0; x < num; x++)
	{
		int index = returnPos(arr, num, tsort[x] -> name);
		
		if (distances[index] != INT_MAX)
		{
		struct graphNode* temp = arr[index] -> next;
		if (temp != 0)
		{
			while (temp != 0)
			{
				int new = distances[index] + temp->distance;
				if  (distances[returnPos(arr, num, temp->name)] == INT_MAX)
				{
					 distances[returnPos(arr, num, temp->name)] = new;
				}
				else 
				{
					if ( new < distances[returnPos(arr, num, temp->name)])
						distances[returnPos(arr, num, temp->name)] = new;
				}
				temp = temp -> next;
			}
		}
		}
	}
	return distances;	
}	


int find(struct graphNode** arr, int index, int* visited, int* queue, int num)
{
	visited[index] = 1;
	queue[index] = 1;
	struct graphNode* temp = arr[index]->next;
	
	while (temp != 0)
	{
		if (visited[returnPos(arr, num, temp->name)] == 0)
		{	
			if (find(arr, returnPos(arr, num, temp->name), visited, queue, num) == 1)
				return 1;
		}

		else if (queue[returnPos(arr, num, temp->name)] == 1)
			return 1;

		temp = temp -> next;
	}
	
	queue[index] = 0;
	return 0;
}

int isCyclic(struct graphNode** arr, int num)
{
	int* visited = malloc(num*sizeof(int));
	int* queue = malloc(num*sizeof(int));

	for (int x = 0; x < num; x++)
	{
		visited[x] = 0;
	}
	
	int fff = 0;

	switch(fff)
	{
		case 0:

	for (int x = 0; x < num; x++)
	{
		queue[x] = 0;
	}
		break;
	}

	for (int x = 0; x < num; x++)
	{
		if (visited[x] == 0)
		{

			if (find(arr, x, visited, queue, num) == 1)
			{
				free(visited);
				free(queue);
				return 1;
			}
		}
	}
	int return1 = 5;
	
	if (return1 == 5)
	{	
	free(queue);
	free(visited);
	}
	return 0;
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

	int cyclic = isCyclic(arr, num);
	if (cyclic == 1)
	{
		printf("CYCLE\n");
		return EXIT_SUCCESS;
	}
		
	FILE* f2 = fopen(argv[2], "r");
	struct graphNode** tsorted = tsort(arr, num);
	
	char node[21];
	printf("\n");
	while (fscanf(f2, "%s\n", node) != EOF)
	{			
		int* distances = spa(arr, num, node, tsorted);
		for (int x = 0; x < num; x++)
		{
			if (distances[x] == INT_MAX)
				printf("%s INF\n", arr[x]->name);
			else
			printf("%s %d \n", arr[x]->name, distances[x]);
		}
		free(distances);
		printf("\n");
	}		

	free(tsorted);	

	freeAll(num, arr);
	free(arr);
	fclose(f1);
	fclose(f2);
	return EXIT_SUCCESS;
}


