#ifndef SCREENPIXELS_H_INCLUDED
#define SCREENPIXELS_H_INCLUDED

#include<vector>
using namespace std;

struct Point
{
    int x, y;
    Point(int x1 = 0, int y1 = 0)
    {
        x = x1;
        y = y1;
    }
};

class ScreenPixels
{
    static vector<Point> pixel;

	static vector<COLORREF> colors;

	static void PutPixel(HDC hdc, int x, int y, COLORREF c) {
	    Point p(x,y);
		pixel.push_back(p);
		colors.push_back(c);
		SetPixel(hdc, x, y, c);
	}

	static void clear() {
		points.clear();
		colors.clear();
	}

};

#endif // SCREENPIXELS_H_INCLUDED
