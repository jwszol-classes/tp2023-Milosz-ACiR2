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
	int move_x = 0;
	int move_y = 0;
	bool ksztalt = 0;

};

// buttons
HWND hwndButton;

RECT rcCurrent = { 0,0,20,20 };
HDC hdc;
int HOLD = 0;
int pr_x = 0, pr_y = 20;
int lewo = 0, prawo = 0, gora = 0, dol = 0, tower = 0;
int ODL_x1, ODL_x2;
int ODL_y1, ODL_y2;
int Masa = 0;
int Udźwig = 100;
int Colision = 0;
int czybylo00 = 0;

Przedmiot BOX[5];

VOID MovingBoxCreat(Rect Test, Rect TestUp, HDC hdc, HWND hWnd, Rope_stats Rope, RECT WINDOW, int Box_w, int Box_h, int Box_nr)
{
	Graphics graphics(hdc);
	Region TEST(Test);
	Region TEST_UP(TestUp);

	Rect Box(BOX[Box_nr].x - 150, BOX[Box_nr].y - 350, Box_w, Box_h);


	Pen blackPen(Color(255, 0, 0, 0), 2);

	if (TEST.IsVisible(Box, &graphics) && HOLD == 1 && BOX[Box_nr].ksztalt == 0)
	{
		Masa = BOX[Box_nr].masa;
		if (BOX[Box_nr].masa <= Udźwig)
		{
			ODL_x1 = Rope.x - BOX[Box_nr].x + BOX[Box_nr].move_x;
			BOX[Box_nr].move_x = BOX[Box_nr].move_x + ODL_x1 - ODL_x2;
			ODL_x2 = ODL_x1;

			ODL_y1 = Rope.h - BOX[Box_nr].y + BOX[Box_nr].move_y;
			BOX[Box_nr].move_y = BOX[Box_nr].move_y + ODL_y1 - ODL_y2;
			ODL_y2 = ODL_y1;
		}
	}
	if (TEST_UP.IsVisible(Box, &graphics) && HOLD == 1 && BOX[Box_nr].ksztalt == 0)
	{
		Masa = BOX[Box_nr].masa;

		ODL_y1 = Rope.h - BOX[Box_nr].y + BOX[Box_nr].move_y;
		BOX[Box_nr].move_y = BOX[Box_nr].move_y + ODL_y1 - ODL_y2;
		ODL_y2 = ODL_y1;
	}
	else if (TEST.IsVisible(Box, &graphics) && HOLD == 0 && BOX[Box_nr].ksztalt == 0)
	{
		Masa = BOX[Box_nr].masa;

		ODL_x1 = Rope.x - BOX[Box_nr].x + BOX[Box_nr].move_x;
		ODL_x2 = ODL_x1;

		ODL_y1 = Rope.h - BOX[Box_nr].y + BOX[Box_nr].move_y;
		ODL_y2 = ODL_y1;

		KillTimer(hWnd, TMR_D);
	}

	float x1 = ((WINDOW.right - WINDOW.left) - (WINDOW.right - WINDOW.left) / 4) + BOX[2].move_x;
	float x2 = ((WINDOW.right - WINDOW.left) - 3 * (WINDOW.right - WINDOW.left) / 13) + BOX[2].move_x;
	float	x3 = ((WINDOW.right - WINDOW.left) - 2 * (WINDOW.right - WINDOW.left) / 9) + BOX[2].move_x;
	float y1 = (WINDOW.bottom - WINDOW.top - 5 * WINDOW.bottom / 14) + BOX[2].move_y;
	float	y2 = (WINDOW.bottom - WINDOW.top - 3 * WINDOW.bottom / 7) + BOX[2].move_y;
	Point point1(x1, y2);
	Point point2(x2, y1);
	Point point3(x3, y2);
	Point points[3] = { point1, point2, point3 };
	Point* pPoints = points;
	switch (Box_nr)
	{
	case 0:

		graphics.DrawRectangle(&blackPen, Box);
		break;
	case 1:

		graphics.DrawEllipse(&blackPen, Box);
		break;
	case 2:
		//graphics.DrawRectangle(&blackPen, Box);
		graphics.DrawPolygon(&blackPen, pPoints, 3);
		break;
	case 3:

		graphics.DrawRectangle(&blackPen, Box);
		break;
	case 4:

		graphics.DrawRectangle(&blackPen, Box);
		break;
	default:
		break;
	}


}

