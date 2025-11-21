#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>

using namespace geode::prelude;

#include "../includes/winSize.hpp"
#include "../includes/states.hpp"

class $modify(ChrmdMenuLayer, MenuLayer) {
    struct Fields {
        CCSprite* bg = nullptr;
        int status = 0;
        CCMenu* toggleMenu = nullptr;
    };
    $override
    bool init() {
        if (!MenuLayer::init()) return false;

        m_fields->bg = CCSprite::createWithSpriteFrameName("block005b_05_001.png");
        m_fields->bg->setID("toggle-menu-bg"_spr);

        m_fields->bg->setColor({ 0, 0, 0 });
        this->addChild(m_fields->bg);
        m_fields->bg->setScale(66.725f);
        m_fields->bg->setOpacity(140.5);
        m_fields->bg->setVisible(false);
        m_fields->bg->setPosition({-1000, 1000});
        m_fields->bg->setZOrder(998);

        auto bottomMenu = getChildByID("bottom-menu");

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

        m_fields->toggleMenu = CCMenu::create();

        m_fields->toggleMenu->setID("toggle-menu"_spr);
        m_fields->toggleMenu->setLayout(RowLayout::create());
        m_fields->toggleMenu->setZOrder(1000);
        m_fields->toggleMenu->setPosition({-1000, 1000});
        m_fields->toggleMenu->addChild(furyOfTheFallen);
        m_fields->toggleMenu->updateLayout();
        m_fields->toggleMenu->setVisible(false);
        this->addChild(m_fields->toggleMenu);
        furyOfTheFallen->setPosition({58.90, 102});
        auto furyOfTheFallenText = CCLabelBMFont::create("Fury of the fallen", "bigFont.fnt");
        m_fields->toggleMenu->addChild(furyOfTheFallenText);
        furyOfTheFallenText->setPosition({145.50, 102});
        furyOfTheFallenText->setScale(0.42500000);

        auto chrmIco = CCSprite::create("furyOfTheFallen.png"_spr);
        chrmIco->setID("fury-of-the-fallen-icon"_spr);

        m_fields->toggleMenu->addChild(chrmIco);
        chrmIco->setPosition({235, 102});
        chrmIco->setScale(0.4);

        return true;
    }

    void onChrmBtnClicked(CCObject* sender) {
        if(m_fields->status == 0) {
            m_fields->bg->setPosition({winSize.width / 2, winSize.height / 2});
            m_fields->bg->setVisible(true);
            m_fields->status = 1;
            m_fields->toggleMenu->setPosition({winSize.width / 2, winSize.height / 2});
            m_fields->toggleMenu->setVisible(true);
        }
        else {
            m_fields->bg->setPosition({-1000, 1000});
            m_fields->bg->setVisible(false);
            m_fields->status = 0;
            m_fields->toggleMenu->setPosition({-1000, 1000});
            m_fields->toggleMenu->setVisible(false);
            
        }
    }
    //193 102

    void fOTFChrmOn(CCObject* sender) {
        Singelton::get().glob_fOTF_state = !static_cast<CCMenuItemToggler*>(sender)->isToggled();
        log::info("Toggled {}", Singelton::get().glob_fOTF_state);
    }
};