//
// Created by cheily on 17.06.2022.
//

#ifndef INILIB_INIPARSER_HPP
#define INILIB_INIPARSER_HPP

#include <regex>
#include <fstream>
#include "IniSection.hpp"
#include "Exceptions.hpp"

class IniParser {
private:
    std::string path;


    //patterns
    std::string comment = ".*[#;].*";
    std::string entry = "[^=:;#]+([=:].*)?";    //anything but reserved signs, followed by an optional assignment and value
    std::string section = R"(\[[\w\d\s"']+\])";

    /**
     * Trims whitespaces
     */
    static inline auto trim(std::string & str) -> std::string &;

    /**
     * Trims passed chars
     */
    static inline auto trim(std::string & str, const char * c) -> std::string &;

    /**
     * Trims []
     */
    static inline auto trimSection(std::string & str) -> std::string &;

    /**
     * Splits string into two via standard k/v delimiters (:, =)
     */
    static inline auto split(const std::string & str) -> std::pair<std::string, std::string>;

    /**
     * Splits string into two via passed chars
     */
    static inline auto split(const std::string & str, const char * c) -> std::pair<std::string, std::string>;

public:
    /**
     * Attempts to parse the file via the passed path. <br>
     * In future versions rather than throw, empty keys will be ignored depending on the parser config.
     * @param path
     * @returns unique_ptr to a "global" section containing global entries and all sections as subsections. If no valid entry was found the section will be an empty but a valid object.
     * @throws EmptyIdentifierException if section- or entry-like syntax is found but the (section) key is empty.
     */
    auto parse(const std::string & path) -> std::unique_ptr<IniSection>;

};


#endif //INILIB_INIPARSER_HPP
