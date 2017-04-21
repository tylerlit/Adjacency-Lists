#include <iostream>
#include <utility>
#include "Graph.cpp"

using namespace std;

int main(){

    Graph G(5); // G has vertices 0 thru 4
    Graph G2(10);
    Graph G3 = G; //copy constructor
    
    Graph G4(0); //out of range
    Graph G5(-1); // also out of range
    Graph G6(-9999); //just in case

    //add some edges yes
    G.addEdge(0,1);
    G.addEdge(0,4);
    G.addEdge(0,3);
    G.addEdge(1,4);
    G.addEdge(2,2);
    G.addEdge(3,4);
    G.addEdge(2,1);
    G.addEdge(2,4);

    G2 = G ; //assignment operator

    //call dump to see mess of results
    G.dump();
    G2.dump();
    G3.dump();

    
    //iterate them neighbor jaunts
    Graph::NbIterator nit;
  
    for (nit = G.nbBegin(4); nit != G.nbEnd(4) ; nit++) {
       cout << *nit << " ";
     }
    cout << endl;

    //itermate them edges now
    Graph::EgIterator eit;
    pair<int,int> edge;

   for (eit = G.egBegin() ; eit != G.egEnd() ; eit++) {
      edge = *eit;   // get current edge
      cout << "(" << edge.first << ", " << edge.second << ") ";
   }
   cout << endl;

  G.~Graph() ;
  G2.~Graph() ;

  return 0;

}