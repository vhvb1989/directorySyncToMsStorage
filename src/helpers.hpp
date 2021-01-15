#include <chrono>
#include <ctime>
#include <functional>

#include <iostream>
#include <string>

#ifndef APP_NAME
#define APP_NAME "storageFileSync"
#endif

template <typename TP> std::time_t toEpoch(TP tp)
{
  using namespace std::chrono;
  auto sctp = time_point_cast<system_clock::duration>(tp - TP::clock::now() + system_clock::now());
  return system_clock::to_time_t(sctp);
}
