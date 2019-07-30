/*
    prim.h
    7/08/2019
    Chris Madden
    implements prim algorithm on weighted graphs
*/

#ifndef PRIM_H
#define PRIM_H

template <class G>
class Prim
{
  typedef G                      Graph;
  typedef typename G::Vertex     Vertex;
  typedef fsu::Edge<Vertex>      Edge;
  typedef fsu::Vector<Edge>      Container;
  typedef fsu::GreaterThan<Edge> Predicate;
  typedef fsu::PriorityQueue<Edge,Container,Predicate> PQ;

public:
  void                   Init   ( bool verbose = 0 );
  void                   Exec   ( bool verbose = 0 );
  const fsu::List<Edge>& MST    () const { return mst_; }
  double                 Weight () const { return mstw_; }
  Prim                          (const G& g) : g_(g),mst_(), mstw_(0.0), c_(0), pred_(), pq_(c_,pred_), inTree_(0) {}

private:
  const G&        g_;    // undirected weighted graph
  fsu::List<Edge> mst_;  // "output" edge set
  double          mstw_; // weight of MST
  Container       c_;    // "dynamic" edge set - discovered but not yet used
  Predicate       pred_; // edge prioritizer
  PQ              pq_;   // priority queue package operating on c_ with pred_
  fsu::Vector<bool> inTree_; // tree vertices
};

#endif /* PRIM_H */
