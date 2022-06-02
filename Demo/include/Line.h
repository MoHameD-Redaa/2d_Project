#ifndef LINE_H
#define LINE_H
#include <cmath>
#include <iostream>
#include "ScreenPixels.h"
using namespace std;

void swap(int& x1, int& y1, int& x2, int& y2)
{
    int tmp = x1;
    x1 = x2;
    x2 = tmp;
    tmp = y1;
    y1 = y2;
    y2 = tmp;
}

int Round(double x)
{
    return (int)(x + 0.5);
}

void BresenhamLine(HDC hdc, int x1, int y1, int x2, int y2, COLORREF c)
{
    int dx = x2 - x1;
    int dy = y2 - y1;

    //  Check if x is the independent variable
    if(abs(dy) <= abs(dx) )
    {
        if(x1 > x2)
        {
            swap(x1, y1, x2, y2);
            dx = x2 - x1;
			dy = y2 - y1;
        }


        int d = dx - 2 * abs(dy);
        int d1 = 2*(dx - abs(dy) ) ;
        int d2 = -2 * abs(dy);

        int x = x1;
        int y = y1;
        ScreenPixels::PutPixel(hdc, x, y, c);

        while(x <= x2)
        {
            if(d <=0)
            {
                d+= d1;
                // Check if y2 > y1 then --> y++ or y1 > y2 then --> y--
                y += (dy > 0) ? 1 : -1;
            }
            else
                d+= d2;

            x++;
            ScreenPixels::PutPixel(hdc, x, y, c);
        }
    }
    else
    {
        printf("in bresnham m inverse\n");
        if(y1 > y2)
        {
            swap(x1, y1, x2, y2);
            dx = x2 - x1;
			dy = y2 - y1;

        }


        int d = dy - 2 * abs(dx);
        int d1 = 2*(dy - abs(dx) ) ;
        int d2 = -2 * (dx);

        int x = x1;
        int y = y1;
        ScreenPixels::PutPixel(hdc, x, y, c);

        while(y <= y2)
        {
            if(d <= 0)
            {
                d+= d1;
                // Check if x2 > x1 then --> x++ or x1 > x2 then --> x--
                x += (dx > 0) ? 1 : -1;
            }
            else
                d+= d2;

            y++;
            ScreenPixels::PutPixel(hdc, x, y, c);
        }

    }

}


// y = m*x + b || x = m^-1 * y + c
void DDALine(HDC hdc, int x1, int y1, int x2, int y2, COLORREF c)
{
    int dx = x2 - x1;
    int dy = y2 - y1;

    if(abs(dy) <= abs(dx))
    {
        if(x1 > x2)
            swap(x1, y1, x2, y2);
        int x = x1;
        double y = y1;
        double m = (double) dy/dx;
        ScreenPixels::PutPixel(hdc, x, y, c);
        while(x < x2)
        {
            x++;
            y = y + m;
            ScreenPixels::PutPixel(hdc, x, Round(y), c);
        }
    }
    else
    {
        if(y1 > y2)
            swap(x1, y1, x2, y2);

        double x = x1;
        int y = y1;
        double m = (double) dx/dy;
        ScreenPixels::PutPixel(hdc, x, y, c);
        while(y < y2)
        {
            y++;
            x += m;
            ScreenPixels::PutPixel(hdc, Round(x), y, c);
        }
    }
}


void ParametricLine(HDC hdc, int x1, int y1, int x2, int y2, COLORREF c)
{
    for(double t = 0; t <=1; t+= 0.001)
    {

        double x, y;
        x = x1 + t * (x2 - x1);
        y = y1 + t * (y2 - y1);
        ScreenPixels::PutPixel(hdc, Round(x), Round(y), c);
    }
}



#endif // LINE_H
