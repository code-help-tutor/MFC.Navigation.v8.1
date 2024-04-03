WeChat: cstutorcs
QQ: 749389476
Email: tutorcs@163.com
#pragma once

#include "Common.h"
#include "Sprite.h"
#include "Engine.h"
#include "GraphInfo.h"

class SpriteInfoBox;

class NavigationEngine : public Engine
{
public:
    NavigationEngine();
    virtual ~NavigationEngine();

public:
    virtual void countFPS(int fps);
    virtual void onMouseEvent(MOUSE_EVENT_TYPE type, int x, int y);

public:
    GraphInfo& getGraphInfo();
    bool addVertex(const VertexInfo& vertex);
    bool addEdge(const EdgeInfo& edge);
    void search(const CString& category, const CString& begin, const CString& end, CString& output);
    void search(MOUSE_EVENT_TYPE type, int x, int y, const CString& category, CString& begin, CString& end, CString& output);
    void move(MOUSE_EVENT_TYPE type, int x, int y);

public:
    void saveFile(const CString& file) const;
    void loadFile(const CString& file);

private:
    void createInfoBox();

private:
    SpriteInfoBox* m_infobox;
    VertexInfo* m_selected;
    GraphInfo m_graph_info;
};
