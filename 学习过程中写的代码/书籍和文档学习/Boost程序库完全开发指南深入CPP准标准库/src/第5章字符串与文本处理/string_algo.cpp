#include <deque>
#include <iostream>
#include <gtest/gtest.h>
#include <list>
#include <ostream>
#include <string>
#include <vector>
#include "boost/algorithm/string.hpp"
#include "boost/algorithm/string/case_conv.hpp"
#include "boost/algorithm/string/classification.hpp"
#include "boost/algorithm/string/compare.hpp"
#include "boost/algorithm/string/constants.hpp"
#include "boost/algorithm/string/erase.hpp"
#include "boost/algorithm/string/find.hpp"
#include "boost/algorithm/string/find_iterator.hpp"
#include "boost/algorithm/string/finder.hpp"
#include "boost/algorithm/string/join.hpp"
#include "boost/algorithm/string/predicate.hpp"
#include "boost/algorithm/string/replace.hpp"
#include "boost/algorithm/string/split.hpp"
#include "boost/algorithm/string/trim.hpp"
#include "boost/format/format_fwd.hpp"
#include "boost/range/iterator_range_core.hpp"
#include "boost/utility/string_ref.hpp"
#include "boost/format.hpp"
#include "boost/assign.hpp"
#include "boost/assign/list_inserter.hpp"
#include "boost/assign/list_of.hpp"
#include "boost/utility/string_ref_fwd.hpp"

TEST(string_algo, 简单示例) {
    std::string str { "readme.txt" };

    if (boost::ends_with(str, "txt")) {
        std::cout << boost::to_upper_copy(str) + " UPPER" << std::endl;
        assert(boost::ends_with(str, "txt"));
    }

    boost::replace_first(str, "readme", "followme");
    std::cout << str << std::endl;

    std::vector<char> v { begin(str), end(str) };
    std::vector<char> v2 =
        boost::to_upper_copy(boost::erase_first_copy(v, "txt"));
    for (auto ch : v2) {
        std::cout << ch;
    }
    std::endl(std::cout);
}

/*
string_algo库中的算法命名遵循了标准库的惯例，算法名均为小
写形式，并使用不同的词缀来区分不同的版本，命名规则如下。
    ■ 前缀i：大小写不敏感（忽略大小写），否则是大小写敏感的。
    ■ 后缀_copy：不变动输入，返回处理结果的拷贝，否则原地处理，输入即输出。
    ■ 后缀_if：需要一个作为判断式的谓词函数对象，否则使用默认的判断准则。

string_algo库提供的算法共有五大类。
    ■ 大小写转换。
    ■ 判断式与分类。
    ■ 修剪。
    ■ 查找与替换。
    ■ 分割与合并。
接下来将对这些算法进行详细介绍（但不包含regex库的相关算法）。
*/

TEST(string_algo, 大小写转换) {
    // to_upper() 和to_lower()。
    std::string str { "FireEmblem Heroes\n" };
    std::cout << boost::to_upper_copy(str) << std::endl;
    std::cout << str << std::endl;
    boost::to_lower(str);
    std::cout << str << std::endl;
}

TEST(string_algo, 判断式_算法) {
    /*
判断式可以检测两个字符串之间的关系，包括以下几种:
    ■ lexicographical_compare：根据字典顺序检测一个字符串是否小于另一个字符串。
    ■ starts_with：检测字符串是否以另一个字符串为前缀。
    ■ ends_with：检测字符串是否以另一个字符串为后缀。
    ■ contains：检测字符串是否包含另一个字符串。
    ■ equals：检测两个字符串是否相等。
    ■ all：检测字符串是否满足指定的判断式
    */
    std::string str { "Power Bomb" };

    assert(boost::iends_with(str, "bomb"));
    assert(!boost::ends_with(str, "bomb"));

    assert(boost::starts_with(str, "Pow"));

    assert(boost::contains(str, "er"));

    std::string str2 { boost::to_lower_copy(str) };
    assert(boost::iequals(str, str2));

    std::string str3 { "power suit" };
    assert(boost::ilexicographical_compare(str, str3));

    assert(all(str2.substr(0, 5), boost::is_lower()));
}

