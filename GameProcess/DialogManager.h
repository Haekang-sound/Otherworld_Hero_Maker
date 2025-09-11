#pragma once
#include "ElementBase.h"
#include "Vector2.h"
#include <unordered_map>
#include <vector>
#include <string>
#include <functional>

namespace Graphics { struct Sprite; }
class AudioSource;

class DialogManager : public ElementBase
{
public:
	// -------------------------------------------
	DialogManager(int left, int top, int right, int bottom, int ID, Graphics::Sprite* dialogImage, Graphics::Sprite* dialogGotImage);
	virtual ~DialogManager();

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
	// -------------------------------------------

	void ReadDialogCSV(std::string path);
	void SetStartGame(std::function<void(void)> val) { StartGame = val; }

	void SetTextOffset(MathEngine::Vector2 offset) { m_textOffset = offset; }

	void AddSprite(std::string name, Graphics::Sprite* sprite);

	void SetCurrentIndex(int val) { m_currentIndex = val; }

	void SetAudioSource(AudioSource* audioSource) { m_audiosource = audioSource; }

private:
	// Rect
	// ���� ������ 0, 0, UI �ִ� �������� ����
	int m_left;
	int m_top;
	int m_right;
	int m_bottom;

	int m_ID;
	int m_currentIndex;

	AudioSource* m_audiosource;

	// ���ʿ� ĳ����, �����ʿ� ����? (�������� ���۽�) 
	/// �޸� �����ؾ���
	std::unordered_map<std::string, Graphics::Sprite*> m_sprites;
	
	// �Ʒ��ʿ� ���̾�α� â (�������� ���۽�)
	Graphics::Sprite* m_dialogImage;
	Graphics::Sprite* m_dialogGodImage;

	MathEngine::Vector2 m_dialogPosition;

	std::vector<std::string> m_speaker;
	std::vector<std::string> m_dialogText;
	MathEngine::Vector2 m_textOffset;

	std::vector<std::string> m_imageIndexL;
	std::vector<std::string> m_imageIndexM;
	std::vector<std::string> m_imageIndexR;

	std::vector<std::string> m_BGI;
	std::vector<std::string> m_Fade;
	// �ٵ� ���̾� �α� â�� �׳� �߾��� �� �� ���� (�������� �����)
	// �������� ����� ������ �� ���� �������� �ƴϰ� �׳� �̹���
	// ������ ��� ����ؾ� �ɵ�
	
	// ���̾�α� CSV Reader�� �ʿ��� - �¿� ������ ������ ���ų� ��Ź

	std::function<void(void)> StartGame;
};