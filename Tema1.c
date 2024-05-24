#include "Tema1.h"


//task 1

int main(int argc, char **argv)
{
    TeamNode *teamsHead = NULL;
    int nrTeams = 0;

    readTeams(argv[2], &teamsHead, &nrTeams);
    
    int *tasks;
    tasks = readTasks(argv[1]);

    BST *tree = NULL;
   
    if(tasks[4] == 1)
        return 0;
    
    else if(tasks[2] == 1)
    {
        clearTeams(&teamsHead, nrTeams);
        writeTeams(argv[3], teamsHead);
        
        Queue* matchesQueue = createQueue();

        StackNode *Winners, *Losers;
        Winners = Losers = NULL;

        int nrOfRounds = getMaxPowerOf2(nrTeams);
        
        for(int i = 1; i <= nrOfRounds; i++)
        {
            rounds(&Winners, &Losers, &matchesQueue, teamsHead, argv[3], i);

            if(i == nrOfRounds - 3 && tasks[3] == 1) //task 4
            {
                tree = createBST(Winners);
            }
        }
        if(tasks[3] == 1) // print task 4
        {
            if(tree != NULL)
            {
                FILE *f = fopen(argv[3], "a");

                fprintf(f, "\nTOP 8 TEAMS:\n");
                printTree(tree, f);
                
                fclose(f);            
            }
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