#pragma once

#include <SDL3\SDL_timer.h>

class Timer
{
public:

	void Init(float targetDeltaTime);

	void Start();
	void AccumulateTicks();

	unsigned int GetTicks() const;
	float GetDeltaTime() const;

private:

	unsigned int TimeSinceStart;

	unsigned int MillisecondsPerFrame;
};

