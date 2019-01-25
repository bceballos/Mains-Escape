#include <iostream>
#include <chrono>


#include "hTimer.h"

void Timer::setStart() {
	strt = std::chrono::system_clock::now();
}

float Timer::getTime() {
	auto end = std::chrono::system_clock::now();
	std::chrono::duration<float, std::milli> span = end - strt;
	//strt = std::chrono::system_clock::now();

	return span.count();
}

std::string Timer::returnTime() {
	time_t t = time(0);
	std::tm* currentTime = localtime(&t);

	return std::to_string(currentTime->tm_hour) + ":" + std::to_string(currentTime->tm_min) + ":" + std::to_string(currentTime->tm_sec);
}

std::string Timer::returnDate() {
	time_t t = time(0);
	std::tm* currentTime = localtime(&t);

	return std::to_string(currentTime->tm_mday) + ":" + std::to_string(currentTime->tm_mon) + ":" + std::to_string(currentTime->tm_year);
}