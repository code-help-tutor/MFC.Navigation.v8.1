WeChat: cstutorcs
QQ: 749389476
Email: tutorcs@163.com
#pragma once

#include "Common.h"
#include <vector>

class Sprite {
public:
    Sprite(int id) : m_id(id), m_done(false), m_delete(false) {

    }

    virtual ~Sprite() {

    }

public:
    int getID() const {
        return m_id;
    }

    void setDone(bool enabled) {
        m_done = enabled;
    }

    bool isDone() const {
        return m_done;
    }

    void setDelete() {
        m_delete = true;
    }

    bool isDelete() const {
        return m_delete;
    }

public:
    virtual void update(Gdiplus::Graphics& graphics) = 0;
    virtual bool hit(int x, int y) const = 0;

private:
    int m_id;
    bool m_done;
    bool m_delete;
};

class SpriteList {
public:
    SpriteList();
    virtual ~SpriteList();

public:
    int generateID();
    void add(Sprite* sprite);
    Sprite* find(int id) const;
    void refresh();
    bool isDone() const;
    void update(Gdiplus::Graphics& graphics) const;
    Sprite* hit(int x, int y) const;
    void clear();

private:
    int m_id;
    std::vector<Sprite*> m_list;
};
