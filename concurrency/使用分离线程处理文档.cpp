#include <iostream>
#include <string>

void open_document_and_display_gui(std::string const &filename) {}

bool done_editing() { return true; }

void edit_document(std::string const &filename) {
    open_document_and_display_gui(filename);
    while (!done_editing()) {
        if (true) {
        } else {
        }
    }
}

int main(int arvc, char *argv[]) { return 0; }
