#include <Windows.h>

#include"Line.h"
#include"Circle.h"
#include "Clipping.h"
#include "Curves.h"
#include "Ellipse.h"
#include "ConvexFill.h"
#include <iostream>

using namespace std;



#define COLOR RGB(0, 0, 255)

enum algoType {DDA_Line, BRESN_LINE, param_LINE, D_CIRCLE,EXITE, MIDPELLIPSE, POLARELLIPSE, DIRECTELLIPCE,
              POLAR_CIRCLE, ItPOLAR_CIRCLE, MIDPOINTCIRCLE, MMIDPOINTCIRCLE, RECLIPPING, SQUARCLIP,
              CIRCLECLIP, BEZIERFILL, circleQuarterByLines, HERMITEFILING,
              recursive_FloodFill, nonRecursive_FloodFill, CONVEXFILL, NONCONVEXFILL};



//algoType line;

// menu function
void createMenu(HWND hwnd) {

    HMENU Menubar;
    HMENU subMenuCircle;
    HMENU subMenuLine;
    HMENU subMenuEllipse;
    HMENU subMenuClipping;
    HMENU subMenuFilling;


    Menubar = CreateMenu();
    subMenuLine = CreateMenu();
    subMenuCircle = CreateMenu();
    subMenuClipping = CreateMenu();
    subMenuFilling = CreateMenu();
    subMenuEllipse = CreateMenu();

    AppendMenuW(subMenuCircle, MF_STRING, D_CIRCLE, L"&Direct_Circle");
    AppendMenuW(subMenuCircle, MF_STRING, POLAR_CIRCLE, L"&Polar_Circle");
    AppendMenuW(subMenuCircle, MF_STRING, ItPOLAR_CIRCLE, L"&iterative_Polar");
    AppendMenuW(subMenuCircle, MF_STRING, MIDPOINTCIRCLE, L"&midpoint");
    AppendMenuW(subMenuCircle, MF_STRING, MMIDPOINTCIRCLE, L"&modified_midpoint");

    // Line subMenu
    AppendMenuW(subMenuLine, MF_STRING, DDA_Line, L"&DDA_Line");
    AppendMenuW(subMenuLine, MF_STRING, BRESN_LINE, L"&midpoint_Line");
    AppendMenuW(subMenuLine, MF_STRING, param_LINE, L"&parametric_Line");

    // Ellipse menu
    AppendMenuW(subMenuEllipse, MF_STRING, DIRECTELLIPCE, L"&Direct_Ellipse");
    AppendMenuW(subMenuEllipse, MF_STRING, POLARELLIPSE, L"&polar_Ellipse");
    AppendMenuW(subMenuEllipse, MF_STRING, MIDPELLIPSE, L"&Midpoint_Ellipse");


    // clipping menu
    AppendMenuW(subMenuClipping, MF_STRING, RECLIPPING, L"&Rectangle");
    AppendMenuW(subMenuClipping, MF_STRING, SQUARCLIP, L"&Square");
    AppendMenuW(subMenuClipping, MF_STRING, CIRCLECLIP, L"&Circle");


    // filling menu
    AppendMenuW(subMenuFilling, MF_STRING, BEZIERFILL, L"&BeizerFilling");
    AppendMenuW(subMenuFilling, MF_STRING, circleQuarterByLines, L"&circleQuarterByLines");
    AppendMenuW(subMenuFilling, MF_STRING, HERMITEFILING, L"&HermitFilling");
    AppendMenuW(subMenuFilling, MF_STRING, CONVEXFILL, L"&convexFilling");
    AppendMenuW(subMenuFilling, MF_STRING, NONCONVEXFILL, L"&nonConvexFilling");
    AppendMenuW(subMenuFilling, MF_STRING, recursive_FloodFill, L"&recursive_FloodFill");
    AppendMenuW(subMenuFilling, MF_STRING, nonRecursive_FloodFill, L"&nonRecursive_FloodFill");

    // Main menu bar
    AppendMenuW(Menubar, MF_POPUP, (UINT_PTR)subMenuLine, L"&Line");
    AppendMenuW(Menubar, MF_POPUP, (UINT_PTR)subMenuCircle, L"&Circle");
    AppendMenuW(Menubar, MF_POPUP, (UINT_PTR)subMenuClipping, L"&Clipping");
    AppendMenuW(Menubar, MF_POPUP, (UINT_PTR)subMenuFilling, L"&Filling");
    AppendMenuW(Menubar, MF_POPUP, (UINT_PTR)subMenuEllipse, L"&Eillpse");
    AppendMenuW(Menubar, MF_POPUP, (UINT_PTR)subMenuEllipse, L"&Eillpse");

    AppendMenuW(Menubar, MF_STRING, EXITE, L"&Exit");

    SetMenu(hwnd, Menubar);
}


