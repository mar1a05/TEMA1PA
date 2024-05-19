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


//task 1

void addTeam(TeamNode **teamsHead, TeamData team)
{

    TeamNode *newTeam = (TeamNode *)malloc(sizeof(TeamNode));
    newTeam->teamData = team;
    newTeam->next = *teamsHead;
    *teamsHead = newTeam;
    
}

void print(TeamNode *teamsHead){

    while(teamsHead != NULL)
    {
        //printf("%d\n", teamsHead->teamData.nrPlayers);
        printf("%.2f ", teamsHead->teamData.teamPoints);
        printf("%s", teamsHead->teamData.teamName);
        // for(int j = 0; j < teamsHead->teamData.nrPlayers; j++)
        // {
        //     printf("%s %s %d\n", teamsHead->teamData.player[j].surname, teamsHead->teamData.player[j].firstName, teamsHead->teamData.player[j].points);
        // }
        // printf("\n");
        teamsHead = teamsHead->next;
    }

}

void printOneTeam(TeamNode *teamsHead){
    
    printf("%d\n", teamsHead->teamData.nrPlayers);
    printf("%s", teamsHead->teamData.teamName);
    printf("%.2f\n", teamsHead->teamData.teamPoints);
    for(int j = 0; j < teamsHead->teamData.nrPlayers; j++)
    {
        printf("%s %s %d\n", teamsHead->teamData.player[j].surname, teamsHead->teamData.player[j].firstName, teamsHead->teamData.player[j].points);
    }
    printf("\n");

}

void freeTeam(TeamNode *teamsHead){
    
  free(teamsHead->teamData.teamName);

    for(int i = 0; i < teamsHead->teamData.nrPlayers; i++)
    { 
      free(teamsHead->teamData.player[i].firstName);
      free(teamsHead->teamData.player[i].surname);
    }

  free(teamsHead);

}

void deleteTeam(TeamNode **teamsHead, int i){

    TeamNode *aux = *teamsHead;
    
    if(i == 0)
    {
        TeamNode *deletedTeam = *teamsHead;
        *teamsHead = (*teamsHead)->next;
        freeTeam(deletedTeam);
        return;
    }
        
    while(aux != NULL && i > 1)
    {
        aux = aux->next;  //aux->next este echipa pe care vreau sa o sterg
        i--;
    }

    TeamNode *deletedTeam = aux->next;

    aux->next = aux->next->next;

    deletedTeam->next = NULL;

    freeTeam(deletedTeam);
}

char *trimSpaces(char string[])
{
    while(string[strlen(string) - 1] == ' ')
    {
        string[strlen(string) - 1] = '\0';
    }

    while(string[0] == ' ')
    {
        for(int i = 1; i < strlen(string); i++)
            string[i - 1] = string[i];
    }

    return string;
}

void readTeams(char fileName[], TeamNode **teamsHead, int *nrTeams)
{

    FILE *teamsFile = fopen(fileName, "r");
    fscanf(teamsFile, "%d", nrTeams);

    for (int i = 0; i < *nrTeams; i++)
    {
        int sum = 0;

        TeamData team;
        fscanf(teamsFile, "%d ", &team.nrPlayers);
        char teamName[50], surname[50], firstName[50];

        fgets(teamName, 1023, teamsFile);
        teamName[strlen(teamName)-2] = '\0';
        team.teamName = (char*)malloc((strlen(teamName))*sizeof(char));
        strcpy(team.teamName, trimSpaces(teamName));
        
        team.player = (Player *)malloc((team.nrPlayers) * sizeof(Player));

        for (int j = 0; j < team.nrPlayers; j++)
        {
            fscanf(teamsFile, "%s", surname);
            team.player[j].surname = (char*)malloc(sizeof(char) * (strlen(surname)+1));
            strcpy(team.player[j].surname, surname);
            fscanf(teamsFile, "%s", firstName);
            team.player[j].firstName = (char*)malloc(sizeof(char) * (strlen(firstName)+1));
            strcpy(team.player[j].firstName, firstName);
            fscanf(teamsFile, "%d", &team.player[j].points);
            sum += team.player[j].points;
        }

        team.teamPoints = (float)sum/team.nrPlayers;
        addTeam(teamsHead, team);
    }
}

