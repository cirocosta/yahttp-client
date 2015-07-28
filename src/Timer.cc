#include "yahttp/Timer.hh"

using namespace std::chrono;

namespace yahttp {

Timer::Timer ()
{}

Timer::~Timer ()
{}

void Timer::reset ()
{
  m_start = steady_clock::now();
}

double Timer::elapsed () const
{
  milliseconds dur = duration_cast<milliseconds>(steady_clock::now()-m_start);

  return dur.count();
}

bool Timer::has_elapsed (unsigned amount) const
{
  if (elapsed() > amount)
    return true;
  return false;
}

}; // ! ns yahttp

