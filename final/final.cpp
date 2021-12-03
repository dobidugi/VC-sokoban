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
#include "Direction.h"
#include "Validator.h"

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

//
//#define PLAYER 9
//#define NORMAL 0
//#define WALL 1
//#define KEY 2
//#define NOT_CLEAR 3
//#define CLEAR 4


#define MOVE_UP 0
#define MOVE_DOWN 1
#define MOVE_LEFT 2
#define MOVE_RIGHT 3


Board*brd;
Player *player;
vector<vector<int>> map;
pair<int, int> user;
pair<int, int> mapSize;

int allClearCount = 0;
int nowClearCount = 0;



//void getMapSize(int stage)
//{
//    string file = to_string(stage) + ".dat";
//    ifstream in;
//    in.open(file);
//    if (!in.is_open()) {
//        std::cout << "파일을 찾을 수 없습니다!" << std::endl;
//    }
//    char buff[30];
//    int tmpX = 0;
//    int tmpY = 0;
//    while (in) {
//        in.getline(buff, 30);
//        for (int z = 0; z < 30; z++) {
//            if (buff[z] == NULL) {
//                break;
//            }
//            else {
//                tmpX++;
//            }
//        }
//        break;
//    }
//    while (in) {
//        in.getline(buff, 30);
//        tmpY++;
//    }
//    mapSize = { tmpY, tmpX };
//}
//
//void loadMap(int stage) {
//    string file = to_string(stage) + ".dat";
//    ifstream in;
//    string s;
//    char buff[30];
//    in.open(file);
//    if (!in.is_open()) {
//        std::cout << "파일을 찾을 수 없습니다!" << std::endl;
//        return;
//    }
//
//    int i = 0;
//    int j = 0;
//    bool firstFlag = true;
//
//    getMapSize(1);
//    while (in) {
//        in.getline(buff, 30);
//
//        if (firstFlag) { // 맵의 크기를 구해주기위해
//            int size = 0;
//            for (int z = 0; z < 30; z++) {
//                if (buff[z] == NULL) {
//                    break;
//                }
//                else {
//                    size++;
//                }
//            }
//
//            map.resize(size, vector<int>(size,0));
//            firstFlag = false;
//        }
//        for (int k = 0; k < 30; k++) {
//            if (buff[k] == NULL )
//                break;
//            else
//            {
//                map[i][j] = buff[k] -'0';
//                if (map[i][j] == PLAYER)
//                    user = { i, j };
//                if (map[i][j] == CLEAR)
//                    nowClearCount++;
//                if (map[i][j] == NOT_CLEAR || map[i][j] == CLEAR)
//                    allClearCount++;
//                j++;
//            }
//               
//        }
//        i++;
//        j = 0;
//    }
//
//    for (int i = 0; i < mapSize.first; i++) {
//        for (int j = 0; j < mapSize.second; j++) {
//            cout << map[i][j] << " ";
//        }
//        cout << endl;
//    }
//
//    cout << "읽기끝";
//}
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.
    brd = new Board();
    brd->loadStage(1);
    Validator* validator = new Validator(brd);
    player = new Player(validator);
 
    cout << "test" << endl;
    

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
//bool outOfRange(int y, int x)
//{
//    if (y < 0 || y >= map.size() || x < 0 || x >= map.size()) return true;
//    return  false;
//}
//
//bool checkMovePlayer(int y, int x)
//{
//    if (map[y][x] == WALL || map[y][x] == NOT_CLEAR || map[y][x] == CLEAR) return false;
//    return true;
//}
//
//bool checkMoveKey(int y, int x)
//{
//    if (map[y][x] == WALL || map[y][x] == CLEAR ) return false;
//    return true;
//}

void updatePlayerPosition(int y, int x)
{
    user = { y , x };
}


