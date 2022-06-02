#ifndef CONVEXFILL_H_INCLUDED
#define CONVEXFILL_H_INCLUDED
#include"FloodFill.h"
#include <vector>
#include <cmath>
#include <Windows.h>
#include "ScreenPixels.h"

#include <list>
using namespace std;
#define MAXENTRIES 600

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
                ScreenPixels::PutPixel(hdc,x,y,color);
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


struct EdgeRec
{
    double x;
    double minv;
    int ymax;
    bool operator<(EdgeRec r)
    {
        return x < r.x;
    }
};
typedef list<EdgeRec> EdgeList;

EdgeRec InitEdgeRec(POINT &v1, POINT &v2)
{
    if (v1.y > v2.y)
        swap(v1, v2);
    EdgeRec rec;
    rec.x = v1.x;
    rec.ymax = v2.y;
    rec.minv = (double)(v2.x - v1.x) / (v2.y - v1.y);
    return rec;
}

void InitEdgeTable(vector<POINT>polygon, int n, EdgeList table[])
{
    POINT v1 = polygon[n - 1];
    for (int i = 0; i < n; i++)
    {
        POINT v2 = polygon[i];
        if (v1.y == v2.y)
        {
            v1 = v2;
            continue;
        }
        EdgeRec rec = InitEdgeRec(v1, v2);
        table[v1.y].push_back(rec);
        v1 = polygon[i];
    }
}

void GeneralPolygonFill(HDC hdc, vector<POINT> polygon, int n, COLORREF c)
{
    EdgeList *table = new EdgeList[MAXENTRIES];
    InitEdgeTable(polygon, n, table);
    int y = 0;
    while (y < MAXENTRIES && table[y].size() == 0)
        y++;
    if (y == MAXENTRIES)
        return;
    EdgeList ActiveList = table[y];
    while (ActiveList.size() > 0)
    {
        ActiveList.sort();
        for (EdgeList::iterator it = ActiveList.begin(); it != ActiveList.end(); it++)
        {
            int x1 = (int)ceil(it->x);
            it++;
            int x2 = (int)floor(it->x);
            for (int x = x1; x <= x2; x++)
                SetPixel(hdc, x, y, c);
        }
        y++;
        EdgeList::iterator it = ActiveList.begin();
        while (it != ActiveList.end())
            if (y == it->ymax)
                it = ActiveList.erase(it);
            else
                it++;
        for (EdgeList::iterator it = ActiveList.begin(); it != ActiveList.end(); it++)
            it->x += it->minv;
        ActiveList.insert(ActiveList.end(), table[y].begin(), table[y].end());
    }
    delete[] table;
}

#endif // CONVEXFILL_H_INCLUDED