TEST(string_algo, 判断式_函数对象) {
    /*
    string_algo 增强了标准库中的equal_to 和 less 函数对象，允
    许对不同类型的字符串进行比较，并提供大小写无关的形式。这些函
    数对象如下。
        ■ is_equal：与equals算法类似，比较两个对象是否相等。
        ■ is_less：比较两个对象是否具有小于关系。
        ■ is_not_greater：比较两个对象是否具有不大于关系。
    */

    std::string str1 { "Samus" }, str2 { "samus" };

    assert(!boost::is_equal {}(str1, str2));
    assert(boost::is_less {}(str1, str2));

    assert(!boost::is_equal {}(str1, boost::string_ref(str2)));
}

TEST(string_algo, 分类) {
    /*
string_algo提供一组分类函数，可以用于检测一个字符是否符合
某种特性，主要用于搭配其他算法：
    ■ is_space：字符是否为空格或制表符（tab）。
    ■ is_alnum：字符是否为字母和数字字符。
    ■ is_alpha：字符是否为字母。
    ■ is_cntrl：字符是否为控制字符。
    ■ is_digit：字符是否为十进制数字。
    ■ is_graph：字符是否为图形字符。
    ■ is_lower：字符是否为小写字符。
    ■ is_print：字符是否为可打印字符。
    ■ is_punct：字符是否为标点符号字符。
    ■ is_upper：字符是否为大写字符。
    ■ is_xdigit：字符是否为十六进制数字。
    ■ is_any_of：字符是否是参数字符序列中的任意字符。
    ■ if_from_range：字符是否位于指定区间内，即from <= ch <= to。
    */
}

TEST(string_algo, 修剪) {
    // string_algo提供三个修剪算法：trim_left、trim_right和trim
    boost::format fmt { "|%s|\n" };

    std::string str { " samus aran " };
    std::cout << fmt % boost::trim_copy(str) << std::endl;
    std::cout << fmt % boost::trim_left_copy(str) << std::endl;

    boost::trim_right(str);
    std::cout << fmt % str << std::endl;

    std::string str2 { "2020 Happy new Year!!!" };

    std::cout << fmt % boost::trim_left_copy_if(str2, boost::is_digit())
              << std::endl;
    std::cout << fmt % boost::trim_right_copy_if(str2, boost::is_punct())
              << std::endl;
    std::cout << fmt % boost::trim_copy_if(str2, boost::is_punct() ||
                                                     boost::is_digit() ||
                                                     boost::is_space())
              << std::endl;
}

TEST(string_algo, 查找) {
    /*
string_algo提供的查找算法包括下列几种。
    ■ find_first：查找字符串在输入中第一次出现的位置。
    ■ find_last：查找字符串在输入中最后一次出现的位置。
    ■ find_nth：查找字符串在输入中的第N次（从0开始计数）出现的位置。
    ■ find_head：取一个字符串开头N个字符的子串，相当于substr(0, n)。
    ■ find_tail：取一个字符串末尾N个字符的子串。
    */

    boost::format fmt { "|%s|, pos = %d\n" };
    std::string str { "Long long age, there was a king." };
    boost::iterator_range<std::string::iterator> rge;

    rge = boost::find_first(str, "long");
    std::cout << fmt % rge % (rge.begin() - str.begin()) << std::endl;

    rge = boost::ifind_first(str, "long");
    std::cout << fmt % rge % (rge.begin() - str.begin()) << std::endl;

    rge = boost::find_nth(str, "ng", 2);
    std::cout << fmt % rge % (rge.begin() - str.begin()) << std::endl;

    rge = boost::find_head(str, 4);
    std::cout << fmt % rge % (rge.begin() - str.begin()) << std::endl;

    rge = boost::find_tail(str, 5);
    std::cout << fmt % rge % (rge.begin() - str.begin()) << std::endl;

    rge = boost::find_first(str, "samus");
    assert(rge.empty() && !rge);
}

