#ifndef CONVEXFILL_H_INCLUDED
#define CONVEXFILL_H_INCLUDED
#include"FloodFill.h"
#include <vector>
#include <cmath>
#include <Windows.h>

using namespace std;

#define EdgeTableSize 600
#define INT_MAX 99999999

struct EdgeTable
{
    int xmin,xmax;
};


//initializing EdgeTable
void InitEdgeTable(EdgeTable table[])
{
    for(int i=0; i < EdgeTableSize; i++)
    {
        table[i].xmin =  INT_MAX;
        table[i].xmax = - INT_MAX;
    }
}
void EdgeToTable(Vertex v1,Vertex v2,EdgeTable table[])
{
    if(v1.y==v2.y)
        return;
    if(v1.y>v2.y)
        swap(v1,v2);

    double minv=(double)(v2.x-v1.x)/(v2.y-v1.y);
    double x=v1.x;
    int y=v1.y;

    while(y<v2.y)
    {
        if(x<table[y].xmin)table[y].xmin=(int)ceil(x);
        if(x>table[y].xmax)table[y].xmax=(int)floor(x);
        y++;
        x+=minv;
    }
}

void DrawScanLines(HDC hdc,EdgeTable table[],COLORREF color)
{
    for(int y = 0; y < EdgeTableSize; y++)
        if(table[y].xmin < table[y].xmax)
            for(int x = table[y].xmin; x<= table[y].xmax; x++)
                SetPixel(hdc,x,y,color);
}

//void ConvexFill(HDC hdc,Vertex p[],int n,COLORREF color)
void ConvexFill(HDC hdc,vector<POINT> p,int n,COLORREF color)
{
    EdgeTable *table = new EdgeTable[EdgeTableSize];
    InitEdgeTable(table);
    Vertex v1(p[n-1].x, p[n-1].y);
    for(int i=0; i<n; i++)
    {
        Vertex v2(p[i].x, p[i].y);
        EdgeToTable(v1,v2,table);
        v1= *(new Vertex(p[i].x, p[i].y));
    }
    DrawScanLines(hdc,table,color);
    delete table;
}


#endif // CONVEXFILL_H_INCLUDED