VOID MovePaint(HDC hdc, RECT WINDOW, Rope_stats Rope, HWND hWnd)
{
	int w = 50 * (WINDOW.right - WINDOW.left - 18) / 1000,
		h = 650 * (WINDOW.bottom - WINDOW.top - 40) / 1000,
		x = (WINDOW.right - WINDOW.left - 18) / 2 - w / 2,
		y = WINDOW.bottom - WINDOW.top - 40 - h;


	Masa = 0;
	Pen blackPen(Color(255, 0, 0, 0), 2);

	Graphics graphics(hdc);

	int y2 = y - h;

	y2 = y2 + h;

	int Box_w = (WINDOW.right - WINDOW.left - 18) / 30,
		Box_h = (WINDOW.bottom - WINDOW.top - 18) / 15;

	SolidBrush solidBrush(Color(100, 0, 0, 0));
	Rect TEST(Rope.x - 10, y2 + Rope.h, 20, 5);
	Rect TEST_UP(Rope.x - 10, y2 + Rope.h + 20, 20, 5);

	//Jeśli więcej boxów to skopiować te 5 linijek i zmienić Box nr
	int Box_nr = 0;
	BOX[Box_nr].ksztalt = 0;
	BOX[Box_nr].x = ((WINDOW.right - WINDOW.left) - (WINDOW.right - WINDOW.left) / 5) + BOX[0].move_x;
	BOX[Box_nr].y = (WINDOW.bottom - WINDOW.top - WINDOW.top / 5) + BOX[0].move_y;
	BOX[Box_nr].masa = 30;
	MovingBoxCreat(TEST, TEST_UP, hdc, hWnd, Rope, WINDOW, Box_w, Box_h, Box_nr);

	Box_nr = 1; // kolo
	BOX[Box_nr].ksztalt = 1;
	BOX[Box_nr].x = ((WINDOW.right - WINDOW.left) - (WINDOW.right - WINDOW.left) / 4) + BOX[1].move_x;
	BOX[Box_nr].y = (WINDOW.bottom - WINDOW.top - WINDOW.top / 5) + BOX[1].move_y;
	BOX[Box_nr].masa = 40;
	MovingBoxCreat(TEST, TEST_UP, hdc, hWnd, Rope, WINDOW, Box_w, Box_h, Box_nr);

	Box_nr = 2; //trojkat
	BOX[Box_nr].ksztalt = 2;
	BOX[Box_nr].x = ((WINDOW.right - WINDOW.left) - (WINDOW.right - WINDOW.left) / 7) + BOX[2].move_x;
	BOX[Box_nr].y = (WINDOW.bottom - WINDOW.top - WINDOW.top / 5) + BOX[2].move_y;
	BOX[Box_nr].masa = 5;
	MovingBoxCreat(TEST, TEST_UP, hdc, hWnd, Rope, WINDOW, Box_w, Box_h, Box_nr);

	Box_nr = 3;
	BOX[Box_nr].ksztalt = 0;
	BOX[Box_nr].x = ((WINDOW.right - WINDOW.left) - (WINDOW.right - WINDOW.left) / 6.5) + BOX[3].move_x;
	BOX[Box_nr].y = (WINDOW.bottom - WINDOW.top + WINDOW.top / 6) + BOX[3].move_y;
	BOX[Box_nr].masa = 25;
	MovingBoxCreat(TEST, TEST_UP, hdc, hWnd, Rope, WINDOW, Box_w, Box_h, Box_nr);

	Box_nr = 4;
	BOX[Box_nr].ksztalt = 0;
	BOX[Box_nr].x = ((WINDOW.right - WINDOW.left) - (WINDOW.right - WINDOW.left) / 4) + BOX[4].move_x;
	BOX[Box_nr].y = ((WINDOW.bottom - WINDOW.top) + (WINDOW.bottom - WINDOW.top) / 6) + BOX[4].move_y;
	BOX[Box_nr].masa = 51;
	MovingBoxCreat(TEST, TEST_UP, hdc, hWnd, Rope, WINDOW, Box_w, Box_h, Box_nr);

	//lina
	graphics.DrawLine(&blackPen, Rope.x, y2, Rope.x, y2 + Rope.h);

	//graphics.FillRectangle(&solidBrush, TEST);
	//graphics.FillRectangle(&solidBrush, TEST_UP);

	//Napis po prawej
	FontFamily  fontFamily(L"Times New Roman");
	Font        font(&fontFamily, 24, FontStyleRegular, UnitPixel);
	PointF      pointF(30.0f, 10.0f);
	PointF      pointF2(95.0f, 10.0f);
	SolidBrush  solidBrush2(Color(255, 0, 0, 255));
	WCHAR string[] =
		L"Masa:";
	wchar_t MASA[12];
	_itow_s(Masa, MASA, sizeof(MASA) / 2, 10);

	graphics.DrawString(string, -1, &font, pointF, &solidBrush2);
	if (Masa <= Udźwig)
	{
		graphics.DrawString(MASA, -1, &font, pointF2, &solidBrush2);
	}
	else
		graphics.DrawString(
			L"Zbyt ciężkie", -1, &font, pointF2, &solidBrush2);

}

