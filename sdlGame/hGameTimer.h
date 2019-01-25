#ifndef gameTimer
#define gameTimer

class GameTimer
{
	public:
		GameTimer();
		~GameTimer();

		void resetTicksTimer();
		void gameLoopDelay();

		int getTicks();

		const int fps = 60;

	private:
		const float deltaTime = 1000 / fps;

		int startTicks;
		int speed = fps / 60;
};


#endif // !HTIMER
