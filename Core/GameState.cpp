#include "pch.h"
#include "GameState.h"
#include "systemHandle.h"


GameState::GameState(const std::string& filePath)
{
	m_p.filePath = filePath;
	loadSave(filePath);
	init();
}

GameState::~GameState()
{
}

void GameState::update()
{
	if (systemHandle::isKeyPressed(sf::Keyboard::Escape))
		pmenu->pause();

	if (!pmenu->isPause())
	{
		updateMoving();
		player->update();
		tileMap->update();
	}
	else
	{
		pmenu->update();
		if (pmenu->isSave())
			saveWorld();
	}
}

void GameState::render(sf::RenderTarget* target)
{
	target->setView(*systemHandle::getView());

	player->render(target);

	if (!pmenu->isPause())
		tileMap->render(target);

	target->setView(target->getDefaultView());

	if (pmenu->isPause())
		pmenu->render(target);
}


void GameState::init()
{
	player = std::make_unique<Player>();
	pmenu = std::make_unique<PauseMenu>();
}

void GameState::loadSave(const std::string& filePath)
{
	unsigned int seed = 0;
	std::stringstream ss;
	m_p.dateCount = time(0);

	std::ifstream INFILE(filePath);
	if (INFILE.is_open())
	{		
		INFILE >> m_p.dateCreate >> m_p.total;
		INFILE.ignore();
		std::getline(INFILE, m_p.seed);
		ss << INFILE.rdbuf();

		INFILE.close();
	}
	else
		logERROR("couldn't load save: " + filePath);

	srand(static_cast<unsigned>(std::hash<std::string>{}(m_p.seed)));
	tileMap = std::make_unique<TileMap>();
	if (!tileMap->loadSave(ss))
		logWARNING("couldn't load tilemap: " + filePath);
}

void GameState::updateMoving()
{
	float speed = systemHandle::getDeltaTime() * 0.001f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		systemHandle::getView()->move(-speed, 0.f);
		player->Move(-speed, 0.f);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		systemHandle::getView()->move(speed, 0.f);
		player->Move(speed, 0.f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		systemHandle::getView()->move(0.f, -speed);
		player->Move(0.f, -speed);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		systemHandle::getView()->move(0.f, speed);
		player->Move(0.f, speed);
	}
}

void GameState::saveWorld()
{

	std::ofstream OUTFILE(m_p.filePath);
	if (OUTFILE.is_open())
	{
		OUTFILE << m_p.dateCreate << " " << (time(0) - m_p.dateCount) + m_p.total << "\n";
		OUTFILE << m_p.seed;
		tileMap->saveTile(OUTFILE);

		OUTFILE.close();
	}

	this->states->pop();
	delete this;
}

