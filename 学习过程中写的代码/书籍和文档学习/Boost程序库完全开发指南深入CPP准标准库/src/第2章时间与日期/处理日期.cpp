#include <algorithm>
#include <bits/types/struct_tm.h>
#include <iostream>
#include <gtest/gtest.h>
#include <cassert>
#include <string>
#include "boost/date_time/gregorian/conversion.hpp"
#include "boost/date_time/gregorian/formatters.hpp"
#include "boost/date_time/gregorian/greg_calendar.hpp"
#include "boost/date_time/gregorian/greg_date.hpp"
#include "boost/date_time/gregorian/greg_duration_types.hpp"
#include "boost/date_time/gregorian/greg_month.hpp"
#include "boost/date_time/gregorian/greg_weekday.hpp"
#include "boost/date_time/gregorian/gregorian_types.hpp"
#include "boost/date_time/gregorian/parsers.hpp"

TEST(处理日期, 创建日期对象) {
    {
        boost::gregorian::date d1;
        boost::gregorian::date d2 { 2010, 1, 1 };
        boost::gregorian::date d3 { 2000, boost::gregorian::Jan, 1 };
        boost::gregorian::date d4 { d2 };

        assert(d1 ==
               boost::gregorian::date { boost::date_time::not_a_date_time });
        assert(d2 == d4);
        assert(d3 < d4);
    }

    {
        boost::gregorian::date d1 { boost::gregorian::from_string(
            "1999-12-31") };
        boost::gregorian::date d2 { boost::gregorian::from_string("2015/1/1") };
        boost::gregorian::date d3 { boost::gregorian::from_undelimited_string(
            "20111118") };
    }
}

TEST(处理日期, 访问日期) {
    using namespace boost::gregorian;
    date d { 2017, 6, 1 };

    // 成员函数year（）、month（）和day（）分别返回日期的年、月、日：
    assert(d.year() == 2017);
    assert(d.month() == 6);
    assert(d.day() == 1);

    // 成员函数year_month_day（）返回一个date：：ymd_type结构，可以一次性地获取年、月、日数据
    date::ymd_type ymd { d.year_month_day() };
    assert(ymd.year == 2017);
    assert(ymd.month == 6);
    assert(ymd.day == 1);

    // 成员函数day_of_week() 返回date的星期数，0表示星期天。
    // day_of_year() 返回date是当年的第几天（最大值是366）。
    // end_of_month() 返回当月的最后一天的date对象：
    std::cout << d.day_of_week() << std::endl; // 4
    std::cout << d.day_of_year() << std::endl; // 152
    assert(d.end_of_month() == (date { 2017, 6, 30 }));

    // 成员函数week_number() 返回date所在的周是当年的第几周，其范围是0～53：
    std::cout << date { 2015, 1, 10 }.week_number() << std::endl;
    std::cout << date { 2016, 1, 10 }.week_number() << std::endl;
    std::cout << date { 2017, 1, 10 }.week_number() << std::endl;

    /*
    date还有5个is_xxx() 函数，用于检验日期是否是一个特殊日期，具体如下。
        ■ is_infinity()：是否是一个无限日期。
        ■ is_neg_infinity()：是否是一个负无限日期。
        ■ is_pos_infinity()：是否是一个正无限日期。
        ■ is_not_a_date()：是否是一个无效日期。
        ■ is_special()：是否是任意一个特殊日期。
    */
    assert(date { pos_infin }.is_infinity());
    assert(date { pos_infin }.is_pos_infinity());
    assert(date { neg_infin }.is_neg_infinity());
    assert(date { not_a_date_time }.is_not_a_date());
    assert(date { not_a_date_time }.is_special());
    assert(!date(2017, 5, 31).is_special());
}

TEST(处理日期, 日期的输出) {
    /*
    可以将date对象很方便地转换成字符串，它提供了3个自由函数。
        ■ to_simple_string()：转换为YYYY-mmm-DD 格式的字符串，
        其中，mmm为3字符的英文月份名。
        ■ to_iso_string()：转换为YYYYMMDD格式的数字字符串。
        ■ to_iso_extended_string()：转换为YYYY-MM-DD格式的数字字符串。
    */

    // date也支持流输入输出，默认使用YYYY-mmm-DD格式。例如：
    using namespace boost::gregorian;
    date d { 2017, 1, 23 };

    std::cout << to_simple_string(d) << std::endl;
    std::cout << to_iso_string(d) << std::endl;
    std::cout << to_iso_extended_string(d) << std::endl;
    // std::cout << d << std::endl; // Error
    // std::cin >> d; // Error
}

