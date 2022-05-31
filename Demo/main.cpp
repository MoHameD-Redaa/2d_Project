#include <Windows.h>

#include"Line.h"
#include"Circle.h"
#include "Clipping.h"

#include <iostream>

using namespace std;



#define COLOR RGB(0, 0, 255)
#define EXITE 5

enum algoType {DDA_Line, BRESN_LINE, param_LINE, D_CIRCLE, POLAR_CIRCLE, ItPOLAR_CIRCLE, COHENALGO};



//algoType line;

// menu function
void makeMenu(HWND hwnd) {

    HMENU Menubar;
    HMENU subMenuCircle;
    HMENU subMenuLine;
    HMENU subMenuClipping;

    Menubar = CreateMenu();
    subMenuLine = CreateMenu();
    subMenuCircle = CreateMenu();
    subMenuClipping= CreateMenu();

    AppendMenuW(subMenuCircle, MF_STRING, D_CIRCLE, L"&Direct_Circle");
    AppendMenuW(subMenuCircle, MF_STRING, POLAR_CIRCLE, L"&Polar_Circle");

    // Line subMenu
    AppendMenuW(subMenuLine, MF_STRING, DDA_Line, L"&DDA_Line");
    AppendMenuW(subMenuLine, MF_STRING, BRESN_LINE, L"&Bresenham_Line");


    // clipping menu
    AppendMenuW(subMenuClipping, MF_STRING, COHENALGO, L"&Cohen_Algo");

    AppendMenuW(Menubar, MF_POPUP, (UINT_PTR)subMenuLine, L"&Line");
    AppendMenuW(Menubar, MF_POPUP, (UINT_PTR)subMenuCircle, L"&Circle");
    AppendMenuW(Menubar, MF_POPUP, (UINT_PTR)subMenuClipping, L"&Clipping");
    AppendMenuW(Menubar, MF_STRING, EXITE, L"&Exit");

    SetMenu(hwnd, Menubar);
}


