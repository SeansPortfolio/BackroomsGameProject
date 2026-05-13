#pragma once

#include <iostream>
#include <vector>

#include <GL\GLEW.h>
#include <SDL3\SDL.h>

#include "Physics.h"

#include "Timer.h"
#include "Resources.h"
#include "Input.h"

#include "Scene.h"
#include "ColoredCubesScene.h"
#include "FallingShapesScene.h"

class Application
{
public:

	bool Init(int width, int height, const char* name);

	void Run();

	bool Quit();

private:

	bool InitWindow();

	bool InitRenderer();

	bool InitPhysics();

	void ToggleWireframe(bool toggle);

	void LoadScene();

	void ProcessEvents();

	void Update(float deltaTime);

	void Render();

	bool isRunning;

	int width;

	int height;

	float test;

	const char* name;

	Scene* gameScene;

	SDL_Window* window;

	SDL_GLContext context;

	Timer GameTimer;

	Input InputManager;

	std::unique_ptr<Physics> PhysicsSystem;
};

