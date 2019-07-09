#ifndef KRUSKAL_H
#define KRUSKAL_H

template < class G>
class Kruskal 
{
  typedef G                      Graph
  typedef typename G::Vertex     Vertex;
  typedef fsu::Edge<Vertex>      Edge;
  typedef fsu::Vector<Edge>      Container;
  typedef fsu::GreaterThan<Edge> Predicate;
  typedef fsu::PriorityQueue<Edge,Container,Predicate> PQ;


public:
  // constructor initializes all class variables in init list
  Kruskal (const G& g);

  // implementing the algorithm
  void Init(bool verbose = 0); // preps class variables for execution of algorithm
  void Exec(bool verbose = 0); // runs algorithm

  // extracting information
  const fsu::List<Edge>& MST() const;
  double                 Weight() const;
  ... // expand API optional
private:
  const Graph& g_;
  ...
  PQ           pq_;
};




#endif /* KRUSKAL_H */