void writeTeams(char fileName[], TeamNode *teamsHead){

    FILE *f = fopen(fileName, "w");
    
    while(teamsHead != NULL){
        fprintf(f, "%s\n", teamsHead->teamData.teamName);
                
        teamsHead = teamsHead->next;
    }
    fclose(f);

}

int *readTasks(char *fileName){

    FILE *f = fopen(fileName, "r");
    int *v = malloc(5*sizeof(int));
    fscanf(f, "%d %d %d %d %d", &v[0], &v[1], &v[2], &v[3], &v[4]);
    fclose(f);
    return v;
}

int getMaxPowerOf2(int nrTeams){

    int i = 1;

    while(pow(2, i) <= nrTeams){ 
        i++;
    }
    
    return (i-1);
}

float minPoints(TeamNode *teamsHead){

    float min = teamsHead->teamData.teamPoints;
    
    while(teamsHead != NULL)
    {    
        if(min > teamsHead->teamData.teamPoints)
            min = teamsHead->teamData.teamPoints;
        teamsHead = teamsHead->next;
    }

    return min;
}

//task2

void clearTeams(TeamNode **teamsHead, int nrTeams){
    
    int n = pow(2, getMaxPowerOf2(nrTeams));

    while(nrTeams > n)
    {    
        TeamNode *aux = *teamsHead;
        int i = 0;
        float min = minPoints(*teamsHead);
        //printf("%f\n", min);
        while(aux != NULL)
        {
            if(aux->teamData.teamPoints == min)
            {
                //printf("%d %s", i, aux->teamData.teamName);
                deleteTeam(teamsHead, i);
                nrTeams--;
                break;
            }

            aux = aux->next;
            i++;
        }
    }
}

//task 3

void deleteStack(StackNode **top)
{
    StackNode *temp;
    while((*top)!=NULL)
    {
        temp = *top;
        *top = (*top)->next;
        free(temp->team.teamName);
        free(temp);
    }
}

int isStackEmpty(StackNode *top)
{
    return top == NULL;
}

int isQueueEmpty(Queue *q)
{
    return (q->front == NULL);
}

void getTeamInfoFromQueueToStack(MatchTeamData source, MatchTeamData *target)
{
    strcpy((*target).teamName, source.teamName);
    (*target).points = source.points;
}


/////////////////////////////////



MatchTeamData topElementStackData(StackNode *top)
{

    if (isStackEmpty(top))
    {
        printf("Couldn't return top element data. Stack is empty");
        return;
    }

    return top->team;
}




/*
    print task 2
    task 3:
    for()
    {
        if(prima runda)
        {
            fac coada din lista initiala
        }
        else
        {
            populez coada din stiva de winners
            golesc winners
        }
        print coada
        populez winners losers si golesc coada cand le populez
        print winners
        golesc losers
    }
    
*/

void createStacks(Queue *q, StackNode **Winners, StackNode **Losers)
{
    // printMatchesQueue(q->front);
    while (!isQueueEmpty(q))
    {

        // printf("%f\n", q->front->teams.team1.points);
        if (q->front->teams.team1.points > q->front->teams.team2.points)
        {
            q->front->teams.team1.points += 1;
            push(Winners, q->front->teams.team1);
            push(Losers, q->front->teams.team2);

        }
        else
        {
            q->front->teams.team2.points += 1;
            push(Winners, q->front->teams.team2);
            push(Losers, q->front->teams.team1);
        }

        removeMatch(q);
    }
}




void push(StackNode **top, MatchTeamData team)
{
    StackNode *newTeam = (StackNode*)malloc(sizeof(StackNode));
    newTeam->team.teamName = malloc(sizeof(char) * strlen(team.teamName));
    getTeamInfoFromQueueToStack(team, &(newTeam->team));
    newTeam->next = *top;
    *top = newTeam;
}

void pop(StackNode **top)
{
    if(isStackEmpty(*top))
    {
        printf("Couldn't pop element. Stack is empty");
        return;
    }

    StackNode *temp = (*top);

    //if((*top)->next != NULL)
    *top = (*top)->next;

  free(temp->team.teamName);
  free(temp);
}

