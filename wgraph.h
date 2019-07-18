/*
    wgraph.h
    Chris Madden
    07/10/19

*/

#ifndef _WGRAPH_H
#define _WGRAPH_H

#include <iostream>
#include <vector.h>
// #include <ovector.h>
#include <list.h>
// #include <olist.h>
// #include <rbllt_adt.h>
// #include <matrix.h>
 #include "graph.h"
 #include "aa.h"
 #include "hashclasses.h"
 #include "hashclasses.cpp"
 #include "xstring.cpp"

namespace fsu
{

  template < typename N >
  class ALUWGraph : public ALUGraph <N>
  {
  public:
    typedef N                                      Vertex;
    typedef fsu::String                            KeyType;
    typedef double                                 DataType;
    typedef hashclass::KISS < KeyType >            HashType;
    typedef fsu::Entry < KeyType, DataType >       EntryType;
    typedef fsu::List<EntryType>             BucketType;
    typedef fsu::HashTable<KeyType, DataType, HashType > SetType;
    typedef typename SetType::ConstIterator        AdjIterator;

    void   SetVrtxSize  (N n);
    size_t VrtxSize     () const;
    void   AddEdge      (Vertex from, Vertex to, double wt = 1.0);
    bool   HasEdge      (Vertex from, Vertex to) const;
    size_t EdgeSize     () const;           // Theta (|V| + |E|)
    size_t OutDegree    (Vertex v) const;
    size_t InDegree     (Vertex v) const;
    void   SetWeight  (Vertex from, Vertex to, double weight);
    void   GetWeight  (Vertex from, Vertex to);

    AdjIterator Begin   (Vertex v) const;
    AdjIterator End     (Vertex v) const;

    void Clear          ();
    void Dump           (std::ostream& os); // Theta (|V| + |E|)
    void Shuffle        (); // shuffles all adjacency lists

    ALUWGraph            ();
    explicit ALUWGraph   (N n);

  protected:
    SetType weight_;
    Vector < BucketType >  al_;
  };

  template < typename N >
  class ALDWGraph : public ALDGraph <N>
  {
  public:
    typedef N                                          Vertex;
    typedef fsu::String                            KeyType;
    typedef double                                 DataType;
    typedef hashclass::KISS < KeyType >            HashType;
    typedef fsu::Entry < KeyType, DataType >       EntryType;
    typedef fsu::HashTable<KeyType, DataType, HashType > SetType;
    typedef typename ALUGraph<N>::AdjIterator          AdjIterator;

     void   SetVrtxSize  (N n);
    // size_t VrtxSize     () const;
    void   AddEdge      (Vertex from, Vertex to, double wt = 1.0);
    // bool   HasEdge      (Vertex from, Vertex to) const;
    size_t EdgeSize     () const;          // Theta (|V| + |E|)
    // size_t OutDegree    (Vertex v) const;
    size_t InDegree     (Vertex v) const;  // Theta (|V| + |E|)

    ALDWGraph ( );
    explicit ALDWGraph ( N n );
  protected:
    SetType weight_;
    Vector < BucketType >  al_;
    // new method - creates d as the reverse directed graph of *this
  };

  /////////////////////////
  // ALU implementations //
  /////////////////////////

  template < typename N >
  ALUWGraph<N>::ALUWGraph () : al_(0){}

  template < typename N >
  ALUWGraph<N>::ALUWGraph ( N n ) : al_((size_t)n){}

  template < typename N >
  void ALUWGraph<N>::SetVrtxSize (N n)
  {
    weight_.Rehash((size_t)n);
  }

  template < typename N >
  void ALUWGraph<N>::AddEdge (Vertex from, Vertex to, double wt)
  {
    if (from == to) return;
    al_[(size_t)from].Insert(to);
    al_[(size_t)to].Insert(from);
    fsu::String key = fsu::ToHex(from) + "." + fsu::ToHex(to);
	  weight_.Insert(key, wt);
  }

  template < typename N >
  bool ALUWGraph<N>::HasEdge (Vertex from, Vertex to) const
  {
   fsu::String key = fsu::ToHex(from) + "." + fsu::ToHex(to);
    AdjIterator i = al_[from].Includes(to);
    if (i == End(from))
      return 0;
    weight_.Insert(key, wt);
    return 1;
  }

