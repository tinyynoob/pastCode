#include<stdio.h>
#include<stdlib.h>

typedef struct edge
{
	char name;
	int weight;
	struct edge* next;
}Edge;

typedef struct vertex
{
	char name;
	struct vertex* next;
	struct edge* son;
	int processed;
}Ver;

void test(Ver*);
void insertVertex(char, Ver**);
Ver* findVertex(char, Ver*);
int addEdge(char, char, int, Ver**);
int deleteEdge(char, char, Ver*);
int deleteVertex(char, Ver**);
void destroyGraph(Ver*);
Edge* shortestEdge(char, Ver*);
int depthFT(char, Ver*);
int BreadthFT(char, Ver*);
int MST(char, Ver*);
int shortestPath1(char, Ver*);
Ver* shortestPathTree(char, Ver*);
int shortestPath2(char, char, Ver*);
int graphProperty(Ver*);

void main()
{
	int N = 0;		//assume	//N=0 there will no extra vertex
	Ver* graph = NULL;
	int i, choice;
	int weight;
	char name, a, b;
	FILE* f;
	f = fopen("./topology.txt", "r");
	for (i = 0; i < N; i++)
		insertVertex(i + 65, &graph);		//assume the vertex name start from 'A' /  will start from '1' if change 65 to 49
	while (fscanf(f, "%c %c %d\n", &a, &b, &weight) != EOF)
	{
		if (!addEdge(a, b, weight, &graph))
		{
			printf("ERROR\n");
			continue;
		}
		//assume it is undirected graph
		addEdge(b, a, weight, &graph);
	}
	fclose(f);

	while (1)
	{
		printf("function:\n");
		printf("(0)test (1)insert vertex (2)delete vertex (3)add edge (4)delete edge (5)find vertex (6)traverse graph\n");
		printf("(7)MST (8)shortest path (9)graph property (10)destroy graph\n");
		printf("input your choice :");
		scanf("%d", &choice);
		if (choice == 0)
			test(graph);
		else if (choice == 1)
		{
			printf("name of the vertex :");
			scanf("%c%c", &name, &name);		//to ensure the compiler not read '\n' as char
			if (findVertex(i, graph))
				printf("the vertex has existed\n");
			else
				insertVertex(name, &graph);
		}
		else if (choice == 2)
		{
			printf("input the vertex to delete :");
			scanf("%c%c", &name, &name);
			if (!deleteVertex(name, &graph))
				printf("the vertex doesn't exist\n");
		}
		else if (choice == 3)
		{
			printf("the edge is from :");
			scanf("%c%c", &a, &a);
			printf("to :");
			scanf("%c%c", &b, &b);
			printf("weight of the edge :");
			scanf("%d", &weight);
			if (!addEdge(a, b, weight, &graph))
			{
				printf("add failed, please retry\n");
				continue;
			}
			//assume it is undirected graph
			addEdge(b, a, weight, &graph);
		}
		else if (choice == 4)
		{
			printf("delete the edge from :");
			scanf("%c%c", &a, &a);
			printf("to :");
			scanf("%c%c", &b, &b);
			if (!deleteEdge(a, b, graph))
			{
				printf("delete failed, please retry\n");
				break;
			}
			//assume it is undirected graph
			deleteEdge(b, a, graph);
		}
		else if (choice == 5)
		{
			printf("input name of the vertex :");
			scanf("%c%c", &name, &name);
			if (findVertex(name, graph))
				printf("1\n");
			else
				printf("0\n");
		}
		else if (choice == 6)
		{
			printf("starting point :");
			scanf("%c%c", &name, &name);
			printf("(1)Depth-first (2)Breadth-first :");
			scanf("%d", &i);
			if (i == 1)
			{
				if (!depthFT(name, graph))
					printf("there is not the vertex in graph\n");
			}
			else if (i == 2)
			{
				if (!BreadthFT(name, graph))
					printf("there is not the vertex in graph\n");
			}
			else
				printf("wrong input, please retry\n");
		}
		else if (choice == 7)
		{
			printf("\nnote: only use MST in strongly connected graph\nstarting point :");
			scanf("%c%c", &name, &name);
			if (!MST(name, graph))
				printf("there is not the vertex in graph\n");
		}
		else if (choice == 8)
		{
			printf("starting point :");
			scanf("%c%c", &name, &name);
			printf("(1)create shortest path graph (2)to another vertex :");
			scanf("%d", &i);		//the second one is not important
			if (i == 1)
			{
				if (!shortestPath1(name, graph))
					printf("there is not the vertex in graph\n");
			}
			else if (i == 2)
			{
				printf("end point :");
				scanf("%c%c", &b, &b);
				i = shortestPath2(name, b, graph);
				if (i == 0)
					printf("the graph is empty\n");
				else if (i == -1)
					printf("there is no path between %c and %c\n", name, b);
				else
					;
			}
			else
				printf("wrong input, please retry\n");
		}
		else if (choice == 9)
		{
			i = graphProperty(graph);
			if (!i)
				printf("the graph is empty\n");
			else if (i == 1)
				printf("weakly connected graph\n");
			else if (i == 2)
				printf("strongly connected graph\n");
			else if (i == 3)
				printf("disjoint graph\n");
		}
		else if (choice == 10)
		{
			destroyGraph(graph);
			break;
		}
		else
			printf("wrong input, please retry");
		printf("\n\n");
	}

	system("pause");
	return;
}

