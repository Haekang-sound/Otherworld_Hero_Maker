#pragma once

#include <string>
#include <vector>

class GameObject;

class DirectY;

class Scene
{
public:
	Scene(std::string sceneName);
	~Scene();

	void Init();

	void FixedUpdate();
	void Update(float deltaTime);
	void LateUpdate();

	void PreRender();
	void Render(DirectY* directY);
	void PostRender(DirectY* directY);

	void Release();

	GameObject* CreateObject(std::string name);
	void		AddObject(GameObject* gameObject);
	void		DeleteObject(std::string name);
	GameObject* FindObject(std::string name);

	void DeleteAllObject();

	/// ������Ʈ ���̾ ���� �ͺ��� (�θ����) TransformMatrix�� ����� ���� Sort�� �Ѵ�. ������ Transform�� Layer
	void		SortObjects();

	std::string GetName() const { return m_name; }

private:
	std::string m_name;
	std::vector<GameObject*> m_objects;
};