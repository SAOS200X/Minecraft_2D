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
}

void Core::run()
{
	while (window->isOpen())
	{
		update();
		render();
	}
}

void Core::init()
{
	srand(static_cast<unsigned int>(time(0)));

	initDefaultWindow();

	//loadSetting();

	initWindow();

	clock.restart();
}

void Core::initDefaultWindow()
{
	DefaultWindow = new sf::RenderWindow(sf::VideoMode(800, 600),
		"Default", sf::Style::Close | sf::Style::Titlebar);
	DefaultWindow->setFramerateLimit(30);
}

void Core::initWindow()
{
	logMSG("this is text 1!");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
	logMSG("this is text 2!");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
	logMSG("this is text 3!");

	std::ifstream INFILE("window.init");
	if (INFILE.is_open())
	{
		sf::Vector2u window_size;
		float fps_limit;
		std::string title;


		INFILE >> window_size.x;
		INFILE.ignore();
		INFILE >> window_size.y;
		INFILE >> fps_limit;
		INFILE >> title;


		window = new sf::RenderWindow(sf::VideoMode(window_size.x, window_size.y),
			title, sf::Style::Close | sf::Style::Titlebar);

		delete DefaultWindow;
		DefaultWindow = nullptr;

	}
	else
	{
		logMSG("couldn't open file!");

		window = DefaultWindow;
	}
	INFILE.close();
}

void Core::loadSetting()
{
	
}

void Core::updateInput()
{
	dt = clock.restart().asMilliseconds();

	while (window->pollEvent(ev))
	{
		if (ev.type == sf::Event::Closed)
			window->close();
		else if (ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::Escape)
			window->close();
	}

}


void Core::update()
{
	updateInput();
}

void Core::render()
{
	window->clear();

	window->display();
}