void test(Ver* graph)			//print graph
{
	Ver* p;
	Edge* q;
	for (p = graph; p; p = p->next)
	{
		printf(" %c ->", p->name);
		for (q = p->son; q; q = q->next)
			printf(" %c|%d", q->name, q->weight);
		printf("\n");
	}
}

void insertVertex(char name, Ver** graph)
{
	Ver* newNode, * p;
	newNode = (Ver*)malloc(sizeof(Ver));
	newNode->name = name;
	newNode->next = NULL;
	newNode->son = NULL;
	newNode->processed = 0;

	if (!*graph)		//nothing in graph
		*graph = newNode;
	else
	{
		for (p = *graph; p->next; p = p->next)
			;
		p->next = newNode;
	}
}

Ver* findVertex(char name, Ver* graph)	//if the vertex not exist, return NULL
{
	Ver* p;
	for (p = graph; 1; p = p->next)		//find the vertex, break
	{
		if (p == NULL)
			return NULL;
		if (p->name == name)
			return p;
	}
}

int addEdge(char a, char b, int weight, Ver** graph)		//from a to b
{
	Ver* p;
	Edge* newEdge, * q;

	//if the vertex doesnt exist, create it
	if (!findVertex(a, *graph))
		insertVertex(a, graph);
	if (!findVertex(b, *graph))
		insertVertex(b, graph);

	for (q = findVertex(a, *graph)->son; q; q = q->next)
	{
		if (q->name == b)		// the edge has existed
			return 0;
	}
	newEdge = (Edge*)malloc(sizeof(Edge));
	if (!newEdge)
		return 0;
	newEdge->name = b;
	newEdge->weight = weight;
	newEdge->next = NULL;

	p = findVertex(a, *graph);
	if (!p->son)
		p->son = newEdge;
	else
	{
		for (q = p->son; q->next; q = q->next)
			;
		q->next = newEdge;
	}
	return 1;
}

int deleteEdge(char a, char b, Ver* graph)
{
	Ver* p;
	Edge* q, * preQ;
	//printf("%c %c\n",a,b);
	if (!(p = findVertex(a, graph)))		//if the vertex not exists
		return 0;

	if (!(p->son))			//if the vertex point to nothing
		return 0;

	if (b == p->son->name)		//the first arc
	{
		q = p->son;
		p->son = p->son->next;
		free(q);
		return 1;
	}

	for (q = p->son->next, preQ = p->son; q; q = q->next)
	{
		if (q->name == b)		//found
		{
			preQ->next = q->next;
			free(q);
			return 1;
		}
		preQ = q;
	}
	return 0;			//the edge not exists
}

int deleteVertex(char name, Ver** graph)
{
	Ver* p, * preP;
	Edge* q;
	p = *graph;
	if (!p)			//the graph is empty
		return 0;

	if (p->name == name)		//the first vertex
		(*graph) = (*graph)->next;
	else
	{
		for (p = (*graph)->next, preP = (*graph); 1; p = p->next)
		{
			if (p == NULL)		//the vertex doesn't exist
				return 0;
			if (p->name == name)
			{
				preP->next = p->next;
				break;
			}
			preP = p;
		}
	}
	//found =>p

	while (p->son)		//delete all edge from p
	{
		q = p->son;
		p->son = p->son->next;
		free(q);
	}
	free(p);

	//delete all edge to the node
	for (p = *graph; p; p = p->next)
		deleteEdge(p->name, name, *graph);
	return 1;
}

void destroyGraph(Ver* graph)
{
	while (graph)
		deleteVertex(graph->name, &graph);
}

Edge* shortestEdge(char name, Ver* graph)		//return the edge of input vertex, will not return a edge which go to processed vertex
{
	Ver* p;
	Edge* q, * k;
	int min;
	p = findVertex(name, graph);
	if (!p->son)				//the vertex has no edge
		return NULL;

	k = NULL;
	for (q = p->son; q; q = q->next)
	{
		if (findVertex(q->name, graph)->processed)
			continue;
		if (k == NULL)		//first time
		{
			min = q->weight;
			k = q;
		}
		else if (q->weight < min)
		{
			min = q->weight;
			k = q;
		}
	}
	return k;
}

