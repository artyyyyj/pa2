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

void findDegree(int num, struct graphNode** arr, char c[21])
{
	int counter = 0;
	for (int x = 0; x < num; x++)
	{
		if (strcmp(arr[x] -> name, c) == 0)
		{
			counter = x;
		}
	}

	struct graphNode* temp = arr[counter];
	counter = 0;
	while (temp -> next != 0)
	{
		counter++;
		temp = temp -> next;
	}

	printf("%d\n", counter);
}

void printAdj(int num, struct graphNode** arr, char c[21])
{
	 int counter = 0;
	 for (int x = 0; x < num; x++)
	 {
	  	if (strcmp(arr[x] -> name, c) == 0)
		{
			counter = x;
		}
	}
		
	 struct graphNode* temp = arr[counter];
	temp = temp -> next;
	 while (temp !=0)
	 {
		printf("%s ", temp->name);
		temp = temp ->next;
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
	
	// READ SECOND FILE
	FILE* f2 = fopen(argv[2], "r");
	char toDo;
	char node[21];
	char degree = 'd';

	while (fscanf(f2, "%c %s\n", &toDo, node) != EOF)
	{
		if (degree == toDo)
		{
			findDegree(num, arr, node);
		}

		else
		{
			printAdj(num, arr, node);
		}
	}


	freeAll(num, arr);
	free(arr);
	fclose(f1);
	fclose(f2);
	return EXIT_SUCCESS;
}
