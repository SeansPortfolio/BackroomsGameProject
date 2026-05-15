#include "Material.h"

void Material::SetTexture(std::shared_ptr<Texture> texture)
{
	BaseTexture = texture;
}

void Material::BindTextures()
{
	BaseTexture->Bind(0);
}

void Material::Render()
{

}
