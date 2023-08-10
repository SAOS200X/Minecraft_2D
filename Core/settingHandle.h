#pragma once
#include "inordered_map.h"


class settingHandle
{
public:
	friend class Core;
	friend class SettingState;

	static std::string title;
private:
	struct settings {
		inordered_map<std::string, std::variant<unsigned int, sf::Vector2u>> values;
		unsigned int current = 0;
	};

	static void loadSetting(const std::string filePath);

	static std::variant<unsigned int, sf::Vector2u>& getCurrentSetting(const std::string key);

	static inordered_map<std::string, std::unique_ptr<settings>> m_setting;

	static sf::RenderWindow* window;
};

