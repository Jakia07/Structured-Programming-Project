#include <stdio.h>

int pc=0,mark=0;
int spath=1000000000;
int forbidden_node;

struct Node
{
    int nodeid;
    int adjcount;
    int adjs[10];
    int costs[10];
};
int addNode (struct Node * p, int nid, int count)
{
    int i =0, ncount = count;
    for (i=0; i<count; i++)
    {
        if (p[i].nodeid == nid)
        {
            break;
        }
    }
    if (i == count)
    {
        p[i].nodeid = nid;
        p[i].adjcount = 0;
        ncount++;
    }
    return ncount;
}

void addAdjacent (struct Node *p, int nid1, int nid2, int cost, int count)
{
    int i =0, index;
    for (i=0; i<count; i++)
    {
        if (p[i].nodeid == nid1)
        {
            int c = p[i].adjcount;
            p[i].adjs[c] = nid2;
            p[i].costs[c] = cost;
            p[i].adjcount = c+1;

            break;
        }
    }
}

int added (int * list, int lcount, int nid)
{
    int i =0;
    for (i=0; i<lcount; i++)
    {
        if (list[i] == nid)
        {
            return 1;
        }
    }
    return 0;
}


void findPath (struct Node * p, int count, int start, int end, int * list, int *clist, int lcount)
{
    int index = 0, i=0;


    //check if list contains the end node
    if (list[lcount-1] == end)
    {    mark=0;
        int tcost = 0;


        for (i=0; i<lcount; i++)
        {
            if(list[i]==forbidden_node)
                mark=1;

        }
        if(mark!=1)
        {   printf ("\n");
            pc++;
            for (i=0; i<lcount; i++)
            {
                printf (" %d ", list[i]);
                tcost += clist[i];
            }
            printf (" cost = %d", tcost);
        }

        return;
    }

    for (i=0; i<count; i++)
    {
        if (p[i].nodeid == start)
        {
            index = i;
            break;
        }
    }

    for (i=0; i<p[index].adjcount; i++)
    {
        int a = added (list, lcount, p[index].adjs[i]);
        if (a == 0)
        {
            list[lcount] = p[index].adjs[i];
            clist[lcount] = p[index].costs[i];
            lcount++;

            findpath (p, count, p[index].adjs[i], end, list, clist, lcount);
            lcount--;
        }
    }
}
int main()
{

    struct Node nodes[50];
    int nodecount = 0;
    int n1=0, n2=0, c = 0;

    while (1)
    {
        printf ("n1, n2, cost ? ");
        scanf("%d %d %d", &n1, &n2, &c);
        if (n1 == -9 || n2 == -9 || c== -9)
        {
            break;
        }
        nodecount = addNode (&nodes[0], n1, nodecount);
        nodecount = addNode (&nodes[0], n2, nodecount);

        addAdjacent (&nodes[0], n1, n2, c, nodecount);
        addAdjacent (&nodes[0], n2, n1, c, nodecount);
    }

    int start, end;
    printf ("start, end ? ");
    scanf ("%d %d", &start, &end);
    printf("Forbidden node ?");
    scanf("%d",&forbidden_node);
    int list[50], clist[50], lcount = 0;
    list[0] = start;
    clist[0] = 0;
    lcount = 1;

    findPath (nodes, nodecount, start, end, list, clist, lcount);
    printf("Total possible path=",pc);
    if(pc==0)
        printf("There is no path");


    return 0;
}


