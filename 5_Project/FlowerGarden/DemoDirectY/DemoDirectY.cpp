// DemoDirectY.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//


#include "framework.h"
#include "DemoDirectY.h"

#define _USE_MATH_DEFINES
#include <math.h>
#include <cmath>

#include "../DirectY/DirectY.h"

#include <direct.h>//디렉토리 위치 찾기

///메모리 누수확인용
//https://learn.microsoft.com/ko-kr/cpp/c-runtime-library/find-memory-leaks-using-the-crt-library?view=msvc-170
#define _CRTDBG_MAP_ALLOC

#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW
#endif
#endif  // _DEBUG

//#include <cstdlib>
#include <stdlib.h>
#include <crtdbg.h>

// x86.ver
//#include "../DirectY/DirectY.h"

#include "../DirectY/Paticle.h"

#include "InputManager.h"



#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);

///test용 전역변수
float x = 0;
float y = 0;
double angle = 0;
float scaleX = 1;
float scaleY = 1;

float coffientX = 0.0f;
float coffientY = 0.0f;
float coffientZ = 0.0f;
float coffientW = 0.0f;

D2D1_MATRIX_3X2_F rotationMatrix;
D2D1_MATRIX_3X2_F moveMatrix;
D2D1_MATRIX_3X2_F scalematrix;
D2D1_MATRIX_3X2_F transformmatrix;

ID2D1Bitmap* arr[10];

static double frame = 0;
static int index = 0;


