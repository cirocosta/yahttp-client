#ifndef YAHTTP__UTILS_HH
#define YAHTTP__UTILS_HH
#endif

#include <chrono>
#include <ostream>

namespace yahttp {

class Timer {
  std::chrono::steady_clock::time_point m_start;
public:
  Timer ();
  ~Timer();

  void reset ();
  double elapsed () const;
  bool has_elapsed (const unsigned amount) const;
};

}; // !ns yahhtp client

