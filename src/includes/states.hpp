#pragma once
#include <Geode/Geode.hpp>
using namespace geode::prelude;

class Singelton final {
public:
    static Singelton& get() {
        static Singelton instance;

        return instance;
    }
    bool glob_fOTF_state = false;
};