VOID StationPaint(HDC hdc, RECT WINDOW, Rope_stats Rope, HWND hWnd) {
	Graphics graphics(hdc);

	// Create a Pen object.
	Pen blackPen(Color(255, 0, 0, 0), 2);
	Pen yellowPen(Color(255, 255, 255, 0), 10);
	SolidBrush yellowBrush(Color(255, 200, 200, 0));
	SolidBrush orangeBrush(Color(255, 255, 191, 0));
	SolidBrush blueBrush(Color(255, 0, 255, 255));
	SolidBrush blackBrush(Color(255, 0, 0, 0));
	// Create a RectF object.
	int w = 50 * (WINDOW.right - WINDOW.left - 18) / 1000,
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
}

VOID RePaint(HWND hWnd, RECT* drawArea, RECT* Text, RECT WINDOW, Rope_stats Rope, PAINTSTRUCT& ps)
{
	if (&drawArea == NULL)
		InvalidateRect(hWnd, NULL, TRUE); // repaint all
	else
	{
		InvalidateRect(hWnd, drawArea, TRUE); //repaint drawArea
		InvalidateRect(hWnd, Text, TRUE);
	}
	hdc = BeginPaint(hWnd, &ps);
	MovePaint(hdc, WINDOW, Rope, hWnd);
	StationPaint(hdc, WINDOW, Rope, hWnd);
	EndPaint(hWnd, &ps);
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

	hwndButton = CreateWindow(TEXT("button"), TEXT("T"), WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX, 300, 200, 50, 50, hWnd, (HMENU)ID_BUTTON6, hInstance, NULL);

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

	int speed = 5;
	Rope_stats Rope;
	PAINTSTRUCT  ps;
	RECT WINDOW;
	GetWindowRect(hWnd, &WINDOW);
	Rope.x = (WINDOW.right - WINDOW.left - 18) / 2 + ((400 * (WINDOW.right - WINDOW.left - 18) / 1000) / 6) + pr_x;
	Rope.y = WINDOW.bottom - WINDOW.top - 40 - (50 * (WINDOW.bottom - WINDOW.top - 40) / 1000);
	Rope.h = pr_y;
	int wmId;
	int w = 50 * (WINDOW.right - WINDOW.left - 18) / 1000,
		h = 650 * (WINDOW.bottom - WINDOW.top - 40) / 1000,
		x = (WINDOW.right - WINDOW.left - 18) / 2 - w / 2,
		y = WINDOW.bottom - WINDOW.top - 40 - h;
	RECT drawArea{ x + 100,y + 3,2000,2000 };
	RECT Text{ 100,0,300,100 };
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
				SetTimer(hWnd, TMR_R, speed, NULL);
				prawo = 1;
			}
			else
			{
				prawo = 0;
				KillTimer(hWnd, TMR_R);
				RePaint(hWnd, &drawArea, &Text, WINDOW, Rope, ps);
			}
			break;
		case ID_BUTTON2://lewo
			if (lewo == 0)
			{
				SetTimer(hWnd, TMR_L, speed, NULL);
				lewo = 1;
			}
			else
			{
				lewo = 0;
				KillTimer(hWnd, TMR_L);
				RePaint(hWnd, &drawArea, &Text, WINDOW, Rope, ps);
			}
			break;
		case ID_BUTTON3://góra
			if (gora == 0)
			{
				SetTimer(hWnd, TMR_U, speed, NULL);
				gora = 1;
			}
			else
			{
				gora = 0;
				KillTimer(hWnd, TMR_U);
				RePaint(hWnd, &drawArea, &Text, WINDOW, Rope, ps);
			}
			break;
		case ID_BUTTON4://dół
			if (dol == 0)
			{
				SetTimer(hWnd, TMR_D, speed, NULL);
				dol = 1;
			}
			else
			{
				dol = 0;
				KillTimer(hWnd, TMR_D);
				RePaint(hWnd, &drawArea, &Text, WINDOW, Rope, ps);
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
		case ID_BUTTON6:
			if (tower == 0)
			{
				SetTimer(hWnd, TMR_T, speed, NULL);
				tower = 1;
			}
			else
			{
				KillTimer(hWnd, TMR_T);
				tower = 0;
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
					pr_x = pr_x + (WINDOW.right - WINDOW.left) / 700;
					Rope.x = (WINDOW.right - WINDOW.left - 18) / 2 + ((400 * (WINDOW.right - WINDOW.left - 18) / 1000) / 6) + pr_x;
					RePaint(hWnd, &drawArea, &Text, WINDOW, Rope, ps);
				}
			};
		case TMR_L:
			if (lewo == 1)
			{
				if (pr_x - 5 >= 0)
				{
					pr_x = pr_x - (WINDOW.right - WINDOW.left) / 700;
					Rope.x = (WINDOW.right - WINDOW.left - 18) / 2 + ((400 * (WINDOW.right - WINDOW.left - 18) / 1000) / 6) + pr_x;
					RePaint(hWnd, &drawArea, &Text, WINDOW, Rope, ps);
				}
			};
		case TMR_U:
			if (gora == 1)
			{
				if (pr_y >= 25)
				{
					pr_y = pr_y - (WINDOW.bottom - WINDOW.top) / 700;
					Rope.h = pr_y;
					RePaint(hWnd, &drawArea, &Text, WINDOW, Rope, ps);
				}
			};
		case TMR_D:
			if (dol == 1)
			{
				if (pr_y <= WINDOW.bottom - WINDOW.top - 500 * (WINDOW.bottom - WINDOW.top - 40) / 1000)
				{
					pr_y = pr_y + (WINDOW.bottom - WINDOW.top) / 700;
					Rope.h = pr_y;
					RePaint(hWnd, &drawArea, &Text, WINDOW, Rope, ps);
				}
			};
			break;
		case TMR_T:
			if (tower == 1)
			{
				if (czybylo00 == 0)
				{
					if (pr_x - 5 > 0 || pr_y > 25)
					{
						lewo = 1;
						gora = 1;
						SetTimer(hWnd, TMR_U, speed, NULL);
						SetTimer(hWnd, TMR_L, speed, NULL);
					}
					else
					{
						lewo = 0;
						KillTimer(hWnd, TMR_L);
						gora = 0;
						KillTimer(hWnd, TMR_U);
						czybylo00 = 1;



						if (Rope.x + 250 < BOX[1].x)
						{
							prawo = 1;
							SetTimer(hWnd, TMR_R, speed, NULL);
						}
						else
						{
							prawo = 0;
							KillTimer(hWnd, TMR_R);
						}
						if (Rope.y + 50 < BOX[1].y)
						{
							dol = 1;
							SetTimer(hWnd, TMR_D, speed, NULL);
						}
						else
						{
							dol = 0;
							KillTimer(hWnd, TMR_D);
						}
					}



				}

			}

			break;
		}
		return 0;
	}
	case WM_PAINT:
		BeginPaint(hWnd, &ps);
		MovePaint(hdc, WINDOW, Rope, hWnd);
		StationPaint(hdc, WINDOW, Rope, hWnd);
		EndPaint(hWnd, &ps);
		return 0L;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
} // WndProc