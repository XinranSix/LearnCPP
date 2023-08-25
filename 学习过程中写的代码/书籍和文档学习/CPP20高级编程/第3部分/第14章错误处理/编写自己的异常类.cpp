#include <cstddef>
#include <sstream>
#include <exception>
#include <format>
#include <iostream>
#include <string>
#include <vector>
#include <string_view>
#include <fstream>

class FileError : public std::exception {
public:
    FileError(std::string filename) : m_filename { std::move(filename) } {}

    const char *what() const noexcept override {
        return m_message.c_str();
    }

    virtual const std::string &getFilename() const noexcept {
        return m_message;
    }

protected:
    virtual void setMessage(std::string message) {
        m_message = std::move(message);
    }

private:
    std::string m_filename;
    std::string m_message;
};

class FileOpenError : public FileError {
public:
    FileOpenError(std::string filename) : FileError { std::move(filename) } {
        setMessage(std::format("Unable to open {}.", getFilename()));
    }
};

class FileReadError : public FileError {
public:
    FileReadError(std::string filename, size_t lineNumber)
        : FileError { std::move(filename) }, m_lineNumber { lineNumber } {
        setMessage(std::format("Error reading {}, line {}.", getFilename(),
                               lineNumber));
    }

    virtual size_t getLineNumber() const noexcept {
        return m_lineNumber;
    }

private:
    size_t m_lineNumber { 0 };
};

std::vector<int> readIntegerFile(std::string_view filename) {
    std::ifstream inputStream { filename.data() };
    if (!inputStream) {
        throw FileOpenError { filename.data() };
    }
    std::vector<int> integers;
    size_t lineNumber { 0 };
    while (!inputStream.eof()) {
        std::string line;
        std::getline(inputStream, line);
        ++lineNumber;

        std::istringstream lineStream { line };

        int temp {};
        while (lineStream >> temp) {
            integers.push_back(temp);
        }

        if (!lineStream.eof()) {
            throw FileReadError { filename.data(), lineNumber };
        }
    }
    return integers;
}

int main(int argc, char *argv[]) {


    
    return 0;
}
