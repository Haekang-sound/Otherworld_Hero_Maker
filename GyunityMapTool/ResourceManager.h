#pragma once
class ResourceManager
{
public:
	static ResourceManager& GetInstance()
	{
		static ResourceManager instance;
		return instance;
	}
private:
	//ResourceManager();

public:
	std::wstring GetImagePath(std::wstring path);
};

