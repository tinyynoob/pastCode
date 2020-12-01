#include<stdio.h>
#include<stdlib.h>

typedef struct node
{
	int data;
	struct node* left;
	struct node* right;
}NODE;

int BST_insert(NODE**,int);
int BST_delete(NODE**,int);
void BST_print(NODE*);
void BST_distroy(NODE**);
void BST_print2(NODE*);
void BST_print3(NODE*);

void main()
{
	NODE *root=NULL;
	int data;
	FILE *f;
	f=fopen("./input.txt","r");
	while(fscanf(f,"%d",&data)!=EOF)
	{
		if(BST_insert(&root,data)==2)
			printf("insert failed\n");
	}
	fclose(f);

	int choice;
	while(1)
	{
		printf("(1)inorder traverse (2)delete element (3) exit  (4)preorder traverse (5)postorder traverse :");
		scanf("%d",&choice);
		if(choice==1)
			BST_print(root);
		else if(choice==2)
		{
			printf("type in the data to delete:");
			scanf("%d",&data);
			if(BST_delete(&root,data)==2)
				printf("not exist\n");
		}
		else if(choice==3)
		{
			BST_distroy(&root);
			break;
		}
		else if(choice==4)
			BST_print2(root);
		else if(choice==5)
			BST_print3(root);
		else
			printf("error choice, please retry\n");
		printf("\n\n");
	}
	system("pause");
}

void insertRecur(NODE* node,NODE* root)
{
	if(node->data<root->data)
	{
		if(root->left)
			insertRecur(node,root->left);
		else
			root->left=node;
	}
	else
	{
		if(root->right)
			insertRecur(node,root->right);
		else
			root->right=node;
	}
}

int BST_insert(NODE** root,int data)
{
	NODE *newNode;
	newNode=(NODE*)malloc(sizeof(NODE));
	if(!newNode)
		return 2;
	newNode->data=data;
	newNode->left=NULL;
	newNode->right=NULL;
	if(!*root)
		*root=newNode;
	else
		insertRecur(newNode,*root);
	return 1;
}

NODE* deleteRecur(NODE *root,int data,int *flagptr)
{
	if(!root)
		;		//no sub tree, cant found the node, flag remains 2
	else if(data<root->data)
		root->left=deleteRecur(root->left,data,flagptr);
	else if(data>root->data)
		root->right=deleteRecur(root->right,data,flagptr);
	else		//found  *root
	{
		if(root->left==NULL&&root->right==NULL)		//no subtree
		{
			free(root);
			*flagptr=1;
			return NULL;
		}
		else if(root->left&&root->right==NULL)		//only left tree
		{
			NODE *p;
			p=root->left;
			root->data=p->data;
			root->right=p->right;
			root->left=p->left;
			free(p);
			*flagptr=1;
		}
		else if(root->right&&root->left==NULL)		//only right tree
		{
			NODE *p;
			p=root->right;
			root->data=p->data;
			root->left=p->left;
			root->right=p->right;
			free(p);
			*flagptr=1;
		}
		else		//both subtree
		{
			NODE *p=root->left;		//p is new root
			NODE *q=p;
			while(p->right)
				p=p->right;		//	q is parent of p
			
			root->data=p->data;
			if(p!=q)
				q->right=p->left;
			else
				root->left=p->left;
			free(p);
			*flagptr=1;
		}
	}
	return root;
}

int BST_delete(NODE** root,int data)
{
	int flag=2;			//record whether the data exist
	(*root)=deleteRecur(*root,data,&flag);
	return flag;
}

void BST_print(NODE* root)
{
	if(root)		//if node exists, to left, to self, to right
	{
		BST_print(root->left);
		printf("%d ",root->data);
		BST_print(root->right);
	}
}

void BST_distroy(NODE** root){
	while(*root)
		BST_delete(root,(*root)->data);
}

void BST_print2(NODE* root)
{
	if(root)		//if node exists, print self, to left, to right
	{
		printf("%d ",root->data);
		BST_print2(root->left);
		BST_print2(root->right);
	}
}

void BST_print3(NODE* root)
{
	if(root)		//if node exists, to left, to self, to right
	{
		BST_print3(root->left);
		BST_print3(root->right);
		printf("%d ",root->data);
	}
}
