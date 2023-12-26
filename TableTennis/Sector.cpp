#include "Sector.h"
#include "IPhysicActor.h"

bool Sector::overlap(const BoundingBox& bb, const std::shared_ptr<IPhysicActor>& actor, bool dynamic, bool stat)
{
    bool result = false;

    if (stat) {
        for (int i = 0; i < m_static_actors.size(); i++) {
            if (m_static_actors[i] != actor && m_static_actors[i]->get_bounds().intersects(bb)) {
                result = true;
                break;
            }        
        }
    }
    if (dynamic && !result) {
        for (int i = 0; i < m_dynamic_actors.size(); i++) {
            if (m_dynamic_actors[i] != actor && m_dynamic_actors[i]->get_bounds().intersects(bb)) {
                result = true;
                break;
            }
        }
    }

    return result;
}
