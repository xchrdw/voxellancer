#pragma once
#include <map>
#include <regex>
#include <functional>

#include <glow/logging.h>

#include "property.hpp"

template <class T> 
class PropertyCollection {

public:
    PropertyCollection(std::regex regex, std::function<T(const std::string&)> converter);
    virtual ~PropertyCollection();

    void registerProp(Property<T> * prop);
    void unregisterProp(Property<T> * prop);
    bool update(const std::string & key, const std::string & svalue);

private:
    std::map<std::string, T> m_values;
    std::multimap<std::string, Property<T> *> m_properties;
    std::regex m_regex;
    std::function<T(const std::string&)> m_converter;

};

template <class T>
PropertyCollection<T>::PropertyCollection(std::regex regex, std::function<T (const std::string&)> converter) :
    m_values(),
    m_properties(),
    m_regex(regex),
    m_converter(converter)
{

}

template <class T>
PropertyCollection<T>::~PropertyCollection()
{

}

template <class T>
bool PropertyCollection<T>::update(const std::string & key, const std::string & svalue) {
    if (!std::regex_match(svalue, m_regex)) {
        return false;
    } 

    T tvalue = m_converter(svalue);

    m_values[key] = tvalue;
    auto result = m_properties.equal_range(key);
    for (auto iter = result.first; iter != result.second; ++iter)
    {
        Property<T> * prop = (*iter).second;
        prop->set(tvalue);
    }
    return true;
}


template <class T>
void PropertyCollection<T>::registerProp(Property<T> * prop)
{
    m_properties.insert(std::pair<std::string, Property<T> *>(prop->name(), prop));
    auto iter = m_values.find(prop->name());
    if (iter != m_values.end()) {
        prop->set(iter->second);
    }
    else {
        glow::debug("PropertyCollection: could not find a value for %;", prop->name());
    }
}


template <class T>
void PropertyCollection<T>::unregisterProp(Property<T> * prop)
{
    auto iter = m_properties.find(prop->name());
    for (; iter != m_properties.end(); ++iter) {
        if (iter->second == prop) {
            m_properties.erase(iter);
            break;
        }
    }
}


