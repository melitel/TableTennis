#pragma once
#include "IGameEntity.h"
#include "PhysicActor.h"

class GameEntity :
    public IGameEntity
{
public:
	GameEntity(Vector2f pos, uint32_t entity_id, entity_type entType) : 
		m_position(pos), m_entity_id(entity_id), m_entity_type(entType), m_physicActor(nullptr) {	}

	void initialize() override;
	void draw(std::unique_ptr<sf::RenderWindow>& window) override;
	void onHit(const Vector2f& normal, const std::shared_ptr<IGameEntity>& entity_hit) override {}
	void reset(const Vector2f& vel) override {}
	//void addObserver(Observer* observer) override {};
	//void removeObserver(Observer* observer) override {};
	entity_type get_entity_type() override {
		return m_entity_type;
	}

protected:
	entity_type m_entity_type;
	std::shared_ptr<IPhysicActor> m_physicActor;
	const sf::Color m_sprite_color{ 255, 255, 255 };	
	Vector2f m_position;
	uint32_t m_entity_id;
};

