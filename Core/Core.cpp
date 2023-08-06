#include "pch.h"
#include "Core.h"

Core::Core()
{
	init();
}

Core::~Core()
{
	if (DefaultWindow)
		delete DefaultWindow;
	if (window != DefaultWindow)
		delete window;

	while (!states.empty())
	{
		delete states.top();
		states.pop();
	}

	delete font;
}

void Core::run()
{
	while (window->isOpen() && !states.empty())
	{
		update();
		render();
	}
}

////////////////////////////////////////////////////// INIT ////////////////////////////////////////////////////////

void Core::init()
{
	initDefault();
	initFont("resource/font.ttf");
	initDefaultWindow();
	initWindow("resource/init/window.init");

	initSystem();

	initState();
}

void Core::initDefault()
{
	DefaultWindow = nullptr;
	window = nullptr;
	view = nullptr;
	dt = 0;
	font = nullptr;
	clock.restart();
}

void Core::initFont(std::string filePath)
{
	this->font = new sf::Font;
	if (!font->loadFromFile(filePath))
		logWARNING("couldn't open file: " + filePath);

	text.setFont(*font);
}

void Core::initDefaultWindow()
{
	DefaultWindow = new sf::RenderWindow(sf::VideoMode(800, 600),
		"Default", sf::Style::Close | sf::Style::Titlebar);
	DefaultWindow->setFramerateLimit(30);
}

void Core::initWindow(std::string filePath)
{
	std::ifstream INFILE(filePath);
	if (INFILE.is_open())
	{
		sf::Vector2u window_size;
		float fps_limit;
		std::string title;


		INFILE >> window_size.x;
		INFILE.ignore();
		INFILE >> window_size.y;
		INFILE >> fps_limit;
		INFILE.ignore();
		std::getline(INFILE, title);


		window = new sf::RenderWindow(sf::VideoMode(window_size.x, window_size.y),
			title, sf::Style::Close | sf::Style::Titlebar);

		delete DefaultWindow;
		DefaultWindow = nullptr;

	}
	else
	{
		logWARNING("couldn't open file: " + filePath);
		window = DefaultWindow;
	}
	INFILE.close();
}

void Core::initState()
{
	states.push(new MainMenuState());

	State::states = &this->states;
}

void Core::initSystem()
{
	s_System::window = this->window;
	s_System::font = this->font;
	s_System::dt = &this->dt;
}


//////////////////////////////////////////////////////// UPDATE ////////////////////////////////////////////////////////

void Core::update()
{
	updateInput();

	if (!states.empty())
		states.top()->update();

	updateTextDebug();
}

void Core::updateInput()
{
	dt = clock.restart().asMilliseconds();

	while (window->pollEvent(ev))
	{
		if (ev.type == sf::Event::Closed)
			window->close();
		else if (ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::Escape)
			State::states->pop();
	}

	s_System::mousePosWindow = sf::Mouse::getPosition(*window);

}

void Core::updateTextDebug()
{
	auto m = s_System::getMousePosWindow();
	std::stringstream ss;
	ss << m.x << " " << m.y;
	text.setCharacterSize(16);
	text.setOutlineThickness(2.f);
	text.setString(ss.str());
	text.setPosition(m.x + 10.f, m.y + 10.f);
}


void Core::render()
{
	window->clear();

	if (!states.empty())
		states.top()->render(window);
	window->draw(text);

	window->display();
}

