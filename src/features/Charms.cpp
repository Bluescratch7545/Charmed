#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>

using namespace geode::prelude;

#include "../includes/states.hpp"

class $modify(PlayLayer) {
    struct Fields { 
        int dths = 0;
        int limit = 2;
    };

    void destroyPlayer(PlayerObject* player, GameObject* object) {
        if (Singelton::get().glob_fOTF_state) {
            if (object == m_anticheatSpike) {
                PlayLayer::destroyPlayer(player, object);
            }
        }  
        else {
            PlayLayer::destroyPlayer(player, object);
        }
        
        if (Singelton::get().glob_lH_state == false) {
            log::info("noclip = off");
            PlayLayer::destroyPlayer(player, object);
        }
        else {
            if (m_fields->dths < m_fields->limit) {
                m_fields->dths = m_fields->dths + 1;
            }
            else if (object == m_anticheatSpike || m_fields->dths >= m_fields->limit) {
                m_fields->dths = 0;
                PlayLayer::destroyPlayer(player, object);
            }
            log::info("noclip = on");
        }
    }
};