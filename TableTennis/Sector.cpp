#include "Sector.h"
#include "IPhysicActor.h"

void Sector::delete_dynamic_actor(const std::shared_ptr<IPhysicActor>& actor)
{
    for (int i = 0; i < m_dynamic_actors.size(); i++) {
        if (m_dynamic_actors[i] == actor) {
            m_dynamic_actors[i].swap(m_dynamic_actors.back());
            m_dynamic_actors.pop_back();
        }
    }
}

bool Sector::overlap(const BoundingBox& bb,
    const std::shared_ptr<IPhysicActor>& actor, 
    bool dynamic, bool stat,
    std::vector<std::shared_ptr<IPhysicActor>>& actors_hit)
{
    bool result = false;

    if (stat) {
        for (int i = 0; i < m_static_actors.size(); i++) {
            if (m_static_actors[i] != actor && m_static_actors[i]->get_bounds().intersects(bb)) {
                result = true;
                actors_hit.push_back(m_static_actors[i]);
                break;
            }        
        }
    }
    if (dynamic && !result) {
        for (int i = 0; i < m_dynamic_actors.size(); i++) {
            if (m_dynamic_actors[i] != actor && m_dynamic_actors[i]->get_bounds().intersects(bb)) {
                result = true;
                actors_hit.push_back(m_dynamic_actors[i]);
                break;
            }
        }
    }

    return result;
}
