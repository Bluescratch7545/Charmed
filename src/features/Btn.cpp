#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>
#include "../includes/winSize.hpp"
#include "../includes/states.hpp"
#include "../includes/CharmsLayer.hpp"

using namespace geode::prelude;

CCMenu* toggleMenu = nullptr;

class $modify(ChrmdMenuLayer, MenuLayer) {
    $override
    bool init() {
        if (!MenuLayer::init()) return false;
        auto CharmsLayer = CharmsLayer::create();

        auto charmBtn = CCMenuItemSpriteExtra::create(
            CCSprite::createWithSpriteFrameName("GJ_plainBtn_001.png"),
            this,
            menu_selector(ChrmdMenuLayer::onChrmBtnClicked)
        );

        charmBtn->setID("charm-button"_spr);

        auto charmBtnOverlay = CCSprite::create("furyOfTheFallen.png"_spr);
        charmBtnOverlay->setID("charm-button-overlay"_spr);

        charmBtnOverlay->setPosition({23, 23});
        charmBtnOverlay->setScale(0.35);

        auto chrmBtnMenu = CCMenu::create();

        chrmBtnMenu->setID("charm-button-menu"_spr);

        charmBtn->addChild(charmBtnOverlay);

        this->addChild(chrmBtnMenu);
        chrmBtnMenu->setPosition({58.90, 296});
        chrmBtnMenu->setLayout(RowLayout::create());
        chrmBtnMenu->setZOrder(999);

        chrmBtnMenu->addChild(charmBtn);

        chrmBtnMenu->updateLayout();

        auto furyOfTheFallen = CCMenuItemToggler::createWithStandardSprites(
            this,
            menu_selector(ChrmdMenuLayer::fOTFChrmOn),
            1.0f
        );
        furyOfTheFallen->toggle(Singelton::get().glob_fOTF_state);
        furyOfTheFallen->setID("fury-of-the-fallen"_spr);

        toggleMenu = CCMenu::create();

        auto fOTFMenu = CCMenu::create();
        fOTFMenu->setID("fury-of-the-fallen-menu"_spr);

        toggleMenu->setID("toggle-menu"_spr);
        toggleMenu->setLayout(RowLayout::create());
        fOTFMenu->setLayout(RowLayout::create());
        toggleMenu->setZOrder(1000);
        toggleMenu->setPosition({-1000, 1000});
        toggleMenu->addChild(fOTFMenu);
        fOTFMenu->addChild(furyOfTheFallen);
        fOTFMenu->setPosition({118.90, 249});
        furyOfTheFallen->setPosition({234, 146});
        toggleMenu->setVisible(false);
        this->addChild(toggleMenu);
        auto furyOfTheFallenText = CCLabelBMFont::create("Fury of the fallen", "bigFont.fnt");
        furyOfTheFallenText->setID("fury-of-the-fallen-text"_spr);
        fOTFMenu->addChild(furyOfTheFallenText);
        furyOfTheFallenText->setPosition({326, 146});
        furyOfTheFallenText->setScale(0.42500000);

        auto fOTFChrmIco = CCMenuItemSpriteExtra::create(
            CCSprite::create("furyOfTheFallen.png"_spr),
            this,
            menu_selector(ChrmdMenuLayer::fOTFChrmInfoBtnClicked)
        );

        fOTFChrmIco->setID("fury-of-the-fallen-icon"_spr);

        fOTFMenu->addChild(fOTFChrmIco);
        fOTFChrmIco->setPosition({416, 145});
        fOTFChrmIco->setScale(0.4);
        fOTFChrmIco->m_baseScale = 0.4;

        auto lifebloodHeart = CCMenuItemToggler::createWithStandardSprites(
            this,
            menu_selector(ChrmdMenuLayer::lHChrmOn),
            1.0f
        );
        lifebloodHeart->toggle(Singelton::get().glob_lH_state);
        lifebloodHeart->setID("lifeblood-heart"_spr);

        auto lHMenu = CCMenu::create();
        lHMenu->setID("lifeblood-heart-menu"_spr);

        toggleMenu->addChild(lHMenu);
        lHMenu->setLayout(RowLayout::create());
        lHMenu->addChild(lifebloodHeart);
        lHMenu->setPosition({118.90, 209});
        lifebloodHeart->setPosition({234, 146});
        auto lifebloodHeartText = CCLabelBMFont::create("Lifeblood heart", "bigFont.fnt");
        lifebloodHeartText->setID("lifeblood-heart-text"_spr);
        lifebloodHeartText->setScale(0.525);
        lHMenu->addChild(lifebloodHeartText);
        lifebloodHeartText->setPosition({325, 146});

        auto lHChrmIco = CCMenuItemSpriteExtra::create(
            CCSprite::create("lifebloodHeart.png"_spr),
            this,
            menu_selector(ChrmdMenuLayer::lHChrmInfoBtnClicked)
        );
        lHChrmIco->setID("lifeblood-heart-icon"_spr);
        lHMenu->addChild(lHChrmIco);
        lHChrmIco->setPosition({415, 147});
        lHChrmIco->m_baseScale = 0.4;
        lHChrmIco->setScale(0.4);

        return true;
    }

    void onChrmBtnClicked(CCObject*) {
        CCDirector::sharedDirector()->pushScene(CCTransitionFade::create(0.5f, CharmsLayer::scene()));
    }

    void fOTFChrmOn(CCObject* sender) {
        Singelton::get().glob_fOTF_state = !static_cast<CCMenuItemToggler*>(sender)->isToggled();
        log::info("Fury of the fallen: Toggled {}", Singelton::get().glob_fOTF_state);
    }

    void lHChrmOn(CCObject* sender) {
        Singelton::get().glob_lH_state = !static_cast<CCMenuItemToggler*>(sender)->isToggled();
        log::info("Lifeblood heart: Toggled {}", Singelton::get().glob_lH_state);
    }

    void fOTFChrmInfoBtnClicked(CCObject* sender) {
        FLAlertLayer::create(
            "Charm Info",
            "This charm acts like noclip. Use it wisely.",
            "I Understand"
        )->show();
    }

    void lHChrmInfoBtnClicked(CCObject* sender) {
        FLAlertLayer::create(
            "Charm Info",
            "This charm acts like Noclip deaths, set to 2",
            "I Understand"
        )->show();
    }
};