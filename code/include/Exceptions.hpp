//
// Created by cheily on 17.06.2022.
//

#ifndef INILIB_EXCEPTIONS_HPP
#define INILIB_EXCEPTIONS_HPP

#define quote(x) #x

#include <exception>

class FileStreamException : public std::logic_error {
public:
    FileStreamException() : std::logic_error("Couldn't read from assigned stream.") {}
};

class EmptyIdentifierException : public std::logic_error {
public:
    enum IDENTIFIER {
        SUBSECTION,
        SECTION,
        KEY
    };

    explicit EmptyIdentifierException(IDENTIFIER identifier) : std::logic_error(std::string("Identifier empty. Type: ") + quote(identifier)) {}
};

class SectionNotFoundException : public std::logic_error {
public:
    explicit SectionNotFoundException(const std::string & section) : std::logic_error(std::string("Section not found: ") + section) {}
};

//To be used in incomplete features like __GLOBAL__ before config rollout
class FeatureIncompleteException : public std::logic_error {
public:
    explicit FeatureIncompleteException() : std::logic_error("This feature is still in production. "
                                                             "Please refrain from using it before its full rollout. Or turn off this warning via parser config (in the future).") {}
};



#endif //INILIB_EXCEPTIONS_HPP
