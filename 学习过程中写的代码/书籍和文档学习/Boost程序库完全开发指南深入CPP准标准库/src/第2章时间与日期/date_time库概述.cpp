#include <iostream>
#include "boost/date_time/gregorian/gregorian.hpp"
#include "boost/date_time/posix_time/posix_time.hpp"
#include "boost/date_time/special_defs.hpp"

// using namespace boost::gregorian;
// using namespace boost::posix_time;

int main(int argc, char *argv[]) {

    boost::date_time::pos_infin;       // 表示正无限
    boost::date_time::neg_infin;       // 表示负无限
    boost::date_time::not_a_date_time; // 无效时间
    boost::date_time::min_date_time;   // 可表示的最小日期或时间
    boost::date_time::max_date_time;   // 可表示的最大日期或时间

    return 0;
}
