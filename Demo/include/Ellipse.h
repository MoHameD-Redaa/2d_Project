#ifndef ELLIPSE_H_INCLUDED
#define ELLIPSE_H_INCLUDED
#include"Line.h"

void Draw4Points(HDC hdc, int xc, int yc, int x, int y, COLORREF c)
{
    SetPixel(hdc, xc + x, yc + y, c);
    SetPixel(hdc, xc + x, yc - y, c);
    SetPixel(hdc, xc - x, yc - y, c);
    SetPixel(hdc, xc - x, yc + y, c);
}

void DirectEllipse(HDC hdc, int xc, int yc, int a, int b, COLORREF c)
{
    double x = a;
    int y = 0;
    Draw4Points(hdc, xc, yc, Round(x), y, c);

    while (x * b * b > y * a * a)
    {
        y++;
        x = a * sqrt(1 - (y * y * 1.0) / (b * b));
        Draw4Points(hdc, xc, yc, Round(x), y, c);
    }

    int x1 = 0;
    double y1 = b;
    Draw4Points(hdc, xc, yc, x1, Round(y1), c);

    while (x1 * b * b < y1 * a * a)
    {
        x1++;
        y1 = b * sqrt(1 - (x1 * x1 * 1.0) / (a * a));
        Draw4Points(hdc, xc, yc, x1, Round(y1), c);
    }
}

void PolarEllipse(HDC hdc, int xc, int yc, int a, int b, COLORREF c)
{
    double x = a, y = 0, theta = 0;
    double dtheta = 1.0 / max(a, b);
    double sdtheta = sin(dtheta);
    double cdtheta = cos(dtheta);

    Draw4Points(hdc, xc, yc, Round(x), Round(y), c);

    while (x > 0)
    {
        x = a * cos(theta);
        y = b * sin(theta);
        theta += dtheta;
        Draw4Points(hdc, xc, yc, Round(x), Round(y), c);
    }

}

void IterativePolarEllipse(HDC hdc, int xc, int yc, int a, int b, COLORREF c)
{
    double x = 0, y = b, theta = 0;
    double dtheta = 1.0 / max(a, b);
    double sdtheta = sin(dtheta);
    double cdtheta = cos(dtheta);

    Draw4Points(hdc, xc, yc, Round(x), Round(y), c);

    while (y > 0)
    {
        double x1 = x * cdtheta - a * (y / b) * sdtheta;
        y = y * cdtheta + (x / a) * b * sdtheta;
        x = x1;
        Draw4Points(hdc, xc, yc, Round(x), Round(y), c);
    }

}

void MidpointEllipse(HDC hdc, int xc, int yc, int a, int b, COLORREF c)
{
    int x = a, y = 0;
    int b2 = b * b;
	int a2 = a * a;
    double d = b2 * pow((a - 0.5), 2) + a2 - a2 * b2;
    Draw4Points(hdc, xc, yc, x, y, c);

    while (x * b * b > y * a * a)
    {
        if (d <= 0)
        {
            d += a2 * (2 * y + 3);
            y++;
        }

        else
        {
            d += a2 * (2 * y + 3) + b2 * (-2 * x + 2);
            x--;
            y++;
        }
        Draw4Points(hdc, xc, yc, x, y, c);
    }

    x = 0, y = b;
	d = b2 + a2 * pow((b - 0.5), 2) - a2 * b2;

	Draw4Points(hdc, xc, yc, x, y, c);

	while (x * b * b < y * a * a) {

		if (d <= 0) {
			d += b2 * (2 * x + 3);
			x++;
		}
		else {
			d += b2 * (2 * x + 3) + a2 * (-2 * y + 2);
			x++;
			y--;
		}
		Draw4Points(hdc, xc, yc, x, y, c);
	}

}







#endif // ELLIPSE_H_INCLUDED
