#ifndef CIRCLE_H
#define CIRCLE_H
#include"Line.h"


void Draw8Points(HDC hdc, int xc, int yc, int x, int y, COLORREF c)
{

	SetPixel(hdc,xc + x, yc + y,c);

    SetPixel(hdc,xc + x, yc - y,c);

	SetPixel(hdc,xc - x, yc - y,c);

	SetPixel(hdc,xc - x, yc + y,c);

	SetPixel(hdc,xc + y, yc + x,c);

	SetPixel(hdc,xc + y, yc - x,c);

    SetPixel(hdc,xc - y, yc - x,c);

	SetPixel(hdc,xc - y, yc + x,c);

}

void DirectCircle(HDC hdc, int xc, int yc, int r, COLORREF c)
{
    int x = 0 ;
    int y = r ;
    double r2 = r*r;
    Draw8Points(hdc, xc, yc, x, y, c);
    while(x < y){
        x++;
        y = Round(sqrt(r2 - x*x));
        Draw8Points(hdc, xc, yc, x, y, c);
    }

}

void PolarCircle(HDC hdc, int xc, int yc, int r, COLORREF c)
{
    int x = r ;
    int y = 0 ;
    double theta = 0;
    double dtheta = 1.0 / r;
    Draw8Points(hdc, xc, yc, x, y, c);
    while(x > y){
        theta += dtheta;
        x = Round(r * cos(theta));
        y = Round(r * sin(theta));
        Draw8Points(hdc, xc, yc, x, y, c);
    }
}

void IterativePolerCircle(HDC hdc, int xc, int yc, int r, COLORREF c)
{

}

void MidpointCircle(HDC hdc, int xc, int yc, int r, COLORREF c)
{

}

void ModifiedMidpointCircle(HDC hdc, int xc, int yc, int r, COLORREF c)
{

}
#endif // CIRCLE_H