LRESULT WINAPI MyWndProc(HWND hwnd, UINT mcode, WPARAM wp, LPARAM lp)
{

    static int x1, y1, x2, y2, cnt=1, shapeNum=-1;
    
    // to know clipping type (point, line, polygon)
    static int clippingType;

    // rectangle points
    static Point p1= {400, 350};
    static Point p2= {600, 350};
    static Point p3= {600, 200};
    static Point p4= {400, 200};

    // bool for polygon clipping
    static bool takeVertexInput = true; 

    static vector<POINT> polygonList; // a list contains all polygons' vertices

	HDC hdc;
	switch (mcode)
	{
    case WM_CREATE:
        makeMenu(hwnd);

        break;


	case WM_LBUTTONDOWN:
	    {
	        hdc = GetDC(hwnd);

            drawRec(hdc, p1, p2, p3, p4);
            polygonList.clear();

            POINT p1, p2, p3;
            p1.x = 500; p1.y= 450;
            p2.x = 650; p2.y= 250;
            p3.x = 500; p3.y= 250;
            polygonList.push_back(p1);
            polygonList.push_back(p2);
            polygonList.push_back(p3);

            PolygonClip(hdc, polygonList, (int)polygonList.size(), p1.x, p1.y, p3.x, p3.y);

            polygonList.clear();





            //hdc = GetDC(hwnd);
            //DDALine(hdc, 120, 80, 500, 400, RGB(210, 25 , 205));
            //BresenhamLine(hdc, 120, 80, 500, 400, RGB(210, 25 , 205));
            //BresenhamLine(hdc, 500, 400, 120, 80, RGB(210, 25 , 205));
            //PolarCircle(hdc, 120, 200, 100, RGB(210, 25 , 205));
            //DirectCircle(hdc, 120, 200, 100, RGB(210, 25 , 205));
            //ReleaseDC(hwnd, hdc);

            printf("shapeNum= %d\n", shapeNum);
            ////
            switch (shapeNum)
            {
                case D_CIRCLE:
                    break;
                case DDA_Line:
                    cout<<"DDDDDDDDDDD"<<endl;
                    printf("cnt=%d\n", cnt);
                    switch(cnt)
                    {
                        case 1:
                            printf("x1= %d, y1= %d\n", x1, y1);
                            x1 = LOWORD(lp);
                            y1 = HIWORD(lp);
                            cnt++;

                            break;

                        case 2:

                            x2 = LOWORD(lp);
                            y2 = HIWORD(lp);

                            printf("x2= %d, y2= %d\n", x2, y2);

                            DDALine(hdc, x1, y1, x2, y2, RGB(210, 25 , 205));
                            cnt=1;
                            break;

                        default:
                            break;
                    }
                    break;
                case COHENALGO:
                {

                    // this for line clipping
                    switch (clippingType)
                    {
                        case 1:
                            x1 = LOWORD(lp);
                            y1 = HIWORD(lp);

                            PointClip(hdc, x1, y1, p1.x, p1.y, p3.x, p3.y, COLOR);
                            break;

                        case 2:
                        {
                            switch(cnt)
                            {
                                case 1:

                                    x1 = LOWORD(lp);
                                    y1 = HIWORD(lp);
                                    cnt++;
                                    break;
                                case 2:
                                    {

                                        x2 = LOWORD(lp);
                                        y2 = HIWORD(lp);

                                        // rectangle with cohen


                                        printf("x1=%d, y1=%d, x2=%d, y2=%d, p1.x=%d, p1.y=%d, p3.x=%d, p3.y=%d\n",
                                                x1, y1, x2, y2, p1.x, p1.y, p3.x, p3.y);

                                        CohenSuth(hdc, x1, y1, x2, y2, p1.x, p1.y, p3.x, p3.y);
                                        cnt =1;
                                        break;
                                    }
                            }
                        }

                        case 3:
                        {
                            if(takeVertexInput)
                            {
                                x1 = LOWORD(lp);
                                y1 = HIWORD(lp);

                                POINT p;
                                p.x = x1;
                                p.y = y1;

                                polygonList.push_back(p);
                            }
                            


                            break;
                        }
                    
                        default:
                            break;
                    }
                    
                    

                    break;
                }





                
            }



            ////

            
            break;
	    }
    case WM_RBUTTONDOWN:
        takeVertexInput = false;
        // apply polygon clipping
        PolygonClip(hdc, polygonList, (int)polygonList.size(), p1.x, p1.y, p3.x, p3.y);
        //DestroyWindow(hwnd);

        break;

	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;

    case WM_COMMAND:
        switch (wp)
        {
            case DDA_Line:
                shapeNum = DDA_Line;
                printf("printed Line using DDA Algo\n");
                break;

            case D_CIRCLE:
                shapeNum = D_CIRCLE;
                printf("printed circle using Direct Algo\n");
                break;

            case COHENALGO:
            {
                printf("in Cohen Algo\n");
                shapeNum = COHENALGO;
                hdc = GetDC(hwnd);
                drawRec(hdc, p1, p2, p3, p4);
                //ReleaseDC(hwnd, hdc);

                printf("Enter a number: pointCilpping(1), lineCilpping(2), polygonClipping(3): ");
                cin>>clippingType;
                printf("you entered: %d", clippingType);
                break;
            }

            case EXITE:
                DestroyWindow(hwnd);
                break;
        }

        break;
	case WM_DESTROY:
        ReleaseDC(hwnd, hdc);
		PostQuitMessage(0);
		break;
	default: return DefWindowProc(hwnd, mcode, wp, lp);
	}
	return 0;
}
int APIENTRY WinMain(HINSTANCE hinst, HINSTANCE pinst, LPSTR cmd, int nsh)
{

	WNDCLASS wc;

	wc.cbClsExtra = wc.cbWndExtra = 0;
    //Change the background of window to be white.
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    //Change the shape of the mouse.
	wc.hCursor = LoadCursor(NULL, IDC_CROSS);

	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);


	wc.hInstance = hinst;

	wc.lpfnWndProc = MyWndProc;

	wc.lpszClassName = "MyClass";

	wc.lpszMenuName = NULL;

	wc.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClass(&wc);

	HWND hwnd = CreateWindow("MyClass", "My First Window", WS_OVERLAPPEDWINDOW, 0, 0, 800, 600, NULL, NULL, hinst, 0);

	ShowWindow(hwnd, nsh);

	UpdateWindow(hwnd);

	MSG msg;

	while (GetMessage(&msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}


	return 0;
}
