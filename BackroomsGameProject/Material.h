#pragma once

#include "Texture.h"

#include <glm.hpp>
#include <memory>


class Material
{
public:

	void SetTexture(std::shared_ptr<Texture> texture);

	void BindTextures();



	void Render();


private:

	std::shared_ptr<Texture> BaseTexture;

};

