/*
    ranwgraph.cpp
    10/07/18
    Chris Lacher

    creates random weighted graph with specified vertex and edge counts

    Copyright 2018, R.C. Lacher
*/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <ansicodes.h>
// #include <string>
// #include <map>
// #include <random>
// #include <set>

#include <xran.h>
#include <graph2.h>
#include <graph_util.h>

const double a = 0.5, b = 2.0;

// for the "one vector<signed>" implementation
typedef long IntType;
#include <partition1.h>
// */

/* // for the "two vector<unsigned>" implementation
typedef size_t IntType;
#include <partition2.h>
// */

#include <partition_util.h>
#include <xran.cpp> // in lieu of makefile

int main( int argc , char * argv[] )
{
  std::cout << ANSI_BOLD_BLUE
            << " Welcome to rangraph\n"
            << ANSI_RESET_ALL;
  if (argc < 4)
  {
    std::cout << ANSI_BOLD_RED
              << " ** command line arguments:\n"
	      << "     1: graph file name           (required)\n"
	      << "     2: number of vertices        (required)\n"
	      << "     3: number of edges           (required)\n"
	      << "     4: length of tail to display (optional, default = 10)\n"
	      << " ** try again\n"
              << ANSI_RESET_ALL;
    return 0;
  }

  char* outfile     = argv[1];
  size_t n          = atoll(argv[2]);
  size_t e          = atoll(argv[3]);
  size_t tail       = 10;
  if (argc > 4)
    tail            = atoll(argv[4]);
    
  if (n == 0)
  {
    std::cout << " ** only the empty graph has 0 vertices\n";
    return 0;
  }

  if (e > n*(n - 1)/2)
  {
    std::cout << " ** a graph with " << n << " vertices can have at most " << n*(n - 1)/2 << " edges\n";
    return 0;
  }

  if (e == n*(n - 1)/2)
  {
    std::cout << " ** a graph with " << n << " and " << e << " edges is the complete graph on " << n << " symbols\n";
    return 0;
  }

  long double er = (2*e);  er /= n; er /= n-1;

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
       << "# random graph\n"
       << "#  vertices:                " << n << '\n'
       << "#  edges:                   " << e << '\n'
       << "#  Erdos-Renyi probability: " << er << '\n'
       << "#  expected degree:         " << ((double)2*e)/(n - 1) << '\n'
       << std::setprecision(2)  
       << "#  weight range:            [" << a << ',' << b << ")\n"
       << "#\n\n";
  out1 << n << '\n';
  fsu::ALUGraph<size_t> g(n);
  fsu::Random_unsigned_int ranuint;
  fsu::Random_double randouble;
  size_t v1, v2, count = 0;
  fsu::Partition<IntType> p(n);
  while (count < e)
  {
    v1 = ranuint(0,n);
    v2 = ranuint(0,n);
    if (v1 == v2 || g.HasEdge(v1,v2)) continue;
    // v1 = ranuint(0,n-1);
    // v2 = ranuint(v1,n);
    // if (g.HasEdge(v1,v2)) continue;
    g.AddEdge(v1,v2);
    p.Union(v1,v2);
    ++count;
    out1 << v1 << '\t' << v2 << '\t' << randouble(a,b) << '\n';
  }
  out1.close();
  std::cout << std::fixed << std::showpoint << std::setprecision(10);
  std::cout << " Weighted Graph stored in file " << outfile << '\n'
	    << "  vertices:                " << n << '\n'
	    << "  edges:                   " << count << '\n'
	    << "  Erdos-Renyi probability: " << er << '\n'
	    << "  expected degree:         " << ((double)2*e)/n << '\n'
            << std::setprecision(2)
            << "  weight range:            [" << a << ',' << b << ")\n";
  RankComponentsBySize(p,tail);
  OutDegreeFrequencyDistribution(g);
  return 0;
}

// n = number of vertices
// e = number of edges
// p = probability of edge from v to w (!= v)
// d = expected degree of a vertex
// d = p*(n-1) = 2e/n
// p = 2e/(n(n-1)) = d/(n-1)
