#include <iostream>
#include <mutex>
#include <stdexcept>

class hierarchical_mutex {
public:
    explicit hierarchical_mutex(unsigned long value)
        : hierarchy_value { value }, previous_hierachy_value { 0 } {}

    void lock() {
        check_for_hierarchy_violation();
        internal_mutex.lock();
        updata_hirerarchy_value();
    }

    void unlock() {
        if (this_thread_hierarchy_value != hierarchy_value) {
            throw std::logic_error { "mutex hierarchy violated" };
        }
        this_thread_hierarchy_value = previous_hierachy_value;
        internal_mutex.unlock();
    }

    bool try_lock() {
        check_for_hierarchy_violation();
        if (!internal_mutex.try_lock()) {
            return false;
        }
        updata_hirerarchy_value();
        return true;
    }

private:
    void check_for_hierarchy_violation() {
        if (this_thread_hierarchy_value <= hierarchy_value) {
            throw std::logic_error { "mutex hierarchy violated" };
        }
    }

    void updata_hirerarchy_value() {
        previous_hierachy_value = this_thread_hierarchy_value;
        this_thread_hierarchy_value = hierarchy_value;
    }

private:
    std::mutex internal_mutex;
    unsigned long const hierarchy_value;
    unsigned long previous_hierachy_value;
    static thread_local unsigned long this_thread_hierarchy_value;
};

thread_local unsigned long hierarchical_mutex::this_thread_hierarchy_value {};

hierarchical_mutex high_level_mutex { 10000 };
hierarchical_mutex low_level_mutex { 5000 };
hierarchical_mutex other_mutex { 6000 };

int do_low_level_stuff() {
    return 1;
}

int low_level_fun() {
    std::lock_guard<hierarchical_mutex> lk { low_level_mutex };
    return do_low_level_stuff();
}

void high_level_stuff(int some_param) {}

void high_level_func() {
    std::lock_guard<hierarchical_mutex> lk { high_level_mutex };
    high_level_stuff(low_level_fun());
}

void thread_a() {
    high_level_func();
}

void do_other_stuff() {}

void other_stuff() {
    high_level_func();
    do_other_stuff();
}

void thread_b() {
    std::lock_guard<hierarchical_mutex> lk { other_mutex };
    other_stuff();
}

int main(int argc, char *argv[]) {
    return 0;
}
