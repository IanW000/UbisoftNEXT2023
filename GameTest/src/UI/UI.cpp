#include "stdafx.h"
#include "UI.h"

#include <gameManager/gameManager.h>
#include <string>

UI::UI() : currentScreen(Screens::MAINMENU), failSFXPlayedOnce(false),winSFXPlayedOnce(false),m_gameManager(nullptr), bombsUp(1), speedUp(1), fireUp(1)
{
}

void UI::Init(GameManager& gameManager)
{
	m_gameManager = &gameManager;
	m_player = gameManager.m_player;
	App::PlaySound(".\\res\\Sound\\mainMenuBGM.wav", true);

}

void UI::Update(float deltaTime)
{
	switch (currentScreen) {

	case Screens::MAINMENU:
		StartButton.Update(deltaTime);
		ControlsButton.Update(deltaTime);
		ExitButton.Update(deltaTime);

		if (StartButton.gameScreen) {
			App::StopSound(".\\res\\Sound\\mainMenuBGM.wav");
			App::PlaySound(".\\res\\Sound\\inGameBGM.wav", true);
			setCurrentScreen(Screens::GAME);
			m_gameManager->generateMap();
			StartButton.gameScreen = false;
		}

		if (ControlsButton.controlsScreen) {
			setCurrentScreen(Screens::CONTROLS);
			ControlsButton.controlsScreen = false;
		}
		break;

	case Screens::CONTROLS:
		BackButton.Update(deltaTime);

		if (BackButton.backToMainScreen) {
			setCurrentScreen(Screens::MAINMENU);
			BackButton.backToMainScreen = false;
		}
		break;

	case Screens::GAME:
		PauseButton.Update(deltaTime);
		playerHP.Update(m_gameManager->m_player.getHp());
		enemyHP.Update(m_gameManager->m_enemy.getHp());

		if (PauseButton.pause) {
			setCurrentScreen(Screens::PAUSE);
			PauseButton.pause = false;
		}
		break;

	case Screens::PAUSE:
		BackButtonInGame.Update(deltaTime);
		ResumeButton.Update(deltaTime);

		if (BackButtonInGame.backToMainScreen) {
			m_gameManager->resetMap();
			bombsUp = 1;
			speedUp = 1;
			fireUp = 1;
			App::StopSound(".\\res\\Sound\\inGameBGM.wav");
			App::PlaySound(".\\res\\Sound\\mainMenuBGM.wav", true);
			setCurrentScreen(Screens::MAINMENU);
			BackButtonInGame.backToMainScreen = false;
		}

		if (ResumeButton.resume) {
			setCurrentScreen(Screens::GAME);
			ResumeButton.resume = false;
		}
		break;

	case Screens::DEAD:

		BackButtonInGame.Update(deltaTime);

		if (!failSFXPlayedOnce) {
			App::StopSound(".\\res\\Sound\\inGameBGM.wav");
			App::PlaySound(".\\res\\Sound\\fail.wav");
			failSFXPlayedOnce = true;
		}

		if (BackButtonInGame.backToMainScreen) {
			m_gameManager->resetMap();
			bombsUp = 1;
			speedUp = 1;
			fireUp = 1;
			App::PlaySound(".\\res\\Sound\\mainMenuBGM.wav", true);
			setCurrentScreen(Screens::MAINMENU);
			BackButtonInGame.backToMainScreen = false;
			failSFXPlayedOnce = false;
		}
		break;

	case Screens::WIN:

		BackButtonInGame.Update(deltaTime);

		if (!failSFXPlayedOnce) {
			App::StopSound(".\\res\\Sound\\inGameBGM.wav");
			App::PlaySound(".\\res\\Sound\\fail.wav");
			failSFXPlayedOnce = true;
		}

		if (BackButtonInGame.backToMainScreen) {
			m_gameManager->resetMap();
			bombsUp = 1;
			speedUp = 1;
			fireUp = 1;
			App::PlaySound(".\\res\\Sound\\mainMenuBGM.wav", true);
			setCurrentScreen(Screens::MAINMENU);
			BackButtonInGame.backToMainScreen = false;
			failSFXPlayedOnce = false;
		}
		break;
	}
}

