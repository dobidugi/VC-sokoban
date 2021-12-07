// final.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "final.h"
#include <vector>
#include <fstream>
#include <string>
#include <iostream>

#include "board.h"
#include "player.h"

#include "Validator.h"
#include "Snapshot.h"

#include <windows.h>
#include <objidl.h>
#include <gdiplus.h>
using namespace Gdiplus;
#pragma comment (lib,"Gdiplus.lib")
ULONG_PTR gdiplusToken;
GdiplusStartupInput gdiplusStartupInput;

#define MAX_LOADSTRING 10
using namespace std;

#ifdef UNICODE
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
#else
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#endif


// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

Board*brd;
Player *player;
Validator* validator;
Snapshot* snapshot;
int stage = 1;

void start(int stage)
{
    brd = new Board();
    brd->loadStage(stage);
    validator = new Validator(brd);
    player = new Player(validator);
    snapshot = new Snapshot(brd, player);
    
}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.
    start(stage);
    GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_FINAL, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_FINAL));

    MSG msg;

    // 기본 메시지 루프입니다:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_FINAL));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_FINAL);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);
   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//
//

RECT previousStageBtn;
RECT nextStageBtn;
RECT rollbackBtn;
void createCustomButton(HDC hdc)
{
    WCHAR textBuff[128] = { 0, };
    const int LEFT = 1240;
    const int RIGHT = 1350;
    previousStageBtn.left = LEFT;
    previousStageBtn.top = 60;
    previousStageBtn.right = RIGHT;
    previousStageBtn.bottom = 80;
    Rectangle(hdc, previousStageBtn.left, previousStageBtn.top, previousStageBtn.right, previousStageBtn.bottom);
    wsprintfW(textBuff, L"이전스테이지   ");
    TextOut(hdc, LEFT, 60, textBuff, lstrlenW(textBuff));


    nextStageBtn.left = LEFT;
    nextStageBtn.top = 90;
    nextStageBtn.right =  RIGHT;
    nextStageBtn.bottom = 110;
    Rectangle(hdc, nextStageBtn.left, nextStageBtn.top, nextStageBtn.right, nextStageBtn.bottom);
    wsprintfW(textBuff, L"다음스테이지   ");
    TextOut(hdc, LEFT, 90, textBuff, lstrlenW(textBuff));

    rollbackBtn.left = LEFT;
    rollbackBtn.top = 130;
    rollbackBtn.right = RIGHT;
    rollbackBtn.bottom = 150;
    Rectangle(hdc, rollbackBtn.left, rollbackBtn.top, rollbackBtn.right, rollbackBtn.bottom);
    wsprintfW(textBuff, L"되돌리기           ");
    TextOut(hdc, LEFT, 130, textBuff, lstrlenW(textBuff));

}
    


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    
    switch (message)
    {
    case WM_KEYDOWN:
    {
       
        switch (wParam)
        {
        case VK_LEFT:
            snapshot->capture();
            player->moveLeft();
            break;

        case VK_RIGHT:
            snapshot->capture();
            player->moveRight();
            break;
        case VK_UP:
            snapshot->capture();
            player->moveUp();
            break;
        case VK_DOWN:
            snapshot->capture();
            player->moveDown();
            break;
        }
      
      

        InvalidateRect(hWnd, NULL, true);
        if (validator->isEndGame())
        {
            MessageBox(hWnd, L"클리어 하였습니다.", L"축하 축하", MB_OK);
            start(++stage);
            InvalidateRect(hWnd, NULL, true);
        }
           
    }
    break;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다:
            switch (wmId)
            {
                break;
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            int rectSize = 0;
            if (brd->xSize() < 15 && brd->ySize() < 15)
            {
                rectSize = 60;
            }
            else if(brd->xSize() <20 && brd->ySize() < 20)
            {
                rectSize = 40;
            }
            else
            {
                rectSize = 20;
            }
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
            Image* wall = Image::FromFile(L"wall.png");
            Image* road = Image::FromFile(L"road.png");
            Image* playerUp = Image::FromFile(L"player_up.png");
            Image* playerDown = Image::FromFile(L"player_down.png");
            Image* playerLeft = Image::FromFile(L"player_left.png");
            Image* playerRight = Image::FromFile(L"player_right.png");
            Image* empty = Image::FromFile(L"empty.png"); // not clear
            Image* key = Image::FromFile(L"key.png");
            Image* clear = Image::FromFile(L"clear.png");
            ::Graphics g(hdc);
           
            int tmpI = 0;
            int tmpJ = 0;
            for (int i = 1; i <= brd->ySize() * rectSize; i+=rectSize) 
            {
                tmpJ = 0;
                for (int j = 1; j <= brd->xSize() * rectSize; j+=rectSize) 
                {
          
                    State nowState = brd->nowPositionState(tmpI,tmpJ++);
                    if (nowState == State::WALL) // 벽 
                    {
                        g.DrawImage(wall, j, i, rectSize, rectSize);
                    }
                    else if(nowState == State::NORMAL) // 이동가능한곳
                    {
                        g.DrawImage(road, j, i, rectSize, rectSize);
                    }
                    else if (nowState == State::PLAYER) // Player
                    {
                        if (player->getNowDirection() == 0)
                            g.DrawImage(playerUp, j, i, rectSize, rectSize);
                        else if (player->getNowDirection() == 1)
                            g.DrawImage(playerDown, j, i, rectSize, rectSize);
                        else if (player->getNowDirection() == 2)
                            g.DrawImage(playerLeft, j, i, rectSize, rectSize);
                        else if (player->getNowDirection() == 3)
                            g.DrawImage(playerRight, j, i, rectSize, rectSize);

                    }
                    else if (nowState == State::KEY) // key
                    {
     
                        g.DrawImage(key, j, i, rectSize, rectSize);
 
                    }
                    else if (nowState == State::NOT_CLEAR) // notClear
                    {
                        g.DrawImage(empty, j, i, rectSize, rectSize);

                    }
                    else if (nowState == State::CLEAR) // clear
                    {
                        g.DrawImage(clear, j, i, rectSize, rectSize);
                    }     
                }
                tmpI++;

            }

            
            WCHAR textBuff[30] = { 0, };
            wsprintfW(textBuff, L"이동 횟수 : %d        ", player->getMoveCount());
            TextOut(hdc, 1240, 0, textBuff, lstrlenW(textBuff));
            
            wsprintfW(textBuff, L"클리어 조건 : %d  / %d        ",brd->getNowClearCount(), brd->getAllClearCount());
            TextOut(hdc, 1240, 20, textBuff, lstrlenW(textBuff));
            
            if(brd->isFindFile())
                wsprintfW(textBuff, L"현재 스테이지 : %d        ", stage);
            else
                wsprintfW(textBuff, L"파일을 찾을수 없음");
            TextOut(hdc, 1240, 40, textBuff, lstrlenW(textBuff));
            createCustomButton(hdc);
            

            EndPaint(hWnd, &ps);
            delete wall;
            delete road;
            delete key;
            delete playerUp;
            delete playerDown;
            delete playerLeft;
            delete playerRight;
            delete empty;
            delete clear;
        }
        break;
    case WM_LBUTTONDOWN:
    {
        HDC hdc = GetDC(hWnd);
        int x = LOWORD(lParam);
        int y = HIWORD(lParam);
        RECT rect;
        rect.left = x;
        rect.top = y;
        rect.right = x + 1;
        rect.bottom = y + 1;
        Rectangle(hdc, rect.left, rect.top, rect.right, rect.bottom);
      
        RECT tmp;
        if (IntersectRect(&tmp, &rect, &previousStageBtn))
        {   
            start(--stage);
            if (!brd->isFindFile())
            {
                start(++stage);
            }
                
        }
        if (IntersectRect(&tmp, &rect, &nextStageBtn))
        {
            start(++stage);
            if (!brd->isFindFile())
            {
                start(--stage);
            }
               
        }
        if (IntersectRect(&tmp, &rect, &rollbackBtn))
        {
            snapshot->rollback();
        }
  

        InvalidateRect(hWnd, NULL, true);
        ReleaseDC(hWnd, hdc);
    }   
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
