#include "pch.h"
#include "settingHandle.h"


std::string settingHandle::title;

void settingHandle::loadSetting(const std::string filePath)
{
	std::ifstream INFILE(filePath);
	if (INFILE.is_open())
	{
		while (INFILE.good())
		{
			std::string str;
			size_t off = 0, mark = 0;
			std::getline(INFILE, str);

			m_setting.emplace_back(str.substr(off, mark = str.find('(', off)), new settings());

			str = str.substr(mark, str.rfind(')', str.size() - off) - mark);

			while ((off = str.find('{', off) + 1) != (str.npos + 1))
			{
				std::string token = str.substr(off, str.find('}', off) - off);

				mark = (token.find('[') + 1);
				std::string variable = token.substr(mark, token.rfind(']') - mark);

				std::string type = variable.substr(0, variable.find('('));

				mark = variable.find('(') + 1;
				std::stringstream ss(variable.substr(mark, variable.rfind(')') - mark));

				if (type == "u")
				{
					unsigned int a;
					ss >> a;
					m_setting.back().second()->values.emplace_back(token.substr(0, token.find('(')), a);

				}
				else if (type == "v2u")
				{
					sf::Vector2u a;
					ss >> a.x >> a.y;

					m_setting.back().second()->values.emplace_back(token.substr(0, token.find('(')), a);
				}
			}
		}
		INFILE.close();
	}
	else
	{
		logERROR("couldn't open file: " + filePath);
		settingHandle::window->close();
	}
}

std::variant<unsigned int, sf::Vector2u>& settingHandle::getCurrentSetting(const std::string key)
{

	return m_setting[key]->values.at(m_setting.at(key)->current);
}


inordered_map<std::string, std::unique_ptr<settingHandle::settings>> settingHandle::m_setting;

sf::RenderWindow* settingHandle::window = nullptr;
