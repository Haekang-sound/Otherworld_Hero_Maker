#pragma once

#include <windows.h>	//HWND

///d2dheader
#include <d2d1.h>		//D2D
#include <dwrite.h>		//DWrite
#include <wincodec.h>	//WIC
#pragma comment(lib,"d2d1")					//D2D
#pragma comment(lib,"dwrite")				//DWrite
#pragma comment(lib,"windowscodecs.lib")	//WIC

///effectsheader
#include <d2d1_1.h>	//ID2D1Effect
#include <d2d1effects.h>	//D2DEffect
#include<d2d1effects_2.h> //edgeDetection
#pragma comment(lib,"d2d1.lib")	//���콺�� ����� ������ �� ��
#pragma comment(lib,"dxguid.lib")	//���콺�� ����� ������ �� ��

///myheader
#include "MakeMatrix.h"	//Transform
#include "Sprite.h"	//sprite����ü


class PaticleMaintain;

///mathEngine
#pragma comment(lib, "MathEngine.lib")

/// <summary>
/// ���� ����
/// </summary>
enum class TextAlignMent
{
	LEFT = 0,
	RIGHT,
	CENTER
};

/// <summary>
/// �׷��Ƚ� ����
/// 2023.08.13 ���¿�
/// </summary>
class DirectY
{
public:
	DirectY(HWND hWnd);
	~DirectY();

	///�⺻ �Լ�
	void BeginDraw();	//���� ����
	void EndDraw();	//���� ��
	void CleanWindow();	//ȭ�� ���� �����

	///�귯�� �� ����
	void SetBrushColor(const float& red, const float& green, const float& blue, const float& alpha);
	void SetBrushColor(const int& red, const int& green, const int& blue, const int& alpha);
	void SetBrushColor(D2D1::ColorF color);

	///�⺻ ���� �׸���
	//----------------------------------------------------------------------
	void DrawLine(Graphics::BaseFigure::Line line, const float thickness = 5.0f);	//�� �׸���
	void DrawRectangle(Graphics::BaseFigure::Rectangle rect, const float thickness = 1.0f);	//�簢�� �׸���
	void DrawCircle(Graphics::BaseFigure::Circle circle, const float thickness = 1.0f);	//�� �׸���
	void DrawEllipse(Graphics::BaseFigure::Ellipse ellipse, const float thickness = 1.0f);	//Ÿ�� �׸���
	void FillRectangle(Graphics::BaseFigure::Rectangle rect, const float thickness = 1.0f);	//���� �� �簢�� �׸���
	void DrawIsometric(Graphics::BaseFigure::IsomatricTile tile, const float thickness = 0.5f);	//4���� ������ �̾ �׸���
	//----------------------------------------------------------------------

	///���� ���
	//--------------------------------------------------------------------------
	void DrawText(const WCHAR* command, const float& x, const float& y, const float& fontsize = 20, TextAlignMent alignment = TextAlignMent::LEFT, const WCHAR* msc_fontName = L"Danjo-bold");
	bool DrawText(const int& x, const int& y, const float& fontsize, TextAlignMent alignment, const WCHAR* msc_fontName, const char* pch, ...);	//cŸ������ ���� ���
	DWRITE_TEXT_METRICS GetTextMetrics(const WCHAR* command);
	//--------------------------------------------------------------------------

	///transform
	//--------------------------------------------------------------------------
	void Identity() { m_renderTarget->SetTransform(D2D1::Matrix3x2F::Identity()); }		//�������� ����ȭ
	void SetTransform(const D2D1_MATRIX_3X2_F& matrix);	//��ȯ ����� ���� ��ȯ��Ų��
	//--------------------------------------------------------------------------

	///image
	//--------------------------------------------------------------------------
	ID2D1Bitmap* LoadImageFile(const wchar_t* path);	//�̹��� ��Ʈ�ʿ� �ø���
	void DrawBitmap(Graphics::Sprite* const sprite, const float opacity = 1.0f);	//��Ʈ�� �׸���
	void ImageRelease(ID2D1Bitmap*& image);	//�̹��� ����Ǿ��ִ� �̹��� �޸� ����
	//--------------------------------------------------------------------------

