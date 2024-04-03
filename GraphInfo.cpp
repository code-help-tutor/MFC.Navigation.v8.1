WeChat: cstutorcs
QQ: 749389476
Email: tutorcs@163.com
#include "pch.h"
#include "GraphInfo.h"

std::string convertCStringToString(const CString& text) {
    int cbMultiByte = WideCharToMultiByte(CP_ACP, 0, text, -1, NULL, 0, NULL, NULL);
    char* pszText = NULL;
    pszText = new char[cbMultiByte];
    WideCharToMultiByte(CP_ACP, 0, text, -1, pszText, cbMultiByte, NULL, NULL);
    std::string result = pszText;
    delete[] pszText;
    return result;
}

CString CharToWChar(const char* sstr) {
    int len = MultiByteToWideChar(CP_ACP, 0, sstr, -1, NULL, 0);
    wchar_t* wstr = new wchar_t[len + 1];
    memset(wstr, 0, len + 1);
    MultiByteToWideChar(CP_ACP, 0, sstr, -1, wstr, len);

    CString str = wstr;
    if (wstr) delete[] wstr;
    return str;
}

void VertexInfo::save(std::ofstream& output) const {
    output << convertCStringToString(name) << " ";
    output << convertCStringToString(summary) << " ";
    output << x << " ";
    output << y << " ";
    output << std::endl;
}

void VertexInfo::load(std::ifstream& input) {
    std::string _name;
    std::string _summary;
    input >> _name;
    input >> _summary;
    name = CharToWChar(_name.c_str());
    summary = CharToWChar(_summary.c_str());
    input >> x;
    input >> y;
}

void VertexInfo::update() {
    if (sprite) {
        sprite->setLocation(x, y);
        sprite->setName(name);
        sprite->setHighlight(highlight);
    }
}

void VertexInfo::setDelete() {
    if (sprite) {
        sprite->setDelete();
        sprite = NULL;
    }
}


void EdgeInfo::save(std::ofstream& output) const {
    output << convertCStringToString(begin) << " ";
    output << convertCStringToString(end) << " ";
    output << distance << " ";
    output << time << " ";
    output << std::endl;
}

void EdgeInfo::load(std::ifstream& input) {
    std::string _begin;
    std::string _end;
    input >> _begin;
    input >> _end;
    begin = CharToWChar(_begin.c_str());
    end = CharToWChar(_end.c_str());
    input >> distance;
    input >> time;
}

void EdgeInfo::update(VertexInfo* begin, VertexInfo* end) {
    if (sprite) {
        sprite->setLocation(begin->x, begin->y, end->x, end->y);
        sprite->setDistance(distance);
        sprite->setTime(time);
        sprite->setHighlight(highlight);
    }
}

void EdgeInfo::setDelete() {
    if (sprite) {
        sprite->setDelete();
        sprite = NULL;
    }
}

bool GraphInfo::canRenameVertex(const CString& name, VertexInfo* info) {
    for (std::vector<VertexInfo>::iterator iter = m_vertex_list.begin(); iter != m_vertex_list.end(); ++iter) {
        if (&*iter != info && iter->name == name) {
            return false;
        }
    }
    return true;
}

void GraphInfo::renameEdge(const CString& oldname, const CString& newname) {
    for (std::vector<EdgeInfo>::iterator iter = m_edge_list.begin(); iter != m_edge_list.end(); ++iter) {
        if (iter->begin == oldname) {
            iter->begin = newname;
        }
        if (iter->end == oldname) {
            iter->end = newname;
        }
    }
}

VertexInfo* GraphInfo::findVertex(const CString& name) {
    for (std::vector<VertexInfo>::iterator iter = m_vertex_list.begin(); iter != m_vertex_list.end(); ++iter) {
        if (iter->name == name) {
            return &*iter;
        }
    }
    return NULL;
}

EdgeInfo* GraphInfo::findEdge(const CString& begin, const CString& end) {
    for (std::vector<EdgeInfo>::iterator iter = m_edge_list.begin(); iter != m_edge_list.end(); ++iter) {
        if (iter->begin == begin && iter->end == end) {
            return &*iter;
        }
    }
    return NULL;
}

int GraphInfo::findVertexIndex(const CString& name) {
    int index = 0;
    for (std::vector<VertexInfo>::iterator iter = m_vertex_list.begin(); iter != m_vertex_list.end(); ++iter) {
        if (iter->name == name) {
            return index;
        }
        ++index;
    }
    return -1;
}

