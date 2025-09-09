#pragma once
#include <d2d1.h>		//D2D
#include <vector>
#include <string>

namespace Graphics
{
	//�⺻ ����
	namespace BaseFigure
	{
		//�簢��
		struct Rectangle
		{
			float left;
			float top;
			float right;
			float bottom;
		};

		//��
		struct Line
		{
			float startX;
			float startY;
			float endX;
			float endY;
		};

		//��
		struct Circle
		{
			float centerX;
			float centerY;

			float radius;
		};

		//Ÿ��
		struct Ellipse
		{
			float centerX;
			float centerY;

			float radiusX;
			float radiusY;
		};

		struct Point
		{
			float x;
			float y;
		};

		//isomatric �ٴ��� �� ��ġ�� ���� �ִ� ����ü
		struct IsomatricTile
		{
			Graphics::BaseFigure::Point centerXY;
			float height = 72 / 2;
			float width = 144 / 2;
		};

	}

	//sprite �ϳ� �ϳ��� ������ ���� ����ü
	struct Sprite
	{
		std::string m_name;	//�̸�
		int m_index;	//�ִϸ��̼� ��ü���� ���°���� �ε���
		float m_delayTime;	//��� ������ �ð�
		ID2D1Bitmap* m_image;	//�̹���
		D2D1_RECT_F m_drawSize;	//�׸� �̹��� ������
		D2D1_RECT_F m_drawArea;	//�̹��� ���ο� ��� �κ��� �׸���
		D2D1_POINT_2F m_drawPos;	//�̹����� ��� ��ġ�� �׸���
		D2D1_POINT_2F m_pivot = {0.5,0.5};	//���Լ��� �ؽ�Ʈ ������ �޾� �׸� �̹��� ������(drawSize)�� ����,���� ���� ���� ���� ũ���� pivot�� ����������Ѵ�

		Sprite(const std::string& name, const int& index, const float& delayTime, ID2D1Bitmap*& image, const D2D1_RECT_F& drawSize, const D2D1_RECT_F drawArea, const D2D1_POINT_2F& drawPos, const D2D1_POINT_2F& pivot)
			: m_name(name), m_index(index),m_delayTime(delayTime),m_image(image)
			,m_drawSize(drawSize), m_drawArea(drawArea), m_drawPos(drawPos),m_pivot(pivot)
		{
		}
	};

	//sprtie���� �ϳ��� ������� �����ϱ����� Ŭ����
	class Motion
	{
	public:
		Motion();
		~Motion();

		void AddSprite(Sprite* sprite);
		void SetTotalFrame(int totalFrame);
		void SetName(std::string name) { m_name = name; }

		Sprite* GetSprite(int index) const { /*if (index < 0) { index = 0; }*/ return m_spriteArray[index]; }
		std::string GetName() const { return m_name; }
		int GetTotalFrame() const { return m_totalFrame; }

		//test
		void SetImage(ID2D1Bitmap*& image)
		{
			static int index = 0;

			if (m_totalFrame <= 0)
			{
				return;
			}

			while (m_totalFrame > index)
			{
				m_spriteArray[index]->m_image = image;

				index++;
			}
		}

	private:
		std::string m_name;	//�̸�
		std::vector<Sprite*> m_spriteArray;	//��� �ϳ�
		int m_totalFrame;	//�ִϸ��̼� ��ü ������ ��

		void ResizeMotion();
	};
}