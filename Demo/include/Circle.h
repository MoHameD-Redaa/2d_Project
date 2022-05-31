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
    while(x < y)
    {
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
    while(x > y)
    {
        theta += dtheta;
        x = Round(r * cos(theta));
        y = Round(r * sin(theta));
        Draw8Points(hdc, xc, yc, x, y, c);
    }
}
// x'= x*cos(dtheta) - y*sin(dtheta)
// y'= x*sin(dtheta) + y*cos(dtheta)
void IterativePolerCircle(HDC hdc, int xc, int yc, int r, COLORREF c)
{
    double x = r ;
    double y = 0, x1;
    double dtheta = 1.0 / r;
    double sdtheta = sin(dtheta);
    double cdtheta = cos(dtheta);
    Draw8Points(hdc, xc, yc, x, y, c);
    while(x > y)
    {
        x1 = x * cdtheta - y * sdtheta;
        y = x * sdtheta + y * cdtheta;
        x = x1;
        Draw8Points(hdc, xc, yc, Round(x), Round(y), c);
    }
}

void MidpointCircle(HDC hdc, int xc, int yc, int r, COLORREF c)
{
    // Start from the Second octant.
    int x = 0, y = r;
    Draw8Points(hdc, xc, yc, x, y, c);
    while (x < y)
    {
        double d = (x + 1) * (x + 1) + (y - 0.5) * (y - 0.5) - r * r;
        //if the point outside the circle
        if (d >= 0)
            y--;
        x++;
        Draw8Points(hdc, xc, yc, x, y, c);
    }

}

void ModifiedMidpointCircle(HDC hdc, int xc, int yc, int r, COLORREF c)
{
    int x = 0;
    int y = r;
    int d = 1 - r;
    int c1 = 3 ;
    int c2 = 5 - 2*r ;
    Draw8Points(hdc, xc, yc, x, y, c);
    while(x<y)
    {
        if(d<0)
        {
            d += c1;
            c2 += 2;
        }
        else
        {
            d += c2;
            c2 += 4;
            y--;
        }
        d1 += 2;
        x++;
        Draw8Points(hdc, xc, yc, x, y, c);
    }

}
#endif // CIRCLE_H
