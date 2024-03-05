#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FALSE 0
#define TRUE 1

struct TreeNode
{
  char name[20];
  char office[10];
  struct TreeNode* left;
  struct TreeNode* right;
  struct TreeNode* next; //this is used for multiple office numbers, if there is more than one, memory will be allocated for it.
};

struct TreeNode* CreateTree(void);
struct TreeNode* Insert(char[20],char[10], struct TreeNode*); 
void DisplayTree(struct TreeNode*);
void searchInstructor(char[], struct TreeNode*);
void doubleOffice(struct TreeNode*);

int main()
{
    struct TreeNode* myTree;
    int exit;
    char val[20], office[10], search[20]; 
    char command;
	myTree = CreateTree();
    exit = FALSE;
	while (!exit)
	{
      printf("\nMenu:\n i)nitialize\n n)ew element \n s)earch instructor \n d)ouble office \n e)xit\nEnter command: ");
      scanf(" %c", &command);
     switch(command)
     {
		case 'i':
			myTree = CreateTree();
			break;
		case 'n':
			printf("enter name: ");
			scanf("%s", val);
			fflush(stdin);
			
			printf("\nenter office:");
			scanf("%s",office[10]);
			fflush(stdin);
			myTree = Insert(val,office, myTree);
			printf("Tree now:\n");
			DisplayTree(myTree);
			break;
        case 's':
            printf("\nenter name to search:");
            scanf("%s", search);
            fflush(stdin);
            searchInstructor(search, myTree);
            break;
        case 'd':
            doubleOffice(myTree);
            break;
  		case 'e':
			exit = TRUE;
			break;
		default:
			printf("command not recognized\n");
			break;
	}//end switch
  }//end while

  printf("\n\n");
  system("PAUSE");
  return 0;
}//end main

struct TreeNode* CreateTree(void)
{
    return NULL;
}

struct TreeNode* Insert(char instructor[20],char office[10], struct TreeNode* t)
{
    if(t == NULL)
    {
        t = (struct TreeNode*) malloc(sizeof(struct TreeNode));
        if(t == NULL)
            printf("Out of memory space!!!\n");
        else
        {
            strcpy(t->name, instructor);
            t->left = t->right = NULL, t->next=NULL; //added t->next=NULL for single office cases.
            strcpy(t->office, office);
        }
    }
    else if(strcmp(t->name,instructor)<0)
    {
        t->left = Insert(instructor,office,t->left);
    }
    else if(strcmp(t->name,instructor)>0)
    {
        t->right = Insert(instructor,office, t->right);
    }
    else //same name case
    {
        if(strcmp(t->office,office)==0)
            printf("\nError! Entered same name and office!\n");
        else
        {
            t->next=(struct TreeNode*) malloc(sizeof(struct TreeNode));
            strcpy(t->next->name, instructor);
            strcpy(t->next->office, office);
            t->next->left = t->next->right = NULL;
        }

    }

	return t;
}

void DisplayTree(struct TreeNode* t)
{
   if (t !=NULL)
   {
		DisplayTree(t->left);
		printf("%s", t->name);
		printf(" %s\n", t->office); //added info for office.
		DisplayTree(t->right);
   }
}

void searchInstructor(char search_name[20], struct TreeNode* t)
{
    if(strcmp(search_name,t->name)==0)
    {
        printf("Found! Office number is %s", t->office);
    }
    else if(strcmp(search_name,t->name)<0)
    {
        if(t->left==NULL)
        {
            printf("Not found!");
        }
        else
            searchInstructor(search_name,t->left);
    }
    else if(strcmp(search_name,t->name)>0)
    {
        if(t->right==NULL)
        {
            printf("Not found!");
        }
        else
            searchInstructor(search_name,t->right);
    }

}

void doubleOffice(struct TreeNode* t)
{
    if(t->next!=NULL)
    {
        printf("%s",t->name); //if next is not null, it should have multiple offices. print the name

        //do the traversal again to check for other names which have multiple offices.
        if(t->left!=NULL)
        {
            doubleOffice(t->left);
        }
        if(t->right!=NULL)
        {
            doubleOffice(t->right);
        }
    }
    else
    {
        if(t->left!=NULL)
        {
            doubleOffice(t->left);
        }
        if(t->right!=NULL)
        {
            doubleOffice(t->right);
        }

    }
}
