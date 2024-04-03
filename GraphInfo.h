WeChat: cstutorcs
QQ: 749389476
Email: tutorcs@163.com
#pragma once

#include <vector>
#include <string>
#include <fstream>
#include "Sprite.h"

#define GRAPH_FILE TEXT("GraphInfo.txt")

std::string convertCStringToString(const CString& text);
CString CharToWChar(const char* sstr);

class SpriteVertex : public Sprite {
public:
    SpriteVertex(int id)
        : Sprite(id), m_scale(16), m_x(0), m_y(0), m_highlight(false), m_selected(false) {

    }

public:
    void setLocation(int x, int y) {
        m_x = x;
        m_y = y;
    }

    void setName(const CString& name) {
        m_name = name;
    }

    void setHighlight(bool highlight) {
        m_highlight = highlight;
    }

    void setSelected(bool selected) {
        m_selected = selected;
    }

public:
    virtual bool hit(int x, int y) const {
        int left = m_x - (m_scale / 2);
        int top = m_y - (m_scale / 2);
        int right = m_x + m_scale;
        int bottom = m_y + m_scale;

        if (x < left || x > right) return false;
        if (y < top || y > bottom) return false;

        return true;
    }

private:
    virtual void update(Gdiplus::Graphics& graphics) {
        Gdiplus::SolidBrush brush(Gdiplus::Color::Orange);
        Gdiplus::SolidBrush highlightbrush(Gdiplus::Color::Red);
        Gdiplus::SolidBrush shadowbrush(Gdiplus::Color::Gray);
        Gdiplus::SolidBrush stringbrush(Gdiplus::Color::Black);

        Gdiplus::Pen selectedpen(Gdiplus::Color::Red);

        Gdiplus::Font font(L"Arial", 10, Gdiplus::FontStyleRegular);

        Gdiplus::StringFormat stringformat;
        stringformat.SetLineAlignment(Gdiplus::StringAlignment::StringAlignmentCenter);
        stringformat.SetAlignment(Gdiplus::StringAlignment::StringAlignmentCenter);

        int half = m_scale / 2;
        graphics.FillEllipse(&shadowbrush, m_x - half + 2, m_y - half + 2, m_scale, m_scale);
        if (m_selected) {
            graphics.DrawEllipse(&selectedpen, m_x - half - 4, m_y - half - 4, m_scale + 8, m_scale + 8);
            graphics.FillEllipse(&highlightbrush, m_x - half, m_y - half, m_scale, m_scale);
        } else {
            if (m_highlight) {
                graphics.FillEllipse(&highlightbrush, m_x - half, m_y - half, m_scale, m_scale);
            } else {
                graphics.FillEllipse(&brush, m_x - half, m_y - half, m_scale, m_scale);
            }
        }
        Gdiplus::RectF rect((Gdiplus::REAL)(m_x - 100), (Gdiplus::REAL)(m_y + 4), (Gdiplus::REAL)200, (Gdiplus::REAL)40);
        graphics.DrawString(m_name, m_name.GetLength(), &font, rect, &stringformat, &stringbrush);
    }

private:
    int m_x;
    int m_y;
    int m_scale;
    CString m_name;
    bool m_highlight;
    bool m_selected;
};

class SpriteEdge : public Sprite {
public:
    SpriteEdge(int id)
        : Sprite(id), m_begin_x(0), m_begin_y(0), m_end_x(0), m_end_y(0), m_distance(0), m_time(0), m_highlight(false) {

    }

public:
    void setLocation(int begin_x, int begin_y, int end_x, int end_y) {
        m_begin_x = begin_x;
        m_begin_y = begin_y;
        m_end_x = end_x;
        m_end_y = end_y;
    }

    void setDistance(double distance) {
        m_distance = distance;
    }

    void setTime(double time) {
        m_time = time;
    }

    void setHighlight(bool highlight) {
        m_highlight = highlight;
    }

private:
    virtual void update(Gdiplus::Graphics& graphics) {
        if (m_highlight) {
            Gdiplus::Pen pen(Gdiplus::Color::Red, 4);
            graphics.DrawLine(&pen, m_begin_x, m_begin_y, m_end_x, m_end_y);
        } else {
            Gdiplus::Pen pen(Gdiplus::Color::LightGray, 1);
            graphics.DrawLine(&pen, m_begin_x, m_begin_y, m_end_x, m_end_y);
        }
        Gdiplus::Font font(L"Arial", 7, Gdiplus::FontStyleRegular);
        Gdiplus::SolidBrush stringbrush(Gdiplus::Color::Blue);
        Gdiplus::StringFormat stringformat;
        stringformat.SetLineAlignment(Gdiplus::StringAlignment::StringAlignmentCenter);
        stringformat.SetAlignment(Gdiplus::StringAlignment::StringAlignmentCenter);
        Gdiplus::RectF rect((Gdiplus::REAL)((m_begin_x + m_end_x) / 2) - 50, (Gdiplus::REAL)((m_begin_y + m_end_y) / 2) - 10, (Gdiplus::REAL)100, (Gdiplus::REAL)20);
        CString info;
        info.Format(TEXT("%G  %G"), m_distance, m_time);
        graphics.DrawString(info, info.GetLength(), &font, rect, &stringformat, &stringbrush);
    }

    virtual bool hit(int x, int y) const {
        return false;
    }

private:
    int m_begin_x;
    int m_begin_y;
    int m_end_x;
    int m_end_y;
    double m_distance;
    double m_time;
    bool m_highlight;
};

struct VertexInfo {
    VertexInfo() :sprite(NULL), x(0), y(0), highlight(0) {

    }

    void save(std::ofstream& output) const;
    void load(std::ifstream& input);
    void update();
    void setDelete();

    SpriteVertex* sprite;
    CString name;
    CString summary;
    int x;
    int y;
    bool highlight;
};

struct EdgeInfo {
    EdgeInfo() :sprite(NULL), distance(0), time(0), highlight(0) {

    }
    
    void save(std::ofstream& output) const;
    void load(std::ifstream& input);
    void update(VertexInfo* begin, VertexInfo* end);
    void setDelete();

    SpriteEdge* sprite;
    CString begin;
    CString end;
    double distance;
    double time;
    bool highlight;
};

class GraphInfo {
public:
    GraphInfo() {

    }

public:
    bool canRenameVertex(const CString& name, VertexInfo* info);
    void renameEdge(const CString& oldname, const CString& newname);
    VertexInfo* findVertex(const CString& name);
    EdgeInfo* findEdge(const CString& begin, const CString& end);
    int findVertexIndex(const CString& name);

public:
    VertexInfo* hitVertex(int x, int y);

public:
    bool addVertex(const VertexInfo& vertex);
    bool addEdge(const EdgeInfo& edge);
    bool removeVertex(const CString& name);
    bool removeEdge(const CString& begin, const CString& end);
    void removeEdge(const CString& name);
    void updateEdge();
    void updateEdge(EdgeInfo& edge);
    void update();
    void clearHighlight();

public:
    void saveFile(const CString& file) const;
    void loadFile(const CString& file);

public:
    std::vector<VertexInfo> m_vertex_list;
    std::vector<EdgeInfo> m_edge_list;
};

