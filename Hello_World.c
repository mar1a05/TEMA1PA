#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char nume[30];
    char prenume[30];
    int punctaj;
} Jucator;

typedef struct Echipa
{
    int nrJucatori;
    char numeEchipa[50];
    Jucator *j;
    float punctaj;

    struct Echipa *next;
} Echipa;

Echipa *readTeams(Echipa *head, char filename[])
{
    
    FILE *in = fopen(filename, "r");
    int nrE;
    char s[1024];

    fscanf(in, "%d", &nrE);

    for (int i = 0; i < nrE; i++)
    {
        Echipa *e = (Echipa *)malloc(1 * sizeof(Echipa));
        e->next = NULL;
        e->punctaj = 0;

        fscanf(in, "%d", &e->nrJucatori); // cietsc nr de jucatori din echipa
        fgets(e->numeEchipa, 1023, in);   // cietsc numele echipei

        e->j = (Jucator *)malloc(e->nrJucatori * sizeof(Jucator));
        for (int j = 0; j < e->nrJucatori; j++)
            fscanf(in, "%s%s%d", e->j[j].nume, e->j[j].prenume, &e->j[j].punctaj); // citesc jucatorii
        fgets(s, 1023, in);                                                        // sar peste linia libera

        if (head == NULL) // O(1)
            head = e;
        else
        {
            e->next = head;
            head = e;
        }
    }

    return head;
}

int main()
{
    int n;
    Echipa *head = NULL, *head2;
    //head = readTeams(head, "Echipe.txt");
    //print(head);

    //eliminare(head);


    //FILE *in=fopen("date/t1/d.in", "r");
    FILE *out=fopen("out/r.out", "w");

    head2 = readTeams(head, "date/t1/d.in");
    head = head2;

    char s[1024];
    //fclose(in);
    fclose(out);

    return 0;
}