#include "Scrollbar.h"
#include "../DirectY/DirectY.h"
#include "../DirectY/Sprite.h"

#include "GameObject.h"
#include "Transform.h"
#include "InputManager.h"

Scrollbar::Scrollbar(int left, int top, int right, int bottom, Graphics::Sprite* background, Graphics::Sprite* bar, Graphics::Motion* messagebubble1, Graphics::Motion* messagebubble2)
	:m_left(left),m_top(top),m_right(right),m_bottom(bottom), m_background(background), m_bar(bar), m_herochatwindow(NULL),m_goddesschatwindow(NULL),
	m_lineInteval(30), m_interval(0), m_maxLine(9), m_offsetY (25), m_offsetX (35)
{
	
}

Scrollbar::~Scrollbar()
{
	m_texts.clear();
	delete m_goddesschatwindow;
	delete m_herochatwindow;
	delete m_background;
	delete m_bar;
}

void Scrollbar::Init()
{

}

//(m_maxLine + m_interval) * m_lineInteval

void Scrollbar::FixedUpdate()
{

}

void Scrollbar::Update(float deltaTime)
{
	if (InputManager::GetInstance().GetWheelPower() > 0)
	{
		InputManager::GetInstance().SetWheelPower(0);
		if (m_interval > 0)
		{
			m_interval--;
		}
	}
	if (InputManager::GetInstance().GetWheelPower() < 0)
	{
		InputManager::GetInstance().SetWheelPower(0);
		if ((int)m_texts.size() > m_interval + m_maxLine)
		{
			m_interval++;
		}
	}

	// interval�� 0�̸� �ٰ� �� ����
	if (m_interval < 0.01f)
	{
		m_bar->m_drawPos = { m_background->m_drawSize.right - m_bar->m_drawSize.right - 30, m_background->m_drawSize.top };
	}
	else if (m_texts.size() >= m_interval + m_maxLine)
	{
		m_bar->m_drawPos = { m_background->m_drawSize.right - m_bar->m_drawSize.right - 30,
		m_background->m_drawSize.top +
		(((m_background->m_drawSize.bottom - m_bar->m_drawSize.bottom) - m_background->m_drawSize.top) *
		(m_interval / (m_texts.size() - m_maxLine))) };
	}
	// ������ ���� �巡�� �����ϰ�
	// interval + maxLine�� ������ m_texts.size() 
}

void Scrollbar::LateUpdate()
{

}

void Scrollbar::PreRender()
{

}

