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




#endif //INILIB_EXCEPTIONS_HPP
