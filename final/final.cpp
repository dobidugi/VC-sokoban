// final.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "final.h"
#include <vector>
#include <fstream>
#include <string>
#include <iostream>
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

vector<vector<int>> map;
void loadMap(int stage) {
    string file = to_string(stage) + ".dat";
    ifstream in;
    string s;
    char buff[30];
    in.open(file);
    if (!in.is_open()) {
        std::cout << "파일을 찾을 수 없습니다!" << std::endl;
    }

    int i = 0;
    int j = 0;
    bool firstFlag = true;
    while (in) {
        in.getline(buff, 30);

        if (firstFlag) { // 맵의 크기를 구해주기위해
            int size = 0;
            for (int z = 0; z < 30; z++) {
                if (buff[z] == NULL) {
                    break;
                }
                else {
                    size++;
                }
            }

            map.resize(size, vector<int>(size,0));
            firstFlag = false;
        }
        for (int k = 0; k < 30; k++) {
            if (buff[k] == NULL )
                break;
            else
            {
                map[i][j++] = buff[k] -'0';
            }
               
        }
        i++;
        j = 0;
    }

    for (int i = 0; i < map.size(); i++) {
        for (int j = 0; j < map.size(); j++) {
            cout << map[i][j] << " ";
        }
        cout << endl;
    }

    cout << "읽기끝";
}
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.
   
 
    cout << "test" << endl;
    loadMap(1);
    

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

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다:
            switch (wmId)
            {
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
            int rectSize = 50;  
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
            HBRUSH wallBrush, normalBrush, humanBrush, keyBrush, doorBrush;
            wallBrush = CreateSolidBrush(RGB(100, 0, 0));
            normalBrush = CreateSolidBrush(RGB(255, 255, 255));
            humanBrush = CreateSolidBrush(RGB(0, 0, 255));
            int nX = 0;
            int nY = rectSize;
            int nTop = 0;
            int nBottom = rectSize;
            for (int i = 1; i <= map.size(); i++) {
                for (int j = 1; j <= map.size(); j++) {
                    //int nowState = map[i = 1][j - 1];
                   /* if (nowState == 1)
                        SelectObject(hdc, wallBrush);*/
                    int nowState = map[i - 1][j - 1];
                    if (nowState == 1)
                    {
                        SelectObject(hdc, wallBrush);
                        Rectangle(hdc, nX, nTop, nY, nBottom);
                    }
                    else if(nowState == 0)
                    {
                        SelectObject(hdc, normalBrush);
                        Rectangle(hdc, nX, nTop, nY, nBottom);
                    }
                    else if (nowState == 9)
                    {
                        SelectObject(hdc, humanBrush);
                        Rectangle(hdc, nX, nTop, nY, nBottom);
                    }
                        
                    nX = nX + rectSize;
                    nY = nY + rectSize;
                }
                nX = 0;
                nY = rectSize;
                nTop = nTop + rectSize;
                nBottom = nBottom + rectSize;
            }
            EndPaint(hWnd, &ps);
            DeleteObject(wallBrush);
            DeleteObject(normalBrush);
            DeleteObject(humanBrush);
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
