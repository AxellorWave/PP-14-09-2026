#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <vector>
#include <boost/process.hpp>
#include <algorithm>

namespace bp = boost::process;

int main()
{
  std::ofstream csv("results.csv");
  if (!csv) {
    std::cerr << "cannot open file\n";
    return 1;
  }

  csv << "threads,time\n";
  std::cout << "threads time\n";

  int threads = 2;
  for (; threads <= 1024; threads *= 2)
  {
    std::vector<double> v;
    for (size_t i = 0; i < 5; ++i)
    {
      bp::ipstream out;
      bp::child c("./counter", std::to_string(threads), bp::std_out > out);
      double result;
      out >> result;
      c.wait();
      v.push_back(result);
    }
    std::sort(v.begin(), v.end());

    double median = v[2];

    std::cout << threads << " " << median << "\n";
    csv << threads << "," << median << "\n";
  }
}