#pragma once

#include "GameObject.h"
#include "Resources.h"

#include "Input.h"
#include "Physics.h"

#include <vector>


class Scene
{
public:

	virtual void Load() = 0;

	virtual void Unload() = 0;

	virtual void Update(float dt);

	virtual void Render(float aspectRatio);

protected:

	std::vector<std::shared_ptr<GameObject>> SceneObjects;





	template<typename T>
	inline std::vector<std::shared_ptr<T>> GetAllComponents()
	{
		static_assert(std::is_base_of<Component, T>::value, "Type must inherit from Component");

		std::vector<std::shared_ptr<T>> result;
		for (auto& gameObject : SceneObjects)
		{
			auto component = gameObject->GetComponent<T>();
			if (component != NULL)
			{
				result.push_back(component);
			}
		}

		return result;
	}


private:

	void Render(std::shared_ptr<CameraComponent> camera, float aspectRatio);

};

