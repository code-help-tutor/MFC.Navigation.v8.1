WeChat: cstutorcs
QQ: 749389476
Email: tutorcs@163.com
#include "pch.h"
#include "Sprite.h"

SpriteList::SpriteList() : m_id(0) {

}

SpriteList::~SpriteList() {
    clear();
}

int SpriteList::generateID() {
    return ++m_id;
}

void SpriteList::add(Sprite* sprite) {
    m_list.push_back(sprite);
}

Sprite* SpriteList::find(int id) const {
    for (std::vector<Sprite*>::const_iterator iter = m_list.begin(); iter != m_list.end(); ++iter) {
        if ((*iter)->getID() == id) {
            return *iter;
        }
    }
    return NULL;
}

void SpriteList::refresh() {
    std::vector<Sprite*>::iterator iter = m_list.begin();
    while (iter != m_list.end()) {
        if ((*iter)->isDelete()) {
            delete (*iter);
            iter = m_list.erase(iter);
        } else {
            ++iter;
        }
    }
}

bool SpriteList::isDone() const {
    for (std::vector<Sprite*>::const_iterator iter = m_list.begin(); iter != m_list.end(); ++iter) {
        if (!(*iter)->isDone()) {
            return false;
        }
    }
    return true;
}

void SpriteList::update(Gdiplus::Graphics& graphics) const {
    for (std::vector<Sprite*>::const_reverse_iterator iter = m_list.rbegin(); iter != m_list.rend(); ++iter) {
        (*iter)->update(graphics);
    }
    for (std::vector<Sprite*>::const_reverse_iterator iter = m_list.rbegin(); iter != m_list.rend(); ++iter) {
        (*iter)->update(graphics);
    }
}

Sprite* SpriteList::hit(int x, int y) const {
    for (std::vector<Sprite*>::const_iterator iter = m_list.begin(); iter != m_list.end(); ++iter) {
        if ((*iter)->hit(x, y)) {
            return (*iter);
        }
    }
    return NULL;
}

void SpriteList::clear() {
    for (std::vector<Sprite*>::iterator iter = m_list.begin(); iter != m_list.end(); ++iter) {
        delete (*iter);
    }
    m_list.clear();
}
