https://github.com/ajw170/FSU-Graphs
/*
    partition_util_stub.h
    utilities for the Partition class
    stub version anticipating cop4531 hw4 (Fall 2018)
*/

#ifndef _PARTITION_UTIL_H
#define _PARTITION_UTIL_H

#include <cassert>
#include <map>
#include <cmath>
#include <compare.h>
#include <gsort.h>
#include <gheap_advanced.h>
#include <iostream>
#include <fstream>
#include <iomanip>

template < class P >
// void RankComponentsBySize (const P& p, fsu::Vector<size_t>& v)
void RankComponentsBySize (P& p, fsu::Vector<size_t>& v) // allows path compression
{
  size_t components = p.Components();//number of components in p
  size_t size = p.Size();//number of elements in p
  
  	//this nested for loop will go through each component, check how big it is
	//and then assign that value to the corresponding index in the vector v.
  for(size_t i = 0; i < components; i++)
  {
	for(size_t j = 0; j < size; j++)
	{
		if(p.Find(i, j)
			v[i]++;
	}
  }
  //this will sort the vector from largest to smallest.
  std::sort(v.begin(), v.end(), std::greater<size_t>()); 
}
 
 template < class G >
void ComponentRankSequence(const G& g , size_t maxToDisplay, std::ostream& os)
{
fsu::Partition p (g.VrtxSize());
// your process to model the components of g with p goes here
  fsu::Vector<size_t> component;
  unsigned components = 0;
  for (size_t i = 0; i < g.VrtxSize; i++)
  {
    if (color[i] == white)
    {
      components +=1;
      Search(i);
    } 
  component[i] = components;
  }
RankComponentsBySize(p,maxToDisplay,os); // <-- calls your algorithm here
}

template < class P >
// void RankComponentsBySize (const P& p, size_t maxToDisplay, std::ostream& os = std::cout)
void RankComponentsBySize (P& p, size_t maxToDisplay, std::ostream& os = std::cout) // allows path compression
{
  int cw = floor(log10(p.Size()));
  if (cw < 4) cw = 4;
  cw += 3;
  // const int cw = 7;
  size_t enough, components;
  fsu::Vector<size_t> componentSize(0);
  RankComponentsBySize(p,componentSize);
  enough = components = componentSize.Size();
  if (0 < maxToDisplay && maxToDisplay < enough) enough = maxToDisplay;
  os << "  number of components: " << components << '\n';
  if (enough == components)
    os << "  all components ranked by size:"  << '\n';
  else
    os << "  top " << enough << " components ranked by size:" << '\n';
  os << std::setw(cw) << "rank"
     << std::setw(cw) << "size" << '\n'
     << std::setw(cw) << "----"
     << std::setw(cw) << "----" << '\n';
  for (size_t i = 0; i < enough; ++i)
  {
    os << std::setw(cw) << 1 + i
       << std::setw(cw) << componentSize[i] << '\n';
    if (componentSize[i] == 1 && 1 + i < componentSize.Size())
    {
      os << std::setw(cw) << '*'
         << std::setw(cw) << 1 << "  (the remaining " << (components - i - 1) << " components have size 1)\n";
      break;
    }
  }
}

template < class P >
// bool RankComponentsBySize (const P& p, size_t maxToDisplay, const char* filename)
bool RankComponentsBySize (P& p, size_t maxToDisplay, const char* filename) // allows path compression
{
  std::ofstream os;
  os.open(filename);
  if (os.fail())
  {
    std::cerr << " ** Error: unable to open file " << filename << '\n';
    return 0;
  }
  RankComponentsBySize (p, maxToDisplay, os);
  os.close();
  return 1;
}

#endif
