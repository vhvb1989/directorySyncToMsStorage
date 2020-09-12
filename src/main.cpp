#include "azure/storage/blobs/blob.hpp"

#include "helpers.hpp"

using namespace Azure::Storage::Blobs;
namespace fs = std::filesystem;

int main(int argc, char* argv[])
{
  auto currentPath = fs::current_path();
  auto mainContainerName = currentPath.filename();

  /**************** Container sdk client ************************/
  /****************   Create container  ************************/
  auto containerClient = BlobContainerClient::CreateFromConnectionString(
      std::getenv("STORAGE_CONNECTION_STRING"), mainContainerName);
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
  auto blobListResponse = containerClient.ListBlobsFlatSegment();
  auto blobList = blobListResponse.ExtractValue();

  for (auto& item : fs::directory_iterator(currentPath))
  {
    auto fileName = item.path().filename();
    if (shouldSkip(item, fileName))
    {
      continue;
    }

    /****************    Block Blob Client            **************/
    /****************  get blob from container client *************/
    auto blobClient = containerClient.GetBlockBlobClient(fileName);

    // check if file is already in storage
    auto blob = findBlob(blobList.Items, [fileName](std::vector<BlobItem>::iterator i) {
      return i->Name == fileName;
    });

    if (blob == blobList.Items.end())
    { // new File. Upload
      std::cout << std::endl << "New file: " << fileName << ". Uploading.";

      /****************    Block Blob Client            **************/
      /****************        Upload                   *************/
      blobClient.UploadFrom(item.path());

      // move on to next file
      continue;
    }

    // Remove blob from the blob list
    blobList.Items.erase(blob);
  }

  // All blobs still in bloblist need to be download
  for (auto blob : blobList.Items)
  {
    auto blobName = blob.Name;
    std::cout << std::endl << "Downloading file: " << blobName;

    /****************    Block Blob Client            **************/
    /****************        Upload                   *************/
    BlockBlobClient blobClient = containerClient.GetBlockBlobClient(blobName);
    blobClient.DownloadTo(blobName);
  }

  std::cout << std::endl << std::endl << "Sync completed " << std::endl;
  return 0;
}
