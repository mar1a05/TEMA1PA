#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct Player
{
    char *surname;
    char *firstName;
    int points;

} Player;

typedef struct TeamData
{
    int nrPlayers;
    char *teamName;
    Player *player;
    float teamPoints;

} TeamData;

typedef struct MatchTeamData
{
    char *teamName;
    float points;

} MatchTeamData;

typedef struct TeamNode
{
    TeamData teamData;
    struct TeamNode *next;

} TeamNode;

typedef struct Match
{
    MatchTeamData team1;
    MatchTeamData team2;

} Match;

typedef struct MatchNode
{
    Match teams;
    struct MatchNode *next;

} MatchNode;

typedef struct Queue
{
    MatchNode *front;
    MatchNode *rear;
} Queue;

typedef struct StackNode
{
    MatchTeamData team;
    struct StackNode *next;
} StackNode;

typedef struct BST
{
    MatchTeamData team;
    struct BST *left;
    struct BST *right;
} BST;

typedef struct AVL
{
    int height;
    MatchTeamData team;
    struct AVL *left;
    struct AVL *right;
}AVL;

//task 1

void addTeam(TeamNode **teamsHead, TeamData team);
void print(TeamNode *teamsHead);
void printOneTeam(TeamNode *teamsHead);
void freeTeam(TeamNode *teamsHead);
void deleteTeam(TeamNode **teamsHead, int i);
char *trimSpaces(char string[]);
void readTeams(char fileName[], TeamNode **teamsHead, int *nrTeams);
void writeTeams(char fileName[], TeamNode *teamsHead);
int *readTasks(char *fileName);
int getMaxPowerOf2(int nrTeams);
float minPoints(TeamNode *teamsHead);

//task 2

void clearTeams(TeamNode **teamsHead, int nrTeams);

//task 3

void deleteStack(StackNode **top);
int isStackEmpty(StackNode *top);
int isQueueEmpty(Queue *q);
void getTeamInfoFromQueueToStack(MatchTeamData source, MatchTeamData *target);
MatchTeamData topElementStackData(StackNode *top);
void createStacks(Queue *q, StackNode **Winners, StackNode **Losers);
void push(StackNode **top, MatchTeamData team);
void pop(StackNode **top);
void makeMatchesQueueFromStack(Queue **matches, StackNode **winners);
void addMatchFromStack(Queue **q, MatchTeamData team1, MatchTeamData team2);
void printStack(StackNode *stackTop, char fileName[], int i);
void printWinnersStack(StackNode *stackTop, char fileName[], int i);
void getTeamData(MatchTeamData *target, TeamData source);
Queue* createQueue();
void deleteQueue(Queue **q);
void addMatch(Queue **matches, TeamData team1, TeamData team2);
void removeMatch(Queue *matches);
void makeMatchesQueue(Queue **matches, TeamNode *teamsHead);
void printMatchesQueue(MatchNode *matches);
void printRound(MatchNode *matches, char fileName[], int i);
void rounds(StackNode **Winners, StackNode **Losers, Queue **matches, TeamNode *teamsHead, char fileName[], int round);

//task 4

BST *addInTree(BST *tree, MatchTeamData team);
BST *createBST(StackNode *Winners);
void printTreeNode(BST* tree, FILE* f);
void printTree(BST *tree, FILE* f);

//task 5

int nodeHeight(AVL *root);
int maxNumber(int a, int b);
AVL *RightRotation(AVL *z);
AVL *LeftRotation(AVL *z);
AVL *LRRotation(AVL *z);
AVL *RLRotation(AVL*z);
AVL *insert(AVL *root, MatchTeamData team);
AVL *createAVL(BST *BSTroot);
void createAVLfromBST(BST *BST, AVL **AVL);
// void printAVLLayer(AVL *root, FILE *f, int level);
void printAVL(AVL *root, FILE *f, int level);
void printTreeAVL(AVL *root, int level);





