#pragma once
#include "ElementBase.h"

// ElmentType::Script�� Camera ������Ʈ�� �־ ����ϸ� ��

class Camera : public ElementBase
{
public:
	Camera();
	~Camera();

	virtual void Init() override;

	virtual void FixedUpdate() override;
	virtual void Update(float deltaTime) override;
	virtual void LateUpdate() override;

	virtual void PreRender() override;
	virtual void Render(DirectY* directY) override;
	virtual void PostRender(DirectY* directY) abstract override;

	virtual void Release() override;

	virtual ElementType GetElementType() const override;

	virtual GameObject* GetGameObject() const override;
	virtual void SetGameObject(GameObject* gameObject) override;
};