int depthFT(char name, Ver* graph)
{
	Ver* now;		//`now` points to the corresponding vertex in graph
	Edge* stack, * newNode;		//use Edge as node in stack
	Edge* q;
	now = findVertex(name, graph);
	if (!now)		//the node disjoint
		return 0;

	newNode = (Edge*)malloc(sizeof(Edge));
	newNode->name = now->name;
	newNode->next = NULL;
	now->processed = 1;
	stack = newNode;

	while (stack)
	{
		q = stack;		//pop
		stack = stack->next;
		printf("%c ", q->name);
		now = findVertex(q->name, graph);
		free(q);

		for (q = now->son; q; q = q->next)
		{
			if (findVertex(q->name, graph)->processed)		//the node has been processed
				continue;
			newNode = (Edge*)malloc(sizeof(Edge));		//create new node
			newNode->name = q->name;
			findVertex(q->name, graph)->processed = 1;

			newNode->next = stack;		//push
			stack = newNode;
		}
	}

	//reset all processed to 0
	for (now = graph; now; now = now->next)
		now->processed = 0;
	return 1;
}

int BreadthFT(char name, Ver* graph)
{
	Ver* now;	//p is in queue, `now` points to the corresponding vertex in graph
	Edge* queue, * newNode;		//use Edge as node in queue
	Edge* preQ, * q;
	now = findVertex(name, graph);
	if (!now)		//the node disjoint
		return 0;

	newNode = (Edge*)malloc(sizeof(Edge));
	newNode->name = now->name;
	newNode->next = NULL;
	now->processed = 1;
	queue = newNode;

	while (queue)
	{
		//dequeue
		if (queue->next == NULL)		//only one node in queue
		{
			q = queue;
			queue = NULL;
		}
		else
		{
			for (q = queue; q->next; q = q->next)		//more than one, q point to the last node
				preQ = q;
			preQ->next = q->next;
		}
		printf("%c ", q->name);
		now = findVertex(q->name, graph);
		free(q);

		for (q = now->son; q; q = q->next)
		{
			if (findVertex(q->name, graph)->processed)		//the node has been processed
				continue;
			newNode = (Edge*)malloc(sizeof(Edge));		//create new node
			newNode->name = q->name;
			findVertex(q->name, graph)->processed = 1;

			//enqueue
			newNode->next = queue;
			queue = newNode;
		}
	}

	//reset all processed to 0
	for (now = graph; now; now = now->next)
		now->processed = 0;
	return 1;
}

int MST(char name, Ver* graph)
{
	Ver* p, * copyGraph, * now;	//p is in copy graph, `now` points to the corresponding vertex in initial graph
	Edge* SEb;
	char SEa;
	now = findVertex(name, graph);
	if (!now)		//starting point doesnt exist
		return 0;

	copyGraph = NULL;
	insertVertex(now->name, &copyGraph);		//first node
	now->processed = 1;

	while (1)
	{
		//shortest edge is from SEa to SEb
		SEb = NULL;
		for (p = copyGraph; p; p = p->next)		//compare shortest edge of every vertex processed
		{
			if (shortestEdge(p->name, graph) == NULL)
				continue;
			else if (SEb == NULL)
			{
				SEa = p->name;
				SEb = shortestEdge(p->name, graph);
			}
			else if (shortestEdge(p->name, graph)->weight < SEb->weight)
			{
				SEa = p->name;
				SEb = shortestEdge(p->name, graph);
			}
		}
		if (SEb == NULL)		//there is no vertex to go, so the tree has been finished
			break;
		addEdge(SEa, SEb->name, SEb->weight, &copyGraph);
		//assume it is undirected graph
		addEdge(SEb->name, SEa, SEb->weight, &copyGraph);
		findVertex(SEb->name, graph)->processed = 1;
	}

	printf("the tree:\n");
	test(copyGraph);

	//reset all processed to 0
	for (p = graph; p; p = p->next)
		p->processed = 0;

	destroyGraph(copyGraph);
	return 1;
}

int shortestPath1(char name, Ver* graph)
{
	Ver* copyGraph, * p;
	Edge* q;
	if (!copyGraph)
		return 0;

	copyGraph = shortestPathTree(name, graph);		//create the tree
	printf("\n");
	for (p = copyGraph; p; p = p->next)		//print everything but first edge of every vertex (it record where is comes from)
	{
		printf(" %c ->", p->name);
		for (q = p->son->next; q; q = q->next)
		{
			if (!q)
				break;
			else
				printf(" %c|%d", q->name, q->weight);
		}
		printf("\n");
	}

	destroyGraph(copyGraph);
	return 1;
}