TEST(处理日期, 转换C结构) {
    // date支持与C语言中的tm结构相互转换，转换的规则和函数如下。
    /*
    ■ to_tm(date)：date转换到tm。
    将tm的时、分、秒成员（tm_hour/tm_min/tm_sec）均置为0，将夏令时标志tm_isdst置为-1（表示未知）。
    ■ date_from_tm(datetm)：tm 转换到
    date。只使用年、月、日3个成员（tm_year/tm_mon/tm_mday）， 其他成员均被忽略
    */
    using namespace boost::gregorian;
    date d { 2017, 5, 20 };
    tm t = to_tm(d);
    assert(t.tm_hour == 0 && t.tm_min == 0);
    assert(t.tm_year == 117 && t.tm_mday == 20); // 貌似是从 1900年开始算的

    date d2 { date_from_tm(t) };
    assert(d == d2);
}

TEST(处理日期, 日期长度) {
    /*
    日期长度是以天为单位的时长，是度量时间长度的一个标量。
    它与日期不同，其值可以是任意整数，可正可负。
    基本的日期长度类是date_duration
    */
    /*
    date_duration支持全序比较操作（==、！=、＜、＜=等），也支
    持完全的加减法和递增递减操作，用起来很像一个整数。此外date_du
    ration还支持除法运算，可以除以一个整数，但不能除以另一个date_
    duration，它不支持其他的数学运算，如乘法、取模、取余等。
    */
    /// date_time库为date_duration定义了一个常用的typedef：days
    using namespace boost::gregorian;
    days dd1 { 10 }, dd2 { -100 }, dd3 { 255 };

    assert(dd1 > dd2 && dd1 < dd3);
    assert(dd1 + dd2 == days(-90));
    assert((dd1 + dd3).days() == 265);
    assert(dd3 / 5 == days(51));

    /*
    为了方便计算时间长度，date_time库还提供了months、years、weeks3个时长类，
    分别用来表示月、年和星期，它们的含义与days类似，但其行为不太相同
    */
    /*
    months和 years全面支持加减乘除运算，使用成员函数
    number_of_months()和number_of_years()可获得表示的月数和年数。
    weeks是date_duration的子类，除构造函数以7为单位以外，其他的行为与days完全相同，可以说它是days的近义词
    */
    weeks w { 3 }; // 3 个星期
    assert(w.days() == 21);

    months m { 5 }; // 5 个月
    years y { 2 };  // 2 年

    months m2 { y + m }; // 2 年零 5 个月
    assert(m2.number_of_months() == 29);
    assert((y * 2).number_of_years() == 4);
}

TEST(处理日期, 日期运算) {
    /*
    date 支持加减运算，但两个date
    对象的加法操作是无意义的 date_time库会以编译错误的方式通知我们，
    date主要用来与时长概念进行运算
    */
    using namespace boost::gregorian;
    {
        date d1 { 2000, 1, 1 }, d2 { 2017, 11, 18 };
        std::cout << (d2 - d1).days() << std::endl;
        assert(d1 + (d2 - d1) == d2);

        d1 += days { 10 };
        assert(d1.day() == 11);
        d1 += months(2);
        assert(d1.month() == 3 && d1.day() == 11);
        d1 -= weeks(1);
        assert(d1.day() == 4);

        d2 -= years(10);
        assert(d2.year() == d1.year() + 7);
    }

    // 日期与特殊日期长度、特殊日期与日期长度进行运算的结果也是特殊日期：
    {
        date d1 { 2017, 1, 1 };

        date d2 { d1 + days { pos_infin } };
        assert(d2.is_pos_infinity());

        d2 = d1 + days(not_a_date_time);
        assert(d2.is_not_a_date());
        d2 = date(neg_infin);
        days dd { d1 - d2 };
        assert(dd.is_special() && !dd.is_negative());
    }
}

