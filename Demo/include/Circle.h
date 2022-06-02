#ifndef CIRCLE_H
#define CIRCLE_H
#include"Line.h"
#include "ScreenPixels.h"

void Draw8Points(HDC hdc, int xc, int yc, int x, int y, COLORREF c)
{

    ScreenPixels::PutPixel(hdc,xc + x, yc + y,c);

    ScreenPixels::PutPixel(hdc,xc + x, yc - y,c);

    ScreenPixels::PutPixel(hdc,xc - x, yc - y,c);

    ScreenPixels::PutPixel(hdc,xc - x, yc + y,c);

    ScreenPixels::PutPixel(hdc,xc + y, yc + x,c);

    ScreenPixels::PutPixel(hdc,xc + y, yc - x,c);

    ScreenPixels::PutPixel(hdc,xc - y, yc - x,c);

    ScreenPixels::PutPixel(hdc,xc - y, yc + x,c);

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
        c1 += 2;
        x++;
        Draw8Points(hdc, xc, yc, x, y, c);
    }
}


void FillCircleQuarter(HDC hdc, int xc, int yc, int x, int y, int quarter_num, COLORREF c)
{
    if(quarter_num == 1)
    {
        DDALine(hdc, xc, yc, xc + x, yc - y, c);
        DDALine(hdc, xc, yc, xc + y, yc - x, c);
    }
    else if(quarter_num == 2)
    {
        DDALine(hdc, xc, yc, xc - x, yc - y, c);
        DDALine(hdc, xc, yc, xc - y, yc - x, c);

    }
    else if(quarter_num == 3)
    {
        DDALine(hdc, xc, yc, xc - x, yc + y, c);
        DDALine(hdc, xc, yc, xc - y, yc + x, c);

    }
    else if(quarter_num == 4)
    {
        DDALine(hdc, xc, yc, xc + x, yc + y, c);
        DDALine(hdc, xc, yc, xc + y, yc + x, c);
    }

    ScreenPixels::PutPixel(hdc,xc + x, yc + y,c);
    ScreenPixels::PutPixel(hdc,xc + x, yc - y,c);
    ScreenPixels::PutPixel(hdc,xc - x, yc - y,c);
    ScreenPixels::PutPixel(hdc,xc - x, yc + y,c);

    ScreenPixels::PutPixel(hdc,xc + y, yc + x,c);
    ScreenPixels::PutPixel(hdc,xc + y, yc - x,c);
    ScreenPixels::PutPixel(hdc,xc - y, yc - x,c);
    ScreenPixels::PutPixel(hdc,xc - y, yc + x,c);

}


void FillCircleWithLines(HDC hdc, int xc, int yc, int r, int quarter_num, COLORREF c)
{
    int x = 0;
    int y = r;
    int d = 1 - r;
    int c1 = 3 ;
    int c2 = 5 - 2*r ;
    FillCircleQuarter(hdc, xc, yc, x, y, quarter_num, c);
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
        c1 += 2;
        x++;
        FillCircleQuarter(hdc, xc, yc, x, y, quarter_num, c);
    }


}

void fillingQWithCircles(HDC hdc, int xc, int yc, int r, int n, COLORREF c)
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

    int xS = 1, yS = 1;

    if(n==2)
        xS = -1;
    else if(n==3)
    {
        xS = -1;
        yS = -1;
    }
    else
        yS= -1;


    int tmpR = 5;

    while(tmpR < r)
    {
        double x = tmpR ;
        double y = 0, x1;
        double dtheta = 1.0 / tmpR;
        double sdtheta = sin(dtheta);
        double cdtheta = cos(dtheta);
        
        while(x > y)
        {
            x1 = x * cdtheta - y * sdtheta;
            y = x * sdtheta + y * cdtheta;
            x = x1;



            if(n == 1)
            {
                ScreenPixels::PutPixel(hdc,xc + (x), yc - (y),c);
                ScreenPixels::PutPixel(hdc,xc + (y) , yc - (x),c);
                
            }
            else if(n == 2)
            {
                ScreenPixels::PutPixel(hdc,xc - (x), yc - (y),c);
                ScreenPixels::PutPixel(hdc,xc - (y) , yc - (x),c);

            }
            else if(n == 3)
            {
                ScreenPixels::PutPixel(hdc,xc - (x), yc + (y),c);
                ScreenPixels::PutPixel(hdc,xc - (y) , yc + (x),c);
            }
            else if(n == 4)
            {
                ScreenPixels::PutPixel(hdc,xc + (x), yc + (y),c);
                ScreenPixels::PutPixel(hdc,xc + (y) , yc + (x),c);
            }

            
            //Draw8Points(hdc, xc, yc, Round(x), Round(y), c);
        }

        tmpR += 5;
    }

    
    
}


#endif // CIRCLE_H
