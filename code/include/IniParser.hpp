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

    //patterns
    std::string comment = ".*[#;].*";
    std::string entry = "[^=:;#]+([=:].*)?";    //anything but reserved signs, followed by an optional assignment and value
    std::string section = R"(\[[\w\d\s"']*\])";
    std::string subsection = R"(\[.*\.+.+\])";

    std::regex rcomment;
    std::regex rentry;
    std::regex rsection;
    std::regex rsubsection;

    /**
     * Trims whitespaces
     */
    static auto trim(std::string & str) -> std::string &;

    /**
     * Trims passed chars
     */
    static auto trim(std::string & str, const char * c) -> std::string &;

    /**
     * Trims []
     */
    static auto trimSection(std::string & str) -> std::string &;

    /**
     * Splits string into two via standard k/v delimiters (:, =)
     */
    static auto split(const std::string & str) -> std::pair<std::string, std::string>;

    /**
     * Splits string into two via passed chars
     */
    static auto split(const std::string & str, const char * c) -> std::pair<std::string, std::string>;

    /**
     * Splits string into a vector of string via standard access delimiter (.)
     */
    static auto separate(const std::string & str) -> std::vector<std::string>;

    /**
     * Splits string into a vector of strings via passed delimiter
     */
     static auto separate(const std::string & str, const char * c) -> std::vector<std::string>;

    /**
     * Climbs hierarchy to the specified level
     * The specified level should not include a single reference,
     *  i.e. it should not be used for e.g. "[.sub]", but rather "[..sub]" with the level equal to 1
     * For level = 0, the function returns the passed context.
     */
    static auto climbHierarchy(IniSection * currentContext, int level) -> IniSection *;

public:
    /**
     * Ctor initializing the regex patterns from respective strings
     */
    IniParser();

    /**
     * Attempts to parse the file via the passed path. <br>
     * In future versions rather than throw, empty keys will be ignored depending on the parser config.
     * @param path
     * @returns unique_ptr to a "global" section containing global entries and all sections as subsections.
     *     <br> If no valid entry was found the section will be an empty but a valid object.
     *     <br> If the parser fails to access the path, a nullptr is returned.
     * @throws EmptyIdentifierException if section- or entry-like syntax is matched but the (section) key is empty.
     */
    auto parse(const std::string & path) -> std::unique_ptr<IniSection>;

};


#endif //INILIB_INIPARSER_HPP
