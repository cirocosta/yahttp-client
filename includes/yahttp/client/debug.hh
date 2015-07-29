#ifndef YAHTTP__CLIENT__DEBUG_HH
#define YAHTTP__CLIENT__DEBUG_HH

#ifndef NDEBUG
#   define ASSERT(condition, message) \
    do { \
        if (! (condition)) { \
            std::cerr << "Assertion `" #condition "` failed in " << __FILE__ \
                      << " line " << __LINE__ << ": " << message << std::endl; \
            std::exit(EXIT_FAILURE); \
        } \
    } while (0)

#   define LOG(message) \
    do { \
        std::cout << "LOG: " << message << std::endl; \
    } while (0)

#   define LOGERR(message) \
    do { \
        std::cerr << "LOG: " << message << std::endl; \
    } while (0)
#else
#   define ASSERT(condition, message) do { } while (0)
#   define LOG(message) do { } while (0)
#   define LOGERR(message) do { } while (0)
#endif // ! NDEBUG

#endif // ! YAHTTP__CLIENT__DEBUG_HH

