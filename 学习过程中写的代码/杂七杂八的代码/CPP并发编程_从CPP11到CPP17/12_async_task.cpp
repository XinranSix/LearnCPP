#include <cmath>
#include <future>
#include <iostream>

using namespace std;

static const int MAX = 10e8;
static double sum { 0 };

void worker(int min, int max) {
    for (int i { min }; i <= max; ++i) {
        sum += std::sqrt(i);
    }
}

class Worker {
public:
    Worker(int min, int max) : mMin(min), mMax(max) {} // ①
    double work() {                                    // ②
        mResult = 0;
        for (int i = mMin; i <= mMax; i++) {
            mResult += sqrt(i);
        }
        return mResult;
    }
    double getResult() { return mResult; }

private:
    int mMin;
    int mMax;
    double mResult;
};

int main(int argc, char *argv[]) {

    sum = 0;
    auto f1 { std::async(worker, 0, MAX) };
    std::cout << "Async task triggered" << std::endl;
    f1.wait();
    std::cout << "Async task finish, result: " << sum << std::endl << std::endl;

    // double result = 0;
    // cout << "Async task with lambda triggered, thread: "
    //      << this_thread::get_id() << endl;
    // auto f2 = async(launch::async, [&result]() {
    //     cout << "Lambda task in thread: " << this_thread::get_id() << endl;
    //     for (int i = 0; i <= MAX; i++) {
    //         result += sqrt(i);
    //     }
    // });
    // f2.wait();
    // cout << "Async task with lambda finish, result: " << result << endl << endl;

    Worker w(0, MAX);
    cout << "Task in class triggered" << endl;
    auto f3 = async(&Worker::work, &w); // ③
    f3.wait();  
    cout << "Task in class finish, result: " << w.getResult() << endl << endl;

    return 0;
}