TEST(处理日期, 日期区间) {
    /*
    date_time库使用date_period来表示日期区间的概念，它是时间
    轴上的一个左闭右开的区间，其端点是两个date对象。日期区间的左
    边界必须小于右边界，否则date_period将表示一个无效的日期区间。
    */
    using namespace boost::gregorian;
    {
        date_period dp1 { date { 2017, 1, 1 }, days { 20 } };
        date_period dp2 { date { 2017, 1, 1 }, date { 2016, 1, 1 } }; // 无效
        date_period dp3 { date { 2017, 3, 1 }, days { -20 } };        // 无效

        date_period dp { date { 2017, 1, 1 }, days { 20 } };
        assert(!dp.is_null());
        assert(dp.begin().day() == 1);
        assert(dp.last().day() == 20);
        assert(dp.end().day() == 21);
        assert(dp.length().days() == 20);
    }

    /*
    date_period可以进行全序比较运算，但它依据的并不是日期区间
    的长度，而是区间的端点，即第一个区间的end（）和第二个区间的be
    gin（），判断这两个区间在时间轴上的位置大小。如果两个日期区间
    相交或包含，那么比较操作就无意义。
    */

    {
        date_period dp1 { date { 2017, 1, 1 }, days { 20 } };
        date_period dp2 { date { 2017, 2, 19 }, days { 10 } };

        // std::cout << dp1; // Error
        assert(dp1 < dp2);
    }
}

TEST(处理日期, 日期区间运算) {
    /*
    date_period同date、days一样，也支持很多运算。
    成员函数shift() 和expand() 可以变动区间：shift() 将日
    期区间平移n天而长度不变，expand() 将日期区间向两端延伸n天，
    相当于区间长度增加2n天。例如：
    */
    using namespace boost::gregorian;

    {
        date_period dp { date { 2017, 1, 1 }, days { 20 } };

        dp.shift(days(3));
        assert(dp.begin().day() == 4);
        assert(dp.length().days() == 20);

        dp.expand(days(3));
        assert(dp.begin().day() == 1);
        assert(dp.length().days() == 26);
    }

    /*
    date_period
    可以使用成员函数判断某个日期是否在区间内，还可以计算日期区间的交集。 ■
    is_before() /is_after()：日期区间是否在日期前或后。 ■
    contains()：日期区间是否包含另一个区间或日期。 ■
    intersects()：两个日期区间是否存在交集。 ■
    intersection()：返回两个区间的交集，如果无交集，则返回一个无效区间。 ■
    is_adjacent()：两个日期区间是否相邻。
    */
    {
        date_period dp { date { 2010, 1, 1 }, days { 20 } };

        assert(dp.is_after(date(2009, 12, 1)));
        assert(dp.is_before(date(2010, 2, 1)));
        assert(dp.contains(date(2010, 1, 10)));

        date_period dp2 { date { 2010, 1, 5 }, days { 10 } };
        assert(dp.contains(dp2));
        assert(dp.intersects(dp2));
        assert(dp.intersection(dp2) == dp2);

        date_period dp3 { date { 2010, 1, 21 }, days { 5 } };
        assert(!dp3.intersects(dp2));
        assert(dp3.intersection(dp2).is_null());

        assert(dp.is_adjacent(dp3));
        assert(!dp.intersects(dp3));
    }

    /*
    date_period提供了两种并集操作。
    ■
    merge()：返回两个日期区间的并集，如果日期区间无交集或不相邻，则返回无效区间。
    ■ span()：合并两个日期区间及两者间的间隔，相当于广义的merge（）。
    */
    {
        date_period dp1 { date { 2010, 1, 1 }, days { 20 } };
        date_period dp2 { date { 2010, 1, 5 }, days { 10 } };
        date_period dp3 { date { 2010, 2, 1 }, days { 5 } };
        date_period dp4 { date { 2010, 1, 15 }, days { 10 } };

        assert(dp1.contains(dp2) && dp1.merge(dp2) == dp1);
        assert(!dp1.intersects(dp3) && dp1.merge(dp3).is_null());
        assert(dp1.intersects(dp2) && dp1.merge(dp4).end() == dp4.end());
        assert(dp1.span(dp3).end() == dp3.end());
    }
}

