#include "stdafx.h"
#include "draw2.h"
#include <vector>
#include <cstdio>
#include <iostream>


using namespace Gdiplus;
#pragma comment (lib,"Gdiplus.lib")

struct Rope_stats
{
	int x;
	int y;
	int h;
};

struct Przedmiot
{
	int x;
	int y;
	int masa;
	int object_class; //1-koło 2-kwadrat 3-trujkąt
	int move_x = 0;
	int move_y = 0;
};

// buttons
HWND hwndButton;

RECT rcCurrent = { 0,0,20,20 };
HDC hdc;
int HOLD = 0;
int pr_x = 0, pr_y = 20;
int lewo = 0, prawo = 0, gora = 0, dol = 0;
int ODL_x1, ODL_x2;
int ODL_y1, ODL_y2;

Przedmiot BOX[3];

VOID OnPaint(HDC hdc, RECT WINDOW, Rope_stats Rope, HWND hWnd)
{
	Graphics graphics(hdc);

	// Create a Pen object.
	Pen blackPen(Color(255, 0, 0, 0), 2);
	Pen yellowPen(Color(255, 255, 255, 0), 10);
	SolidBrush yellowBrush(Color(255, 200, 200, 0));
	SolidBrush orangeBrush(Color(255, 255, 191, 0));
	SolidBrush blueBrush(Color(255, 0, 255, 255));
	SolidBrush blackBrush(Color(255, 0, 0, 0));
	// Create a RectF object.
	REAL w = 50 * (WINDOW.right - WINDOW.left - 18) / 1000,
		h = 650 * (WINDOW.bottom - WINDOW.top - 40) / 1000,
		x = (WINDOW.right - WINDOW.left - 18) / 2 - w / 2,
		y = WINDOW.bottom - WINDOW.top - 40 - h;
	RectF rect(x, y, w, h);

	graphics.DrawRectangle(&yellowPen, rect);
	graphics.DrawRectangle(&blackPen, rect); //Główna belka

	graphics.DrawLine(&yellowPen, x, y + h / 5, x + w, y + 2 * h / 5);//belki wspomagajace skos yellow
	graphics.DrawLine(&yellowPen, x, y + 2 * h / 5, x + w, y + 3 * h / 5);
	graphics.DrawLine(&yellowPen, x, y + 3 * h / 5, x + w, y + 4 * h / 5);
	graphics.DrawLine(&yellowPen, x, y + 4 * h / 5, x + w, y + 5 * h / 5);
	graphics.DrawLine(&yellowPen, x, y + 2 * h / 5, x + w, y + h / 5);
	graphics.DrawLine(&yellowPen, x, y + 3 * h / 5, x + w, y + 2 * h / 5);
	graphics.DrawLine(&yellowPen, x, y + 4 * h / 5, x + w, y + 3 * h / 5);
	graphics.DrawLine(&yellowPen, x, y + 5 * h / 5, x + w, y + 4 * h / 5);

	graphics.DrawLine(&yellowPen, x, y + 2 * h / 5, x + w, y + 2 * h / 5); // poziome yellow
	graphics.DrawLine(&yellowPen, x, y + 3 * h / 5, x + w, y + 3 * h / 5);
	graphics.DrawLine(&yellowPen, x, y + 4 * h / 5, x + w, y + 4 * h / 5);
	graphics.DrawLine(&yellowPen, x, y + 5 * h / 5, x + w, y + 5 * h / 5);

	graphics.DrawLine(&blackPen, x, y + h / 5, x + w, y + 2 * h / 5);//belki wspomagajace skos czarne
	graphics.DrawLine(&blackPen, x, y + 2 * h / 5, x + w, y + 3 * h / 5);
	graphics.DrawLine(&blackPen, x, y + 3 * h / 5, x + w, y + 4 * h / 5);
	graphics.DrawLine(&blackPen, x, y + 4 * h / 5, x + w, y + 5 * h / 5);
	graphics.DrawLine(&blackPen, x, y + 2 * h / 5, x + w, y + h / 5);
	graphics.DrawLine(&blackPen, x, y + 3 * h / 5, x + w, y + 2 * h / 5);
	graphics.DrawLine(&blackPen, x, y + 4 * h / 5, x + w, y + 3 * h / 5);
	graphics.DrawLine(&blackPen, x, y + 5 * h / 5, x + w, y + 4 * h / 5);

	graphics.DrawLine(&blackPen, x, y + 2 * h / 5, x + w, y + 2 * h / 5); // poziome black 
	graphics.DrawLine(&blackPen, x, y + 3 * h / 5, x + w, y + 3 * h / 5);
	graphics.DrawLine(&blackPen, x, y + 4 * h / 5, x + w, y + 4 * h / 5);
	graphics.DrawLine(&blackPen, x, y + 5 * h / 5, x + w, y + 5 * h / 5);



	int h1 = h / 5;
	int x1 = x * 1.05;
	int y1 = y * 1.08;

	RectF rect3(x, y, w, h1);
	graphics.DrawRectangle(&blackPen, rect3);
	graphics.FillRectangle(&orangeBrush, rect3);
	RectF rect4(x1, y1, w - 50, h1 - 55);
	graphics.DrawRectangle(&blackPen, rect4);
	graphics.FillRectangle(&blueBrush, rect4);

	graphics.DrawLine(&yellowPen, x, y - h / 14, x + w / 2, y - h / 5);	//trojkat wspomagajacy
	graphics.DrawLine(&yellowPen, x + w / 2, y - h / 5, x + w, y - h / 14);
	graphics.DrawLine(&blackPen, x, y - h / 14, x + w / 2, y - h / 5);
	graphics.DrawLine(&blackPen, x + w / 2, y - h / 5, x + w, y - h / 14);



	w = 400 * (WINDOW.right - WINDOW.left - 18) / 1000;
	h = 50 * (WINDOW.bottom - WINDOW.top - 40) / 1000;
	x1 = (WINDOW.right - WINDOW.left - 18) / 2 - w / 4;
	int y2 = y - h;
	RectF rect2(x1, y2, w, h);

	int xl = x1 + x1 / 4;
	int yl = y2 - y2 / 3.9;
	int xl1 = x + 3 * w / 4;
	int yb = y;
	int wx = w;
	//Ramie
	graphics.DrawRectangle(&yellowPen, rect2);

	graphics.DrawLine(&yellowPen, x1, y2, x1 + wx / 5, yb); //belki wspomagajace skos yellow
	graphics.DrawLine(&yellowPen, x1 + wx / 5, y2, x1 + 2 * wx / 5, yb);
	graphics.DrawLine(&yellowPen, x1 + 2 * wx / 5, y2, x1 + 3 * wx / 5, yb);
	graphics.DrawLine(&yellowPen, x1 + 3 * wx / 5, y2, x1 + 4 * wx / 5, yb);
	graphics.DrawLine(&yellowPen, x1 + 4 * wx / 5, y2, x1 + wx, yb);

	graphics.DrawLine(&yellowPen, x1, yb, x1 + wx / 5, y2); //belki wspomagajace skos yellow
	graphics.DrawLine(&yellowPen, x1 + wx / 5, yb, x1 + 2 * wx / 5, y2);
	graphics.DrawLine(&yellowPen, x1 + 2 * wx / 5, yb, x1 + 3 * wx / 5, y2);
	graphics.DrawLine(&yellowPen, x1 + 3 * wx / 5, yb, x1 + 4 * wx / 5, y2);
	graphics.DrawLine(&yellowPen, x1 + 4 * wx / 5, yb, x1 + wx, y2);

	graphics.DrawLine(&yellowPen, x1 + wx / 5, yb, x1 + wx / 5, y2);
	graphics.DrawLine(&yellowPen, x1 + 2 * wx / 5, yb, x1 + 2 * wx / 5, y2);
	graphics.DrawLine(&yellowPen, x1 + 3 * wx / 5, yb, x1 + 3 * wx / 5, y2);
	graphics.DrawLine(&yellowPen, x1 + 4 * wx / 5, yb, x1 + 4 * wx / 5, y2);
	graphics.DrawLine(&blackPen, x1 + wx / 5, yb, x1 + wx / 5, y2);
	graphics.DrawLine(&blackPen, x1 + 2 * wx / 5, yb, x1 + 2 * wx / 5, y2);
	graphics.DrawLine(&blackPen, x1 + 3 * wx / 5, yb, x1 + 3 * wx / 5, y2);
	graphics.DrawLine(&blackPen, x1 + 4 * wx / 5, yb, x1 + 4 * wx / 5, y2);


	graphics.DrawLine(&blackPen, x1, y2, x1 + wx / 5, yb); //belki wspomagajace skos black
	graphics.DrawLine(&blackPen, x1 + wx / 5, y2, x1 + 2 * wx / 5, yb);
	graphics.DrawLine(&blackPen, x1 + 2 * wx / 5, y2, x1 + 3 * wx / 5, yb);
	graphics.DrawLine(&blackPen, x1 + 3 * wx / 5, y2, x1 + 4 * wx / 5, yb);
	graphics.DrawLine(&blackPen, x1 + 4 * wx / 5, y2, x1 + wx, yb);

	graphics.DrawLine(&blackPen, x1, yb, x1 + wx / 5, y2); //belki wspomagajace skos black
	graphics.DrawLine(&blackPen, x1 + wx / 5, yb, x1 + 2 * wx / 5, y2);
	graphics.DrawLine(&blackPen, x1 + 2 * wx / 5, yb, x1 + 3 * wx / 5, y2);
	graphics.DrawLine(&blackPen, x1 + 3 * wx / 5, yb, x1 + 4 * wx / 5, y2);
	graphics.DrawLine(&blackPen, x1 + 4 * wx / 5, yb, x1 + wx, y2);

	graphics.DrawRectangle(&blackPen, rect2);

	graphics.DrawLine(&blackPen, x1, y2, xl, yl);
	graphics.DrawLine(&blackPen, xl, yl, xl1, y2);


	int x2 = (WINDOW.right - WINDOW.left - 18) / 2 - w / 5;
	int	y3 = y2 + h;
	int w1 = 30 * (WINDOW.right - WINDOW.left - 18) / 1000;
	h = 40 * (WINDOW.bottom - WINDOW.top - 40) / 1000;
	RectF rect5(x2, y3, w1, h);
	graphics.DrawRectangle(&blackPen, rect5);
	graphics.FillRectangle(&blackBrush, rect5);



	y2 = y2 + h;



	int Box_w = (WINDOW.right - WINDOW.left - 18) / 30,
		Box_h = (WINDOW.bottom - WINDOW.top - 18) / 15;

	BOX[0].object_class = 2;
	BOX[0].x = ((WINDOW.right - WINDOW.left) - (WINDOW.right - WINDOW.left) / 5);
	BOX[0].y = (WINDOW.bottom - WINDOW.top - WINDOW.top / 5);
	RectF BOX_1(BOX[0].x - 150 + BOX[0].move_x, BOX[0].y - 350 + BOX[0].move_y, Box_w, Box_h);


	/*BOX[1].object_class = 2;
	BOX[1].x = (WINDOW.right - WINDOW.left - 18) - (WINDOW.right - WINDOW.left - 18) / 4;
	BOX[1].y = WINDOW.bottom - WINDOW.top - 70 - Box_h + 30;

	BOX[2].object_class = 2;
	BOX[2].x = (WINDOW.right - WINDOW.left - 18) - (WINDOW.right - WINDOW.left - 18) / 5;
	BOX[2].y = WINDOW.bottom - WINDOW.top - 70 - Box_h + 30;*/

	SolidBrush solidBrush(Color(0, 0, 0, 0));
	Region TEST(Rect(Rope.x - 10, y2 + Rope.h, 20, 5));
	Region TEST_UP(Rect(Rope.x - 10, y2 + Rope.h + 20, 20, 5));

	if (TEST.IsVisible(BOX_1, &graphics) && BOX[0].object_class == 2 && HOLD == 1)
	{
		// The point is in the region. Use an opaque brush.
		ODL_x1 = Rope.x - BOX[0].x;
		if (ODL_x1 != ODL_x2)
		{
			BOX[0].move_x = BOX[0].move_x + ODL_x1 - ODL_x2;
			ODL_x2 = ODL_x1;
		}
		ODL_y1 = Rope.h - BOX[0].y;
		if (ODL_y1 != ODL_y2)
		{
			BOX[0].move_y = BOX[0].move_y + ODL_y1 - ODL_y2;
			ODL_y2 = ODL_y1;
		}
		else
		{
			KillTimer(hWnd, TMR_D);
		}
		solidBrush.SetColor(Color(255, 255, 0, 0));
	}
	if (TEST_UP.IsVisible(BOX_1, &graphics) && BOX[0].object_class == 2 && HOLD == 1)
	{
		ODL_y1 = Rope.h - BOX[0].y;
		if (ODL_y1 != ODL_y2)
		{
			BOX[0].move_y = BOX[0].move_y + ODL_y1 - ODL_y2;
			ODL_y2 = ODL_y1;
		}
	}
	else if (TEST.IsVisible(BOX_1, &graphics) && BOX[0].object_class == 2 && HOLD == 0)
	{
		ODL_x1 = Rope.x - BOX[0].x;
		if (ODL_x2 != ODL_x1)
		{
			ODL_x2 = ODL_x1;
		}
		ODL_y1 = Rope.h - BOX[0].y;
		if (ODL_y2 != ODL_y1)
		{
			ODL_y2 = ODL_y1;
		}
		KillTimer(hWnd, TMR_D);
		solidBrush.SetColor(Color(255, 255, 0, 0));
	}
	else if (!TEST.IsVisible(BOX_1, &graphics))
	{
		// The point is not in the region. Use a semitransparent brush.
		solidBrush.SetColor(Color(64, 255, 0, 0));
	}

	graphics.DrawLine(&blackPen, Rope.x, y2, Rope.x, y2 + Rope.h);
	graphics.DrawRectangle(&blackPen, BOX_1);
	//graphics.FillRegion(&solidBrush, &TEST);
	//graphics.FillRegion(&solidBrush, &TEST_UP);


	//RectF BOX_2(BOX[1].x, BOX[1].y, Box_w, Box_h);
	//graphics.DrawRectangle(&blackPen, BOX_2);
	//RectF BOX_3(BOX[2].x, BOX[2].y, Box_w, Box_h);
	//graphics.DrawRectangle(&blackPen, BOX_3);
}

