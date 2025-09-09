#pragma once

#include <unordered_map>
#include <string>

struct ID2D1Bitmap;
namespace FMOD { class Sound; } // SoundManager�� ����� FMOD�� Sound�� ����
class DirectY;

class ResourceManager
{
public:
	void Init();

	/// Text ���Ͽ��� Path�� �ҷ����� ���� �̸��� �о �ĺ��ڷ� ������ش�. 
	/// 
	/// ���ڷ� ���� ���� �ش��ϴ� Images, Sounds�� �ҷ��´�. �� �ʿ��� ���ҽ��� �ִٸ� �߰��Ѵ�.
	/// �̹��� Ȯ����: png, jpg�� ���� ��ü�� ������ ��� ��Ʈ�� ���� �� �ʿ��ϸ� �߰� ����
	/// ���� Ȯ����: mp3, wav, �� �ʿ��ϴٸ� �߰�
	void LoadResource(std::string sceneName, DirectY& directY);

	FMOD::Sound* GetSound(std::string soundName) { return m_sounds[soundName]; }
	ID2D1Bitmap* GetImage(std::string imageName) { return m_images[imageName]; }

	void Release();

private:
	void AddImage(std::string path, DirectY& directY);
	void AddSound(std::string path);

private:
	std::unordered_map<std::string, ID2D1Bitmap*> m_images;
	std::unordered_map<std::string, FMOD::Sound*> m_sounds;
};