void makeMatchesQueueFromStack(Queue **matches, StackNode **winners) //?
{
    int i=0;

    StackNode *aux = *winners;
    while(!isStackEmpty(aux))
    {
        i++;
        aux = aux->next;
    }
    
    while(!isStackEmpty(*winners))
    {
        MatchTeamData team1, team2;
        team1.teamName = malloc(sizeof(char) * strlen((*winners)->team.teamName));
        // printf("%d\n", i);

        strcpy(team1.teamName, (*winners)->team.teamName);
        team1.points = (*winners)->team.points;


        // printf("%s\n", (*winners)->team.teamName);
        // if(i==4)
            // printf("%s %f\n", team1.teamName, team1.points);


        pop(winners);

        team2.teamName = malloc(sizeof(char) * strlen((*winners)->team.teamName));

        strcpy(team2.teamName, (*winners)->team.teamName);
        team2.points = (*winners)->team.points;
        // printf("%s\n", (*winners)->team.teamName);
        // if(i==4)
            // printf("%s %f\n", team2.teamName, team2.points);

        
        pop(winners);
        addMatchFromStack(matches, team1, team2);
        // if(i==4)
            // printMatchesQueue(*matches);
      free(team1.teamName);
      free(team2.teamName);
        
    }
    // printMatchesQueue(*matches);
}

void addMatchFromStack(Queue **q, MatchTeamData team1, MatchTeamData team2) //?
{
    
    // printf("%s %f\n", team1.teamName, team1.points);
    // printf("%s %f\n", team2.teamName, team2.points);
    
    
    MatchNode *newMatch=(MatchNode*)malloc(sizeof(MatchNode));
    newMatch->teams.team1.teamName = malloc(sizeof(char)*strlen(team1.teamName));
    newMatch->teams.team2.teamName = malloc(sizeof(char)*strlen(team2.teamName));

    strcpy(newMatch->teams.team1.teamName, team1.teamName);
    strcpy(newMatch->teams.team2.teamName, team2.teamName);
    newMatch->teams.team1.points = team1.points;
    newMatch->teams.team2.points = team2.points;

    newMatch->next = NULL;



    if((*q)->rear == NULL)
        (*q)->rear = newMatch;
    else
    {
        ((*q)->rear)->next = newMatch;
        ((*q)->rear) = newMatch;
    }    

    if((*q)->front == NULL)
        (*q)->front = (*q)->rear;
}


void printStack(StackNode *stackTop, char fileName[], int i)
{
    int j = 0;
    StackNode *aux = stackTop;
    while(aux != NULL)
    {
        j++;
        printf("%s %f\n", aux->team.teamName, aux->team.points);
        printf("isStackEmpty %d\n", aux->next == NULL);
        if(j == 5)
            return;
        aux = aux->next;
    }
}

void printWinnersStack(StackNode *stackTop, char fileName[], int i)
{
    FILE *f = fopen(fileName, "a");
    fprintf(f, "\nWINNERS OF ROUND NO:%d\n", i);
    
    StackNode *aux = stackTop;

    while(aux != NULL)
    {
        int spaces = 34 - strlen(aux->team.teamName);
        fprintf(f, "%s", aux->team.teamName);
        for(int i = 0; i < spaces; i++)
            fprintf(f, " ");
        fprintf(f, "-  %.2f\n", aux->team.points);
        
        aux = aux->next;
    }

    fclose(f);
}

void getTeamData(MatchTeamData *target, TeamData source)
{
    strcpy((*target).teamName, source.teamName);
    (*target).points = source.teamPoints;
}

Queue* createQueue(){
    Queue *q;
    q = (Queue*)malloc(sizeof(Queue));
    if(q == NULL)
        return NULL;
    q->front = q->rear = NULL;
    return q;
}

void deleteQueue(Queue **q)
{
    MatchNode *aux;
    while(!isQueueEmpty(*q)){

        aux = (*q)->front;
        (*q)->front = (*q)->front->next;

        free(aux);
    }

    free(*q);
}

