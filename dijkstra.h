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
  typedef G                                          Graph;
  typedef typename G::Vertex                         Vertex;
  typedef fsu::Pair<double,Vertex>                   DV;
  typedef fsu::Vector<DV>                            Container;
 // typedef fsu::GreaterThan<DV>                       Predicate;
 // typedef fsu::PriorityQueue<DV,Container,Predicate> PQ;
public:
  // constructor initializes all class variables in init list
  Dijkstra (const G& g) : g_(g),start_(0),c_(0),pred_(),pq_(c_,pred_),d_(0), p_(0), hasNegativeWeight_(0) {}

  // implementing the algorithm
  void Init(Vertex source); // preps variables for startup of algorithm
  void Exec();              // executes algorithm

  // extracting information
  //const fsu::Vector<double>& Distance() const;
  //const fsu::Vector<size_t>& Parent() const;
  //void                       Path(Vertex x, fsu::List<Vertex>& path) const;

private: // data
  void Relax(Vertex v);
  const G&            g_;    // <- directed weighted graph
  Vertex              start_;
  Container           c_;    // <- "input" edge set
  Predicate           pred_; // vertex prioritizer
  PQ                  pq_;   // priority queue package
  fsu::Vector<double> d_; // distance
  fsu::Vector<Vertex> p_; // predecessor in search
  bool                hasNegativeWeight_;

private: // methods
  void Relax(Vertex x, Vertex y, double wt, PQ);
};

template < class G>
void Dijkstra<G>::Init(Vertex source)
{
 /*
 sort the priority queue pq_
 */
    
}

template < class G>
void Dijkstra<G>::Exec(Vertex source)
{
 /*pq_.Push(source);
 while (!pq_.Empty())
{
Vertex u = pq_.Front();
pq_.Pop();
//for(each vertex y adjacent to x)
        Relax3(x,y,w,pq_);
}*/
 
    
}
#endif /* DIJKSTRA_H */
