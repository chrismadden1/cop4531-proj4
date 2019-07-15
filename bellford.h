/*
    bellford.h
    7/08/2019
    Chris Madden
    implements bellford algorithm on weighted graphs
*/

#ifndef BELLFORD_H
#define BELLFORD_H

template < class G>
class Bellford
{
  typedef G                      Graph
  typedef typename G::Vertex     Vertex;
   // more definitions optional

public:
  // constructor initializes all class variables in init list
  Bellford (const G& g);

  // implementing the algorithm
  void Init(Vertex source); // preps variables for startup of algorithm
  void Exec();              // executes algorithm

  // extracting information
  const fsu::Vector<double>& Distance() const;
  const fsu::Vector<size_t>& Parent() const;
  void                       Path(Vertex x, fsu::List<Vertex>& path) const;
  // expand API optional

private: // data
  const Graph& g_;

private: // methods
  void Relax(Vertex v)
};

template <class G>
void Bellford<G>::Init(vertex source)
{
 /*
 Initialize-single-source(G,s)
 */
    
}
template <class G>
void Bellford<G>::Exec(vertex source)
{
  /*  repeat (|V| - 1) times
{
for each edge (x,y)
{
Relax(x,y,d);
}
}
for each edge (x,y)
if (d[y] > d[x] + w(x,y))
return false;
return true
  */ 
}
#endif /* BELLFORD_H */