LRESULT WINAPI MyWndProc(HWND hwnd, UINT mcode, WPARAM wp, LPARAM lp)
{

    static int x1, y1, x2, y2, cnt=1, shapeNum=-1;
    
    // quarter number
    static int qNum;
    // to know clipping type (point, line, polygon)
    static int clippingType;

    // rectangle points
    static Point p1= {400, 350};
    static Point p2= {600, 350};
    static Point p3= {600, 200};
    static Point p4= {400, 200};

    // square points
    static Point sqP1, sqP2, sqP3, sqP4;
    sqP1 = {350, 400};
    sqP2 = {550, 400};
    sqP3 = {550, 200};
    sqP4 = {350, 200};

    // main circle
    static int xc, yc, r;

    // bool for polygon clipping
    static bool takeVertexInput = true; 

    static vector<POINT> polygonList; // a list contains all polygons' vertices

	HDC hdc;
	switch (mcode)
	{
    case WM_CREATE:
        createMenu(hwnd);

        break;


	case WM_LBUTTONDOWN:
	    {
	        hdc = GetDC(hwnd);



        

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
                    x1 = LOWORD(lp);
                    y1 = HIWORD(lp);
                    DirectCircle(hdc, x1, y1, 100, COLOR);

                    break;
                case POLAR_CIRCLE:
                {
                    x1 = LOWORD(lp);
                    y1 = HIWORD(lp);
                    PolarCircle(hdc, x1, y1, 100, COLOR);
                    break;
                }

                
                case ItPOLAR_CIRCLE:
                {
                    x1 = LOWORD(lp);
                    y1 = HIWORD(lp);
                    IterativePolerCircle(hdc, x1, y1, 100, COLOR);
                    break;
                }

                case MIDPOINTCIRCLE:
                {
                    x1 = LOWORD(lp);
                    y1 = HIWORD(lp);
                    MidpointCircle(hdc, x1, y1, 100, COLOR);
                    break;
                }
                case MMIDPOINTCIRCLE:
                {
                    x1 = LOWORD(lp);
                    y1 = HIWORD(lp);
                    ModifiedMidpointCircle(hdc, x1, y1, 100, COLOR);
                    break;
                }

                case BRESN_LINE:
                {
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

                            hdc = GetDC(hwnd);
                            BresenhamLine(hdc, x1, y1, x2, y2, RGB(210, 25 , 205));
                            cnt=1;
                            break;

                        default:
                            break;
                    }

                    break;
                }

                case param_LINE:
                {
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

                            hdc = GetDC(hwnd);
                            ParametricLine(hdc, x1, y1, x2, y2, RGB(210, 25 , 205));
                            cnt=1;
                            break;

                        default:
                            break;
                    }

                    break;
                }

                case DDA_Line:
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

                            hdc = GetDC(hwnd);
                            DDALine(hdc, x1, y1, x2, y2, RGB(210, 25 , 205));
                            cnt=1;
                            break;

                        default:
                            break;
                    }
                    break;

                case MIDPELLIPSE:
                {
                    x1 = LOWORD(lp);
                    y1 = HIWORD(lp);

                    MidpointEllipse(hdc, x1, y1, 200, 150, COLOR);

                    break;
                }

                case POLARELLIPSE:
                {
                    x1 = LOWORD(lp);
                    y1 = HIWORD(lp);

                    PolarEllipse(hdc, x1, y1, 200, 150, COLOR);

                    break;
                }

                case DIRECTELLIPCE:
                {
                    x1 = LOWORD(lp);
                    y1 = HIWORD(lp);

                    DirectEllipse(hdc, x1, y1, 200, 150, COLOR);

                    break;
                }


                case RECLIPPING:
                {

                    // this for line clipping
                    switch (clippingType)
                    {
                        case 1:
                            x1 = LOWORD(lp);
                            y1 = HIWORD(lp);

                            hdc = GetDC(hwnd);
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

                                        hdc = GetDC(hwnd);
                                        CohenSuth(hdc, x1, y1, x2, y2, p1.x, p1.y, p3.x, p3.y);
                                        cnt =1;
                                        break;
                                    }
                            }
                            break;
                        }

                        // Rectangle polygon clipping
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
                            else
                            {
                                PolygonClip(hdc, polygonList, (int)polygonList.size(), p1.x, p1.y, p3.x, p3.y);
                                polygonList.clear();
                            }
                            


                            break;
                        }
                    
                        default:
                            break;
                    }
                    
                    

                    break;
                }
                case SQUARCLIP :
                {
                    printf("in square: clipp type:%d\n", clippingType);
                    switch (clippingType)
                    {
                        case 1:
                            x1 = LOWORD(lp);
                            y1 = HIWORD(lp);

                            hdc = GetDC(hwnd);
                            PointClip(hdc, x1, y1, sqP1.x, sqP1.y, sqP3.x, sqP3.y, COLOR);
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
                                                x1, y1, x2, y2, sqP1.x, sqP1.y, sqP3.x, sqP3.y);

                                        hdc = GetDC(hwnd);
                                        CohenSuth(hdc, x1, y1, x2, y2, sqP1.x, sqP1.y, sqP3.x, sqP3.y);
                                        cnt =1;
                                        break;
                                    }
                            }
                        }
                    
                        default:
                            break;
                    }

                    break;
                }

                case CIRCLECLIP:
                {
                    printf("in circle: clipp type:%d\n", clippingType);
                    switch (clippingType)
                    {
                        case 1:
                            x1 = LOWORD(lp);
                            y1 = HIWORD(lp);

                            hdc = GetDC(hwnd);
                            
                            if(isInsideCircle(x1, y1, xc, yc, r))
                            {
                                SetPixel(hdc, x1, y1, COLOR);
                            }

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

                                        hdc = GetDC(hwnd);

                                        line_CircleWin(hdc, x1, y1, x2, y2, xc, yc, r, COLOR);
                                        cnt =1;
                                        break;
                                    }
                            }
                        }
                    
                        default:
                            break;
                    }


                    break;
                }

                case BEZIERFILL:
                {
                    printf("filling with bezier\n");
                    fillingRecWithBeizer(hdc, p1, p2, p3, p4);

                    break;
                }
                case circleQuarterByLines:
                {
                    x1 = LOWORD(lp);
                    y1 = HIWORD(lp);
                    FillCircleWithLines(hdc, x1, y1, 200, qNum, COLOR);
                    break;
                }

                case HERMITEFILING:
                {
                    x1 = LOWORD(lp);
                    y1 = HIWORD(lp);
                    FillSquareWithHermit(hdc, x1, y1, 120, COLOR);
                    break;
                }
                
                case NONCONVEXFILL:
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
                    else
                    {
                        ConvexFill(hdc, polygonList, polygonList.size(), COLOR);
                    }
                    

                    break;
                }

                case CONVEXFILL:
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
                    else
                    {
                        ConvexFill(hdc, polygonList, polygonList.size(), COLOR);
                    }
                    

                    break;
                }

                case recursive_FloodFill:
                {
                    x1 = LOWORD(lp);
                    y1 = HIWORD(lp);

                    COLORREF bc = GetPixel(hdc, x1, y1);

                    IRecursiveFloodFill(hdc, x1, y1, bc, RGB(0, 255,0));
                    break;
                }

                case nonRecursive_FloodFill:
                {
                    x1 = LOWORD(lp);
                    y1 = HIWORD(lp);

                    

                    NonRecursiveFloodFill(hdc, x1, y1, RGB(0, 0,255), RGB(0, 255,0));
                    break;
                }

            }



            ////

            
            break;
	    }
    case WM_RBUTTONDOWN:
        takeVertexInput = false;
        // apply polygon clipping
        
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

            case POLAR_CIRCLE:
            {
                shapeNum = POLAR_CIRCLE;
                printf("printed circle using POLAR_CIRCLE Algo\n");
                break;
            }

            case ItPOLAR_CIRCLE:
            {
                shapeNum = ItPOLAR_CIRCLE;
                printf("printed circle using ItPOLAR_CIRCLE Algo\n");
                break;
            }

            case MIDPOINTCIRCLE:
            {
                shapeNum = MIDPOINTCIRCLE;
                printf("printed circle using MIDPOINTCIRCLE Algo\n");
                break;
            }
            case MMIDPOINTCIRCLE:
            {
                shapeNum = MMIDPOINTCIRCLE;
                printf("printed circle using MMIDPOINTCIRCLE Algo\n");
                break;
            }

            case BRESN_LINE:
            {
                shapeNum = BRESN_LINE;
                printf("printed line using midpoint Algo\n");

                break;
            }

            case param_LINE:
            {
                shapeNum = param_LINE;
                printf("printed line using parametric Algo\n");

                break;
            }

            case DIRECTELLIPCE:
            {  
                shapeNum = DIRECTELLIPCE;
                printf("printed Ellipse using DirectEllipse Algo\n");
                break;
            }

            case POLARELLIPSE:
            {  
                shapeNum = POLARELLIPSE;
                printf("printed Ellipse using POLARELLIPSE Algo\n");
                break;
            }

            case MIDPELLIPSE:
            {  
                shapeNum = MIDPELLIPSE;
                printf("printed Ellipse using MIDPELLIPSE Algo\n");
                break;
            }

            case RECLIPPING:
            {
                printf("Enter a number: pointCilpping(1), lineCilpping(2), polygonClipping(3): ");
                cin>>clippingType;
                printf("you entered: %d\n", clippingType);

                hdc = GetDC(hwnd);
                printf("in Rec-Clipping Algo\n");
                shapeNum = RECLIPPING;
                //hdc = GetDC(hwnd);
                drawRec(hdc, p1, p2, p3, p4);
                //ReleaseDC(hwnd, hdc);

                
                break;
            }
            case SQUARCLIP:
            {
                hdc = GetDC(hwnd);
                printf("in SQUARE-Clipping Algo\n");
                shapeNum = SQUARCLIP;

                

                printf("Enter a number: pointCilpping(1), lineCilpping(2):");
                cin>>clippingType;
                printf("you entered: %d\n", clippingType);

                drawRec(hdc, sqP1, sqP2, sqP3, sqP4);

                

                break;
            }

            case CIRCLECLIP:
            {
                hdc = GetDC(hwnd);
                printf("in SQUARE-Clipping Algo\n");
                shapeNum = CIRCLECLIP;

                printf("Enter a number: pointCilpping(1), lineCilpping(2):");
                cin>>clippingType;
                printf("you entered: %d\n", clippingType);

                xc= 250;
                yc=300;
                r= 200;

                IterativePolerCircle(hdc, xc, yc, r, COLOR);


                break;
            }

            case BEZIERFILL:
            {
                hdc = GetDC(hwnd);
                printf("in Filling Rectangle with Bezier Curve[horizontal]\n");
                shapeNum = BEZIERFILL;
                

                drawRec(hdc, p1, p2, p3, p4);

                break;
            }

            case HERMITEFILING:
            {
                printf("in Filling Square with Hermite Curve[Vertical]\n");

                break;
            }
            case circleQuarterByLines:
            {
                printf("in Filling Circle Quarter with lines\n");
                shapeNum = circleQuarterByLines;

                printf("Enter quarter number (1-4): ");
                cin>>qNum;


                break;
            }

            case CONVEXFILL:
            {
                printf("in convex fill\n");
                shapeNum = CONVEXFILL;
                break;
            }

            case NONCONVEXFILL:
            {
                printf("in nonconvex fill\n");
                shapeNum = NONCONVEXFILL;
                break;
            }

            case recursive_FloodFill:
            {
                printf("in recursive_FloodFill fill\n");
                shapeNum = recursive_FloodFill;

                break;
            }

            case nonRecursive_FloodFill:
            {
                printf("in nonRecursive_FloodFill fill\n");
                shapeNum = nonRecursive_FloodFill;

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
