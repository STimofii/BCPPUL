#include "bcppul/file_utils.h"

namespace bcppul {
    std::vector<std::string> getFilesInDirectory(std::string path, bool recursively, std::vector<std::string>& files) {
        try {
            for (const auto& entry : std::filesystem::directory_iterator(path)) {
                if (std::filesystem::is_regular_file(entry.path())) {
                    files.push_back(entry.path().generic_string());
                }
                else if (std::filesystem::is_directory(entry.path())) {
                    if (recursively) {
                        getFilesInDirectory(entry.path().generic_string(), true, files);
                    }
                }
            }
        }
        catch (const  std::filesystem::filesystem_error& exception) {
            std::cerr << "Error while working with directory: " << path << " - " << exception.what() << std::endl;
        }
        return files;
    }
    std::vector<std::string> getFilesInDirectory(std::string path, bool recursively) {
        std::vector<std::string> files;
        return getFilesInDirectory(path, recursively, files);
    }
} // namespace bcppul