#include "Object.h"
#include "Components/TransformComponent.h"
#include "Scene.h"

namespace Forgex::Scene
{
	Object::Object(std::string name) : Object(name, glm::vec3(0), nullptr) {}

	Object::Object(std::string name, glm::vec3 position, Scene* ownerScene)
	: m_Name(name), m_UniqueIdentifier(std::rand()), m_OwnerScene(ownerScene)
	{
		m_Components.reserve(5);
		m_Transform = AddComponent<TransformComponent>();
		m_Transform->SetPosition(position);
	};

	Object::~Object() {}

	void Object::Update(float deltaTime) 
	{
		for (Component* component : m_Components)
			component->Update(deltaTime);
	}
}
