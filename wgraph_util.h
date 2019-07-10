/*
    wgraph_util.h
    7/08/2019
    Chris Madden
    for loading/saving weighted graph types
*/

#ifndef _WGRAPH_UTIL_H
#define _WGRAPH_UTIL_H

#include <graph_util.h>


template < class G >
bool WLoad (const char* inFile, G& g)
{
	std::ifsteam instream;
	instream.open(inFile);
	if(instream.fail())
		return 0;
	bool status = WLoad(instream, g);
	instream.close();
	instream.clear();
	return status;
}

template < class G >
bool WLoad (std::istream& inStream, G& g)
{
   typename G::Vertex v, x; // general purpose vertex variables
   char ch;                 // general purpose file read variable  
   double w; 				//for weight
  // skip documentation -- '#' in column 1
  ch = inStream.peek();
  while (ch == '#')
  {
    ch = inStream.get();
    while ((ch != '\n') && (!inStream.eof()))
		ch = inStream.get();
    ch = inStream.peek();
  }
	// read graph data and build graph
  inStream >> v;
  if (inStream.fail())
  {
    std::cerr << " ** Load error: vertex size not readable\n";
    return 0;
  }
  g.SetVrtxSize(v);
  while (inStream >> v >> x >> w)
  {
    g.AddEdge(v,x, w);
  }
  return 1;
}

template < class G >
bool Save_UWG (const char* filenameBase, const G& g)
{
  size_t size = strlen(filenameBase);
  char filename [size+5];
  strcpy(filename,filenameBase);
  filename[size] = '.';
  filename[size+1] = 'u';
  filename[size+2] = 'w';
  filename[size+3] = 'g';
  filename[size+4] = '\0';
  std::ofstream outStream;
  outStream.open(filename);
  if (outStream.fail())
  {
    return 0;;
  }
  typename G::Vertex v;
  double w;
  typename G::AdjIterator i; 
  outStream << g.VrtxSize() << '\n';
  for (v = 0; v < g.VrtxSize(); ++v)
  {
    for (i = g.Begin(v); i != g.End(v); ++i)
    {
      if (v < *i) outStream << v << '\t' << *i << w << '\n';
    }
  }
  outStream.close();
  std::cout << " uwgraph saved as " << filename << '\n';
  return 1;
	
}

template < class G >
bool Save_DWG (const char* filenameBase, const G& g)
{
  size_t size = strlen(filenameBase);
  char filename [size+5];
  strcpy(filename,filenameBase);
  filename[size] = '.';
  filename[size+1] = 'u';
  filename[size+2] = 'd';
  filename[size+3] = 'g';
  filename[size+4] = '\0';
  std::ofstream outStream;
  outStream.open(filename);
  if (outStream.fail())
  {
    return 0;;
  }
  typename G::Vertex v;
  double w;
  typename G::AdjIterator i; 
  outStream << g.VrtxSize() << '\n';
  for (v = 0; v < g.VrtxSize(); ++v)
  {
    for (i = g.Begin(v); i != g.End(v); ++i)
    {
      if (v < *i) outStream << v << '\t' << *i << w << '\n';
    }
  }
  outStream.close();
  std::cout << " dwgraph saved as " << filename << '\n';
  return 1;
}



void WFileSpec(std::ostream& os = std::cout)
{
  os << " -----------------------------------------------------------------------\n"
     << " Graph File Specs                                                       \n"
     << " ----------------                                                       \n"
     << " File documentation at beginning of file, lines begin with '#'          \n"
     << " Remainder of file consists of unsigned integers in decimal notation    \n"
     << " first entry is unsigned int n = number of vertices                     \n"
     << " followed by triples x y w                                              \n"
     << " x,y represent vertices of edge from x to y (unsigned < n)              \n"
     << " w is a real number representing weight of edge                         \n"
     << " -----------------------------------------------------------------------\n";
}

#endif
