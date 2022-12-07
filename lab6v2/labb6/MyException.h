#ifndef MYEXCEPTION_H
#define MYEXCEPTION_H

#include <sstream>

#define MYEXCEPTION(msg) MyException(msg, __FILE__, __LINE__)

inline void MyException(const std::string& msg,
                        char* file,
                        unsigned line){
    std::stringstream ss;
    ss << msg << " at " << file << ":" << line;
    throw std::runtime_error(ss.str());
}

#endif // MYEXCEPTION_H
