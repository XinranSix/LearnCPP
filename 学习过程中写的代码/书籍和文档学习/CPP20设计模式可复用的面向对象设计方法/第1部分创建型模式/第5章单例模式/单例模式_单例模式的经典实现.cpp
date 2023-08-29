#include <iostream>
#include <stdexcept>

struct Database {
public:
    /*
        static Database &get() {
            static Database database;
            return database;
        }
    */

    static Database &get() {
        static Database *database = new Database;
        return *database;
    }

    Database(Database const &) = delete;
    Database(Database &&) = delete;

    Database &operator=(Database const &) = delete;
    Database &operator=(Database &&) = delete;

protected:
    Database() {}
};

int main(int argc, char *argv[]) { return 0; }
