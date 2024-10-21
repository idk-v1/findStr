#include <filesystem>
#include <fstream>

#include <string>
#include <vector>

#include <iostream>
#include "CLI11.hpp"

namespace fs = std::filesystem;

int main(int argc, char* argv[])
{
    std::string string, path = ".";
    uint64_t sizeLimit;

    CLI::App app("Recursive string finder", "FindStr");
    app.add_option("string", string, "String to find in files")
        ->required();

    app.add_option("-p,--path", path, "Path to search\nDefaults to current directory")
        ->check(CLI::ExistingDirectory)
        ->default_str("../");

    app.add_option("-z,--size", sizeLimit, "Ignore files over size (bytes)\nDefaults to 0 (disabled)")
        ->transform(CLI::AsSizeValue(true))
        ->default_str("0");

    CLI11_PARSE(app, argc, argv);


    std::ifstream file;
    std::string fileLine;
    uint64_t lineNum = 0, count = 0;
    fs::recursive_directory_iterator dirIt(path);
    for (const fs::directory_entry& item : dirIt)
        if (item.is_regular_file())
        {
            if (item.file_size() > sizeLimit && sizeLimit != 0)
                std::cout << "\x1B[31mNot attempted\x1B[0m \"" << item.path().lexically_normal().string() << "\"\n";
            else
            {
                file.open(item.path().string());
                if (file.is_open())
                {
                    lineNum = 0;
                    while (std::getline(file, fileLine))
                    {
                        lineNum++;
                        if (fileLine.find(string) != std::string::npos)
                        {
                            std::cout << "\x1B[92mFound\x1B[0m at " << lineNum << ":\"" << item.path().lexically_normal().string() << "\"\n";
                            count++;
                        }
                    }
                    file.close();
                }
            }
        }

    if (count > 0)
        std::cout << "--------------------------------------\n\x1B[92mFound\x1B[0m \"" << string << "\" " << count << " times\n";
    else
        std::cout << "--------------------------------------\n\x1B[31mDid not find\x1B[0m \"" << string << "\"\n";

    return 0;
}
