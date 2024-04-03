WeChat: cstutorcs
QQ: 749389476
Email: tutorcs@163.com
#pragma once

#include <vector>
#include <string>
#include <fstream>

using namespace std;

std::string convertCStringToString(const CString& text);
CString CharToWChar(const char* sstr);

struct RouteInfo {
    RouteInfo() {

    }

    void save(std::ofstream& output) const {
        output << convertCStringToString(name) << " ";
        output << convertCStringToString(first) << " ";
        output << convertCStringToString(last) << " ";
        output << convertCStringToString(stations) << " ";
        output << std::endl;
    }

    void load(std::ifstream& input) {
        string _name;
        string _first;
        string _last;
        string _stations;

        input >> _name;
        input >> _first;
        input >> _last;
        input >> _stations;
        name = CharToWChar(_name.c_str());
        first = CharToWChar(_first.c_str());
        last = CharToWChar(_last.c_str());
        stations = CharToWChar(_stations.c_str());
    }

    CString name;
    CString first;
    CString last;
    CString stations;
};

class RouteInfoList {
public:
    RouteInfoList() {

    }

public:
    bool add(const RouteInfo& info) {
        if (!find(info.name)) {
            m_list.push_back(info);
            return true;
        } else {
            return false;
        }
    }

    bool remove(const CString& name) {
        for (std::vector<RouteInfo>::const_iterator iter = m_list.begin(); iter != m_list.end(); ++iter) {
            if (iter->name == name) {
                m_list.erase(iter);
                return true;
            }
        }
        return false;
    }

     RouteInfo* find(const CString& name) {
        for (std::vector<RouteInfo>::iterator iter = m_list.begin(); iter != m_list.end(); ++iter) {
            if (iter->name == name) {
                return &(*iter);
            }
        }
        return NULL;
    }

public:
    void saveFile(const CString& file) const {
        std::string filename = convertCStringToString(file);
        std::ofstream output(filename);
        if (output) {
            output << m_list.size() << std::endl;
            for (std::vector<RouteInfo>::const_iterator iter = m_list.begin(); iter != m_list.end(); ++iter) {
                iter->save(output);
            }
        }
    }

    void loadFile(const CString& file) {
        std::string filename = convertCStringToString(file);
        std::ifstream input(filename);
        if (input) {
            m_list.clear();
            int count = 0;
            input >> count;

            for (int index = 0; index < count; ++index) {
                RouteInfo info;
                info.load(input);
                m_list.push_back(info);
            }
        }
    }

public:
    std::vector<RouteInfo> m_list;
};

