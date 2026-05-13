#include "Timer.h"

void Timer::Init(float targetDeltaTime)
{
	// target delta time is in fractions of a second.
	// SDL_GetTicks returns the number of milliseconds
	// need to convert fractions of second to number of milliseconds
	MillisecondsPerFrame = (int)(targetDeltaTime * 1000.0f);
	TimeSinceStart = 0;
}

void Timer::Start()
{
	TimeSinceStart = SDL_GetTicks();
}

void Timer::AccumulateTicks()
{
	while (GetTicks() < MillisecondsPerFrame)
	{

	}
}

unsigned int Timer::GetTicks() const
{
	return SDL_GetTicks() - TimeSinceStart;
}

float Timer::GetDeltaTime() const
{
	return GetTicks() / 1000.0f;
}
