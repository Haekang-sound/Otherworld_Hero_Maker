#include "pch.h"
#include "Scene.h"
#include "MyFile.h"

#include "Global.h"
Scene::Scene()
{

}

Scene::~Scene()
{

}

void Scene::Clear()
{
	for (auto& f : m_files)
	{
		delete f;
		f = nullptr;
	}
	m_files.clear();
}

void Scene::AddFile(MyFile* file)
{
	m_files.push_back(file);
	m_fileCount++;
}

void Scene::DeleteFileByIndex(int idx)
{
	if (idx < 0 || m_fileCount == 0)
		return;

	m_files.erase(m_files.begin() + idx);
	m_fileCount--;
}

void Scene::SetRelativePath()
{
	CString relativePath;
	//relativePath.Append(g_relativePath.c_str())
	for (MyFile* file : m_files)
	{
		file->SetPath(file->GetPath());
		//file->SetRelativePath(g_relativePath.c_str());
	}
}
