#include <ctime>
#include <iostream>
#include <gtest/gtest.h>
#include <map>
#include <string>
#include "boost/date_time/gregorian/greg_duration_types.hpp"
#include "boost/date_time/gregorian/gregorian_types.hpp"
#include "boost/date_time/posix_time/conversion.hpp"
#include "boost/date_time/posix_time/posix_time.hpp"
#include "boost/date_time/posix_time/posix_time_config.hpp"
#include "boost/date_time/posix_time/posix_time_duration.hpp"
#include "boost/date_time/posix_time/posix_time_types.hpp"
#include "boost/date_time/posix_time/ptime.hpp"
#include "boost/date_time/posix_time/time_formatters.hpp"
#include "boost/date_time/posix_time/time_parsers.hpp"
#include "boost/date_time/posix_time/time_period.hpp"

using namespace boost::posix_time;

TEST(处理时间, 时间长度) {
    /*
    为了方便使用，time_duration也有几个子类，可以度量不同的时间分辨率，
    它们的名字很容易记，分别是：hours、minutes、seconds、millisec、microsec和nanosec。
    time_duration 支持全序比较操作和输入输出，而且比 date_duration
    支持的算术运算要多， 可以用它进行加减乘除四则运算
    */
}

TEST(处理时间, 操作时间长度) {
    time_duration td1 { 1, 10, 30, 1000 };

    // 时、分、秒等值可以是任意数值，不一定必须在它们的限度里，超出的时间会自动进位或借位
    time_duration td2 { 1, 60, 60, 1000 * 1000 * 6 + 1000 };

    hours h { 1 };
    minutes m { 10 };
    seconds s { 30 };
    millisec ms { 1 };
    time_duration td3 { h + m + s + ms };
    time_duration td4 { hours { 2 } + seconds { 10 } };

    /*
    使用工厂函数 duration_from_string()，time_duration 也可
    以从一个字符串创建，字符串中的时、分、秒、微秒需要用冒号隔开
    */
    time_duration td { duration_from_string("1:10:30:001") };

    time_duration td5 { 1, 10, 30, 1000 };

    assert(td5.hours() == 1 && td5.minutes() == 10 && td5.seconds() == 30);
    assert(td5.total_seconds() == 1 * 3600 + 10 * 60 + 30);
    assert(td5.total_milliseconds() == td5.total_seconds() * 1000 + 1);
    assert(td5.fractional_seconds() == 1000);

    {
        hours h { -10 };
        assert(h.is_negative());

        time_duration h2 { h.invert_sign() };
        assert(!h2.is_negative() && h2.hours() == 10);
    }

    {
        time_duration td1 { not_a_date_time };
        assert(td1.is_special() && td1.is_not_a_date_time());

        time_duration td2 { neg_infin };
        assert(td2.is_negative() && td2.is_neg_infinity());
    }

    {
        time_duration td1 { hours { 1 } };
        time_duration td2 { hours { 2 } + minutes { 30 } };

        assert(td1 < td2);
        assert((td1 + td2).hours() == 3);
        assert((td1 - td2).is_negative());
        assert((td1 * 5) == td2 * 2);
        assert((td1 / 2).minutes() == td2.minutes());
    }

    {
        time_duration td { 1, 10, 30, 1000 };
        std::cout << to_simple_string(td) << std::endl;
        std::cout << to_iso_string(td) << std::endl;
    }
    // time_duration也可以使用to_tm()函数转换到tm结构，但不能进行反向转换
    // 我想也是😎
}

TEST(处理时间, 时间精确度) {
    /*
     date_time库默认时间精确度是微秒，纳秒相关的类和函数（如nanosec和成员函数nanoseconds()、total_nanoseconds()）
     都不可用，秒以下的时间度量都使用微秒。
     当定义了宏 BOOST_DATE_TIME_POSIX_TIME_STD_CONFIG
     时，time_duration的一些行为将发生变化，它
     的时间分辨率将精确到纳秒，构造函数中秒以下的时间度量单位也会变成纳秒
    */
}

TEST(处理时间, 时间点) {
    // ptime也是个轻量级的对象，可以被高效地任意拷贝、赋值，也支持全序比较运算和加减运算
    using namespace boost::gregorian;
    // 创建时间点对象
    { ptime p { date { 2017, 7, 7 }, hours { 1 } }; }

    {
        ptime p1 { second_clock::local_time() };
        ptime p2 { microsec_clock::universal_time() };
        std::cout << p1 << std::endl << p2 << std::endl;
    }

    {
        ptime p1 { not_a_date_time };
        assert(p1.is_not_a_date_time());

        ptime p2 { pos_infin };
        assert(p2.is_special() && p2.is_pos_infinity());
    }
}

