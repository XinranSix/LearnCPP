#include <memory>
#include <iostream>
#include <gtest/gtest.h>
#include <cstdio>

struct Simple {
    Simple() { std::cout << "构造子" << std::endl; }
    ~Simple() { std::cout << "解构子" << std::endl; }
    void go() {}
};

void leaky() {
    Simple *mySimplePtr{new Simple{}};
    mySimplePtr->go();
}

void couldBeLeaky() {
    Simple *mySimplePtr{new Simple{}};
    mySimplePtr->go();
    delete mySimplePtr;
}

void notLeaky() {
    auto mySimpleSmartPtr{std::make_unique<Simple>()};
    mySimpleSmartPtr->go();

    std::unique_ptr<Simple> mySimpleSmartPtr1{new Simple{}};
}

void processData(Simple *simple) {}

struct Foo {
    Foo(std::unique_ptr<int> data) : m_data{std::move(data)} {}

    std::unique_ptr<int> m_data;
};

TEST(智能指针, unique_ptr) {
    auto mySimpleSmartPtr{std::make_unique<Simple>()};
    mySimpleSmartPtr->go();
    (*mySimpleSmartPtr).go();
    processData(mySimpleSmartPtr.get());

    mySimpleSmartPtr.reset();
    mySimpleSmartPtr.reset(new Simple);

    Simple *simple{mySimpleSmartPtr.release()};
    // 一顿操作
    delete simple;
    simple = nullptr;

    // 移动
    auto myIntSmartPtr{std::make_unique<int>(42)};
    Foo f{std::move(myIntSmartPtr)};
    // Foo f1{myIntSmartPtr}; // Error
}

TEST(智能指针, unique_ptr和C风格数组) {
    auto myVariableSizedArray{std::make_unique<int[]>(10)};
    myVariableSizedArray[1] = 123;
}

int *my_alloc(int value) { return new int{value}; }

void my_free(int *p) { delete p; }

TEST(智能指针, 自定义deleter) {
    std::unique_ptr<int, decltype(&my_free)> myIntSmartPtr{my_alloc(42),
                                                           my_free};
}

TEST(智能指针, shared_ptr) {
    auto mySimpleSmartPtr{std::make_shared<Simple>()};

    std::shared_ptr<int> myIntSmartPtr{my_alloc(42), my_free};
}

TEST(智能指针, shared_ptr存储文件指针) {

    FILE *f{nullptr};
    fopen_s(&f, "data.txt", "w");
    std::shared_ptr<FILE> filePtr{f, [](FILE *filePtr) {
                                      if (filePtr == nullptr) {
                                          return;
                                      }
                                      fclose(filePtr);
                                      std::cout << "File closed." << std::endl;
                                  }};
    if (filePtr == nullptr) {
        std::cerr << "Error opening file." << std::endl;
    } else {
        std::cout << "File opened." << std::endl;
        // Use filePtr
    }
}

TEST(智能指针, 引用计数) {
    Simple *mySimple1{new Simple{}};
    Simple *mySimple2{mySimple1};
    delete mySimple1;
    // delete mySimple2; // 错误地

    auto smartPt1{std::make_shared<Simple>()};
    auto smartPt2{smartPt1};

    // // 错误地
    // Simple *mySimple{new Simple{}};
    // std::shared_ptr<Simple> smartPtr1{mySimple};
    // std::shared_ptr<Simple> smartPtr2{mySimple};
}

TEST(智能指针, shared_ptr别名) {
    struct Foo {
        Foo(int value) : m_data{value} {}
        int m_data;
    };

    auto foo{std::make_shared<Foo>(42)};
    auto aliasing{std::shared_ptr<int>{foo, &foo->m_data}};

    std::cout << *aliasing << std::endl;
    std::cout << foo.use_count() << std::endl;
}

void useResource(std::weak_ptr<Simple> &weakSimple) {
    auto resource{weakSimple.lock()};
    if (resource) {
        std::cout << "Resource still alive." << std::endl;
    } else {
        std::cout << "Resource has been freed!" << std::endl;
    }
}

TEST(智能指针, weak_ptr) {
    auto sharedSimple{std::make_shared<Simple>()};
    std::weak_ptr<Simple> weakSimple{sharedSimple};

    std::cout << sharedSimple.use_count() << std::endl;
    useResource(weakSimple);
    sharedSimple.reset();
    std::cout << sharedSimple.use_count() << std::endl;
    useResource(weakSimple);
}

int main(int argc, char *argv[]) {

    printf("Running main() from %s\n", __FILE__);
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
    return 0;
}
