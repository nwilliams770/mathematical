#ifndef LOGGING_HPP
#define LOGGING_HPP

#include <string>
#include <iostream>
#include <sstream>
#include <vector>

// Function to log a message
inline void logMessage(const std::string& msg) {
    std::cout << msg << std::endl;
}

#ifdef NDEBUG
    #define LOG(msg) // No-op in release mode
    #define LOG_ARGS(msg, ...) // No-op in release mode
#else
    #define LOG(msg) \
        do { \
            std::ostringstream os; \
            os << msg; \
            log_helper(os); \
        } while (0)

    #define LOG_ARGS(msg, ...) \
        do { \
            std::ostringstream os; \
            os << msg; \
            log_helper(os, __VA_ARGS__); \
        } while (0)
#endif

inline void log_helper(std::ostringstream &os) {
    logMessage(os.str());
}

template<typename T>
inline void log_element(std::ostringstream &os, const T& element) {
    os << element;
}

// Specialization for std::vector
template<typename T>
inline void log_element(std::ostringstream &os, const std::vector<T>& vec) {
    os << "[";
    for (size_t i = 0; i < vec.size(); ++i) {
        log_element(os, vec[i]);
        if (i != vec.size() - 1) {
            os << ", ";
        }
    }
    os << "]";
}

template<typename T, typename... Args>
inline void log_helper(std::ostringstream &os, T first, Args... args) {
    os << " ";
    log_element(os, first);
    log_helper(os, args...);
}

#endif // LOGGING_HPP