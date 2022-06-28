//
// Created by cheily on 17.06.2022.
//

#include "../include/IniParser.hpp"

auto IniParser::trim(std::string & str) -> std::string & {
    return trim(str, " \t\n\r\f\v");
}

auto IniParser::trim(std::string & str, const char * c) -> std::string & {
    return str = str.erase(0, str.find_first_not_of(c)).erase(str.find_last_not_of(c) + 1);
}

auto IniParser::trimSection(std::string & str) -> std::string & {
    return str = str.substr(1, str.length() - 2);
}

auto IniParser::split(const std::string & str) -> std::pair<std::string, std::string> {
    return split(str, "=:");
}

auto IniParser::split(const std::string & str, const char * c) -> std::pair<std::string, std::string> {
    std::string left, right;
    left = str.substr(0, str.find_first_of(c));
    int f = str.find_last_of(c);
    right = (f == std::string::npos) ? "" : str.substr(f + 1);

    return {left, right};
}

auto IniParser::climbHierarchy(IniSection * currentContext, int level) -> IniSection * {
    while (level > 0 && currentContext->getParent() != nullptr) {
        currentContext = currentContext->getParent();
        --level;
    }
    return currentContext;
}


IniParser::IniParser() : rcomment(comment), rentry(entry), rsection(section), rsubsection(subsection) {}

auto IniParser::parse(const std::string & path) -> std::unique_ptr<IniSection> {
    std::ifstream file(path);
    if (!file) return nullptr;

    auto global = std::make_unique<IniSection>(nullptr);

    IniSection * temp = global.get();
    std::string line;

    while (std::getline(file, line)) {
        trim(line);

        if (std::regex_match(line, rcomment)) {
            if ( (trim( line = split(line, "#;").first) ).empty() ) continue;   //assign the part before comment token to line, go to next line if it's empty, continue with the assigned value otherwise
        }


        if (std::regex_match(line, rsection)) {
            trimSection(line);
            trim(line);
            if (line.empty()) throw EmptyIdentifierException(EmptyIdentifierException::SECTION);

            temp = global->makeSection(line, global.get());

        } else if (std::regex_match(line, rsubsection)) {
            trimSection(line);                          //matching rsubsection means the text inside brackts will be at least 2 characters long
            if (line[line.length() - 1] == '.') throw EmptyIdentifierException(EmptyIdentifierException::SUBSECTION);

            auto pair = split(line, ".");

            if (pair.first == "") {
                // TODO [..anotherBranch.child]
                int lv = (int) line.find_first_not_of('.') - 1;
                auto parent = climbHierarchy(temp, lv);
                temp = parent->makeSection(pair.second, parent);

            } else {
                //TODO multi . operators
            }


        } else if (std::regex_match(line, rentry)) {
            auto pair = split(line);
            trim(pair.first);
            trim(pair.second);

            if (pair.first.empty()) throw EmptyIdentifierException(EmptyIdentifierException::KEY);

            temp->put(pair.first, pair.second);
        }

    }

    return global;
}