VertexInfo* GraphInfo::hitVertex(int x, int y) {
    for (std::vector<VertexInfo>::iterator iter = m_vertex_list.begin(); iter != m_vertex_list.end(); ++iter) {
        if (iter->sprite && iter->sprite->hit(x, y)) {
            return &*iter;
        }
    }
    return NULL;
}

bool GraphInfo::addVertex(const VertexInfo& vertex) {
    if (findVertex(vertex.name)) return false;
    m_vertex_list.push_back(vertex);
    return true;
}

bool GraphInfo::addEdge(const EdgeInfo& edge) {
    if (findEdge(edge.begin, edge.end)) return false;
    m_edge_list.push_back(edge);
    return true;
}

bool GraphInfo::removeVertex(const CString& name) {
    for (std::vector<VertexInfo>::iterator iter = m_vertex_list.begin(); iter != m_vertex_list.end(); ++iter) {
        if (iter->name == name) {
            removeEdge(name);
            iter->setDelete();
            m_vertex_list.erase(iter);
            return true;
        }
    }
    return false;
}

bool GraphInfo::removeEdge(const CString& begin, const CString& end) {
    for (std::vector<EdgeInfo>::iterator iter = m_edge_list.begin(); iter != m_edge_list.end(); ++iter) {
        if (iter->begin == begin && iter->end == end) {
            iter->setDelete();
            m_edge_list.erase(iter);
            return true;
        }
    }
    return false;
}

void GraphInfo::removeEdge(const CString& name) {
    std::vector<EdgeInfo>::iterator iter = m_edge_list.begin();
    while (iter != m_edge_list.end()) {
        if (iter->begin == name || iter->end == name) {
            iter->setDelete();
            iter = m_edge_list.erase(iter);
            continue;
        }
        ++iter;
    }
}

void GraphInfo::updateEdge() {
    for (std::vector<EdgeInfo>::iterator iter = m_edge_list.begin(); iter != m_edge_list.end(); ++iter) {
        updateEdge(*iter);
    }
}

void GraphInfo::updateEdge(EdgeInfo& edge) {
    VertexInfo* begin = findVertex(edge.begin);
    VertexInfo* end = findVertex(edge.end);
    if (begin && end) {
        edge.update(begin, end);
    }
}

void GraphInfo::update() {
    for (std::vector<VertexInfo>::iterator iter = m_vertex_list.begin(); iter != m_vertex_list.end(); ++iter) {
        iter->update();
    }
    for (std::vector<EdgeInfo>::iterator iter = m_edge_list.begin(); iter != m_edge_list.end(); ++iter) {
        updateEdge(*iter);
    }
}

void GraphInfo::clearHighlight() {
    for (std::vector<VertexInfo>::iterator iter = m_vertex_list.begin(); iter != m_vertex_list.end(); ++iter) {
        iter->highlight = false;
    }
    for (std::vector<EdgeInfo>::iterator iter = m_edge_list.begin(); iter != m_edge_list.end(); ++iter) {
        iter->highlight = false;
    }
}

void GraphInfo::saveFile(const CString& file) const {
    std::string filename = convertCStringToString(file);
    std::ofstream output(filename);
    if (output) {
        output << m_vertex_list.size() << " " << m_edge_list.size() << std::endl;
        for (std::vector<VertexInfo>::const_iterator iter = m_vertex_list.begin(); iter != m_vertex_list.end(); ++iter) {
            iter->save(output);
        }
        for (std::vector<EdgeInfo>::const_iterator iter = m_edge_list.begin(); iter != m_edge_list.end(); ++iter) {
            iter->save(output);
        }
    }
}

void GraphInfo::loadFile(const CString& file) {
    std::string filename = convertCStringToString(file);
    std::ifstream input(filename);
    if (input) {
        m_vertex_list.clear();
        m_edge_list.clear();
        int vcount = 0;
        int ecount = 0;
        input >> vcount >> ecount;

        for (int index = 0; index < vcount; ++index) {
            VertexInfo info;
            info.load(input);
            m_vertex_list.push_back(info);
        }

        for (int index = 0; index < ecount; ++index) {
            EdgeInfo info;
            info.load(input);
            m_edge_list.push_back(info);
        }
    }
}
