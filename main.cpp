#include <iostream>
#include <thread>
#include <vector>
#include <future>
#include "clicker.hpp"

using data_t = std::vector< unsigned long long >;
using value_t = data_t::value_type;
using citer = data_t::const_iterator;

value_t calc(citer begin, citer end)
{
  value_t res = 0;
  for (; begin!=end; ++begin)
  {
    res += * begin;
  }
  return res;
}

int main(int argc, char** argv)
{
  long long threads = 1;
  if (argc >= 2) {
    threads = std::stoi(argv[1]);
  }
  if (threads <=0)
  {
    std::cerr << "bad threads count\n";
    return 1;
  }

  constexpr size_t size{1'000'000'000};
  double init{0}, total{0};
  value_t sum{0};
  try
  {
    std::vector< std::future< value_t > > results;
    results.reserve(threads);
    size_t nums_on_thread = size / threads;
    {
      zharov::Clicker cl;
      data_t values(size, 1);
      for (size_t i = 0; i < threads - 1; ++i)
      {
        results.push_back(std::async(std::launch::async, calc, values.cbegin() + i * nums_on_thread,
          values.cbegin() + (i + 1) * nums_on_thread ));
      }
      results.push_back(std::async(std::launch::async, calc, values.cbegin() + (threads - 1) * nums_on_thread,
        values.cend()));

      init = cl.millisec();

      for (size_t i = 0; i < threads; ++i)
      {
        sum += results[i].get();
      }
      total = cl.millisec();
    }
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << "\n";
  }
  std::cout << total - init << "\n";
}

