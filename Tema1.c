#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

void readTeams(char fileName[], TeamNode **teamsHead, int *nrTeams)
{

    FILE *teamsFile = fopen(fileName, "r");
    //int nrTeams;

    fscanf(teamsFile, "%d", nrTeams);
    

    for (int i = 0; i < *nrTeams; i++)
    {
        TeamData team;
        fscanf(teamsFile, "%d", &team.nrPlayers);

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
        }
        addTeam(teamsHead, team);
    }
}


void print(TeamNode *teamsHead){
    while(teamsHead != NULL)
    {
        printf("%d %s", teamsHead->teamData.nrPlayers, teamsHead->teamData.teamName);
        for(int j = 0; j < teamsHead->teamData.nrPlayers; j++)
        {
            printf("%s %s %d\n", teamsHead->teamData.player[j].surname, teamsHead->teamData.player[j].firstName, teamsHead->teamData.player[j].points);
        }
        printf("\n");
        teamsHead = teamsHead->next;
    }
}

int main()
{
    TeamNode *teamsHead = NULL;
    int nrTeams = 0;
    readTeams("./date/t1/d.in", &teamsHead, &nrTeams);

    print(teamsHead);

    return 0;
}