void clearCheck()
{
    cout << "check HAMSU" << endl;
    cout << nowClearCount << "/" << allClearCount << endl;
    if (nowClearCount == allClearCount) cout << "클리어 !!" << endl;
}
//void move_user(int direction) 
//{
//    cout << "move_user" << direction << endl;
//    int dy[] = { -1, 1, 0, 0 };
//    int dx[] = { 0, 0, -1, 1 };
//   
//    int nowY = user.first;
//    int nowX = user.second;
//    int ny = dy[direction] + nowY;
//    int nx = dx[direction] + nowX;
//
//    if (outOfRange(ny,nx)) return;
//    if (!checkMovePlayer(ny, nx)) return;
//    
//    if (map[ny][nx] == NORMAL)
//    {
//        map[nowY][nowX] = NORMAL;
//        map[ny][nx] = PLAYER;
//        user = { ny , nx };
//        updatePlayerPosition(ny, nx);
//    }
//      
//    else if (map[ny][nx] == KEY)
//    {
//        int nny = dy[direction] + ny;
//        int nnx = dx[direction] + nx;
//        if (outOfRange(nny, nnx)) return;
//        if (!checkMoveKey(nny, nnx)) return;
//        
//        if (map[nny][nnx] == NOT_CLEAR) {
//            map[nny][nnx] = CLEAR;
//            nowClearCount++;
//        }   
//        else if(map[nny][nnx] == NORMAL)
//            map [nny][nnx] = KEY;
//        map[user.first][user.second] = NORMAL;
//        map[ny][nx] = PLAYER;
//        updatePlayerPosition(ny, nx);
//        
//    }
//    
//}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_KEYDOWN :
    {
        switch (wParam)
        {
        case VK_LEFT:
            player->moveLeft();
            break;

        case VK_RIGHT:
            player->moveRight();
            break;
        case VK_UP:
            player->moveUp();
            break;
        case VK_DOWN:
            player->moveDown();
            break;
        }
        clearCheck();
        InvalidateRect(hWnd, NULL, false);
    }
    break;
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
            HBRUSH wallBrush, normalBrush, userBrush, keyBrush, notClearBrush, clearBrush;
            wallBrush = CreateSolidBrush(RGB(100, 0, 0));
            normalBrush = CreateSolidBrush(RGB(255, 255, 255));
            userBrush = CreateSolidBrush(RGB(0, 0, 255));
            notClearBrush = CreateSolidBrush(RGB(255, 0, 0));
            keyBrush = CreateSolidBrush(RGB(255, 255, 0));
            clearBrush = CreateSolidBrush(RGB(0, 255, 0));
            int nX = 0;
            int nY = rectSize;
            int nTop = 0;
            int nBottom = rectSize;
            for (int i = 1; i <= brd->ySize(); i++) {
                for (int j = 1; j <= brd->xSize(); j++) {
                    State nowState = brd->nowPositionState(i-1, j-1); //[i - 1] [j - 1] ;
                    if (nowState == State::WALL) // 벽 
                    {
                        SelectObject(hdc, wallBrush);
                        Rectangle(hdc, nX, nTop, nY, nBottom);
                    }
                    else if(nowState == State::NORMAL) // 이동가능한곳
                    {
                        SelectObject(hdc, normalBrush);
                        Rectangle(hdc, nX, nTop, nY, nBottom);
                    }
                    else if (nowState == State::PLAYER) // Player
                    {
                        
                        SelectObject(hdc, userBrush);
                        Rectangle(hdc, nX, nTop, nY, nBottom);
                    }
                    else if (nowState == State::KEY) // key
                    {
                        SelectObject(hdc, keyBrush);
                        Rectangle(hdc, nX, nTop, nY, nBottom);
                    }
                    else if (nowState == State::NOT_CLEAR) // notClear
                    {
                        SelectObject(hdc, notClearBrush);
                        Rectangle(hdc, nX, nTop, nY, nBottom);
                    }
                    else if (nowState == State::CLEAR) // clear
                    {
                        SelectObject(hdc, clearBrush);
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
            DeleteObject(userBrush);
            DeleteObject(keyBrush);
            DeleteObject(notClearBrush);
            DeleteObject(clearBrush);
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