TEST(处理日期, 日期迭代器) {
    // 这些日期迭代器包括day_iterator、week_iterator、month_iterator和year_iterator，
    // 它们分别以天、周、月和年为单位
    /*
    日期迭代器的用法基本类似，都需要在构造时传入一个起始日期
    和增减步长（可以是一天、两周或N个月等，默认是1个单位），然后
    就可以用operator++、operator--

    为了方便用户使用，日期迭代器还重载了比较操作符，不需要用
    解引用操作符就可以直接与其他日期对象比较大小
    */
    using namespace boost::gregorian;
    date d { 2007, 9, 28 };
    day_iterator d_iter { d };

    assert(d_iter == d);
    ++d_iter;
    assert(d_iter == date(2007, 9, 29));

    year_iterator y_iter { *d_iter, 10 };
    assert(y_iter == d + days(1));
    ++y_iter;
    assert(y_iter->year() == 2017);
    /*
    虽然 day_iterator、week_iterator的名字叫迭代器，
    但它并不符合标准迭代器的定义，如果没有difference_type、pointer、reference等内部类型定义，
    就不能使用std::advance() 或operator+=来前进或后退
    */
}

TEST(处理日期, 其他功能) {
    /*
    boost::gregorian::gregorian_calendar 类提供了格里高利
    历的一些操作函数，这些操作函数基本上在被date类内部使用，用户
    很少会用到。但它也提供了几个有用的静态函数：成员函数is_leap_year()可以判断年份是否是闰年；
    end_of_month_day()可以给定年份和月份，并返回该月的最后一天
    */
    using namespace boost::gregorian;
    using gre_cal = gregorian_calendar;

    std::cout << "Y2017 is " << (gre_cal::is_leap_year(2017) ? "" : "not")
              << " a leap year." << std::endl;

    assert(gre_cal::end_of_month_day(2017, 2) == 28);
    /*
    date_time库还提供了很多有用的日期生成器，如某个月的最后一
    个星期天或第一个星期一等，它们封装了一些常用但计算起来又比较
    麻烦的时间概念.
     */
}

TEST(处理日期, 综合运用) {
    using namespace boost::gregorian;

    // 显示月历
    std::cout << "显示月历" << std::endl;
    {
        date d { 2017, 1, 23 };

        date d_start(d.year(), d.month(), 1);
        date d_end = d.end_of_month();

        for (day_iterator d_iter { d_start }; d_iter != d_end; ++d_iter) {
            std::cout << d_iter->day() << " "
                      << d_iter->day_of_week().as_short_string() << std::endl;
        }
    }

    // 简单的日期计算.
    std::cout << "简单的日期计算" << std::endl;
    {
        // 下面的程序可以计算一个人18岁的生日是星期几，当月有几个星期天，当年有多少天
        date d { 2017, 1, 23 };

        date d18years { d + years { 18 } };
        std::cout << to_simple_string(d18years) << " is "
                  << d18years.day_of_week().as_short_string() << std::endl;

        int count { 0 };
        for (day_iterator d_iter { date { d18years.year(), 1, 1 } };
             d_iter != d18years.end_of_month(); ++d_iter) {
            if (d_iter->day_of_week() == Sunday) {
                ++count;
            }
        }
        std::cout << "total " << count << " Sundays." << std::endl;

        count = 0;
        for (month_iterator m_iter { date { d18years.year(), 1, 1 } };
             m_iter < date { d18years.year() + 1, 1, 1 }; ++m_iter) {
            count += m_iter->end_of_month().day();
        }
        std::cout << "total " << count << " days of year." << std::endl;
    }

    // 计算信用卡的免息期
    std::cout << "计算信用卡的免息期" << std::endl;
    {
        class credit_card {
        public:
            std::string bank_name;
            int bill_day_no {};

            credit_card(const char *bname, int no)
                : bank_name { bname }, bill_day_no { no } {}

            int
            calc_free_days(date consume_day = day_clock::local_day()) const {
                date bill_day { consume_day.year(), consume_day.month(),
                                bill_day_no };

                if (consume_day > bill_day) {
                    bill_day += months { 1 };
                }

                return (bill_day - consume_day).days() + 20;
            }

            bool operator<(credit_card const &r) const {
                return calc_free_days() < r.calc_free_days();
            }
        };

        credit_card a { "A bank", 25 };
        credit_card b { "B bank", 12 };

        credit_card tmp = std::max(a, b);
        std::cout << "You should use " << tmp.bank_name
                  << ", free days = " << tmp.calc_free_days() << std::endl;
    }
}

int main(int argc, char *argv[]) {
    printf("Running main() from %s\n", __FILE__);
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