TEST(string_algo, 替换与删除) {
    /*
    替换、删除操作与查找算法非常接近，是在查找到结果后再对字
符串进行处理，所以它们的算法名称很相似，具体如下。
    ■ replace/erase_first：替换/删除字符串在输入中的第一次出现。
    ■ replace/erase_last：替换/删除字符串在输入中的最后一次出现。
    ■ replace/erase_nth：替换/删除字符串在输入中的第n次出现。
    ■ replace/erase_all：替换/删除字符串在输入中的所有出现。
    ■ replace/erase_head：替换/删除输入的开头。
    ■ replace/erase_tail：替换/删除输入的末尾。
上述算法是一个相当大的家族。前8个算法每个都有前缀i、后缀_copy的组合，有四个版本，后4个则只有后缀_copy的两个版本。
    */

    std::string str { "Samus beat the monster.\n" };

    std::cout << boost::replace_first_copy(str, "Samus", "samus") << std::endl;

    boost::replace_last(str, "beat", "kill");
    std::cout << str << std::endl;

    boost::replace_tail(str, 9, "ridley.\n");
    std::cout << str << std::endl;

    std::cout << boost::ierase_all_copy(str, "samus") << std::endl;
    std::cout << boost::replace_nth_copy(str, "l", 1, "L") << std::endl;
    std::cout << boost::erase_tail_copy(str, 8) << std::endl;
}

TEST(string_algo, 分割) {
    /*
    string_algo 提供了两个字符串分割算法：find_all（虽然它的
    名称含有find，但因为其功能而被归类为分割算法）和 split，可以
    使用某种策略把字符串分割成若干部分，并将分割后的字符串拷贝存
    入指定的容器。
    */
    std::string str { "Samus,Link.Zelda::Mario-Luigi+zelda" };
    std::deque<std::string> d;
    boost::ifind_all(d, str, "zELDA");
    assert(d.size() == 2);
    for (auto x : d) {
        std::cout << "{" << x << "}";
    }
    std::endl(std::cout);

    std::list<boost::iterator_range<std::string::iterator>> l;
    boost::split(l, str, boost::is_any_of(",.:-+"));
    for (auto x : l) {
        std::cout << "{" << x << "}";
    }
    std::endl(std::cout);

    l.clear();
    boost::split(l, str, boost::is_any_of(".:-"), boost::token_compress_on);
    for (auto x : l) {
        std::cout << "{" << x << "}";
    }
    std::endl(std::cout);
}

TEST(string_algo, 合并) {
    /*
    合并算法join是分割算法的逆运算，它把存储在容器中的字符串连接成一个新的字符串，并且可以指定连接的分隔符
    */
    using namespace boost::assign;
    std::vector<std::string> v = list_of("Samus")("Link")("Zelda")("Mario");

    std::cout << boost::join(v, "+") << std::endl;

    std::cout << boost::join_if(v, "**", [](boost::string_ref s) {
        return boost::contains(s, "a");
    }) << std::endl;
}

TEST(string_algo, 查找_分隔_迭代器) {
    /*
    除通用的find_all 或 split 之外，string_algo库还提供了两个
    查找迭代器find_iterator和split_iterator，它们可以在字符串中像
    迭代器那样遍历匹配，执行查找或分割，无须使用容器来容纳
    */
    std::string str { "Samus||samus||mario||||Link" };

    using string_find_iterator = boost::find_iterator<std::string::iterator>;

    string_find_iterator pos, end;

    for (pos = boost::make_find_iterator(
             str, boost::first_finder("samus", boost::is_iequal {}));
         pos != end; ++pos) {
        std::cout << "{" << *pos << "}";
    }
    std::endl(std::cout);

    using string_split_iterator = boost::split_iterator<std::string::iterator>;

    string_split_iterator p, endp;
    for (p = boost::make_split_iterator(
             str, boost::first_finder("||", boost::is_equal {}));
         p != endp; ++p) {
        std::cout << "[" << *p << "]";
    }
    std::endl(std::cout);
}

int main(int argc, char *argv[]) {
    printf("Running main() from %s\n", __FILE__);
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
