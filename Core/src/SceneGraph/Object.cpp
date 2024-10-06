#include "Object.h"
#include "Transform.h"
#include "Scene.h"

Object::Object(std::string name, glm::vec3 position, Scene* ownerScene) : m_Name(name), m_UniqueIdentifier(std::rand()), m_OwnerScene(ownerScene)
{
	m_Components.reserve(5);
	m_Transform = AddComponent<Transform>();
	m_Transform->SetPosition(position);
};

Object::~Object() {}

void Object::DrawEditor() 
{
	for (Component* component : m_Components) 
	{
		component->DrawEditor();
	}
}

void Object::Update(float deltaTime) 
{
	for (Component* component : m_Components)
		component->Update(deltaTime);
}

void Object::Render(const Renderer& renderer) 
{
	for (Component* component : m_Components)
		component->Render(renderer);
}

void Object::RemoveComponent(Component* component)
{
	auto it = std::find(m_Components.begin(), m_Components.end(), component);
	if (it != m_Components.end())
	{
		delete* it;
		m_Components.erase(it);
	}
}