TEST(处理时间, 操作时间点对象) {
    using namespace boost::gregorian;
    {
        ptime p { date { 2010, 3, 20 }, hours { 12 } + minutes { 30 } };

        date d { p.date() };

        time_duration td { p.time_of_day() };
        assert(d.month() == 3 && d.day() == 20);
        assert(td.total_seconds() == 12 * 3600 + 30 * 60);
    }

    {
        ptime p1 { date { 2010, 3, 20 }, hours { 12 } + minutes { 30 } };
        ptime p2 { p1 + hours { 3 } };

        assert(p1 < p2);
        assert(p2 - p1 == hours(3));

        p2 += months { 1 };
        assert(p2.date().month() == 4);
    }

    {
        /*
        ptime提供了3个自由函数转换为字符串，具体如下。
    ■ to_simple_string（）：转换为YYYY-mmm-DD HH：MM：SS.ffffff格式；
    ■ to_iso_string（）：转换为YYYYMMDDTHHMMSS，ffffff格式；
    ■ to_iso_extended_string（）：转换为YYYY-MM-DDTHH:MM:SS，ffffff格式。
    其中的ffffff是秒的小数部分，如果为0则不显示，T是日期与时间的分隔符
        */

        ptime p { date { 2017, 2, 14 }, hours { 20 } };
        std::cout << to_simple_string(p) << std::endl;
        std::cout << to_iso_string(p) << std::endl;
        std::cout << to_iso_extended_string(p) << std::endl;
    }
}

TEST(处理时间, 转换C结构) {
    using namespace boost::gregorian;
    /*
        使用函数 to_tm()，ptime 可以转换到 tm 结构，转换规则是 将 date 和
        time_duration组合，而使用ptime_from_tm()函数可以把tm结构转换成ptime。
    */
    {
        ptime p { date { 2017, 5, 20 }, hours { 14 } };
        tm t { to_tm(p) };

        assert(t.tm_year == 117 && t.tm_hour == 14);
        assert(ptime_from_tm(t) == p);
    }

    {
        ptime p { from_time_t(std::time(0)) };
        assert(p.date() == day_clock::local_day());
        std::cout << to_time_t(p) << std::endl;
    }
}

TEST(处理时间, 时间区间) {
    using namespace boost::gregorian;

    ptime p { date { 2017, 1, 1 }, hours { 12 } };
    time_period tp1 { p, hours { 8 } };
    time_period tp2 { p + hours { 8 }, hours { 1 } };
    assert(tp1.end() == tp2.begin() && tp1.is_adjacent(tp2));
    assert(!tp1.intersects(tp2));

    tp1.shift(hours { 1 });
    assert(tp1.is_after(p));
    assert(tp1.intersects(tp2));

    tp2.expand(hours { 10 });
    assert(tp2.contains(p) && tp2.contains(tp1));
}

TEST(处理时间, 时间迭代器) {
    using namespace boost::gregorian;

    ptime p { date { 2017, 5, 31 }, hours { 10 } };

    for (time_iterator t_iter { p, minutes { 10 } }; t_iter < p + hours { 1 };
         ++t_iter) {
        std::cout << *t_iter << std::endl;
    }
}

using namespace boost::gregorian;

template <typename Clock = microsec_clock>
class basic_ptimer {
public:
    basic_ptimer() { restart(); }

    void restart() { _start_time = Clock::local_time(); }

    void elapsed() const { std::cout << Clock::local_time() - _start_time; }

    ~basic_ptimer() { elapsed(); }

private:
    ptime _start_time;
};

using ptimer = basic_ptimer<microsec_clock>;
using sptimer = basic_ptimer<second_clock>;

class work_time {
public:
    using map_t = std::map<time_period, std::string>;

    work_time() { init(); }

    void greeting(ptime const &t) {
        for (auto &x : map_ts) {
            if (x.first.contains(t)) {
                std::cout << x.second << std::endl;
                break;
            }
        }
    }

    void init() {
        ptime p { day_clock::local_day() };
        map_ts[time_period { p, hours { 9 } }] =
            "It's too early, just relax.\n";
        p += hours { 9 };
        map_ts[time_period { p, hours { 3 } + minutes { 30 } }] =
            "Is's AM, please work hard.\n";
        p += hours { 3 } + minutes { 30 };
        map_ts[time_period { p, hours { 1 } }] =
            "It's lunch time, are you hungry?\n";
        p += hours { 1 };
        map_ts[time_period { p, hours { 4 } + minutes { 30 } }] =
            "It's PM, ready to go home.\n";

        p += hours { 4 } + minutes { 30 };
        map_ts[time_period { p, hours { 6 } }] =
            "Are you still working? you do need a rest.\n";
    }

private:
    map_t map_ts;
};

TEST(处理时间, 综合运用) {

    {
        std::cout << "高精度计时器" << std::endl;
        ptimer t;
    }

    {
        std::cout << "计算工作时间" << std::endl;
        work_time wt;
        wt.greeting(second_clock::local_time());
    }
}

int main(int argc, char *argv[]) {
    printf("Running main() from %s\n", __FILE__);
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
