#include "azure/storage/blobs.hpp"

#include "helpers.hpp"

using namespace Azure::Storage::Blobs;

int main(int argc, char* argv[])
{

  /**************** Container sdk client ************************/
  /****************   Create container  ************************/
  auto containerClient = BlobContainerClient::CreateFromConnectionString(
      std::getenv("STORAGE_CONNECTION_STRING"), "aaa");
  try
  {
    containerClient.Create();
  }
  catch (std::runtime_error& e)
  {
    std::cout << e.what() << std::endl;
  }

  /**************** Container sdk client ************************/
  /****************      list Blobs     ************************/
  // 5000 max blobs supported by call. It's fine for this app

  std::cout << std::endl << std::endl << "Sync completed " << std::endl;
  return 0;
}
