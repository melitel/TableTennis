#pragma once
#include "IGameEntity.h"
#include "PhysicActor.h"

class GameEntity :
    public IGameEntity
{
public:
	GameEntity(sf::Vector2f pos, uint32_t entity_id) : m_position(pos), m_entity_id(entity_id), m_physicActor(nullptr) {	}

	void initialize() override;
	void draw(std::unique_ptr<sf::RenderWindow>& window) override;

protected:
	std::shared_ptr<PhysicActor> m_physicActor;
	const sf::Color m_sprite_color{ 255, 255, 255 };	
	sf::Vector2f m_position;
	uint32_t m_entity_id;
};