// ��� ��� - ���, Ŭ���� ��ġ
// Ŭ����
// �� ��� - �� ��ġ
// �ؽ�Ʈ Set Transform
// �ؽ�Ʈ ���
void Scrollbar::Render(DirectY* directY)
{
	directY->DrawBitmap(m_background);
	if ((int)m_texts.size() > m_maxLine)
	{
		directY->DrawBitmap(m_bar);
	}

	// Text ��� ����
	directY->StartClipping(m_left, m_top, m_right, m_bottom);
	
	Transform* myTransform = ((Transform*)m_gameObject->GetElement(ElementType::Transform));
	myTransform->SetLocalPosition({myTransform->GetLocalPosition().x, myTransform->GetLocalPosition().y + (-m_interval * m_lineInteval)});
	directY->SetTransform(myTransform->GetWorldMatrix());

	directY->SetBrushColor(255, 0, 0, 255);
	for (int i = 0; i < (int)m_texts.size(); i++)
	{
		//ù��°������ height���� �ι�� Ƥ�� �̰� ���� -�̰Ŷ��� �ϵ� �ڵ��Ѵ�... ��Ʈ �ٲٴϱ� �ذ�ȴ�
		float imagewidth = 17; // ��ǳ�� width ��
		float imageoffset = 11;	//�̹������� ���ļ� �ϳ��� ��ǳ�� ó�� �����ߵȴ�

		DWRITE_TEXT_METRICS textRect = directY->GetTextMetrics(m_texts[i].first.c_str());

		if (m_texts[i].second)
		{
			m_herochatwindow->GetSprite(0)->m_drawPos = { m_background->m_drawSize.left + m_offsetX + imageoffset ,m_offsetY + 25 + (float)(m_lineInteval * i) };
			m_herochatwindow->GetSprite(0)->m_drawSize = { 0,0,imagewidth,textRect.height };

			m_herochatwindow->GetSprite(2)->m_drawPos = { m_background->m_drawSize.left + textRect.width + m_offsetX + imageoffset + imagewidth - 1 ,m_offsetY + 25 + (float)(m_lineInteval * i) };
			m_herochatwindow->GetSprite(2)->m_drawSize = { 0,0,imagewidth,textRect.height};

			directY->DrawBitmap(m_herochatwindow->GetSprite(0));
			directY->DrawBitmap(m_herochatwindow->GetSprite(2));

			m_herochatwindow->GetSprite(1)->m_drawPos = { m_background->m_drawSize.left + m_offsetX + imageoffset+ imagewidth ,m_offsetY + 25 + (float)(m_lineInteval * i) };
			m_herochatwindow->GetSprite(1)->m_drawSize = { 0,0,textRect.width  ,textRect.height};
			directY->DrawBitmap(m_herochatwindow->GetSprite(1));

			directY->SetBrushColor(255, 255, 255, 255);
			directY->DrawText(m_texts[i].first.c_str(),m_background->m_drawSize.left + m_offsetX + imageoffset + imagewidth, m_top + (float)(m_lineInteval * i), 20, TextAlignMent::LEFT, L"Danjo");
		}
		else
		{
			m_goddesschatwindow->GetSprite(0)->m_drawPos = { m_background->m_drawSize.right - textRect.width - m_offsetX - imageoffset ,m_offsetY + 27 + (float)(m_lineInteval * i) };
			m_goddesschatwindow->GetSprite(0)->m_drawSize = { 0,0,imagewidth,textRect.height };

			m_goddesschatwindow->GetSprite(2)->m_drawPos = { m_background->m_drawSize.right - m_offsetX - imagewidth ,m_offsetY + 27 + (float)(m_lineInteval * i) };
			m_goddesschatwindow->GetSprite(2)->m_drawSize = { 0,0,imagewidth,textRect.height };

			directY->DrawBitmap(m_goddesschatwindow->GetSprite(0));
			directY->DrawBitmap(m_goddesschatwindow->GetSprite(2));

			m_goddesschatwindow->GetSprite(1)->m_drawSize = { 0,0,textRect.width - imagewidth  ,textRect.height };
			m_goddesschatwindow->GetSprite(1)->m_drawPos = { m_background->m_drawSize.right - textRect.width - m_offsetX ,m_offsetY + 27 + (float)(m_lineInteval * i) };
			directY->DrawBitmap(m_goddesschatwindow->GetSprite(1));

			directY->SetBrushColor(255, 255, 255, 255);
			directY->DrawText(m_texts[i].first.c_str(), m_background->m_drawSize.right - m_offsetX, m_top + (float)(m_lineInteval * i), 20, TextAlignMent::RIGHT, L"Danjo");
		}
	}

	myTransform->SetLocalPosition({ myTransform->GetLocalPosition().x, myTransform->GetLocalPosition().y + (m_interval * m_lineInteval) });
	directY->SetTransform(myTransform->GetWorldMatrix());

 	directY->EndClipping();
}

void Scrollbar::PostRender(DirectY* directY)
{

}

void Scrollbar::Release()
{

}

ElementType Scrollbar::GetElementType() const
{
	return ElementType::Scrollbar;
}

GameObject* Scrollbar::GetGameObject() const
{
	return m_gameObject;
}

void Scrollbar::SetGameObject(GameObject* gameObject)
{
	m_gameObject = gameObject;
}

void Scrollbar::AddText(std::wstring text,bool isNpc)
{
	m_texts.push_back({text,isNpc});
	if ((int)m_texts.size() > m_maxLine + m_interval)
	{
		m_interval++;
	}
}