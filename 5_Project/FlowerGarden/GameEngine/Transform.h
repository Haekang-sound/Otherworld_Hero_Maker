#pragma once
#include "ElementBase.h"
#include "../MathEngine/Vector2.h"
// �θ��� ����� �������� �� ����� �����Ϸ��� D2D1_MATRIX_3X2_F �� �ʿ��� �� ����... ���� �� ������?
#include "../DirectY/DirectY.h"

using namespace MathEngine;

class Transform : public ElementBase
{
public:
	Transform();
	~Transform();

	/// Element Override
	virtual void Init() override;

	virtual void FixedUpdate() override;
	virtual void Update(float deltaTime) override;
	virtual void LateUpdate() override;

	virtual void PreRender() override;
	virtual void Render(DirectY* directY) override;
	virtual void PostRender(DirectY* directY) override;

	virtual void Release() override;

	virtual ElementType GetElementType() const override;

	virtual GameObject* GetGameObject() const override;
	virtual void SetGameObject(GameObject* gameObject) override;

	/// Local Coordinate System
	void SetLocalPosition(Vector2 position);
	void SetLocalRotation(float rotation);
	void SetLocalScale(Vector2 scale);

	Vector2 GetLocalPosition() const { return m_localPosition; }
	float GetLocalRotation() const { return m_localRotation; }
	Vector2 GetLocalScale() const { return m_localScale; }

	D2D1_MATRIX_3X2_F GetTransformMatrix
	() const { return m_transformMatrix; }

	/// World ��ǥ�� �θ� + �ڽ�
	Vector2 GetWorldPosition() const;

	D2D1_MATRIX_3X2_F GetWorldMatrix() const;

	/// Screen ��ǥ�� - �߰��ؾߵ�

	Vector2 GetScreenPosition() const;

	D2D1_MATRIX_3X2_F GetScreenMatrix() const;

	// SetTransform
	void SetTransform(DirectY* directY);

	/// ��ȯ ����
	void Translate(Vector2 translation);
	void Rotate(float angle);
	void Scale(Vector2 scale);

	void SetUseCamera(bool isUseCamera) { m_isUseCamera = isUseCamera; }

public:
	void SetParent(Transform* parentTransform);
	Transform* GetParent() { return m_parentTransform; }

	void SetLayer(int layer) { m_layer = layer; }
	int GetLayer() const { return m_layer; }

private:
	Vector2 m_localPosition;
	float	m_localRotation;
	Vector2 m_localScale;

	D2D1_MATRIX_3X2_F m_transformMatrix;

	bool m_isUseCamera;

private:
	int m_layer;
	Transform* m_parentTransform;
};