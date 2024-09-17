//Disjoint Set Union
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
int parent[N];
int group_size[N];
int level[N];

/*  Initially:
      assume parent of all elements is -1 (element itself)
      initially group size of an element is 1
      level of each element is 0 */
void dsu_initialize(int n)
{
    for (int i=0; i<n; i++)
    {
        parent[i]=-1;
        group_size[i]=1;
        level[i]=0;
    }
}

//To find the leader of an element/group
int dsu_find(int x)
{
    if (parent[x]==-1) //if parent of an element is -1, then itself is the leader
    {
        return x;
    }
    int leader=dsu_find(parent[x]); //else start a recursion to find the leader
    parent[x]=leader; //Make the leader as parent of all elements. It is called path compression
    return leader;
}

//Simple Union
//this is not optimum function. Use union by size or union by rank/level
void dsu_union(int x, int y)
{
    int leader_x=dsu_find(x);
    int leader_y=dsu_find(y);
    parent[leader_x]=leader_y;
}

//dsu union by size
void dsu_union_size(int x, int y)
{
    int leader_x=dsu_find(x);
    int leader_y=dsu_find(y);
    if (group_size[leader_x]>group_size[leader_y])
    {
        parent[leader_y]=leader_x;
        group_size[leader_x]+=group_size[leader_y];
    }
    else
    {
        parent[leader_x]=leader_y; //if group sizes are equal, we assume leader_y is the parent of the leader_x
        group_size[leader_y]+=group_size[leader_x];
    }
}

//dsu union by rank or level
void dsu_union_level(int x, int y)
{
    int leader_x=dsu_find(x);
    int leader_y=dsu_find(y);
    if (level[leader_x] > level[leader_y]) //if you have higher level you are the leader
    {
        parent[leader_y]=leader_x;
    }
    else if (level[leader_x] < level[leader_y])
    {
        parent[leader_x]=leader_y;
    }
    else
    {
        parent[leader_y]=leader_x; //if you both have same level, we assume parent of leader_y is leader_x
        level[leader_x]++; //then leader_x will have 1 higher level than before.
    }
}

int main()
{
    int n;
    cin>>n;
    dsu_initialize(n);
    int q;
    cin>>q;
    while (q--)
    {
        int x,y;
        cin>>x>>y;
        //Now you can use dsu_union or dsu_union_size or dsu_union_level
        dsu_union_level(x,y);
        cout<<dsu_find(x)<<endl;
        cout<<dsu_find(y)<<endl;
    }

    return 0;
}
