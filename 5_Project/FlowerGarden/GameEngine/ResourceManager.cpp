#include "ResourceManager.h"
#include <iostream>
#include <fstream>

#include <algorithm>

#include "../DirectY/DirectY.h"

#include "SoundManager.h"

/// <summary>
/// ���� �� �߶� �����Ѵ�.
/// </summary>
/// <param name="path">���� path</param>
/// <returns>���� �̸�</returns>
std::string GetFileName(std::string path)
{
	int lastPoint = path.find_last_of(".");
	int lastSlash = path.find_last_of("/");

	return path.substr(lastSlash + 1, lastPoint - lastSlash - 1);
}

void ResourceManager::Init()
{

}

/// <summary>
/// �ؽ�Ʈ ���Ͽ��� Path�� �о� ���ҽ��� �ҷ��´�. 
/// �� ������ �� ���� �ؾ� �Ѵ�.
/// 
/// SceneManager���� Scene�� Load�� �� �� �ִ� �� ���� �� ����.
/// </summary>
/// <param name="sceneName"></param>
/// <param name="directY"></param>
void ResourceManager::LoadResource(std::string sceneName, DirectY& directY)
{
	std::ifstream resourceTextFile("Resource/Text/Scene/" + sceneName + ".txt");
	std::string path;
	if (resourceTextFile.is_open())
	{
		// txt ���� �� �� �� �б�
		while (std::getline(resourceTextFile, path))
		{
			// �޾ƿ� string��(Line��) ������ ��� ���α׷� ����
			if (path._Equal(""))
			{
				break;
			}

			// ���� Ȯ���� ����
			std::string fileExtension = path.substr(path.length() - 3);
			if (fileExtension._Equal("png"))
			{
				AddImage(path, directY);
			}
			if (fileExtension._Equal("jpg"))
			{
				AddImage(path, directY);
			}
			if (fileExtension._Equal("mp3"))
			{
				AddSound(path);
			}
			if (fileExtension._Equal("wav"))
			{
				AddSound(path);
			}
		}
		resourceTextFile.close();
	}
	else
	{
		std::cout << "���� ���� ����...";
	}
	return;
}

void ResourceManager::Release()
{
	for (auto& image : m_images)
	{
		if (image.second != nullptr)
		{
			image.second->Release();
		}
	}
	m_images.clear();

	for (auto& sound : m_sounds)
	{
		if (sound.second != nullptr)
		{
			sound.second->release();
		}
	}
	m_sounds.clear();
}

void ResourceManager::AddImage(std::string path, DirectY& directY)
{
	// string -> wstring ��ȯ
	std::wstring pathWStr;
	pathWStr.assign(path.begin(), path.end());

	// �׷��Ƚ� ������ �̿��ؼ� Bitmap �ҷ�����
	ID2D1Bitmap* loadedImage = directY.LoadImageFile(pathWStr.c_str());

	// Ȯ���ڿ� ��θ� ������ ���� �̸��� �����´�. 
	std::string fileName = GetFileName(path);

	m_images.insert({ fileName, loadedImage });
}

void ResourceManager::AddSound(std::string path)
{
	m_sounds.insert({ GetFileName(path), SoundManager::GetInstance().LoadSound(path) });
}