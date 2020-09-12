#include <chrono>
#include <ctime>
#include <filesystem>
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

bool shouldSkip(std::filesystem::directory_entry const& dir, std::string const& fileName)
{
  return dir.is_directory() || fileName == APP_NAME;
}

std::vector<Azure::Storage::Blobs::BlobItem>::iterator findBlob(
    std::vector<Azure::Storage::Blobs::BlobItem>& source,
    std::function<bool(std::vector<Azure::Storage::Blobs::BlobItem>::iterator)> Fn)
{
  auto find = source.begin();
  for (; find != source.end(); find++)
  {
    if (Fn(find))
    {
      return find;
    }
  }
  return find;
}
