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

typedef struct TeamNode
{
    TeamData teamData;
    struct TeamNode *next;

} TeamNode;

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
        team.teamName = (char*)malloc((strlen(teamName)+1)*sizeof(char));
        strcpy(team.teamName, teamName);
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
        fprintf(f, "%s", teamsHead->teamData.teamName);
        
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
    
    return pow(2, i-1);
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
    
    int n = getMaxPowerOf2(nrTeams);

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

int main(int argc, char **argv)
{
    TeamNode *teamsHead = NULL;
    int nrTeams = 0;

    readTeams(argv[2], &teamsHead, &nrTeams);

    //print(teamsHead);
    //deleteTeam(&teamsHead, 3);
    //print(teamsHead);

    int *tasks;
    tasks = readTasks(argv[1]);

    if(tasks[4] == 1)
        return 0;
    else if(tasks[3] == 1)
        return 0;
    else if(tasks[2] == 1)
        return 0;
    else if(tasks[1] == 1)
    {
        clearTeams(&teamsHead, nrTeams); //task2
        writeTeams(argv[3], teamsHead);
    }
    else if(tasks[0] == 1)
        writeTeams(argv[3], teamsHead);
    

    return 0;
}