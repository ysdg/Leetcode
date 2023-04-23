/*************************************************
 * @Description: file content
 * @Author: yuanquan
 * @Email: yuanquan2011@qq.com
 * @Date: 2021-05-17 21:20:13
 * @LastEditors: yuanquan
 * @LastEditTime: 2021-07-24 12:20:47
 * @copyright: Copyright (c) yuanquan
 *************************************************/
#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <gtest/gtest.h>
#include <boost/array.hpp>
#include <tuple>
#include <thread>
#include <fstream>
#include <filesystem>
#include <atomic>
#include <stdio.h>
#include <chrono>

#include "date.h"
#include "json.hpp"
#include <boost/asio/ip/host_name.hpp>

using std::jthread;
using namespace std;
using namespace boost;
using namespace testing;

#define TIME_FORMAT "%F %T%z"

int main()
{
	using namespace std::chrono;

     time_point<system_clock, nanoseconds> tp;
	std::istringstream ss{"2023-04-18 10:20:00+0000"};
	ss >> date::parse(TIME_FORMAT, tp);

     std::cout << "time ns: " <<  tp.time_since_epoch().count() << std::endl;

	std::ostringstream os;
     auto nsCount = nanoseconds(tp.time_since_epoch().count());
     auto tp1 = time_point<system_clock, nanoseconds>(nsCount);
	os << date::format(TIME_FORMAT, tp1);

     std::cout << os.str() << std::endl;

	return 0;
}
