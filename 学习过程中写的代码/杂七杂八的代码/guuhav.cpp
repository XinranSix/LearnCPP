#include <utility>
#include <functional>
#include <type_traits>
#include <string_view>
#include <gtest/gtest.h>
#include <meta/factory.hpp>
#include <meta/meta.hpp>
#include <meta/policy.hpp>

template <typename Type>
void set(Type &prop, Type value) {
    prop = value;
}

template <typename Type>
Type get(Type &prop) {
    return prop;
}

enum class properties { prop_int, prop_bool };

struct empty_type {
    virtual ~empty_type() = default;

    static void destroy(empty_type &) {
        ++counter;
    }

    inline static int counter = 0;
};

struct fat_type : empty_type {
    fat_type() = default;

    fat_type(int *value) : foo { value }, bar { value } {
    }

    int *foo { nullptr };
    int *bar { nullptr };

    bool operator==(const fat_type &other) const {
        return foo == other.foo && bar == other.bar;
    }
};

union union_type {
    int i;
    double d;
};

struct base_type {
    virtual ~base_type() = default;
};

struct derived_type : base_type {
    derived_type() = default;

    derived_type(const base_type &, int value, char character)
        : i { value }, c { character } {
    }

    int f() const {
        return i;
    }
    static char g(const derived_type &type) {
        return type.c;
    }

    const int i {};
    const char c {};
};

derived_type derived_factory(const base_type &, int value) {
    return { derived_type {}, value, 'c' };
}

struct data_type {
    int i { 0 };
    const int j { 1 };
    inline static int h { 2 };
    inline static const int k { 3 };
    empty_type empty {};
    int v { 0 };
};

struct array_type {
    static inline int global[3];
    int local[3];
};

struct func_type {
    int f(const base_type &, int a, int b) {
        return f(a, b);
    }
    int f(int a, int b) {
        value = a;
        return b * b;
    }
    int f(int v) const {
        return v * v;
    }
    void g(int v) {
        value = v * v;
    }

    static int h(int &v) {
        return (v *= value);
    }
    static void k(int v) {
        value = v;
    }

    int v(int v) const {
        return (value = v);
    }
    int &a() const {
        return value;
    }

    inline static int value = 0;
};

struct setter_getter_type {
    int value {};

    int setter(int val) {
        return value = val;
    }
    int getter() {
        return value;
    }

    int setter_with_ref(const int &val) {
        return value = val;
    }
    const int &getter_with_ref() {
        return value;
    }

    static int static_setter(setter_getter_type &type, int value) {
        return type.value = value;
    }
    static int static_getter(const setter_getter_type &type) {
        return type.value;
    }
};

struct not_comparable_type {
    bool operator==(const not_comparable_type &) const = delete;
};

bool operator!=(const not_comparable_type &,
                const not_comparable_type &) = delete;

struct an_abstract_type {
    virtual ~an_abstract_type() = default;
    void f(int v) {
        i = v;
    }
    virtual void g(int) = 0;
    int i {};
};

struct another_abstract_type {
    virtual ~another_abstract_type() = default;
    virtual void h(char) = 0;
    char j {};
};

struct concrete_type : an_abstract_type, another_abstract_type {
    void f(int v) {
        i = v * v;
    } // hide, it's ok :-)
    void g(int v) override {
        i = -v;
    }
    void h(char c) override {
        j = c;
    }
};

