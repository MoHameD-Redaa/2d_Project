#ifndef CURVES_H_INCLUDED
#define CURVES_H_INCLUDED

#include <Windows.h>
#include "Line.h"
#include <vector>



struct Vector
{
    int x, y;
    double v[2];
    Vector(double xIn = 0, double yIn = 0)
    {
        v[0] = xIn;
        v[1] = yIn;

        x = xIn;
        y = yIn;
    }
    double& operator[](int i)
    {
        return v[i];
    }
};

// We need to figure out how we will update it to fill the square.
void DrawHermiteCurve(HDC hdc,Vector& p1, Vector& T1, Vector& p2, Vector& T2, COLORREF c)
{
    double a0 = p1[0], a1 = T1[0],
           a2 = -3 * p1[0] - 2 * T1[0] + 3 * p2[0] - T2[0],
           a3 = 2 * p1[0] + T1[0] - 2 * p2[0] + T2[0];

    double b0 = p1[1], b1 = T1[1],
           b2 = -3 * p1[1] - 2 * T1[1] + 3 * p2[1] - T2[1],
           b3 = 2 * p1[1] + T1[1] - 2 * p2[1] + T2[1];

    for (double t = 0; t <= 1; t += 0.001)
    {
        double t2 = t*t, t3 = t2*t;
        double x = a0 + a1*t + a2*t2 + a3*t3;
        double y = b0 + b1*t + b2*t2 + b3*t3;

        SetPixel(hdc, Round(x), Round(y), c);
    }
}


void DrawBezierCurve(HDC hdc,Vector& P0,Vector& P1,Vector& P2,Vector& P3,int numpoints)
{
    Vector T0((double)3*(P1.x- P0.x),3*((double)P1.y-P0.y));
    Vector T1(3*((double)P3.x-P2.x),3*((double)P3.y-P2.y));
    DrawHermiteCurve(hdc,P0,T0,P3,T1,numpoints);
}

void fillingRecWithBeizer(HDC hdc, Point p1, Point p2, Point p3, Point p4)
{
    printf("p1.y= %d, p4.y= %d\n", p1.y, p4.y);
    for (int i = p4.y; i < p1.y; i++)
    {  
        printf("in looop\n");

        Vector mid;
        mid[0] = (int)(p2.x + p1.x)/2;
        mid[1] = i;

        Vector v1;
        v1[0] = p1.x; v1[1] = i;
        
        Vector v2;
        v2[0] = p2.x; v2[1] = i;

        Vector t1;
        t1[0] = mid[0] + 20;
        t1[1] = i - 15;

        Vector t2;
        t2[0] = mid[0] - 40;
        t2[1] = i + 55;

        DrawBezierCurve(hdc, v1, t1, t2, v2, 2);
    }
    
}

void DrawCardinalSpline(HDC hdc,vector<POINT> P, int n, COLORREF c)
{
    Vector T0(0.5*(P[1].x - P[0].x), 0.5*(P[1].y - P[0].y));
    for(int i = 2; i < n-1; i++)
    {
        Vector T1(0.5*(P[i+1].x - P[i-1].x), 0.5*(P[i+1].y - P[i-1].y));
        Vector tmpP1(P[i-1].x, P[i-1].y);
        Vector tmpP2(P[i].x, P[i].y);

        DrawHermiteCurve(hdc, tmpP1, T0, tmpP2, T1, c);
        T0 = T1;
    }
}



void FillSquareWithHermit(HDC hdc, int x1, int y1, int length, COLORREF c) {
	int x2 = x1 + length;

	DDALine(hdc, x1, y1, x2, y1, c);

	DDALine(hdc, x1, y1, x1, y1 + length, c);

	DDALine(hdc, x1 + length, y1 + length, x1, y1 + length, c);

	DDALine(hdc, x1 + length, y1 + length, x1 + length, y1, c);


	while (x1 <= x2) {

		Vector p1(x1, y1);
		Vector T1(0,0);
		Vector p2(x1, y1 + length);
		Vector T2(0,0);
		DrawHermiteCurve(hdc, p1, T1, p2, T2, c);
		x1++;
	}

}

#endif // CURVES_H_INCLUDED