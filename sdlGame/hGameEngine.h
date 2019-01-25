#ifndef gameEngine
#define gameEngine

#include <vector>
#include <SDL_mixer.h>
#include "hGameObject.h"
#include "hDoor.h"
#include "hPlayer.h"
#include "hEnemy.h"
#include "hFont.h"
#include "hTimer.h"
#include "hLog.h"
#include "hKeys.h"

#define FONT_PATH "Assets/Font/jmhtypewriter.ttf"
// #define MUSIC_PATH
// #define GLITCH_PATH
// LEARN HOW TO AUDIO FROM THIS https://gist.github.com/armornick/3447121#file-playwav-c-L60

class Game {
	public:

		Logging* log = NULL;

		bool init();

		void build();
		void runMenu();
		void run();
		void update();
		void lateUpdate();
		void render();
		void input();
		void clean();
		void menuInput();
		void menuUpdate();
		void menuRender();
		void setPausedTexture();
		void selectItemFunctionality();
		void endScoreScreen();
		void endScoreUpdate();
		void endScoreRender();
		void initAudio();


		void initFonts();

		void windowResize();

		//Fix later
		void readFile();

		enum GameState { MENU, PLAY, SETTINGS, HOWTO, SCORE, END, PAUSE };

		GameState state = MENU;
		bool paused = false;
		bool fullScreen = false;

		std::vector<int> worldInts;
		std::vector<GameObject*> worldTiles;
		std::vector<Door*> doorTiles;
		std::vector<Enemy*> enemyObjs;
		std::vector<Font*> menuItems;
		std::vector<Font*> difficultyItems;
		std::vector<Font*> settingsItems;
		std::vector<Font*> howtoItems;
		std::vector<Font*> scoreItems;
		std::vector<Font*> pauseMenuItems;

		const int blockSize = 20;
		static const int windowRows = 40;
		static const int windowColumns = 30;
		static const int windowHeight = 660;
		static const int windowWidth = 800;

		const int hardHealth = 1;
		const int normalHealth = 2;
		const int easyHealth = 3;

		int scaleTextHitBoxX;
		int scaleTextHitBoxY;

		Player player;

		int chosenHealth;
		int previousResizeW = windowWidth;
		int previousResizeH = windowHeight;

		float lastDoorChange = 0.0f;
		float timeLimit = 0.0f;

		int gameDuration = 0;

		int timer = 60000;

		SDL_Surface* pausedSurface;
		SDL_Texture* pausedTexture;
		SDL_Surface* menuSurface;
		SDL_Texture* menuTexture;
		SDL_Surface* howtoSurface;
		SDL_Texture* howtoTexture;
		SDL_Rect pausedRect;
		SDL_Rect menuRect;

		Keys keys;

		SDL_Joystick* gamePad = NULL;

		bool gameRunning;

		Mix_Music* bgMusic = NULL;
		Mix_Chunk* menuHover = NULL;
	private:
		int x, y;
		Font* health = NULL;
		Font* time = NULL;
		Font* score = NULL;
		Font* play = NULL;
		Font* settings = NULL;
		Font* howToPlay = NULL;
		Font* easyText = NULL;
		Font* normalText = NULL;
		Font* hardText = NULL;
		Font* audioVolume = NULL;
		Font* audioVolumeInt = NULL;
		Font* audioIncreaseVol = NULL;
		Font* audioDecreaseVol = NULL;
		Font* muteAudio = NULL;
		Font* muteSFX = NULL;
		Font* howToPlayText = NULL;
		Font* backButton = NULL;
		Font* muteAudioText = NULL;
		Font* muteSFXText = NULL;
		Font* quit = NULL;
		Font* returnToMenu = NULL;
		Font* endScore = NULL;
		Font* keyboardInputs = NULL;
		Font* controllerInputs = NULL;
		Font* pauseAudioVolume;
		Font* pauseAudioVolumeInt;
		Font* pauseAudioIncreaseVol;
		Font* pauseAudioDecreaseVol;
		Font* pauseMuteAudio;
		Font* pauseMuteAudioText;
		Font* pauseMuteSFX;
		Font* pauseMuteSFXText;

		void handleMouseClicks(SDL_MouseButtonEvent &button);
		int volume = 100;
		int interpVol = 255;
		bool audioToggle = false;
		bool sfxToggle = false;
		bool menuRunning;
		bool isRunning;
		SDL_Window *window;
		SDL_Renderer *renderer;
		int endScoreIndex = 0;
		int menuIndex = 0;
		int difficultyIndex = 0;
		int settingsIndex = 0;
		int howtoIndex = 0;
		int selectedMenuIndex = NULL;
		int selectedScoreIndex = NULL;
		int pauseIndex = NULL;
		bool fileHasBeenRead = false;

};

#endif // !GameEngine