	///����Ʈ
	//------------------------------------------------------------
	ID2D1Bitmap* GausBlur(Graphics::Sprite* const sprite, const float blurCoefficient);
	ID2D1Bitmap* Convolve(Graphics::Sprite* const sprite);
	ID2D1Bitmap* DirectionBlur(Graphics::Sprite* const sprite, const float blurCoefficient);
	ID2D1Bitmap* EdgeDetection(Graphics::Sprite* const sprite, const float lineThickness, const float blur);
	ID2D1Bitmap* Morphology(Graphics::Sprite* const sprite);
	ID2D1Bitmap* DisplacementMap(Graphics::Sprite* const sprite, const float effectPower);
	ID2D1Bitmap* Sepia(Graphics::Sprite* const sprite, const float coefficient);
	ID2D1Bitmap* PointDiffuse(Graphics::Sprite* const sprite, Graphics::BaseFigure::Point pos, const float& red, const float& green, const float& blue);
	ID2D1Bitmap* Posterize(Graphics::Sprite* const sprite);
	ID2D1Bitmap* Emboss(Graphics::Sprite* const sprite);
	ID2D1Bitmap* Shadow(Graphics::Sprite* const sprite);

	//������ ���� - ���� ���� �ȴ�
	//---------------------------------------------------------------------
	ID2D1Bitmap* DistantDiffuse(Graphics::Sprite* const sprite, const float& red, const float& green, const float& blue);
	ID2D1Bitmap* DistantSpecular(Graphics::Sprite* const sprite, const float& red, const float& green, const float& blue);
	//---------------------------------------------------------------------

	/// �̹��� ����
	void FadeInFadeOut(Graphics::Sprite* image1, Graphics::Sprite* image2, D2D1_VECTOR_4F coefficient);

	// Ŭ����
	void StartClipping(int left, int top, int right, int bottom);
	void EndClipping();

	///�̹��� ��ġ��
	ID2D1Bitmap* ArithmeticComposite(Graphics::Sprite* image1, Graphics::Sprite* image2, D2D1_VECTOR_4F coefficient);
	ID2D1Bitmap* ArithmeticComposite(Graphics::Sprite* image1, Graphics::Sprite* image2);
	ID2D1Bitmap* ArithmeticCompositeBitmap(ID2D1Bitmap* image1, ID2D1Bitmap* image2, UINT32 width, UINT32 height);
	ID2D1Bitmap* Blend(Graphics::Sprite* image1, Graphics::Sprite* image2);
	//------------------------------------------------------------

	///text���� �а� �����ϴ� �Լ�
	//------------------------------------------------------------
	//��ǿ� ����
	void ReadSpriteTxtFile(const std::string textFileName, ID2D1Bitmap* image, Graphics::Motion* motion);
	//��������Ʈ�� ����
	Graphics::Sprite* ReadSpriteTxtFile(const std::string textFileName, ID2D1Bitmap* image);
	//------------------------------------------------------------

	//matrix�� vector2 ����
	static MathEngine::Vector2 MarixToVector(D2D1_MATRIX_3X2_F& matrix, MathEngine::Vector2 point)
	{
		MathEngine::Vector2 temp;
		temp.x = matrix.m11 * point.x + matrix.m12 * point.y + matrix.dx;
		temp.y = matrix.m21 * point.x + matrix.m22 * point.y + matrix.dy;

		return temp;
	}

	
	/// ��ƼŬ
	//test
	bool ispaticle = false;
	//------------------------------------------------------------
	//��ƼŬ�� ����� �����Ѵ�
	void SetPaticle(MathEngine::Vector2 pos, float deadTime, int movementSeed, Graphics::Sprite* sprite);
	
	//��ƼŬ�� �׸���
	void PaticleEffect(D2D1_MATRIX_3X2_F matrix);
	void PaticeUpdate(float deltatTime);

