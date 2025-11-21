#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>

using namespace geode::prelude;

#include "../includes/states.hpp"

class $modify(PlayLayer) {
    void destroyPlayer(PlayerObject* player, GameObject* object) {
        if (Singelton::get().glob_fOTF_state == true) {
            if (object == m_anticheatSpike) {
                PlayLayer::destroyPlayer(player, object);
            }
        }  
        else {
            PlayLayer::destroyPlayer(player, object);
        }
    }
};