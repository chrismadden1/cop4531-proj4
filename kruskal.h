/*
    kruskal.h
    7/08/2019
    Chris Madden
    implements kruskal algorithm on weighted graphs
*/

#ifndef KRUSKAL_H
#define KRUSKAL_H

template < class G>
class Kruskal 
{
  typedef G                      Graph
  typedef typename G::Vertex     Vertex;
  //typedef fsu::Edge<Vertex>      Edge;
 // typedef fsu::Vector<Edge>      Container;
  typedef fsu::GreaterThan<Edge> Predicate;
 // typedef fsu::PriorityQueue<Edge,Container,Predicate> PQ;


public:
  // constructor initializes all class variables in init list
  Kruskal (const G& g);

  // implementing the algorithm
  void Init(bool verbose = 0); // preps class variables for execution of algorithm
  void Exec(bool verbose = 0); // runs algorithm

  // extracting information
  const fsu::List<Edge>& MST() const;
  double                 Weight() const;
private:
  const Graph& g_;
  PQ           pq_;
};


//implementations
template < class G>
void Kruskal<G>::Init(bool verbose)
{
    /*init queue in sorted order by increasing weight
    //init partition p(|v|)
    //init f as empty
      if (verbose)
  {
    std::cout << "Init: Initial edges in PQ: " << pq_.Size() << '\n';
    if (pq_.Size() < 20)
    {
      std::cout << "PQ.Dump():\n";
      pq_.Dump(std::cout, '\n');
      std::cout << '\n';
    }   
      }*/
}

template < class G>
void Kruskal<G>::Exec(bool verbose)
{
    /*
    [x,y] = q.Front();
    q.Pop();
    if(!p.Find(x,y))
    {
    F = F.Union{[x,y]};
    p.Union(x,y);
    }
    output(v,F);
    */
    
}
#endif /* KRUSKAL_H */
