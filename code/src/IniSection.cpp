//
// Created by cheily on 11.06.2022.
//

#include "../include/IniSection.hpp"

IniSection::IniSection(IniSection * parent) : parent(parent) {}

IniSection::IniSection(IniSection && rhs)  noexcept : entries(std::move(rhs.entries)), parent(rhs.parent), subsections(std::move(rhs.subsections)) {}


auto IniSection::getParent() const -> IniSection * {
    return parent;
}

auto IniSection::size() const -> size_t {
    return entries.size() + subsections.size();
}

auto IniSection::isRoot() -> bool {
    return parent == nullptr;
}

auto IniSection::isLeaf() -> bool {
    return subsections.empty();
}

auto IniSection::get(const std::string & key) const noexcept -> std::string {
    try {
        return entries.at(key);
    } catch (std::out_of_range & ex) {
        return "";
    }
}

auto IniSection::put(const std::string & key, const std::string & value) -> std::string {
    return entries[key] = value;
}

auto IniSection::putIfNotPresent(const std::string & key, const std::string & value) -> bool {
    return ( entries.insert(std::make_pair(key, value)) ).second;
}

auto IniSection::getSection(const std::string & key) const -> IniSection * {
    try {
        return subsections.at(key).get();
    } catch (std::out_of_range & ex) {
        return nullptr;
    }
}

auto IniSection::makeSection(const std::string & key, IniSection * parent) -> IniSection * {
    return (subsections[key] = std::make_unique<IniSection>(parent)).get();
}

auto IniSection::putSection(const std::string & key, IniSection & section) -> IniSection * {
    return (subsections[key] = std::make_unique<IniSection>(std::move(section))).get();
}