VOID RePaint(HWND hWnd, RECT* drawArea, RECT WINDOW, Rope_stats Rope, PAINTSTRUCT& ps)
{
	if (&drawArea == NULL)
		InvalidateRect(hWnd, NULL, TRUE); // repaint all
	else
		InvalidateRect(hWnd, drawArea, TRUE); //repaint drawArea
}


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, INT iCmdShow)
{
	HWND                hWnd;
	MSG                 msg;
	WNDCLASS            wndClass;
	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR           gdiplusToken;

	// Initialize GDI+.
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	wndClass.style = CS_HREDRAW | CS_VREDRAW;
	wndClass.lpfnWndProc = WndProc;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hInstance = hInstance;
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndClass.lpszMenuName = NULL;
	wndClass.lpszClassName = TEXT("GettingStarted");

	RegisterClass(&wndClass);

	hWnd = CreateWindow(
		TEXT("GettingStarted"),   // window class name
		TEXT("Getting Started"),  // window caption
		WS_OVERLAPPEDWINDOW,      // window style
		CW_USEDEFAULT,            // initial x position
		CW_USEDEFAULT,            // initial y position
		CW_USEDEFAULT,            // initial x size
		CW_USEDEFAULT,            // initial y size
		NULL,                     // parent window handle
		NULL,                     // window menu handle
		hInstance,                // program instance handle
		NULL);                    // creation parameters


	hwndButton = CreateWindow(TEXT("button"),                      // The class name required is button
		TEXT("→"),                  // the caption of the button
		WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX,  // the styles
		300, 150,                                  // the left and top co-ordinates
		50, 50,                              // width and height
		hWnd,                                 // parent window handle
		(HMENU)ID_BUTTON1,                   // the ID of your button
		hInstance,                            // the instance of your application
		NULL);                               // extra bits you dont really need
	hwndButton = CreateWindow(TEXT("button"), TEXT("←"), WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX, 200, 150, 50, 50, hWnd, (HMENU)ID_BUTTON2, hInstance, NULL);

	hwndButton = CreateWindow(TEXT("button"), TEXT("↑"), WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX, 250, 100, 50, 50, hWnd, (HMENU)ID_BUTTON3, hInstance, NULL);

	hwndButton = CreateWindow(TEXT("button"), TEXT("↓"), WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX/*BS_DEFPUSHBUTTON*/, 250, 150, 50, 50, hWnd, (HMENU)ID_BUTTON4, hInstance, NULL);

	hwndButton = CreateWindow(TEXT("button"), TEXT("H"), WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX, 250, 200, 50, 50, hWnd, (HMENU)ID_BUTTON5, hInstance, NULL);

	ShowWindow(hWnd, iCmdShow);
	UpdateWindow(hWnd);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	GdiplusShutdown(gdiplusToken);
	return msg.wParam;
}  // WinMain