Ver* shortestPathTree(char name, Ver* graph)
{
	Ver* copyGraph, * delea, * p, * now;	//p is in copy graph, `now` points to the corresponding vertex in initial graph
	Edge* q, * k, * last, * SEb, * newEdge;
	if (!findVertex(name, graph))		//cant find the vertex
		return NULL;
	now = findVertex(name, graph);
	now->processed = 1;

	//first edge the vertex point to is where it come from
	//and its weight is total weight from starting point
	copyGraph = NULL;
	addEdge(now->name, now->name, 0, &copyGraph);
	for (q = now->son; q; q = q->next)		//first node
	{
		addEdge(now->name, q->name, q->weight, &copyGraph);
		addEdge(q->name, now->name, q->weight, &copyGraph);
	}

	while (1)
	{
		//shortest edge is from SEa to SEb
		SEb = NULL;
		for (p = copyGraph; p && findVertex(p->name, graph)->processed; p = p->next)		//compare shortest edge of every vertex
		{
			if (shortestEdge(p->name, graph) == NULL)
				continue;
			else if (SEb == NULL)
				SEb = shortestEdge(p->name, graph);
			else if (shortestEdge(p->name, graph)->weight < SEb->weight)
				SEb = shortestEdge(p->name, graph);
		}
		if (SEb == NULL)		//there is no vertex to go, so the tree has been finished
			break;

		now = findVertex(SEb->name, graph);
		now->processed = 1;
		for (q = now->son; q; q = q->next)		//update with the new node
		{
			if (findVertex(q->name, graph)->processed)
				continue;
			else if (!findVertex(q->name, copyGraph))		//find a vertex which hasnt been visited
			{
				last = findVertex(now->name, copyGraph)->son;		//what `now` points to comes from
				addEdge(now->name, q->name, q->weight, &copyGraph);
				addEdge(q->name, now->name, q->weight + last->weight, &copyGraph);
			}
			else if (q->weight + findVertex(now->name, copyGraph)->son->weight < findVertex(q->name, copyGraph)->son->weight)
			{
				last = findVertex(now->name, copyGraph)->son;		//what `now` points to comes from
				delea = findVertex(findVertex(q->name, copyGraph)->son->name, copyGraph);


				addEdge(now->name, q->name, q->weight, &copyGraph);
				deleteEdge(q->name, delea->name, copyGraph);
				deleteEdge(delea->name, q->name, copyGraph);

				newEdge = (Edge*)malloc(sizeof(Edge));
				newEdge->name = now->name;
				newEdge->weight = q->weight + last->weight;
				newEdge->next = findVertex(q->name, copyGraph)->son;
				findVertex(q->name, copyGraph)->son = newEdge;
			}
		}
	}

	//test(copyGraph);

	//reset all processed to 0
	for (now = graph; now; now = now->next)
		now->processed = 0;
	return copyGraph;
}

int shortestPath2(char a, char b, Ver* graph)
{
	Ver* copyGraph;
	Edge* q, * stack, * newNode;		//use edge as node in stack
	int totalWeight;
	if (!copyGraph)
		return 0;
	if (a == b)
	{
		printf("\n path : %c \ttotal weight = 0\n", a);
		return 1;
	}
	copyGraph = shortestPathTree(a, graph);
	q = findVertex(b, copyGraph);
	if (!q)			//cant achieve the point
		return -1;

	newNode = (Edge*)malloc(sizeof(Edge));
	newNode->next = NULL;
	newNode->name = b;
	//newNode->weight dont care
	stack = newNode;

	//push
	for (totalWeight = q->weight; q->weight; q = findVertex(q->name, copyGraph)->son)
	{
		newNode = (Edge*)malloc(sizeof(Edge));
		newNode->next = stack;
		newNode->name = q->name;
		stack = newNode;
	}

	printf("\n path: ");
	//pop
	while (stack)
	{
		q = stack;
		stack = stack->next;
		printf("%c ", q->name);
		free(q);
	}
	printf("\ttotal weight = %d", totalWeight);

	destroyGraph(copyGraph);
	return 1;
}

int graphProperty(Ver* graph)		// 1_weak 2_strong 3_disjoint
{
	Ver* p, * k;
	Edge* q;
	int flag = 1;
	if (!graph)
		return 0;

	for (k = graph; k; k = k->next)
	{
		if (k->son == NULL)		//k points to nobody
		{
			flag = 0;
			for (p = graph; p; p = p->next)
				for (q = p->son; q; q = q->next)
					if (q->name == k->name)
					{
						flag = 1;		//somebody points to k
						return 1;
					}
		}
	}
	if (!flag)		//nobody points to `k`
		return 3;

	return 2;
}
