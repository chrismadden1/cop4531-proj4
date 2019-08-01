/*
    kruskal.h
    7/08/2019
    Chris Madden
    implements kruskal algorithm on weighted graphs
*/

#ifndef KRUSKAL_H
#define KRUSKAL_H

template < class G >
Kruskal
{
  typedef G             Graph;
  typedef G::Vertex     Vertex;
  typedef fsu::Edge<Vertex>                            Edge;
  typedef fsu::Vector<Edge>                            Container;
  typedef fsu::GreaterThan<Edge>                       Predicate;
  typedef fsu::PriorityQueue<Edge,Container,Predicate> PQ;

public:
  void              Init   ( bool verbose = 0 );
  void              Exec   ( bool verbose = 0 );
  const List<Edge>& MST    () const { return mst_; }
  double            Weight () const { return mstw_; }
  Kruskal                  ( const G& g ) : g_(g),mst_(), mstw_(0.0),c_(0),pred_(),pq_(c_,pred_) {}

private:
  const G&   g_;    // undirected weighted graph
  List<Edge> mst_;  // edges of MST  (calculated by Exec())
  double     mstw_; // weight of MST (calculated by Exec())
  Container       c_;    // "input" edge set
  Predicate       pred_; // edge prioritizer
  PQ              pq_;   // priority queue package operating on c_ with pred_
};

template <class G>
void Prim<G>::Init()
{
    pq_.Init();
    mst_.Clear();
    c_.Clear();
    mstw_ = 0.0;
    inTree_[0] = true;
    fsu::Partition <size_t> p (g_.VrtxSize());      
}

template <class G>
void Prim<G>::Exec()
{
    while(!pq_.Empty())
    {
        mst_.PushBack(pq_.Front());
        pq_.Pop();
        if(!p.Find())
            
        
    }
}

#endif /* KRUSKAL_H */