LRESULT CALLBACK WndProc(HWND hWnd, UINT message,
	WPARAM wParam, LPARAM lParam)
{
	Rope_stats Rope;
	PAINTSTRUCT  ps;
	RECT WINDOW;
	GetWindowRect(hWnd, &WINDOW);
	Rope.x = (WINDOW.right - WINDOW.left - 18) / 2 + ((400 * (WINDOW.right - WINDOW.left - 18) / 1000) / 6) + pr_x;
	Rope.y = WINDOW.bottom - WINDOW.top - 40 - (50 * (WINDOW.bottom - WINDOW.top - 40) / 1000);
	Rope.h = pr_y;
	int wmId;
	RECT drawArea{ 0, 0, 2000, 2000 };
	switch (message)
	{
	case WM_CREATE:
	{
		hdc = GetDC(hWnd);
		//SetTimer(hWnd, TMR_ID, 1000, NULL);
		return 0;
	}
	case WM_COMMAND:
	{
		wmId = LOWORD(wParam);
		switch (wmId)
		{
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		case ID_BUTTON1://prawo

			/*if (pr_x + 50 <= ((400 * (WINDOW.right - WINDOW.left - 18) / 1000) / 2))
			{
				pr_x = pr_x + 50;
				RePaint(hWnd, &drawArea, WINDOW, Rope, ps);
			}*/
			if (prawo == 0)
			{
				SetTimer(hWnd, TMR_R, 1000, NULL);
				prawo = 1;
			}
			else
			{
				prawo = 0;
				KillTimer(hWnd, TMR_R);
				RePaint(hWnd, &drawArea, WINDOW, Rope, ps);
			}
			break;
		case ID_BUTTON2://lewo
			if (lewo == 0)
			{
				SetTimer(hWnd, TMR_L, 1000, NULL);
				lewo = 1;
			}
			else
			{
				lewo = 0;
				KillTimer(hWnd, TMR_L);
				RePaint(hWnd, &drawArea, WINDOW, Rope, ps);
			}
			break;
		case ID_BUTTON3://góra
			if (gora == 0)
			{
				SetTimer(hWnd, TMR_U, 1000, NULL);
				gora = 1;
			}
			else
			{
				gora = 0;
				KillTimer(hWnd, TMR_U);
				RePaint(hWnd, &drawArea, WINDOW, Rope, ps);
			}
			break;
		case ID_BUTTON4://dół
			if (dol == 0)
			{
				SetTimer(hWnd, TMR_D, 1000, NULL);
				dol = 1;
			}
			else
			{
				dol = 0;
				KillTimer(hWnd, TMR_D);
				RePaint(hWnd, &drawArea, WINDOW, Rope, ps);
			}
			break;
		case ID_BUTTON5://łap
			if (HOLD == 0)
			{
				HOLD = 1;
			}
			else
			{
				HOLD = 0;
			}
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	}
	case WM_TIMER:
	{
		switch (wParam)
		{
		case TMR_R:
			if (prawo == 1)
			{
				if (pr_x + 5 <= ((400 * (WINDOW.right - WINDOW.left - 18) / 1000) / 2))
				{
					pr_x = pr_x + (WINDOW.right - WINDOW.left) / 50;
					RePaint(hWnd, &drawArea, WINDOW, Rope, ps);
				}
			};
		case TMR_L:
			if (lewo == 1)
			{
				if (pr_x - 5 >= 0)
				{
					pr_x = pr_x - (WINDOW.right - WINDOW.left) / 50;
					RePaint(hWnd, &drawArea, WINDOW, Rope, ps);
				}
			};
		case TMR_U:
			if (gora == 1)
			{
				if (pr_y >= 25)
				{
					pr_y = pr_y - (WINDOW.bottom - WINDOW.top) / 50;
					RePaint(hWnd, &drawArea, WINDOW, Rope, ps);
				}
			};
		case TMR_D:
			if (dol == 1)
			{
				if (pr_y <= WINDOW.bottom - WINDOW.top - 500 * (WINDOW.bottom - WINDOW.top - 40) / 1000)
				{
					pr_y = pr_y + (WINDOW.bottom - WINDOW.top) / 50;
					RePaint(hWnd, &drawArea, WINDOW, Rope, ps);
				}
			};
			break;
		}
		return 0;
	}
	case WM_ERASEBKGND:

		return DefWindowProc(hWnd, message, wParam, lParam);
	case WM_PAINT:
		BeginPaint(hWnd, &ps);
		OnPaint(hdc, WINDOW, Rope, hWnd);
		EndPaint(hWnd, &ps);
		return 0L;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
} // WndProc