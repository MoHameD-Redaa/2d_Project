#ifndef CURVES_H_INCLUDED
#define CURVES_H_INCLUDED

#include"Line.h"

using namespace std;

struct Vector
{
    double v[2];
    Vector(double x = 0, double y = 0)
    {
        v[0] = x;
        v[1] = y;
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

void DrawCardinalSpline(HDC hdc,Vector P[], int n, COLORREF c)
{
    Vector T0(0.5*(P[2][0] - P[0][0]), 0.5*(P[2][1] - P[0][1]));
    for(int i = 2; i < n-1; i++)
    {
        Vector T1(0.5*(P[i+1][0] - P[i-1][0]), 0.5*(P[i+1][1] - P[i-1][1]));
        DrawHermiteCurve(hdc, P[i-1], T0, P[i], T1, c);
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
