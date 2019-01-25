#ifndef gameSoloTimer
#define gameSoloTimer

#include <chrono>
#include <string>

class Timer {

public:

	std::chrono::system_clock::time_point strt;

	void setStart();
	float getTime();
	std::string returnTime();
	std::string returnDate();

private:

};

#endif
