#include "azure/storage/blobs/blob.hpp"

#include <iostream>
#include <string>

using namespace Azure::Storage::Blobs;

int main()
{
    std::string containerName = "sample-container";
    std::string blobName1 = "sample-blob-1";
    std::string blobName2 = "sample-blob-2";
    std::string blobContent;
    // 50 MB
    blobContent.resize(50 * 1024ULL * 1024, 'x');

    auto containerClient = BlobContainerClient::CreateFromConnectionString(
        "",
        containerName);
    try
    {
        containerClient.Create();
    }
    catch (std::runtime_error &e)
    {
        // The container may already exist
        std::cout << e.what() << std::endl;
    }

    BlockBlobClient blobClient1 = containerClient.GetBlockBlobClient(blobName1);
    BlockBlobClient blobClient2 = containerClient.GetBlockBlobClient(blobName2);

    {
        // Upload with 1 thread. Default options
        blobClient1.UploadFrom(
            reinterpret_cast<const uint8_t *>(blobContent.data()), blobContent.size());
    }
    {
        // Upload with 16 threads. Use Options
        UploadBlockBlobFromOptions options;
        options.Concurrency = 16;
        blobClient2.UploadFrom(
            reinterpret_cast<const uint8_t *>(blobContent.data()), blobContent.size(), options);
    }

    {
        // Download with 1 thread. Default options
        blobClient1.DownloadTo(reinterpret_cast<uint8_t *>(&blobContent[0]), blobContent.size());
    }

    {
        // Download with 16 threads. Use options
        DownloadBlobToOptions options;
        options.Concurrency = 16;
        blobClient2.DownloadTo(
            reinterpret_cast<uint8_t *>(&blobContent[0]), blobContent.size(), options);
    }

    {
        // list blobs. Default options
        std::cout << "List Blobs" << std::endl;
        auto blobList = containerClient.ListBlobsFlatSegment().ExtractValue();
        for (auto blob : blobList.Items)
        {
            std::cout << "name: " << blob.Name << ". eTag: " << blob.ETag << std::endl;
        }
    }

    return 0;
}
