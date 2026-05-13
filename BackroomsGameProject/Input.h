#pragma once

#include <map>
#include <glm.hpp>

enum class KeyCode
{
	KEYCODE_A = 0,
	KEYCODE_B,
	KEYCODE_C,
	KEYCODE_D,
	KEYCODE_E,
	KEYCODE_F,
	KEYCODE_G,
	KEYCODE_H,
	KEYCODE_I,
	KEYCODE_J,
	KEYCODE_K,
	KEYCODE_L,
	KEYCODE_M,
	KEYCODE_N,
	KEYCODE_O,
	KEYCODE_P,
	KEYCODE_Q,
	KEYCODE_R,
	KEYCODE_S,
	KEYCODE_T,
	KEYCODE_U,
	KEYCODE_V,
	KEYCODE_W,
	KEYCODE_X,
	KEYCODE_Y,
	KEYCODE_Z,
};

class Input
{
public:

	void SetMouseMoveVector(float x, float y);

	void SetKeyDown(KeyCode key);

	void SetKeyUp(KeyCode key);

	static bool IsKeyDown(KeyCode key);

	static bool IsKeyUp(KeyCode key);

	static glm::vec2 GetMouseMoveVector();


private:

	static std::map<KeyCode, int> KeyStates;

	static glm::vec2 MouseMoveVector;
};