void UI::Render()
{

	switch (currentScreen) {

	case Screens::MAINMENU:

		UI::CenteringPrint(0.5f * APP_INIT_WINDOW_WIDTH - 40, 0.5f * APP_INIT_WINDOW_HEIGHT + 120, "BOMB! BOMB! BOMB!", 1.0f, .25f, .5f, GLUT_BITMAP_TIMES_ROMAN_24, true);
		UI::CenteringPrint(0.5f * APP_INIT_WINDOW_WIDTH - 42, 0.5f * APP_INIT_WINDOW_HEIGHT + 122, "BOMB! BOMB! BOMB!", 1.0f, 1.0f, 0.0f, GLUT_BITMAP_TIMES_ROMAN_24, true);

		StartButton.CreateButton((GLfloat)-0.1, (GLfloat)0.1, (GLfloat)0.1, (GLfloat)0.2, 0.5f * APP_INIT_WINDOW_WIDTH - 20, 0.5f * APP_INIT_WINDOW_HEIGHT + 52, "Start", Colors::Pink, ButtonType::START);
		ControlsButton.CreateButton((GLfloat)-0.1, (GLfloat)-0.05, (GLfloat)0.1, (GLfloat)0.05, 0.5f * APP_INIT_WINDOW_WIDTH - 34, 0.5f * APP_INIT_WINDOW_HEIGHT - 5, "Controls", Colors::Pink, ButtonType::CONTROLS);
		ExitButton.CreateButton((GLfloat)-0.1, (GLfloat)-0.2, (GLfloat)0.1, (GLfloat)-0.1, 0.5f * APP_INIT_WINDOW_WIDTH - 15, 0.5f * APP_INIT_WINDOW_HEIGHT - 65, "Exit", Colors::Pink, ButtonType::EXIT);

		StartButton.Render();
		ControlsButton.Render();
		ExitButton.Render();
		break;

	case Screens::CONTROLS:

		UI::CenteringPrint(0.5f * APP_INIT_WINDOW_WIDTH - 40, 0.5f * APP_INIT_WINDOW_HEIGHT + 120, "BOMB! BOMB! BOMB!", 1.0f, .25f, .5f, GLUT_BITMAP_TIMES_ROMAN_24, true);
		UI::CenteringPrint(0.5f * APP_INIT_WINDOW_WIDTH - 42, 0.5f * APP_INIT_WINDOW_HEIGHT + 122, "BOMB! BOMB! BOMB!", 1.0f, 1.0f, 0.0f, GLUT_BITMAP_TIMES_ROMAN_24, true);

		BackButton.CreateButton((GLfloat)0.8, (GLfloat)0.8, (GLfloat)0.9, (GLfloat)0.9, 0.5f * APP_INIT_WINDOW_WIDTH + 430, 0.5f * APP_INIT_WINDOW_HEIGHT + 320, "X", Colors::Pink, ButtonType::BACK);

		UI::CenteringPrint(0.5f * APP_INIT_WINDOW_WIDTH, 0.5f * APP_INIT_WINDOW_HEIGHT + 25, "W - Move Forward", (float)0 / 255, (float)191 / 255, (float)255 / 255, GLUT_BITMAP_HELVETICA_18, true);
		UI::CenteringPrint(0.5f * APP_INIT_WINDOW_WIDTH, 0.5f * APP_INIT_WINDOW_HEIGHT, "A - Move Left", (float)0 / 255, (float)191 / 255, (float)255 / 255, GLUT_BITMAP_HELVETICA_18, true);
		UI::CenteringPrint(0.5f * APP_INIT_WINDOW_WIDTH - 5, 0.5f * APP_INIT_WINDOW_HEIGHT - 25, "S - Move Back", (float)0 / 255, (float)191 / 255, (float)255 / 255, GLUT_BITMAP_HELVETICA_18, true);
		UI::CenteringPrint(0.5f * APP_INIT_WINDOW_WIDTH + 5, 0.5f * APP_INIT_WINDOW_HEIGHT - 50, "D - Move Right", (float)0 / 255, (float)191 / 255, (float)255 / 255, GLUT_BITMAP_HELVETICA_18, true);
		UI::CenteringPrint(0.5f * APP_INIT_WINDOW_WIDTH - 7.5, 0.5f * APP_INIT_WINDOW_HEIGHT - 75, "J - BOMB!!!", (float)0 / 255, (float)191 / 255, (float)255 / 255, GLUT_BITMAP_HELVETICA_18, true);

		BackButton.Render();
		break;

	case Screens::GAME:

		playerHP.CreateHPBar((GLfloat)-0.98, (GLfloat)0.93, (GLfloat)0.02, (GLfloat)0.98, 745, Colors::White, Colors::Green, Colors::Yellow);
		UI::CenteringPrint(0.5f * APP_INIT_WINDOW_WIDTH - 250, 0.5f * APP_INIT_WINDOW_HEIGHT - 370, std::to_string(bombsUp).c_str(), (float)0 / 255, (float)191 / 255, (float)255 / 255, GLUT_BITMAP_HELVETICA_18, true);
		UI::CenteringPrint(0.5f * APP_INIT_WINDOW_WIDTH +50, 0.5f * APP_INIT_WINDOW_HEIGHT - 370, std::to_string(fireUp).c_str(), (float)0 / 255, (float)191 / 255, (float)255 / 255, GLUT_BITMAP_HELVETICA_18, true);
		UI::CenteringPrint(0.5f * APP_INIT_WINDOW_WIDTH + 350, 0.5f * APP_INIT_WINDOW_HEIGHT - 370, std::to_string(speedUp).c_str(), (float)0 / 255, (float)191 / 255, (float)255 / 255, GLUT_BITMAP_HELVETICA_18, true);

		App::Print(20, 745, "P1", (float)255 / 255, (float)0 / 255, (float)0 / 255, GLUT_BITMAP_HELVETICA_18);


		enemyHP.CreateHPBar((GLfloat)-0.98, (GLfloat)-0.85, (GLfloat)0.02, (GLfloat)-0.80,60, Colors::White, Colors::Green, Colors::Yellow);
		UI::CenteringPrint(0.5f * APP_INIT_WINDOW_WIDTH - 300, 0.5f * APP_INIT_WINDOW_HEIGHT - 370, "Bombs:", (float)0 / 255, (float)191 / 255, (float)255 / 255, GLUT_BITMAP_HELVETICA_18, true);
		UI::CenteringPrint(0.5f * APP_INIT_WINDOW_WIDTH, 0.5f * APP_INIT_WINDOW_HEIGHT - 370, "Fire:", (float)0 / 255, (float)191 / 255, (float)255 / 255, GLUT_BITMAP_HELVETICA_18, true);
		UI::CenteringPrint(0.5f * APP_INIT_WINDOW_WIDTH + 300, 0.5f * APP_INIT_WINDOW_HEIGHT - 370, "Speed:", (float)0 / 255, (float)191 / 255, (float)255 / 255, GLUT_BITMAP_HELVETICA_18, true);
		PauseButton.CreateButton((GLfloat)0.88, (GLfloat)0.88, (GLfloat)0.98, (GLfloat)0.98, 0.5f * APP_INIT_WINDOW_WIDTH + 470, 0.5f * APP_INIT_WINDOW_HEIGHT + 350, "| |", Colors::Pink, ButtonType::PAUSE);


		App::Print(20, 60, "P2", (float)255 / 255, (float)0 / 255, (float)0 / 255, GLUT_BITMAP_HELVETICA_18);

		PauseButton.Render();
		break;

	case Screens::PAUSE:
		ResumeButton.CreateButton((GLfloat)0.7, (GLfloat)0.7, (GLfloat)0.8, (GLfloat)0.8, 0.5f * APP_INIT_WINDOW_WIDTH + 375, 0.5f * APP_INIT_WINDOW_HEIGHT + 282, " > ", Colors::Pink, ButtonType::RESUME);
		BackButtonInGame.CreateButton((GLfloat)-0.2, (GLfloat)0.25, (GLfloat)0.2, (GLfloat)0.35, 0.5f * APP_INIT_WINDOW_WIDTH - 80, 0.5f * APP_INIT_WINDOW_HEIGHT + 110, "Back to Main Menu", Colors::Pink, ButtonType::BACK);

		ResumeButton.Render();
		BackButtonInGame.Render();
		break;

	case Screens::DEAD:
		BackButtonInGame.CreateButton((GLfloat)-0.2, (GLfloat)0.25, (GLfloat)0.2, (GLfloat)0.35, 0.5f * APP_INIT_WINDOW_WIDTH - 80, 0.5f * APP_INIT_WINDOW_HEIGHT + 110, "Back to Main Menu", Colors::Pink, ButtonType::BACK);
		UI::CenteringPrint(0.5f * APP_INIT_WINDOW_WIDTH - 20, 0.5f * APP_INIT_WINDOW_HEIGHT + 200, "YOU LOSE!", 1.0f, .25f, .5f, GLUT_BITMAP_TIMES_ROMAN_24, true);
		BackButtonInGame.Render();
		break;

	case Screens::WIN:

		BackButtonInGame.CreateButton((GLfloat)-0.2, (GLfloat)0.25, (GLfloat)0.2, (GLfloat)0.35, 0.5f * APP_INIT_WINDOW_WIDTH - 80, 0.5f * APP_INIT_WINDOW_HEIGHT + 110, "Back to Main Menu", Colors::Pink, ButtonType::BACK);
		UI::CenteringPrint(0.5f * APP_INIT_WINDOW_WIDTH -20, 0.5f * APP_INIT_WINDOW_HEIGHT + 200, "YOU WIN!", 1.0f, .25f, .5f, GLUT_BITMAP_TIMES_ROMAN_24, true);
		BackButtonInGame.Render();
		break;
	}
}


void UI::setCurrentScreen(Screens screen)
{
	currentScreen = screen;
}

void UI::addBombsUp()
{
	bombsUp++;
}

void UI::addSpeedUp()
{
	speedUp++;
}

void UI::addFireUp()
{
	fireUp++;
}

Screens UI::getCurrentScreen() const
{
	return currentScreen;
}

void UI::CenteringPrint(float x, float y, const char* st, float r, float g, float b, void* font, bool center)
{
#if APP_USE_VIRTUAL_RES		
	APP_VIRTUAL_TO_NATIVE_COORDS(x, y);
#endif		
	// Set location to start printing text
	glColor3f(r, g, b); // Yellow

	int l = (int)strlen(st);
	const float fontSize = 0.02f;

	glRasterPos2f(x - l / 2 * fontSize, y);
	for (int i = 0; i < l; i++)
	{
		glutBitmapCharacter(font, st[i]); // Print a character on the screen
	}
}