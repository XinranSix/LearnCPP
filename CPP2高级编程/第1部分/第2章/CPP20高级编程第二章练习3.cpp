#include <iostream>
#include <string>
#include <format>
#include <string_view>

std::string replaceString(std::string_view haystack, std::string_view needle,
                          std::string_view replacement) {
    std::string result{haystack};

    auto position{result.find(needle)};
    while (position != std::string::npos) {
        result.replace(position, needle.length(), replacement);
        position = result.find(needle, position + needle.size() - 1);
    }

    return result;
}

int main(int argc, char *argv[]) {
    using namespace std;

    // Ask for the source string (= haystack).
    string haystack;
    cout << "Enter source string: ";
    getline(cin, haystack);

    // Ask for the string to find (= needle).
    string needle;
    cout << "Enter string to find: ";
    getline(cin, needle);

    // Ask for the replacement string.
    string replacement;
    cout << "Enter replacement string: ";
    getline(cin, replacement);

    // Call the replace function.
    string result{replaceString(haystack, needle, replacement)};

    // Print out all the strings for verification.
    cout << "Haystack: " << haystack << endl;
    cout << "Needle: " << needle << endl;
    cout << "Replacment: " << replacement << endl;
    cout << "Result: " << result << endl;

    return 0;
}
