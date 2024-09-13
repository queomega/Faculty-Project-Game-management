#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
struct Player
{
    char *firstName;
    char *secondName;
    int points;
};
struct Team
{
    char *teamName;
    float teamPoints;
};
struct Node
{
    struct Team data;
    struct Node *next;
};
struct Match
{
    struct Team team1;
    struct Team team2;
};
struct MatchNode
{
    struct Match match;
    struct MatchNode *next;
};
struct Queue
{
    struct MatchNode *front;
    struct MatchNode *rear;
};
struct StackNode
{
    struct Team data;
    struct StackNode *next;
};
struct Stack
{
    struct StackNode *top;
};
struct BST
{
    struct Team data;
    struct BST *left;
    struct BST *right;
};
void addToList(struct Node**list,struct Team data)
{
    struct Node *new=malloc(sizeof(struct Node));
    new->data=data;
    new->next=*list;
    *list=new;
}
void read(struct Node**list ,FILE *f_in)
{
    int countTeams;
    fscanf(f_in,"%d",&countTeams);
    for(int i=0;i<countTeams;i++)
    {
        int playerCount;
        char teamName[100];
        fscanf(f_in,"%d",&playerCount);
        fgetc(f_in);
        fgets(teamName,sizeof(teamName),f_in);
        struct Team new;
        new.teamName=strdup(teamName);
        new.teamPoints=0;
        for(int j=0;j<playerCount;j++)
        {
            char firstName[100];
            char secondName[100];
            int points;
            fscanf(f_in, "%s %s %d",firstName,secondName,&points);
            new.teamPoints=new.teamPoints+points;
        }
        addToList(list,new);
    }
}
void write(struct Node*list,FILE *f_out)
{
        struct Node*temp=list;
        while(temp!=NULL)
        {
            fprintf(f_out,"%s",temp->data.teamName);
            temp=temp->next;
        }
}
int countTeams(FILE *f_in)
{
    rewind(f_in);
    int nr;
    fscanf(f_in,"%d",&nr);
    return nr;
}
int power(int countTeams)
{
    int power_2=1;
    while(power_2 <=countTeams)
    {
        power_2=power_2 * 2;
    }
    power_2=power_2 / 2;
    return power_2 ;
}
int searchPosition(struct Node***list)
{
    int minimPoints=1000;
    int position;
    int index=0;
    struct Node*temp=**list;
    while(temp!=NULL)
    {
        if(temp->data.teamPoints < minimPoints)
        {
            minimPoints=temp->data.teamPoints;
            position=index;
        }
        temp=temp->next;
        index++;
    }
    return position;
}
void eliminate(struct Node**list,FILE *f_in)
{
        int nr=countTeams(f_in);
        int power_2=power(nr);
        while(nr>power_2)
        {
            int position=searchPosition(&list);
            // Caz special pentru eliminatea primei pozitii
            if(position==0)
            {
                struct Node*temp=*list;
                *list=(*list)->next;
                free(temp->data.teamName);
                free(temp);
            }
            else
            {
                struct Node*anterior=NULL;
                struct Node*current=*list;
                int index=0;
                while (current!=NULL && index!=position)
                {
                    anterior=current;
                    current=current->next;
                    index++;
                }
                anterior->next=current->next;
                free(current->data.teamName);
                free(current);
            }
            nr--;
        }

}
void initQueue(struct Queue *queue)
{
    queue->front=NULL;
    queue->rear=NULL;
}
int isEmpty(struct Queue *queue)
{
    return queue->front==NULL;
}
void enqueue(struct Queue *queue ,struct Match newMatch)
{
    struct MatchNode *newNode=malloc(sizeof(struct MatchNode));
    newNode->match=newMatch;
    newNode->next=NULL;
    if(isEmpty(queue)==1)
    {
        queue->front=newNode;
        queue->rear=newNode;
    }
    else
    {
        queue->rear->next=newNode;
        queue->rear=newNode;
    }
}
void clearQueue(struct Queue *queue)
{
    struct MatchNode *current=queue->front;
    while(current!=NULL)
    {
        struct MatchNode *temp=current;
        current=current->next;
        free(temp);
    }
    queue->front=NULL;
    queue->rear=NULL;
}
void initStack(struct Stack *stack)
{
    stack->top=NULL;
}
int isEmptyStack(struct Stack *stack)
{
    return stack->top==NULL;
}
struct Team pop(struct Stack *stack)
{
    struct StackNode *temp=stack->top;
    struct Team data=temp->data;
    stack->top=temp->next;
    free(temp);
    return data;
}
void clearStack(struct Stack *stack)
{
    while(isEmptyStack(stack)!=1)
    {
        pop(stack);
    }
}
void push(struct Stack *stack,struct Team data)
{
    struct StackNode *newNode=malloc(sizeof(struct StackNode));
    newNode->data=data;
    newNode->next=stack->top;
    stack->top=newNode;
}
void eliminateWhitespace(char *string)
{
    int i=strlen(string)-1;
    while(i>=0 && (string[i]==' ' || string[i]=='\t' || string[i]=='\n' || string[i]=='\r'))
    {
        string[i]='\0';
        i--;
    }
}
void printQueue(struct Queue *matchQueue,int round,FILE *f_out)
{
    struct MatchNode *current=matchQueue->front;
    fprintf(f_out,"\n");
    fprintf(f_out,"--- ROUND NO:%d\n",round);
    while(current!=NULL)
    {
        struct Match match=current->match;
        eliminateWhitespace(match.team1.teamName);
        eliminateWhitespace(match.team2.teamName);
        fprintf(f_out,"%-33s-%33s\n",match.team1.teamName,match.team2.teamName);
        current=current->next;
    }
}
void printStack(struct Stack *winners,int round,FILE *f_out)
{
    struct StackNode *current=winners->top;
    fprintf(f_out,"\n");
    fprintf(f_out,"WINNERS OF ROUND NO:%d\n",round);
    while(current!=NULL)
    {
        fprintf(f_out,"%-34s-  %.02f\n",current->data.teamName,current->data.teamPoints);
        current=current->next;
    }
}
void createMatches(struct Node *list,struct Queue *matchQueue,int round,FILE *f_out,FILE *f_in)
{
    rewind(f_in);
    int teamCount,playerCount=0;
    fscanf(f_in,"%d",&teamCount);
    fscanf(f_in,"%d",&playerCount);
    struct Node *current=list;
    initQueue(matchQueue);
    while(current!=NULL && current->next!=NULL)
    {
        struct Match newMatch;
        current->data.teamPoints=current->data.teamPoints / playerCount;
        current->next->data.teamPoints=current->next->data.teamPoints / playerCount;
        newMatch.team1=current->data;
        newMatch.team2=current->next->data;
        eliminateWhitespace(newMatch.team1.teamName);
        eliminateWhitespace(newMatch.team2.teamName);
        enqueue(matchQueue,newMatch);
        current=current->next;
        current=current->next;
    }
    printQueue(matchQueue,round,f_out);
}
void decideWinner(struct Queue *matchQueue,struct Stack *winners,struct Stack *losers,FILE *f_out)
{
    while(matchQueue->front!=NULL)
    {
        struct MatchNode *currentMatchNode=matchQueue->front;
        struct Match currentMatch=currentMatchNode->match;
        struct Team winnerTeam;
        struct Team loserTeam;
        if(currentMatch.team1.teamPoints>currentMatch.team2.teamPoints)
        {
            currentMatch.team1.teamPoints=currentMatch.team1.teamPoints+1;
            winnerTeam=currentMatch.team1;
            loserTeam=currentMatch.team2;
        }
        else
        {
            currentMatch.team2.teamPoints=currentMatch.team2.teamPoints+1;
            winnerTeam=currentMatch.team2;
            loserTeam=currentMatch.team1;
        }
        push(winners,winnerTeam);
        push(losers,loserTeam);
        matchQueue->front=matchQueue->front->next;
    }
}
void refillQueueFromStack(struct Stack *winners,int round,struct Queue *matchQueue,FILE *f_out)
{
    struct StackNode *temp=winners->top;
    while(temp!=NULL)
    {
        struct Match newMatch;;
        newMatch.team1=temp->data;
        temp=temp->next;
        newMatch.team2=temp->data;
        enqueue(matchQueue,newMatch);
        temp=temp->next;
    }
}
int sizeQueue(struct Queue *queue)
{
    struct MatchNode *current=queue->front;
    int count=0;
    while(current!=NULL)
    {
        count++;
        current=current->next;
    }
    return count;

}
void processMatches(struct Node *list,struct Node **top8,struct Queue *matchQueue,struct Stack *winners,struct Stack *losers,FILE *f_out,FILE *f_in)
{
        initStack(winners);
        initStack(losers);
        int round=1;
        createMatches(list,matchQueue,round,f_out,f_in);
        while(matchQueue->front!=NULL && matchQueue->front->next!=NULL)
        {
            decideWinner(matchQueue,winners,losers,f_out);
            printStack(winners,round,f_out);
            clearStack(losers);
            refillQueueFromStack(winners,round,matchQueue,f_out);
            if(sizeQueue(matchQueue)==4)
            {
               struct StackNode *current=winners->top;
               *top8=NULL;
               while(current!=NULL)
               {
                struct Node *newNode=malloc(sizeof(struct Node));
                newNode->data=current->data;
                newNode->next=*top8;
                *top8=newNode;
                current=current->next;
               }
                
            }
            round++;
            clearStack(winners);
            printQueue(matchQueue,round,f_out);
        }
        if(matchQueue->front!=NULL)
        {
            decideWinner(matchQueue,winners,losers,f_out);
            printStack(winners,round,f_out);
        }
}
void insertInBST(struct BST **root,struct Team team)
{
    if(*root==NULL)
    {
        struct BST *new=malloc(sizeof(struct BST));
        new->data=team;
        new->left=new->right=NULL;
        *root=new;
    }
    else if(team.teamPoints>(*root)->data.teamPoints)
    {
        insertInBST(&((*root)->left),team);
    }
    else if(team.teamPoints<(*root)->data.teamPoints)
    {
        insertInBST(&((*root)->right),team);
    }
    else if(team.teamPoints==(*root)->data.teamPoints)
    {
        if(strcmp(team.teamName,(*root)->data.teamName) >0)
        {
            insertInBST(&((*root)->left),team);
        }
        else
        {
            insertInBST(&((*root)->right),team);
        }
    }
}
void ListToBST(struct Node *list,struct BST **root)
{   
    struct Node *current=list;
    while(current!=NULL)
    {
        insertInBST(root,current->data);
        current=current->next;
    }
}
void printBST(struct BST *root,FILE *f_out)
{
    if(root!=NULL)
    {
        printBST(root->left,f_out);
        fprintf(f_out,"%-33s -  %.2f\n",root->data.teamName,root->data.teamPoints);
        printBST(root->right,f_out);
    }
}
void task1(FILE *f_task,FILE *f_in,FILE *f_out)
{
    rewind(f_in);
    rewind(f_task);
    int task1,task2;
    fscanf(f_task,"%d %d",&task1,&task2);
    if(task1==1 && task2==0)
    {
        struct Node *list=NULL;
        read(&list,f_in);
        write(list,f_out); 
        free(list);
    }

}
void task2(FILE *f_task,FILE *f_in,FILE *f_out)
{
    rewind(f_in);
    rewind(f_task);
    int task1,task2,task3;
    fscanf(f_task,"%d %d %d",&task1,&task2,&task3);
    if(task2==1 && task3==0)
    {
        struct Node *list=NULL;
        read(&list,f_in);
        eliminate(&list,f_in);
        write(list,f_out); 
        free(list);
    }
}
void task3(FILE *f_task,FILE *f_in,FILE *f_out)
{
    rewind(f_in);
    rewind(f_task);
    int task1,task2,task3,task4;
    fscanf(f_task,"%d %d %d %d",&task1,&task2,&task3,&task4);
    if(task3==1 && task4==0)
    {
        struct Node *list=NULL;
        struct Node *top8=NULL;
        struct Queue matchQueue;
        struct Stack winners;
        struct Stack losers;
        read(&list,f_in);
        eliminate(&list,f_in);
        write(list,f_out);
        processMatches(list,&top8,&matchQueue,&winners,&losers,f_out,f_in); 
        free(list);
        free(top8);
    }
}
void task4(FILE *f_task,FILE *f_in,FILE *f_out)
{
    rewind(f_in);
    rewind(f_task);
    int task1,task2,task3,task4,task5;
    fscanf(f_task,"%d %d %d %d %d",&task1,&task2,&task3,&task4,&task5);
    if(task4==1 && task5==0)
    {
        struct Node *list=NULL;
        struct Node *top8=NULL;
        struct Queue matchQueue;
        struct Stack winners;
        struct Stack losers;
        struct BST *root=NULL;
        read(&list,f_in);
        eliminate(&list,f_in);
        write(list,f_out);
        processMatches(list,&top8,&matchQueue,&winners,&losers,f_out,f_in);
        ListToBST(top8,&root);
        fprintf(f_out,"\nTOP 8 TEAMS: \n");
        printBST(root,f_out);
        free(list);
        free(top8);
        free(root);


    }
}