  template < typename N >
  size_t ALUWGraph<N>::VrtxSize () const
  {
    return weight_.Size();
  }

  template < typename N >
  size_t ALUWGraph<N>::EdgeSize () const // Theta (|V| + |E|)
  // Theta (|V| + |E|)
  {
    size_t esize = 0;
    for (Vertex v = 0; v < al_.Size(); ++v)
      esize += al_[v].Size();
    return esize >> 1; // divide by 2
  }

  template < typename N >
  size_t ALUWGraph<N>::OutDegree (Vertex v) const
  {
    return al_[v].Size();
  }

  template < typename N >
  size_t ALUWGraph<N>::InDegree (Vertex v) const
  {
    return OutDegree(v);
  }

  template < typename N >
  typename ALUWGraph<N>::AdjIterator ALUWGraph<N>::Begin (Vertex v) const
  {
    AdjIterator i = al_[v].Begin();
    return i;
  }

  template < typename N >
  typename ALUWGraph<N>::AdjIterator ALUWGraph<N>::End (Vertex v) const
  {
    AdjIterator i = al_[v].Begin();
    return i;
  }

  template < typename N >
  void ALUWGraph<N>::Dump (std::ostream& os)
  // Theta (|V| + |E|)
  {
    AdjIterator i;
    for (Vertex v = 0; v < VrtxSize(); ++v)
    {
      os << '[' << v << "]->";
      i = this->Begin(v);
      if (i != this->End(v))
      {
	os << *i;
	++i;
      }
      for ( ; i != this->End(v); ++i)
      {
	os << ',' << *i;
      }
      os << '\n';
    }
  }

  template < typename N >
  void ALUWGraph<N>::Shuffle()
  {
    for (Vertex v = 0; v < VrtxSize(); ++v) al_[v].Shuffle();
  }

  template < typename N >
  void ALUWGraph<N>::Clear()
  {
    for (Vertex v = 0; v < VrtxSize(); ++v) al_[v].Clear();
  }

  /////////////////////////
  // ALD implementations //
  /////////////////////////

  template < typename N >
  ALDWGraph<N>::ALDWGraph () : ALDGraph<N> (){}

  template < typename N >
  ALDWGraph<N>::ALDWGraph ( N n ) : ALDGraph<N>(n){}

  template < typename N >
  void ALDWGraph<N>::SetVrtxSize (N n)
  {
    weight_.Rehash((size_t)n);
  }
  template < typename N >
  void ALDWGraph<N>::AddEdge (Vertex from, Vertex to, double wt)
  {
    if (from == to) return;
    al_[(size_t)from].Insert(to);
    al_[(size_t)to].Insert(from);
    fsu::String key = fsu::ToHex(from) + "." + fsu::ToHex(to);
	  weight_.Insert(key, wt);
  }

  template < typename N >
  size_t ALDWGraph<N>::EdgeSize () const
  // Theta (|V| + |E|)
  {
    size_t esize = 0;
    for (Vertex v = 0; v < ALUGraph<N>::al_.Size(); ++v)
      esize += ALUGraph<N>::al_[v].Size();
    return esize;
  }

  template < typename N >
  size_t ALDWGraph<N>::InDegree (Vertex v) const
  // Theta (|V| + |E|)
  {
    size_t indegree = 0;
    AdjIterator i;
    for (Vertex x = 0; x < ALUGraph<N>::VrtxSize(); ++x)
    {
      for (i = this->Begin(x); i != this->End(x); ++i)
      {
	if (v == *i) ++indegree;
      }
    }
    return indegree;
  }

/*  template < typename N >
  void ALDWGraph<N>::Reverse(ALDGraph& d) const
  {
    d.Clear();
    d.SetVrtxSize(this->VrtxSize());
    for (Vertex v = 0; v < this->VrtxSize(); ++v)
    {
      for (AdjIterator i = this->Begin(v); i != this->End(v); ++i)
      {
        d.AddEdge(*i,v);
      }
    }
    return;
  }*/

} // namespace fsu
#endif
