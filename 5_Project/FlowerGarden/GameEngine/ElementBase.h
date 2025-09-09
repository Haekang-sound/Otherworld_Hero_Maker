#pragma once

enum class ElementType
{
	Transform,
	Animator,

	// UI ��, �и��� �ϴ� �� ������
	Button,
	Slider,
	Script,
	Scrollbar,
	Collider,
	// special ? Object? Mine? Script? 
	// �ƹ�ư �� ������Ʈ�� ���� ��ũ��Ʈ. 
	// ��� ������ �̿��ؼ� ������ �� �� ����.
	
	// ����� �ҽ��� ���� ���� �ʴ´�.
	AudioSource,
	
	End
};

class GameObject;
class DirectY;

/// <summary>
/// ��� Element�� ��� �ޱ� ���� Ŭ����
/// 
/// Entity Component System�� component�� �򰥸� �� �־ �̸��� �ٸ��� �������.
/// </summary>
class ElementBase
{
public:
	virtual void Init() abstract;

	virtual void FixedUpdate() abstract;
	virtual void Update(float deltaTime) abstract;
	virtual void LateUpdate() abstract;

	virtual void PreRender() abstract;
	virtual void Render(DirectY* directY) abstract;
	virtual void PostRender(DirectY* directY) abstract;

	virtual void Release() abstract;

	virtual ElementType GetElementType() const abstract;

	virtual GameObject* GetGameObject() const abstract;
	virtual void SetGameObject(GameObject* gameObject) abstract;

	virtual ~ElementBase() {};

protected:
	ElementBase() : m_gameObject(nullptr) {}

	// �� element�� ������ �ִ� Object
	GameObject* m_gameObject;
};