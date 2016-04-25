//**********************************************************
//          Net Utility 1.0
//
//  Description:
//  conf �ļ������֧࣬�ָ�ʽ
//  [section]
//  key=value
//
// Author: Liu ZhaoRui
//         liuzhaorui1@163.com
//**********************************************************

#ifndef _CONFIG_PARSER_H
#define _CONFIG_PARSER_H

#include <string>
#include <map>
#include <iostream>
#include <fstream>
#include "singleton.h"

class ConfigParser;

class Section
{
    friend class ConfigParser;
    public:
        const std::string & get(const std::string key) const;
        inline void set(const std::string &key, const std::string &val)
        {   
             items[key] = val;    
        }
        void scan() const;
    private:
        std::map<std::string, std::string> items;
};


class ConfigParser
{
    //���� map �洢�� ��һ��section: key 
    //                �ڶ���item : key
    public:
        ConfigParser(){}
        virtual ~ConfigParser(){}

    bool parser_file(const std::string &file);
    const std::string & get(const std::string sectionName, const std::string keyName) const;
    
    const Section     & get(const std::string sectionName) const;

    inline void set(const std::string &sectionName, const std::string &keyName, 
        const std::string &value)
    {
        Section &section = mSections[sectionName];
        section.set(keyName,value);
    }
    void scan() const;

private:
    std::map<std::string, Section> mSections;
};


#endif
