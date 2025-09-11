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
	// 파일 이름 지정
	folderPath.Append(std::wstring(L"\\").c_str());
	folderPath.Append(currentScene->GetSceneName().c_str());
	folderPath.Append(std::wstring(L".txt").c_str());

	// 저장
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
	// 파일을 씬마다 따로 1개씩 모두 저장한다.
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
	// 씬 사이즈 저장
	ofs << m_scenes.size() << std::endl;
	for (int sceneIdx = 0; sceneIdx < m_scenes.size(); sceneIdx++)
	{
		// 씬의 이름
		ofs << m_scenes[sceneIdx]->GetSceneName() << std::endl;
		// 파일 수
		int fileCount = m_scenes[sceneIdx]->GetFileCount();
		ofs << fileCount << std::endl;
		for (int fileIdx = 0; fileIdx < fileCount; fileIdx++)
		{
			// 파일이 없을경우 그 파일은 저장을 안 함
// 			CFileFind finder;
// 			if (finder.FindFile(m_scenes[sceneIdx]->GetFileByIndex(fileIdx)->GetPath()) == false)
// 			{
// 				finder.Close();
// 				continue;
// 			}
// 			finder.Close();

			// 파일 이름 저장
			ofs << m_scenes[sceneIdx]->GetFileByIndex(fileIdx)->GetName() << std::endl;
			// 파일 절대 경로 저장
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

	// 상대 경로를 로드
	ifs >> g_relativePath;

	// 씬의 개수
	ifs >> sceneCount;
	for (int i = 0; i < sceneCount; i++)
	{
		
		std::wstring sceneName;
		int fileCount = 0;

		Scene* newScene = new Scene();

		// 씬의 이름과 파일 개수
		ifs >> sceneName;
		ifs >> fileCount;

		newScene->SetSceneName(sceneName);
		for (int j = 0; j < fileCount; j++)
		{
			std::wstring filePath, fileName;
			// 파일 경로
			ifs >> fileName >> filePath;
			CString filePathToCString = _T("");
			filePathToCString.Append(filePath.c_str());
			// 파일이 없을경우 그 파일은 로드를 안 함
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

			// 씬에 파일 추가
			newScene->AddFile(myFile);
		}

		// 최종 씬 추가
		AddSceneData(newScene);
	}
}
