#pragma once

#include <string>
#include <vector>

#include "ElementBase.h"

class DirectY;

class GameObject
{
public:
	GameObject(std::string name);
	~GameObject();

	void Init();

	void FixedUpdate();

	void Update(float deltaTime);
	void LateUpdate();

	/// ����Ƽ������ Renderer��� Component�� ���� �ִµ� ������Ʈ�� �־ ������ ���� �� ����. 
	void PreRender();
	void Render(DirectY* directY);
	void PostRender(DirectY* directY);

	void Release();

	void SetElement(ElementBase* element, ElementType type);
	ElementBase* GetElement(ElementType type) const { return m_elements[(int)type]; }

	std::string GetName() const { return m_name; }
	void SetName(std::string name) { m_name = name; }

	void SetActive(bool isActive) { m_isActive = isActive; m_isDraw = isActive; }
	bool GetActive() { return m_isActive; }

	bool GetIsDraw() const { return m_isDraw; }
	void SetIsDraw(bool val) { m_isDraw = val; }

private:
	std::string m_name;
	/// element �� �������� ���� �ʱ�ȭ �����ִ� �Լ� �����
	std::vector<ElementBase*> m_elements;

	bool m_isActive = true;
	bool m_isDraw = true;
};