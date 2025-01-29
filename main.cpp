#include "framework.h"
#include "HIYOEngine.h"

#include "..\\HIYOEngine_SOURCE\HIYOApp.h"
#include "..\\HIYOEngine_Window\HIYOLoadScenes.h"

// 전역 변수:
HINSTANCE hInst;
HIYO::App gApp;

// 전방 선언:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);

// 메인 함수:
int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
    //윈도우 등록
    MyRegisterClass(hInstance);

    //윈도우 실행
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    MSG msg;

    //메시지 루프
    while (true)
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
                break;

            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            //APP 실행
            gApp.Run();
        }
    }

    return (int) msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_HIYOENGINE));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = nullptr;
    wcex.lpszClassName  = L"HIYOKey";
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance;

   //윈도우 크기 설정:
   const UINT width = 1600;
   const UINT height = 900;

   HWND hWnd = CreateWindowW(L"HIYOKey", L"HIYOEngine", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, 0, width, height, nullptr, nullptr, hInstance, nullptr);


   //APP 초기화:
   gApp.Init(hWnd, width, height);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   //씬 생성:
   HIYO::LoadScenes();

   return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}