void addMatch(Queue **matches, TeamData team1, TeamData team2)
{
    MatchNode *newMatch=(MatchNode*)malloc(sizeof(MatchNode));
    newMatch->teams.team1.teamName = malloc(sizeof(char)*strlen(team1.teamName));
    newMatch->teams.team2.teamName = malloc(sizeof(char)*strlen(team2.teamName));

    getTeamData(&(newMatch->teams.team1), team1);
    getTeamData(&(newMatch->teams.team2), team2);

    newMatch->next = NULL;

    if((*matches)->rear == NULL)
        (*matches)->rear = newMatch;
    else
    {
        ((*matches)->rear)->next = newMatch;
        ((*matches)->rear) = newMatch;
    }    

    if((*matches)->front == NULL)
        (*matches)->front = (*matches)->rear;
}

void removeMatch(Queue *matches)
{
    MatchNode *aux;

    if(isQueueEmpty(matches)) 
    {
        printf("No matches in queue");
        return;
    }

    aux = matches->front;

    if(matches->front->next != NULL)
    {
        matches->front = matches->front->next;
    }
    else
    {
        matches->front = NULL;
        matches->rear = NULL;
    }

    free(aux->teams.team1.teamName);
    free(aux->teams.team2.teamName);
    free(aux);

}

void makeMatchesQueue(Queue **matches, TeamNode *teamsHead)
{

    TeamNode *q = teamsHead;

    while(q != NULL){


        addMatch(matches, q->teamData, q->next->teamData);

        q = q->next->next;
    }
}

void printMatchesQueue(MatchNode *matches)
{
   int i = 0;
    while(matches != NULL)
    {
        i++;
        printf("%s %f\n", matches->teams.team1.teamName, matches->teams.team1.points);
        printf("%s %f\n\n", matches->teams.team2.teamName, matches->teams.team2.points);
        printf("isQueueEmpty %d\n", matches->next == NULL);
        if(i == 5)
            return;
        matches = matches->next;
    }

}


void printRound(MatchNode *matches, char fileName[], int i)
{
    FILE *f = fopen(fileName, "a");
    fprintf(f, "\n--- ROUND NO:%d\n", i);
    while(matches != NULL)
    {

        int spaces = 33 - strlen(matches->teams.team1.teamName);
        fprintf(f, "%s", matches->teams.team1.teamName);
        for(int j = 0; j < spaces; j++)
            fprintf(f, " ");

        fprintf(f, "-");

        spaces = 33 - strlen(matches->teams.team2.teamName);
        for(int j = 0; j < spaces; j++)
            fprintf(f, " ");
        fprintf(f, "%s\n", matches->teams.team2.teamName);

        matches = matches->next;
    }

    fclose(f);
}

void rounds(StackNode **Winners, StackNode **Losers, Queue **matches, TeamNode *teamsHead, char fileName[], int round)
{   
    if(round == 1)
    {
        makeMatchesQueue(matches, teamsHead);

    }
    else
    {
        makeMatchesQueueFromStack(matches, Winners);
    }

    printRound((*matches)->front, fileName, round);
    createStacks((*matches), Winners, Losers);

    printWinnersStack((*Winners), fileName, round);

    deleteStack(Losers);
}

int main(int argc, char **argv)
{
    TeamNode *teamsHead = NULL;
    int nrTeams = 0;

    readTeams(argv[2], &teamsHead, &nrTeams);

    int *tasks;
    tasks = readTasks(argv[1]);

   
    if(tasks[4] == 1)
        return 0;
    else if(tasks[3] == 1)
        return 0;
    else if(tasks[2] == 1)
    {
        clearTeams(&teamsHead, nrTeams);
        writeTeams(argv[3], teamsHead);
        
        Queue* matchesQueue = createQueue();
        // makeMatchesQueue(&matchesQueue, teamsHead);
        // printRound(matchesQueue->front, argv[3], 1);

        StackNode *Winners, *Losers;
        Winners = Losers = NULL;

        int nrOfRounds = getMaxPowerOf2(nrTeams);

        for(int i = 1; i <= nrOfRounds; i++)
        {
            //printf("round = %d\n", i+1);
            rounds(&Winners, &Losers, &matchesQueue, teamsHead, argv[3], i);
        }
        
    }
    else if(tasks[1] == 1)
    {
        clearTeams(&teamsHead, nrTeams); //task2
        writeTeams(argv[3], teamsHead);
    }
    else if(tasks[0] == 1)
    {
        writeTeams(argv[3], teamsHead); //task 1
    }
    
    
    return 0;
}