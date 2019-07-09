#ifndef WGRAPH_H
#define WGRAPH_H

#include <graph_util.h>
#include <list.h>
#include <vector.h>
#include <cstdlib>

namespace fsu {
    
    template < typename N >
    class ALUWGraph
    {
    public:
        
        typedef N                                   Vertex;
		//****need to map an edge to a real number value.
		typedef typename fsu::HashTable<Edge, double>    SetType;
        typedef typename SetType::ConstIterator     AdjIterator;
        
        void     SetVrtxSize (N n);
        size_t   VrtxSize    () const;
        void     AddEdge     (Vertex from, Vertex to, double weight = 1.0);
		bool     HasEdge     (Vertex from, Vertex to, double& wt) const; // sets wt variable if edge exists
		Edge<N>  GetEdge     (Vertex from, Vertex to) const;             // returns [0,0,0.0] if edge does not exist
		void     SetWeight   (Vertex from, Vertex to, double weight);    // (re)sets weight
		double   GetWeight   (Vertex from, Vertex to) const;             // returns weight if edge exists, 0.0 otherwise
        size_t   EdgeSize    () const;
        size_t   OutDegree   (Vertex v) const;   //same as unweighted graph
        size_t   InDegree    (Vertex v) const;   //same as unweighted graph   
        
        AdjIterator Begin   (Vertex x) const;
        AdjIterator End     (Vertex x) const;
        
        ALUWGraph            (); //constructor
        explicit ALUWGraph   (N n); //constructor with no type converting allowed
        
    protected:
        
        fsu::Vector <SetType> al_; //map containing the vertices and weight
		//fsu::Vector <SetType> weight_; //for mapping edges to weight.
        
    }; //end class ALUWGraph
    
    
    //Directed graph - derived from undirected graph
    template < typename N >
    class ALDWGraph : public ALUWGraph <N>
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
		al_ = {(from, to)->wt};
    }
	
    template < typename N >
    bool ALUWGraph<N>::HasEdge (Vertex from, Vertex to, double &wt) const
    {
        AdjIterator i = al_[from].Includes(to);
        if (i == al_[from].End())
            return 0; //not found
		al_ = {(from, to)->wt};
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
	
	template < typename N >
	Edge<N> ALUWGraph<N>::GetEdge(Vertex from, Vertex to) const
	{
		return [0, 0, 0.0]; //if doesn't exist.
		
	}
	
	template < typename N >
    void ALUWGraph<N>::SetWeight(Vertex from, Vertex to, double wt)
    {
       al_= {(from, to) -> wt};
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
    }
	
	
	

#endif
