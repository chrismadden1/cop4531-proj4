#ifndef WGRAPH_H
#define WGRAPH_H

#include <graph_util.h>
#include <list.h>
#include <vector.h>
#include <cstdlib>

namespace fsu {
    
    template < typename N >
    class ALUWGraph : public ALUGraph <N>
    {
    public:
        
        typedef N                                   	 Vertex;
		typedef typename fsu::List<Vertex>               SetType2;
		//****need to map an edge to a real number value.
		//add two edges together like key = ToHex(x)+"."+ToHex(y). 
		typedef typename fsu::HashTable<fsu::String, double>    SetType;
        typedef typename SetType::ConstIterator    		 AdjIterator;
        
        void     SetVrtxSize (N n);
        size_t   VrtxSize    () const;
        void     AddEdge     (Vertex from, Vertex to, double weight = 1.0);
		bool     HasEdge     (Vertex from, Vertex to, double& wt) const; // sets wt variable if edge exists
		//Edge<N>  GetEdge     (Vertex from, Vertex to) const;             // returns [0,0,0.0] if edge does not exist
		void     SetWeight   (Vertex from, Vertex to, double weight);    // (re)sets weight
		double   GetWeight   (Vertex from, Vertex to) const;             // returns weight if edge exists, 0.0 otherwise
        size_t   EdgeSize    () const;
        size_t   OutDegree   (Vertex v) const;  
        size_t   InDegree    (Vertex v) const;    
        
        AdjIterator Begin   (Vertex x) const;
        AdjIterator End     (Vertex x) const;
        
        ALUWGraph            (); //constructor
        explicit ALUWGraph   (N n); //constructor with no type converting allowed
        
    protected:
        
        fsu::Vector <SetType2> al_; //map containing the vertices 
		
		fsu::Vector <SetType> weight_; //for mapping edges to weight.
        
    }; //end class ALUWGraph
    
    
    //Directed graph - derived from undirected graph
    template < typename N >
    class ALDWGraph : public ALDGraph <N>
    {
    public:
        typedef N                                    Vertex;
        typedef typename ALUWGraph<N>::SetType       SetType;
        typedef typename ALUWGraph<N>::AdjIterator   AdjIterator;
        
        void    AddEdge    (Vertex from, Vertex to, double weight = 1.0);
        size_t  EdgeSize   () const;
        size_t  InDegree   (Vertex v) const;
        void 	Reverse    (ALDWGraph & d) const;
        
        ALDWGraph            ();
        explicit ALDWGraph   (N n);
        
    }; //end class ALDWGraph
	
	
	template < typename N >
    void ALUWGraph<N>::AddEdge(Vertex from, Vertex to, double wt)
    {
        al_[from].Insert(to); //adds "to" vertex to the corresponding list
        al_[to].Insert(from);
		//al_ = {(from, to)->wt};
		fsu::String key = ToHex(from) + "." + ToHex(to);
		weight_.Put(key, wt);
    }
	
    template < typename N >
    bool ALUWGraph<N>::HasEdge (Vertex from, Vertex to, double &wt) const
    {
        AdjIterator i = al_[from].Includes(to);
        if (i == al_[from].End())
            return 0; //not found
		fsu::String key = ToHex(from) + "." + ToHex(to);
		weight_.Put(key, wt);
        return 1; //found
    }
	
	
	template < typename N >
	size_t ALUWGraph<N>::EdgeSize () const // Theta (|V| + |E|)
	{
	size_t esize = 0;
	for (Vertex v = 0; v < al_.Size(); ++v)
		esize += al_[v].Size();
	return esize/2;
	}
	
	/*template < typename N >
	Edge<N> ALUWGraph<N>::GetEdge(Vertex from, Vertex to) const
	{
		return [0, 0, 0.0]; //if doesn't exist.
		
	}*/
	
	template < typename N >
    void ALUWGraph<N>::SetWeight(Vertex from, Vertex to, double wt)
    {
       fsu::String key = ToHex(from) + "." + ToHex(to);
	   weight_.Put(key, wt);
    }
	
	template < typename N >
    void ALUWGraph<N>::OutDegree(Vertex v)
    {
      return al_[v].Size(); //return size of list corresponding to vertex
    }
	
	template < typename N >
    void ALUWGraph<N>::InDegree(Vertex v)
    {
      return al_[v].Size(); //return size of list corresponding to vertex
    }
	
	template < typename N >
    typename ALUWGraph<N>::AdjIterator ALUWGraph<N>::Begin (Vertex x) const
    {
        return al_[x].Begin(); //returns Begin list iterator
    }
    
    template < typename N >
    typename ALUWGraph<N>::AdjIterator ALUWGraph<N>::End (Vertex x) const
    {
        return al_[x].End(); //returns End list iterator
    }
	
	template < typename N >
    ALUWGraph<N>::ALUWGraph()
    {} //default constructor 
    
    template < typename N >
    ALUWGraph<N>::ALUWGraph(N n)
    {
        al_.SetSize(n); 
		weight_.SetSize(n); 
    }
	
	template < typename N >
    void ALDWGraph<N>::AddEdge(Vertex from, Vertex to, double weight)
    {
      (this->al_)[from].Insert(to);
	   fsu::String key = ToHex(from) + "." + ToHex(to);
	   weight_.Put(key, wt);
    }
	
	template < typename N >
    void ALDWGraph<N>::EdgeSize()
    {
        size_t esize = 0;
        for (Vertex v = 0; v < (this->al_).Size(); ++v)
            esize += ALUWGraph<N>::al_[v].Size();
        return esize;
    }
	
	template < typename N >
    void ALDWGraph<N>::InDegree(Vertex v) const
    {
      size_t indegree = 0;
        AdjIterator j;
        for (Vertex x = 0; x < this->VrtxSize(); ++x)
        {
            for (j = this->Begin(x); j != this->End(x); ++j)
            {
                if (v == *j) ++indegree;
            }
        }
        return indegree;
    }
	
	  template < typename N >
    ALDGraph<N>::ALDGraph () : ALUGraph<N>() //default constructor
    {}
    
    template < typename N >
    ALDGraph<N>::ALDGraph(N n) : ALUGraph<N> (n)
    {}
	

#endif
