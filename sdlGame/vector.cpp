#include "SDL.h"
#include <iostream>
#include <stdlib.h>
#include <cmath>
#include "hVector.h"

void Vector::calculateVector(int angle) {
	normX = std::sin(angle * (M_PI / 180));
	normY = std::cos(angle * (M_PI / 180));
}