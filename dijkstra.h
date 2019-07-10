/*
    dijsktra.h
    7/08/2019
    Chris Madden
    implements dijkstra algorithm on weighted graphs
*/

#ifndef DIJKSTRA_H
#define DIJKSTRA_H

template < class G>
class Dijkstra
{
  typedef G                      Graph
  typedef typename G::Vertex     Vertex;
  ... // more definitions optional

public:
  // constructor initializes all class variables in init list
  Dijkstra (const G& g);

  // implementing the algorithm
  void Init(Vertex source); // preps variables for startup of algorithm
  void Exec();              // executes algorithm

  // extracting information
  const fsu::Vector<double>& Distance() const;
  const fsu::Vector<size_t>& Parent() const;
  void                       Path(Vertex x, fsu::List<Vertex>& path) const;
  ... // expand API optional

private: // data
  const Graph& g_;
  ...

private: // methods
  void Relax(Vertex v)
  ...
};

#endif /* DIJKSTRA_H */
