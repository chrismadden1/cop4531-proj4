/*
    prim.h
    7/08/2019
    Chris Madden
    implements prim algorithm on weighted graphs
*/

#ifndef PRIM_H
#define PRIM_H

template < class G>
class Prim 
{
  typedef G                      Graph;
  typedef typename G::Vertex     Vertex;
 // typedef fsu::Edge<Vertex>      Edge;
 // typedef fsu::Vector<Edge>      Container;
 // typedef fsu::GreaterThan<Edge> Predicate;
 // typedef fsu::PriorityQueue<Edge,Container,Predicate> PQ;


public:
  // constructor initializes all class variables in init list
  Prim (const G& g);

  // implementing the algorithm
  void Init(bool verbose = 0); // preps class variables for execution of algorithm
  void Exec(bool verbose = 0); // runs algorithm

  // extracting information
//  const fsu::List<Edge>& MST() const;
  double                 Weight() const;
private:
  const Graph& g_;
 //PQ           pq_;
};
template <class G >
void Prim<G>::Init(verbose)
{
    /* 
    init W = {S}
    init T = empty
    */
}
template <class G >
void Prim<G>::Exec(verbose)
{
 /* for each neighbor n of s,
q.Push((s,n)); // ARQ1
while (!q.Empty())
{
// loop invariant 1: (W,T) contains no cycles
// loop invariant 2: (W,T) is connected
(x,y) = q.Front(); // ARQ2
q.Pop(); // ARQ3
if (y is not in W)
{
W = W union {y};
T = T union {[x,y]};
for each neighbor z of y,
if (z is not in W)
q.Push((y,z)); // ARQ4
}
}
output (W,T)
}*/
    
}
#endif /* PRIM_H */
