#include "Input.h"

std::map<KeyCode, int> Input::KeyStates;
glm::vec2 Input::MouseMoveVector;

void Input::SetMouseMoveVector(float x, float y)
{
    MouseMoveVector.x = x;
    MouseMoveVector.y = y;
}

void Input::SetKeyDown(KeyCode key)
{
    KeyStates[key] = 1;
}

void Input::SetKeyUp(KeyCode key)
{
	KeyStates[key] = 0;
}

bool Input::IsKeyDown(KeyCode key)
{
    return KeyStates[key] == 1;
}

bool Input::IsKeyUp(KeyCode key)
{
    return KeyStates[key] == 0;
}

glm::vec2 Input::GetMouseMoveVector()
{
    return MouseMoveVector;
}
