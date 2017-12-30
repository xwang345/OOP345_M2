#include <iostream>
#include <string>
#include <fstream>
#include <istream>
#include "Utilities.h"

char Utilities::delimiter = 0;
std::ofstream Utilities::logFile;

//Default Constructor.  Default Field Width size is 1
Utilities::Utilities(): field_width(1){}

//Get Field Width.  Default is 1
size_t Utilities::getFieldWidth() const {
    return field_width;
}

const std::string Utilities::nextToken(const std::string& s, size_t& t, bool& b) {
    std::string token;

    //mark the job complete if there are no more tokens to be extracted.
    while (t < s.size()) {
        if (s.at(t) == delimiter) { t++;  break; }
        token += s.at(t);
        t++;
    }

    //Trim leading whitespaces
    while (*(token.begin()) == space) {
        token.erase(token.begin());
    }

    //Trim trailing whistespaces
    while (*(token.end() - 1) == space) {
        token.erase(token.end() - 1);
    }

    field_width = token.size();
    return std::move(token);
}

//Sets delimiter
void Utilities::setDelimiter(const char d) {
    delimiter = d;
}

//Opens and sets the File Object
void Utilities::setLogFile(const char* filename) {
    if (!filename) {
        throw std::string("Filename variable is empty");
    }

    logFile.open(filename, logFile.out | logFile.trunc);
    if (!logFile) throw std::string("Error opening file");
}


//Get the file stream
std::ofstream& Utilities::getLogFile() {
    return logFile;
}