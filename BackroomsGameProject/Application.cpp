#include "Application.h"

bool Application::Init(int width, int height, const char* name)
{
	isRunning = false;

	this->width = width;
	this->height = height;
	this->name = name;

	if (!InitWindow())
	{
		return false;
	}

	if (!InitRenderer())
	{
		return false;
	}

	LoadScene();

	isRunning = true;
	return true;
}

bool Application::InitWindow()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("Failed to init SDL. Error: %s\n", SDL_GetError());
		return false;
	}

	window = SDL_CreateWindow(name, width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

	if (window == NULL)
	{
		printf("Failed to create window. Error: %s\n", SDL_GetError());
		return false;
	}

	if (SDL_GL_SetSwapInterval(1) < 0)
	{
		printf("Warning: Unable to set VSync.");
	}
	//SDL_SetWindowRelativeMouseMode(window, true);
	//SDL_CaptureMouse(true);

	return true;
}

bool Application::InitRenderer()
{
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	context = SDL_GL_CreateContext(window);

	if (context == NULL)
	{
		printf("Failed to create OpenGL context. Error: %s\n", SDL_GetError());
		return false;
	}

	glewExperimental = GL_TRUE;
	GLenum glewError = glewInit();
	if (glewError != GLEW_OK)
	{
		printf("Failed to init GLEW. Error: %s\n", glewGetErrorString(glewError));
		return false;
	}

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	glCullFace(GL_BACK);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glViewport(0, 0, width, height);
	glClearColor(0, 0.2, 0.5, 1);

	return true;
}

void Application::ToggleWireframe(bool toggle)
{
	glPolygonMode(GL_FRONT_AND_BACK, toggle ? GL_LINE : GL_FILL);
}

void Application::LoadScene()
{
	gameScene = new FallingShapesScene();

	Resources::Init();
	gameScene->Load();
	gameScene->InitPhysics();
}

void Application::Run()
{
	auto targetFramerate = 1 / 120.0f;
	GameTimer.Init(targetFramerate);
	GameTimer.Start();

	while (isRunning)
	{
		ProcessEvents();

		GameTimer.AccumulateTicks();
		auto timeStep = GameTimer.GetDeltaTime();

		Update(timeStep);
		GameTimer.Start();

		Render();
	}
}

void Application::ProcessEvents()
{
	InputManager.SetMouseMoveVector(0, 0);

	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_EVENT_QUIT:
			isRunning = false;
			break;

		case SDL_EVENT_WINDOW_RESIZED:

			width = event.window.data1;
			height = event.window.data2;

			glViewport(0, 0, width, height);

			break;

		case SDL_EVENT_KEY_DOWN:

			if (event.key.key == SDLK_ESCAPE)
			{
				isRunning = false;
			}

			if (event.key.key >= SDLK_A && event.key.key <= SDLK_Z)
			{
				auto keyAsKeycode = (KeyCode)(event.key.key - SDLK_A);
				InputManager.SetKeyDown(keyAsKeycode);
			}

			break;

		case SDL_EVENT_KEY_UP:

			if (event.key.key >= SDLK_A && event.key.key <= SDLK_Z)
			{
				auto keyAsKeycode = (KeyCode)(event.key.key - SDLK_A);
				InputManager.SetKeyUp(keyAsKeycode);
			}

			break;

		case SDL_EVENT_MOUSE_BUTTON_DOWN:

			break;

		case SDL_EVENT_MOUSE_BUTTON_UP:

			break;

		case SDL_EVENT_MOUSE_MOTION:

			InputManager.SetMouseMoveVector(event.motion.xrel, event.motion.yrel);
			break;
		}
	}
}

void Application::Update(float deltaTime)
{
	gameScene->PhysicsUpdate(deltaTime);
	gameScene->LogicUpdate(deltaTime);
}

void Application::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	auto aspectRatio = width / (float)height;
	gameScene->Render(aspectRatio);

	SDL_GL_SwapWindow(window);
}

bool Application::Quit()
{
	SDL_DestroyWindow(window);
	window = NULL;

	SDL_Quit();

	return true;
}
