#include <iostream>
#include <thread>
#include <vector>
#include "clicker.hpp"

using data_t = std::vector< unsigned long long >;
using value_t = data_t::value_type;

int main()
{
  constexpr size_t size{1'000'000'000};
  double init{0}, total{0};
  value_t sum{0};
  {
    zharov::Clicker cl;
    data_t values(size, 1);
    init = cl.millisec();
    for (size_t i = 0; i < values.size(); ++i)
    {
      sum+= values[i];
    }
    total = cl.millisec();
  }
  std::cout << total - init << "\n";
}

