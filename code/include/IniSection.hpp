//
// Created by cheily on 11.06.2022.
//

#ifndef INILIB_INISECTION_HPP
#define INILIB_INISECTION_HPP

#include <string>
#include <memory>
#include <unordered_map>

class IniSection {
private:
//    std::string key;
    std::unordered_map<std::string, std::string> entries;

    IniSection * parent;
    std::unordered_map<std::string, std::unique_ptr<IniSection>> subsections;

public:
    /**
     * explicit ctor initializing only the parent pointer
     */
    explicit IniSection(IniSection * parent);

    /**
     * explicitly deleted copy-ctor to avoid accidental mess with unique_ptr maps
     */
    IniSection(const IniSection & copy) = delete;

    /**
     * move-ctor, moves the other object's maps to the current object
     */
    IniSection(IniSection && rhs) noexcept;


    /**
     * @returns the pointer to the parent node. nullptr if ran from global section
     */
    [[nodiscard]]
    auto getParent() const -> IniSection *;

    /**
     * @returns size of the underlying collections combined
     */
     [[nodiscard]]
     auto size() const -> size_t;

    /**
     * @returns true if there is no specified parent node
     */
     [[nodiscard]]
     auto isRoot() -> bool;

     /**
      * @returns true if there are no specified children nodes
      */
      [[nodiscard]]
      auto isLeaf() -> bool;

    /**
     * Gets value by key
     * @return empty string if no object was found
     */
    [[nodiscard]]
    auto get(const std::string & key) const noexcept -> std::string;

    /**
     * Puts key-value pair into the entries map
     * @return the stored value.
     */
    auto put(const std::string & key, const std::string & value) -> std::string;

    /**
     * Puts key-value pair only if it isn't present
     * @return true if put, false if present
     */
    auto putIfNotPresent(const std::string & key, const std::string & value) -> bool;

    /**
     * Gets subsection by key
     * @return nullptr if no object was found
     */
    [[nodiscard]]
    auto getSection(const std::string & key) const -> IniSection *;

    /**
     * Creates a new empty subsection.
     * @returns a reference to the created unique_ptr inside the map
     */
    auto makeSection(const std::string & key, IniSection * parent) -> std::unique_ptr<IniSection> &;

    /**
     * Creates a new unique_ptr from the existing section into the subsections map and returns a reference to it
     * @warning The new section is created via the move-ctor. Passed object will not contain its previous data.
     * @returns a reference to the created unique_ptr from within the map
     */
    auto putSection(const std::string & key, IniSection & section) -> std::unique_ptr<IniSection> &;

};


#endif //INILIB_INISECTION_HPP