struct Meta : public ::testing::Test {
    static void SetUpTestCase() {
        meta::reflect<double>().conv<int>();
        std::hash<std::string_view> hash {};

        meta::reflect<char>(hash("char"),
                            std::make_pair(properties::prop_int, 42))
            .data<&set<char>, &get<char>>(hash("value"));

        meta::reflect<properties>()
            .data<properties::prop_bool>(hash("prop_bool"))
            .data<properties::prop_int>(hash("prop_int"))
            .data<&set<properties>, &get<properties>>(hash("value"));

        meta::reflect<unsigned int>()
            .data<0u>(hash("min"))
            .data<100u>(hash("max"));

        meta::reflect<base_type>(hash("base"));

        meta::reflect<derived_type>(hash("derived"),
                                    std::make_pair(properties::prop_int, 99))
            .base<base_type>()
            .ctor<const base_type &, int, char>(
                std::make_pair(properties::prop_bool, false))
            .ctor<&derived_factory>(std::make_pair(properties::prop_int, 42))
            .conv<&derived_type::f>()
            .conv<&derived_type::g>();

        meta::reflect<empty_type>(hash("empty")).dtor<&empty_type::destroy>();

        meta::reflect<fat_type>(hash("fat"))
            .base<empty_type>()
            .dtor<&fat_type::destroy>();

        meta::reflect<data_type>(hash("data"))
            .data<&data_type::i, meta::as_alias_t>(
                hash("i"), std::make_pair(properties::prop_int, 0))
            .data<&data_type::j>(hash("j"),
                                 std::make_pair(properties::prop_int, 1))
            .data<&data_type::h>(hash("h"),
                                 std::make_pair(properties::prop_int, 2))
            .data<&data_type::k>(hash("k"),
                                 std::make_pair(properties::prop_int, 3))
            .data<&data_type::empty>(hash("empty"))
            .data<&data_type::v, meta::as_void_t>(hash("v"));

        meta::reflect<array_type>(hash("array"))
            .data<&array_type::global>(hash("global"))
            .data<&array_type::local>(hash("local"));

        meta::reflect<func_type>(hash("func"))
            .func<static_cast<int (func_type::*)(const base_type &, int, int)>(
                &func_type::f)>(hash("f3"))
            .func<static_cast<int (func_type::*)(int, int)>(&func_type::f)>(
                hash("f2"), std::make_pair(properties::prop_bool, false))
            .func<static_cast<int (func_type::*)(int) const>(&func_type::f)>(
                hash("f1"), std::make_pair(properties::prop_bool, false))
            .func<&func_type::g>(hash("g"),
                                 std::make_pair(properties::prop_bool, false))
            .func<&func_type::h>(hash("h"),
                                 std::make_pair(properties::prop_bool, false))
            .func<&func_type::k>(hash("k"),
                                 std::make_pair(properties::prop_bool, false))
            .func<&func_type::v, meta::as_void_t>(hash("v"))
            .func<&func_type::a, meta::as_alias_t>(hash("a"));

        meta::reflect<setter_getter_type>(hash("setter_getter"))
            .data<&setter_getter_type::static_setter,
                  &setter_getter_type::static_getter>(hash("x"))
            .data<&setter_getter_type::setter, &setter_getter_type::getter>(
                hash("y"))
            .data<&setter_getter_type::static_setter,
                  &setter_getter_type::getter>(hash("z"))
            .data<&setter_getter_type::setter_with_ref,
                  &setter_getter_type::getter_with_ref>(hash("w"));

        meta::reflect<an_abstract_type>(
            hash("an_abstract_type"),
            std::make_pair(properties::prop_bool, false))
            .data<&an_abstract_type::i>(hash("i"))
            .func<&an_abstract_type::f>(hash("f"))
            .func<&an_abstract_type::g>(hash("g"));

        meta::reflect<another_abstract_type>(
            hash("another_abstract_type"),
            std::make_pair(properties::prop_int, 42))
            .data<&another_abstract_type::j>(hash("j"))
            .func<&another_abstract_type::h>(hash("h"));

        meta::reflect<concrete_type>(hash("concrete"))
            .base<an_abstract_type>()
            .base<another_abstract_type>()
            .func<&concrete_type::f>(hash("f"));
    }

    static void SetUpAfterUnregistration() {
        meta::reflect<double>().conv<float>();
        std::hash<std::string_view> hash {};

        meta::reflect<derived_type>(
            hash("my_type"), std::make_pair(properties::prop_bool, false))
            .ctor<>();

        meta::reflect<another_abstract_type>(hash("your_type"))
            .data<&another_abstract_type::j>(hash("a_data_member"))
            .func<&another_abstract_type::h>(hash("a_member_function"));
    }

    void SetUp() override {
        empty_type::counter = 0;
        func_type::value = 0;
    }
};

int main(int argc, char *argv[]) {

    std::hash<std::string_view> hash {};
    auto factory = meta::reflect<my_type>(hash("reflected_type"));

    meta::reflect<my_type>(hash("reflected")).dtor<&destroy>();

    return 0;
}
