#include <atomic>
#include <iostream>
#include <mutex>
#include <stdexcept>

struct Database {
    static Database &intance() {
        Database *db = instance.load(std::memory_order_consume);
        if (!db) {
            std::scoped_lock lock { mtx };
            db = instance.load(std::memory_order_consume);
            if (!db) {
                db = new Database {};
                instance.store(db, std::memory_order_release);
            }
        }
        return *db;
    }

private:
    static std::atomic<Database *> instance;
    static std::mutex mtx;

public:
    Database(Database const &) = delete;
    Database(Database &&) = delete;

    Database &operator=(Database const &) = delete;
    Database &operator=(Database &&) = delete;

protected:
    Database() {}
};

int main(int argc, char *argv[]) { return 0; }
