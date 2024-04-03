WeChat: cstutorcs
QQ: 749389476
Email: tutorcs@163.com
#pragma once

#include "Common.h"
#include "Sprite.h"


enum MOUSE_EVENT_TYPE {
    MOVE,
    LBUTTON,
    RBUTTON,
};

class Engine {
public:
    virtual void update(Gdiplus::Graphics& graphics) {
        m_sprites.refresh();
        m_sprites.update(graphics);
    }

    virtual void countFPS(int fps) {

    }

    virtual void onMouseEvent(MOUSE_EVENT_TYPE type, int x, int y) {

    }

protected:
    SpriteList m_sprites;
};

