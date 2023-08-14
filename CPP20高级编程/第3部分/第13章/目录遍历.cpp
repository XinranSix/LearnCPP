#include <filesystem>
#include <format>
#include <iostream>
#include <string>

void printDirectoryStructure(std::filesystem::path const &p) {
    if (!std::filesystem::exists(p)) {
        return;
    }

    std::filesystem::recursive_directory_iterator begin { p };
    std::filesystem::recursive_directory_iterator end {};
    for (auto iter { begin }; iter != end; ++iter) {
        const std::string spacer(iter.depth() * 2, ' ');

        auto &entry { *iter };

        if (std::filesystem::is_regular_file(entry)) {
            std::cout << std::format("{}File: {} ({} bytes)", spacer,
                                     entry.path().string(),
                                     std::filesystem::file_size(entry))
                      << std::endl;
        } else if (std::filesystem::is_directory(entry)) {
            std::cout << std::format("{}Dir: {}", spacer, entry.path().string())
                      << std::endl;
        }
    }
}

void printDirectoryStructure1(std::filesystem::path const &p,
                              size_t level = 0) {
    if (!std::filesystem::exists(p)) {
        return;
    }

    const std::string spacer(level * 2, ' ');

    if (std::filesystem::is_regular_file(p)) {
    } else if (std::filesystem::is_directory(p)) {
        std::cout << std::format("{}Dir: {}", spacer, p.string()) << std::endl;
        for (auto &entry : std::filesystem::directory_iterator { p }) {
            printDirectoryStructure1(entry, level + 1);
        }
    }
}

int main(int argc, char *argv[]) {

    printDirectoryStructure("../../");
    std::cout << std::endl;
    printDirectoryStructure1("../../");

    return 0;
}