void Keyinput()
{
	//산술연산 X 값 변환
	if (GetAsyncKeyState(VK_UP))
	{
		coffientX += 0.01f;

		if (coffientX >= 1.f)
		{
			coffientX = 1.f;
		}
	}

	if (GetAsyncKeyState(VK_DOWN))
	{
		coffientX -= 0.01f;
		if (coffientX <= 0.f)
		{
			coffientX = 0.f;
		}
	}

	//산술연산 Y 값 변환
	if (GetAsyncKeyState(VK_RIGHT))
	{
		coffientY += 0.01f;

		if (coffientY >= 1.f)
		{
			coffientY = 1.f;
		}
	}

	if (GetAsyncKeyState(VK_LEFT))
	{
		coffientY -= 0.01f;
		if (coffientY <= 0.f)
		{
			coffientY = 0.f;
		}
	}

	//산술 연산 Z값 변환
	if (GetAsyncKeyState(VK_DELETE))
	{
		coffientZ += 0.01f;
		if (coffientZ >= 1.f)
		{
			coffientZ = 1.f;
		}
	}
	if (GetAsyncKeyState(VK_END))
	{
		coffientZ -= 0.01f;
		if (coffientZ <= 0.f)
		{
			coffientZ = 0.f;
		}
	}


	//산술 연산 W값 변환
	if (GetAsyncKeyState(VK_INSERT))
	{
		coffientW += 0.01f;
		if (coffientW >= 1.f)
		{
			coffientW = 1.f;
		}
	}
	if (GetAsyncKeyState(VK_HOME))
	{
		coffientW -= 0.01f;
		if (coffientW <= 0.f)
		{
			coffientW = 0.f;
		}
	}


	///이동
	//A
	if (GetAsyncKeyState(0x41))
	{
		x -= 3;

		moveMatrix.m11 = 1;		moveMatrix.m12 = 0;
		moveMatrix.m21 = 0;		moveMatrix.m22 = 1;
		moveMatrix.dx = (float)x;	moveMatrix.dy = (float)y;
	}
	//D
	if (GetAsyncKeyState(0x44))
	{

		x += 3;
		moveMatrix.m11 = 1;		moveMatrix.m12 = 0;
		moveMatrix.m21 = 0;		moveMatrix.m22 = 1;
		moveMatrix.dx = (float)x;	moveMatrix.dy = (float)y;
	}

	//S
	if (GetAsyncKeyState(0x53))
	{
		y += 3;
		moveMatrix.m11 = 1;		moveMatrix.m12 = 0;
		moveMatrix.m21 = 0;		moveMatrix.m22 = 1;
		moveMatrix.dx = (float)x;	moveMatrix.dy = (float)y;
	}

	//W
	if (GetAsyncKeyState(0x57))
	{
		y -= 3;
		moveMatrix.m11 = 1;		moveMatrix.m12 = 0;
		moveMatrix.m21 = 0;		moveMatrix.m22 = 1;
		moveMatrix.dx = (float)x;	moveMatrix.dy = (float)y;
	}


	//회전 Q
	if (GetAsyncKeyState(0x51))
	{
		angle += 5;

		rotationMatrix.m11 = (float)cos(angle * M_PI / 180);	rotationMatrix.m12 = (float)sin(angle * M_PI / 180);
		rotationMatrix.m21 = (float)-sin(angle * M_PI / 180);	rotationMatrix.m22 = (float)cos(angle * M_PI / 180);
		rotationMatrix.dx = 0; rotationMatrix.dy = 0;
	}
	//회전 E
	if (GetAsyncKeyState(0x45))
	{
		angle -= 5;
		rotationMatrix.m11 = (float)cos(angle * M_PI / 180);	rotationMatrix.m12 = (float)sin(angle * M_PI / 180);
		rotationMatrix.m21 = (float)-sin(angle * M_PI / 180);	rotationMatrix.m22 = (float)cos(angle * M_PI / 180);
		rotationMatrix.dx = 0; rotationMatrix.dy = 0;
	}


	//크기 조정 J
	if (GetAsyncKeyState(0x4A))
	{
		scaleX += 0.01f;
		scaleY += 0.01f;

		scalematrix.m11 = (float)scaleX;  scalematrix.m12 = 0;
		scalematrix.m21 = 0;	scalematrix.m22 = (float)scaleY;
		scalematrix.dx = 0;		scalematrix.dy = 0;
	}
	//크기 조정 K
	if (GetAsyncKeyState(0x4B))
	{
		scaleX -= 0.01f;
		scaleY -= 0.01f;

		scalematrix.m11 = (float)scaleX;  scalematrix.m12 = 0;
		scalematrix.m21 = 0;	scalematrix.m22 = (float)scaleY;
		scalematrix.dx = 0;		scalematrix.dy = 0;
	}

	transformmatrix = scalematrix * rotationMatrix * moveMatrix;
}
void Initialize()
{
	//행렬 초기화
	moveMatrix.m11 = 1;		moveMatrix.m12 = 0;
	moveMatrix.m21 = 0;		moveMatrix.m22 = 1;
	moveMatrix.dx = (float)x;	moveMatrix.dy = (float)y;

	rotationMatrix.m11 = (float)cos(angle * M_PI / 180);	rotationMatrix.m12 = (float)sin(angle * M_PI / 180);
	rotationMatrix.m21 = (float)-sin(angle * M_PI / 180);	rotationMatrix.m22 = (float)cos(angle * M_PI / 180);
	rotationMatrix.dx = 0; rotationMatrix.dy = 0;

	scalematrix.m11 = (float)scaleX;  scalematrix.m12 = 0;
	scalematrix.m21 = 0;	scalematrix.m22 = (float)scaleY;
	scalematrix.dx = 0;		scalematrix.dy = 0;

	//char curDir[1000];

	//graphicsEngine->SetTransform(scalematrix);
	//graphicsEngine->SetTransform(rotationMatrix);
	//graphicsEngine->SetTransform(moveMatrix);

	/*///현재 디렉토리 경로 확인
	_getcwd(curDir, 1000);
	graphicsEngine->SetBrushColor({ 0,0,0,1 });
	graphicsEngine->DrawText(810, 892, 30, L"굴림", "경로 : %s", curDir);*/
}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);


	///메모리 누수 확인
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetBreakAlloc(1229);

	LoadStringW(hInstance, IDC_DEMODIRECTY, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

	HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, 1920, 1220, nullptr, nullptr, hInstance, nullptr);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	MSG msg;

	//엔진 초기화
	DirectY* graphicsEngine = new DirectY(hWnd);
	if (graphicsEngine == NULL)
	{
		MessageBox(hWnd, L"DirectY Create Failed", NULL, MB_OK);
	}



	//test
	Initialize();
	InputManager::GetInstance().Init(hWnd);

	arr[0] = graphicsEngine->LoadImageFile(L"./Resource/light.png");
	arr[1] = graphicsEngine->LoadImageFile(L"./Resource/bg.png");
	arr[2] = graphicsEngine->LoadImageFile(L"./Resource/link.png");
	arr[3] = graphicsEngine->LoadImageFile(L"./Resource/samplepaticle.png");
	arr[4] = graphicsEngine->LoadImageFile(L"./Resource/fog.png");
	arr[5] = graphicsEngine->LoadImageFile(L"./Resource/PoliceCar002.png");
	arr[6] = graphicsEngine->LoadImageFile(L"./Resource/paticle.png");
	arr[7] = graphicsEngine->LoadImageFile(L"./Resource/redlight.png");
	arr[8] = graphicsEngine->LoadImageFile(L"./Resource/bluelight.png");
	//arr[8] = graphicsEngine->LoadImageFile(L"./Resource/PointLight.png");


	/*Graphics::Motion* zelda = new Graphics::Motion();
	graphicsEngine->ReadSpriteTxtFile("Zelda", arr[2], zelda);

	Graphics::Sprite* test1 = new Graphics::Sprite("light", 0, 0, arr[0], { 0,0,1000,1000 }, { 100,100 }, { 100,100 }, { 100,100 });
	Graphics::Sprite* test3 = new Graphics::Sprite("link", 0, 0, arr[2], {0,0,1200,1040 }, { 1400,900 }, { 100,100 }, { 100,100 });
	Graphics::Sprite* test4 = new Graphics::Sprite("circlelightmap", 0, 0, arr[3], { 1400,900 }, { 1400,900 }, { 100,100 }, { 100,100 });
	Graphics::Sprite* test5 = new Graphics::Sprite("fog", 0, 0, arr[4], { 0,0,1400,900 }, { 1400,900 }, { 100,100 }, { 100,100 });
	*/

	//스프라이트
	Graphics::Sprite* bg = new Graphics::Sprite("bg", 0, 0, arr[1], { 0,0,1400,1000 }, { 1400,1000 }, { 100,100 }, { 100,100 });
	Graphics::Sprite* redPoliceCar = new Graphics::Sprite("policecar", 0, 0, arr[5], { 0,0,720,600 }, { 70,70 }, { 0,0 }, { 0,0 });
	Graphics::Sprite* bluePoliceCar = new Graphics::Sprite("policecar", 0, 0, arr[5], { 0,0,720,600 }, { 720,600 }, { 0,0 }, { 0,0 });
	Graphics::Sprite* redlight = new Graphics::Sprite("redlight", 0, 0, arr[7], { 0,0,720,600 }, { 1400,900 }, { 0,0 }, { 0,0 });
	Graphics::Sprite* bluelight = new Graphics::Sprite("bluelight", 0, 0, arr[8], { 0,0,720,600 }, { 1400,900 }, { 0,0 }, { 0,0 });

	Graphics::Sprite* paticle = new Graphics::Sprite("paticle", 0, 0, arr[6], { 0,0,70,70 }, { 70,70 }, { 00,00 }, { 0,0 });
	Graphics::Sprite* samplepaticle = new Graphics::Sprite("samplepaticle", 0, 0, arr[3], { 0,0,70,70 }, { 70,70 }, { 00,00 }, { 0,0 });

	//모션
	Graphics::Motion* redpolicecar = new Graphics::Motion();
	redPoliceCar->m_image = graphicsEngine->ArithmeticComposite(redPoliceCar, redlight, { 1,1,1,0 });
	graphicsEngine->ReadSpriteTxtFile("policecar", redPoliceCar->m_image, redpolicecar);

	Graphics::Motion* bluepolicecar = new Graphics::Motion();
	bluePoliceCar->m_image = graphicsEngine->ArithmeticComposite(bluePoliceCar, bluelight, { 1,1,1,0 });
	graphicsEngine->ReadSpriteTxtFile("bluePolice", bluePoliceCar->m_image, bluepolicecar);

	//Paticle* testpaticle = new Paticle();
	//testpaticle->SetSprite(paticle);

	//test3->m_image = graphicsEngine->PointDiffuse(test3, { 160,55 }, 1, 1, 0);
	//monozelda->GetSprite(1)->m_image = test3->m_image;

	//Graphics::Sprite* policecar = new Graphics::Sprite("pointlightmap", 0, 0, arr[0], { 0,0,700,700 },{ 700,697 }, { 100,100 }, { 100,100 });
	//ID2D1Bitmap* blue = graphicsEngine->PointDiffuse(policecar, { 320,120 }, 0, 0, 1);
	//ID2D1Bitmap* red = graphicsEngine->PointDiffuse(policecar, { 390,160 }, 0.7, 0.1, 0.22);
	//Graphics::Sprite* test10 = new Graphics::Sprite("pointlightmap", 0, 0,red, { 0,0,700,700 }, { 700,697 }, { 100,100 }, { 100,100 });


	//test10->m_image = graphicsEngine->Blend(policecar,test10);
	//test10->m_image = graphicsEngine->Blend(test10,policecar);
	//test10->m_image = graphicsEngine->ArithmeticComposite( test2,test10, { 1,01,00.0,0 });

	while (true)
	{
		InputManager::GetInstance().Update();

		frame += 0.03;
		if (frame >= 2)
		{
			frame = 0;
			index++;
			if (index >= 30)
			{
				index = 0;
			}

			/*if (coffientY > 1.0f)
			{
				coffientY -= 0.1f;

			}
			else
			{
				coffientY += 0.1f;
			}*/
		}

		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			if (GetAsyncKeyState(VK_ESCAPE))
			{
				break;
			}

			if (msg.message == WM_QUIT)
			{
				break;
			}

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			Keyinput();
			if (InputManager::GetInstance().IsGetKeyDown(VK_UP))
			{
				if (!graphicsEngine->ispaticle)
				{
					graphicsEngine->ispaticle = true;
				}
				else
				{
					graphicsEngine->ispaticle = false;
				}
			}

			//PoliceCar->m_image = graphicsEngine->ArithmeticComposite(policecar->GetSprite(index), redlight, { coffientX,coffientY,coffientZ,coffientW });
			graphicsEngine->BeginDraw();
			graphicsEngine->Identity();
			graphicsEngine->CleanWindow();
			//graphicsEngine->DrawBitmap(bg);

			if (graphicsEngine->ispaticle)
			{
				graphicsEngine->SetPaticle({ 500,500 }, 10, 0, samplepaticle);
				graphicsEngine->SetPaticle({ 500,500 }, 5, 1, samplepaticle);
				graphicsEngine->SetPaticle({ 500,500 }, 3, 2, samplepaticle);
				graphicsEngine->SetPaticle({ 500,500 }, 2, 3, samplepaticle);
				graphicsEngine->SetPaticle({ 500,500 }, 7, 4, samplepaticle);
				graphicsEngine->ispaticle = false;
			}

			graphicsEngine->SetTransform(MakeMatrix()({ scaleX,scaleY }, angle, { x,y }));



			graphicsEngine->FadeInFadeOut(bg, redPoliceCar, { coffientX,coffientY,coffientZ,coffientW });

			graphicsEngine->EndDraw();
		}
	}

	//delete zelda;
	//delete test1;
	//delete test3;
	//delete test4;
	//delete test5;

	delete bg;
	delete bluePoliceCar;
	delete redPoliceCar;
	delete paticle;

	delete samplepaticle;

	delete redlight;
	delete bluelight;

	delete redpolicecar;
	delete bluepolicecar;

	delete graphicsEngine;

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);
	_CrtDumpMemoryLeaks();

	return (int)msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_DEMODIRECTY));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_DEMODIRECTY);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
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
