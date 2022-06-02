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
	public:
		static vector<int> pixel;

		static vector<COLORREF> colors;

		static void PutPixel(HDC hdc, int x, int y, COLORREF c) {
			//Point p(x,y);
			pixel.push_back(x);
			pixel.push_back(y);
			colors.push_back(c);
			SetPixel(hdc, x, y, c);
		}

		static void clear() {
			pixel.clear();
			colors.clear();
		}

};
vector<int> ScreenPixels::pixel;
vector<COLORREF> ScreenPixels::colors;

#endif // SCREENPIXELS_H_INCLUDED