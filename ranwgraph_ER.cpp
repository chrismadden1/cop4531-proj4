/*
    ranwgraph_ER_1.cpp
    10/20/18
    Chris Lacher

    creates random weighted Erdos-Renyi graph - specify vertex count and degree probability
    1: uses triangular double loop to keep g simple

    Copyright 2018, R.C. Lacher
*/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
// #include <map>
#include <random>
#include <ansicodes.h>
#include <partition2.h>
#include <partition_util.h>
#include <graph.h>
#include <graph_util.h>
#include <gsort.h>

const double a = 1.5, b = 5.0;

/*
void EG(double p)
{
  std::random_device rd;
  std::mt19937 gen(rd());
  std::bernoulli_distribution d(p);

  std::map<bool, int> histogram;
  for(int n=0; n<10000; ++n)
  {
    ++histogram[d(gen)];
  }
  for(auto p : histogram)
  {
    std::cout << std::boolalpha << std::setw(5) << p.first << ':'
              << std::setw(8) << p.second
              << "  " << std::string(p.second/100, '*') << '\n';
  }
}
*/

// n = number of vertices
// e = number of edges
// p = probability of edge from v to w (!= v)
// d = expected degree of a vertex
// d = p(n-1) = 2e/n
// p = 2e/(n(n-1)) = d/(n-1)
// e = dn/2 = pn(n-1)/2

int main( int argc , char * argv[] )
{
  std::cout << ANSI_BOLD_BLUE
            << " Welcome to ranwgraph_ER\n"
            << ANSI_RESET_ALL;
  if (argc < 4)
  {
    std::cout << ANSI_BOLD_RED
              << " ** command line arguments:\n"
	      << "     1: graph file name                (required)\n"
	      << "     2: number of vertices             (required)\n"
	      << "     3: expected vertex degree (float) (required)\n"
	      << "     4: length of tail to display      (optional, default = 10)\n"
	      << " ** try again\n"
              << ANSI_RESET_ALL;
    return 0;
  }

  char*         outfile = argv[1];
  size_t        n       = atoll(argv[2]);
  double        d       = atof(argv[3]);
  size_t        tail    = 10;
  if (argc > 4) tail    = atoll(argv[4]);
    
  if (n == 0)
  {
    std::cout << " ** only the empty graph has 0 vertices\n";
    return 0;
  }

  if (d < 0.0 || d >= n)
  {
    std::cout << " ** expected degree must be in [0,n-1]\n";
    return 0;
  }
  
  double p = d/(n-1);

  std::ofstream out1(outfile);
  if (out1.fail())
  {
    std::cout << " ** cannot open file " << outfile << '\n'
	      << " ** try again\n";
    return 0;
  }       
  out1 << std::fixed << std::showpoint << std::setprecision(10);
  out1 << "#\n"
       << "# " << outfile << '\n'
       << "#\n"
       << "# random Erdos-Renyi weighted graph\n"
       << "#  vertices:    " << n << '\n'
       << "#  expectation: " << d << '\n'
       << "#  probability: " << p << '\n'
       << std::setprecision(2)  
       << "#  weight range: [" << a << ',' << b << "]\n"
       << "#\n\n";
  out1 << n << '\n';
  
  std::random_device rd;
  std::mt19937 gen(rd());
  std::bernoulli_distribution B(p); // ?? *=2 to compensate for upper-triangular double loop
  std::uniform_real_distribution<double> Weight(a,b);
  /*
  std::map<bool, int> histogram;
  for(int n=0; n<10000; ++n)
  {
    ++histogram[B(gen)];
  }
  */

  fsu::ALUGraph<size_t>  g(n);
  fsu::Partition<size_t> uf(n);
  size_t e(0);
  for (size_t i = 0; i < n; ++i)
  {
    // std::cout << '.';
    for (size_t j = i+1; j < n; ++j)
    {
      if (B(gen))
      {
        g.AddEdge(i,j);
        uf.Union(i,j);
        ++e;
        out1 << i << '\t' << j << '\t' << Weight(gen) << '\n';
      }
    }
  }
  // std::cout << '\n';
  out1.close();

  std::cout << std::fixed << std::showpoint << std::setprecision(10);
  std::cout << "Weighted Graph stored in file " << outfile << '\n'
	    << "  vertices:        " << n << '\n'
	    << "  expected degree: " << d << '\n'
	    << "  probability:     " << p << '\n'
	    << "  edge count:      " << e << '\n'
            << std::setprecision(2)
            << "  weight range:    [" << a << ',' << b << "]\n";
  RankComponentsBySize(uf,tail);
  OutDegreeFrequencyDistribution(g);

  return 0;
}
