#pragma once
#include <Geode/Geode.hpp>
#include "./winSize.hpp"
using namespace geode::prelude;

class CharmsLayer : public CCLayer {
public:
    CREATE_FUNC(CharmsLayer);

    static CCScene* scene() {
        auto layer = CharmsLayer::create();
        auto scene = CCScene::create();
        scene->addChild(layer);

        return scene;
    }

    bool init() {
        if (!CCLayer::init()) return false;

        auto background = CCSprite::create("GJ_gradientBG.png");
        background->setScaleX(winSize.width / background->getContentWidth());
        background->setScaleY(winSize.height / background->getContentHeight());
        background->setPosition( {winSize.width / 2, winSize.height / 2} );
        background->setColor({ 36, 36, 36 });
        this->addChild(background);

        auto mainCharmsArea = CCMenu::create();
        

        auto backMenu = CCMenu::create();
        backMenu->setPosition( {winSize.width / 2, winSize.height / 2} );
        backMenu->setContentSize( {winSize.width, winSize.height} );
        this->addChild(backMenu);

        auto backBtnSprite = CCSprite::createWithSpriteFrameName("GJ_arrow_01_001.png");
        auto backBtn = CCMenuItemSpriteExtra::create(
            backBtnSprite,
            this,
            menu_selector(CharmsLayer::onBack)
        );
        backMenu->addChild(backBtn);
        backBtn->setPosition( { (0 - (winSize.width / 2) + 20.f), (winSize.height / 2) -20.f } );

        return true;
    }

    void onBack(CCObject* sender) {
        CCDirector::sharedDirector()->popSceneWithTransition(0.5f, PopTransition::kPopTransitionFade);
    }
};