	void DeletePaticleEffect(); 
	//------------------------------------------------------------

private:
	//�ʱ�ȭ �Լ�
	int Initialize();
	//���� ����
	void SetTextAlignment(TextAlignMent alignment);
	//���� ����� ���� �⺻ ��������
	void SetTextFormat(const float fontsize = 20, const WCHAR* msc_fontName = L"Danjo-bold");
	//���������� ���ǻ� ����� �Լ�
	void FillRectangle(float leftTopX, float leftTopY, float rightBottomX, float rightBottomY, float thickness = 1.0f);

	//image�� bitmap���� �ٲ۴�
	ID2D1Bitmap* ImageToBitmap(ID2D1Image* pImg, Graphics::Sprite* const sprite);
	ID2D1Bitmap* ImageToBitmap(ID2D1Image* pImg, ID2D1Bitmap* image, UINT32 width, UINT32 height);

	//���� ���� ����
private:
	//���� �ڵ�
	HWND m_hWnd;

	//Ŭ���̾�Ʈ���� ������
	RECT m_clientSize;

	//�׸��� ���(���� Ÿ��)
	ID2D1HwndRenderTarget* m_renderTarget;

	//Factory
	ID2D1Factory* m_d2dFactory;			//D2D
	IDWriteFactory* m_dWriteFactory;	//DWrite
	IDWriteTextFormat* m_textFormat;	//DWrite
	IWICImagingFactory* m_wicImageFactory;	//WIC

	//���Ǽ�
	IDWriteTextLayout* m_textLayOut;	//drawtext
	PaticleMaintain* m_paticleManager;

	//�׸��� ����
	ID2D1SolidColorBrush* m_tempBrush;
	ID2D1SolidColorBrush* m_mainBrush;

	//��������Ʈ �ִϸ��̼�
	IWICBitmapDecoder* m_decoder;	//����� �̹����� ������ ��ü
	IWICBitmapFrameDecode* m_frameDecode;	//Ư�� �׸��� ������ ��ü
	IWICFormatConverter* m_converter;	//�̹��� ��ȯ ��ü

	/// ����Ʈ https://learn.microsoft.com/ko-kr/windows/win32/direct2d/built-in-effects
	//------------------------------------------------------------------------------------------------
	ID2D1DeviceContext* m_deviceContext;	//����Ʈ ����� ���� devicecontext (rendertarget�� ����)

	ID2D1Image* m_afterImage;	//����Ʈ�� ������ �̹��� ���� �뵵
	ID2D1Bitmap* m_afterBitmap;	//����Ʈ�� ������ �̹����� ��Ʈ������ ��ȯ�� ������ �뵵

	//���� effect
	ID2D1Effect* m_gaussianBlur;	//���콺 ��
	ID2D1Effect* m_convolve;	//convolve ��� ȿ��
	ID2D1Effect* m_directionBlur;	//���� ��
	ID2D1Effect* m_edgeDetection;	//������ ����
	ID2D1Effect* m_morphology;	//����

	//���� ȿ��
	ID2D1Effect* m_turbulence;	//�����
	ID2D1Effect* m_flood;	//ȫ��? �߹���

	//���� �� ��Ÿ��ȭ
	ID2D1Effect* m_displacementMap;	//���̾� �ְ�
	ID2D1Effect* m_distantDiffuse;	//�� Ȯ�� ����
	ID2D1Effect* m_distantSpecular;	//�� �ݻ� ����
	ID2D1Effect* m_emboss;	//�̹����� ����ó�� ȸ����
	ID2D1Effect* m_pointDiffuse;	//�� Ȯ��
	ID2D1Effect* m_posterize;	//������
	ID2D1Effect* m_shadow;	//�׸���

	//��ȯ
	ID2D1Effect* m_2DaffineTransform;	//2d ���� ��ȯ

	//����
	ID2D1Effect* m_composite;	//���� ȿ�� - 2�� �̻��� �̹��� ���� �� ��ġ��
	ID2D1Effect* m_arithmeticComposite;	//��� ���� ȿ�� - �̹��� ����ġ�� ����
	ID2D1Effect* m_blend;	//ȥ��

	//����
	ID2D1Effect* m_sepia;	//���Ǿ������� ��ȯ
	//------------------------------------------------------------------------------------------------

	ID2D1Bitmap* m_unFound;	//�����ڿ��� ��ο� �°� �־��ֱ�
};