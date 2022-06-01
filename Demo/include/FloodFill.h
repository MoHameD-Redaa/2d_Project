#ifndef FLOODFILL_H_INCLUDED
#define FLOODFILL_H_INCLUDED
#include <stack>

using namespace std;

void IRecursiveFloodFill(HDC hdc, int x, int y, COLORREF borderColor, COLORREF fillColor)
{
    COLORREF color = GetPixel(hdc, x, y);

    if (color == borderColor || color ==  fillColor)
        return;

    SetPixel(hdc, x, y, fillColor);

    IRecursiveFloodFill(hdc, x + 1, y, borderColor, fillColor);
    IRecursiveFloodFill(hdc, x - 1, y, borderColor, fillColor);
    IRecursiveFloodFill(hdc, x, y + 1, borderColor, fillColor);
    IRecursiveFloodFill(hdc, x, y - 1, borderColor, fillColor);
}

/* struct Vertex
{
    int x, y;
    Vertex(int x, int y) :x(x), y(y)
    {
    }
}; */

void NonRecursiveFloodFill(HDC hdc, int x, int y, COLORREF borderColor, COLORREF fillColor)
{
    stack<Vertex> st;
    st.push(Vertex(x, y));
    while (!st.empty())
    {
        Vertex p = st.top();
        st.pop();

        COLORREF color = GetPixel(hdc, p.x, p.y);

        if (color == borderColor || color == fillColor)
            continue;


        SetPixel(hdc, p.x, p.y, fillColor);

        st.push(Vertex(p.x, p.y - 1));
        st.push(Vertex(p.x, p.y + 1));
        st.push(Vertex(p.x - 1, p.y));
        st.push(Vertex(p.x + 1, p.y));


    }
}

#endif // FLOODFILL_H_INCLUDED
