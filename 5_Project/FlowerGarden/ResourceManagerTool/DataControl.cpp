#include "pch.h"
#include "DataControl.h"
#include "Scene.h"
#include "MyFile.h"

#include "Global.h"

DataControl::DataControl()
{
	SetRelativePath(L"Resource");
}

DataControl::~DataControl()
{

}

void DataControl::AddSceneData(Scene* scene)
{
	//Scene* newScene = new Scene();

	m_scenes.push_back(scene);
}

void DataControl::DeleteSceneDataByIndex(int idx)
{
	m_scenes.erase(m_scenes.begin() + idx);
}

void DataControl::Clear()
{
	for (auto& s : m_scenes)
	{
		s->Clear();
		delete s;
		s = nullptr;
	}
	m_scenes.clear();
}

void DataControl::SetScenesRelativePath()
{
	for (auto& scene : m_scenes)
	{
		scene->SetRelativePath();
	}
}

void DataControl::SaveSceneDataForGameEngine(CString folderPath, Scene* currentScene)
{
	// ���� �̸� ����
	folderPath.Append(std::wstring(L"\\").c_str());
	folderPath.Append(currentScene->GetSceneName().c_str());
	folderPath.Append(std::wstring(L".txt").c_str());

	// ����
	std::wofstream ofs;
	ofs.open(folderPath);
	int fileCount = currentScene->GetFileCount();
	ofs << fileCount << std::endl;
	for (int fileIdx = 0; fileIdx < fileCount; fileIdx++)
	{
		ofs << currentScene->GetFileByIndex(fileIdx)->GetRelativePath() << std::endl;
	}
	ofs.close();
}

void DataControl::SaveAllSceneDataForGameEngine(const CString& path)
{
	// ������ ������ ���� 1���� ��� �����Ѵ�.
	for (int sceneIdx = 0; sceneIdx < m_scenes.size(); sceneIdx++)
	{
		Scene* scene = m_scenes[sceneIdx];

		CString folderPath = path;
		folderPath.Append(std::wstring(L"\\").c_str());
		folderPath.Append(scene->GetSceneName().c_str());
		folderPath.Append(std::wstring(L".txt").c_str());

		std::wofstream ofs;
		ofs.open(folderPath);
		int fileCount = scene->GetFileCount();
		ofs << fileCount << std::endl;
		for (int fileIdx = 0; fileIdx < fileCount; fileIdx++)
		{
			ofs << scene->GetFileByIndex(fileIdx)->GetRelativePath() << std::endl;
		}
		ofs.close();
	}
}

void DataControl::SaveDataForTool(const CString& path)
{

	std::wofstream ofs;
	ofs.open(path);
	ofs << g_relativePath << std::endl;
	// �� ������ ����
	ofs << m_scenes.size() << std::endl;
	for (int sceneIdx = 0; sceneIdx < m_scenes.size(); sceneIdx++)
	{
		// ���� �̸�
		ofs << m_scenes[sceneIdx]->GetSceneName() << std::endl;
		// ���� ��
		int fileCount = m_scenes[sceneIdx]->GetFileCount();
		ofs << fileCount << std::endl;
		for (int fileIdx = 0; fileIdx < fileCount; fileIdx++)
		{
			// ������ ������� �� ������ ������ �� ��
// 			CFileFind finder;
// 			if (finder.FindFile(m_scenes[sceneIdx]->GetFileByIndex(fileIdx)->GetPath()) == false)
// 			{
// 				finder.Close();
// 				continue;
// 			}
// 			finder.Close();

			// ���� �̸� ����
			ofs << m_scenes[sceneIdx]->GetFileByIndex(fileIdx)->GetName() << std::endl;
			// ���� ���� ��� ����
			ofs << std::wstring(CT2W(m_scenes[sceneIdx]->GetFileByIndex(fileIdx)->GetPath())) << std::endl;
		}
	}
	ofs.close();
}

void DataControl::LoadDataForTool(const CString& path)
{
	
	int sceneCount = 0;
	std::wifstream ifs;
	ifs.open(path);

	// ��� ��θ� �ε�
	ifs >> g_relativePath;

	// ���� ����
	ifs >> sceneCount;
	for (int i = 0; i < sceneCount; i++)
	{
		
		std::wstring sceneName;
		int fileCount = 0;

		Scene* newScene = new Scene();

		// ���� �̸��� ���� ����
		ifs >> sceneName;
		ifs >> fileCount;

		newScene->SetSceneName(sceneName);
		for (int j = 0; j < fileCount; j++)
		{
			std::wstring filePath, fileName;
			// ���� ���
			ifs >> fileName >> filePath;
			CString filePathToCString = _T("");
			filePathToCString.Append(filePath.c_str());
			// ������ ������� �� ������ �ε带 �� ��
			{
				CFileFind finder;
				if (finder.FindFile(filePathToCString) == false)
				{
					finder.Close();
					continue;
				}
				finder.Close();
			}
			MyFile* myFile = new MyFile();
			myFile->SetName(fileName);
			myFile->SetPath(filePathToCString);

			// ���� ���� �߰�
			newScene->AddFile(myFile);
		}

		// ���� �� �߰�
		AddSceneData(newScene);
	}
}
