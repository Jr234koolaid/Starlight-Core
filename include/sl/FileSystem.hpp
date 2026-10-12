// include/sl/FileSystem.hpp

#pragma once

#include <filesystem>

namespace sl
{
    using Filepath = std::filesystem::path;
}

namespace sl
{
    using DirectoryIterator          = std::filesystem::directory_iterator;
    using DirectoryRecursiveIterator = std::filesystem::recursive_directory_iterator;
    using DirectoryEntry             = std::filesystem::directory_entry;
}
