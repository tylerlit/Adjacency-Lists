#include "Graph.h"
#include <iostream>    //for dump()

using namespace std;


Graph::Graph(int n ){

  if(n <= 0){
    try{
      throw out_of_range ("Graph index less than or equal to 0");
    }
    catch(const out_of_range& oor){
      cerr << "Out of Range error: " << oor.what() << endl;
    }
  }
  else{
    m_size = n;
    m_adjLists = new AdjListNode*[m_size]; //create array of pointers

    for(int i = 0; i < m_size; i++){
      m_adjLists[i] = new AdjListNode(i,NULL); //allocate each pointer
    }
  }
}

Graph::Graph(const Graph& G){

    m_size = G.m_size;
    m_adjLists = new AdjListNode*[m_size];

    for (int i = 0; i < m_size ; i++){

        AdjListNode *currentPtr = G.m_adjLists[i] ;

        m_adjLists[i] = new AdjListNode ;
        AdjListNode *tempPtr = m_adjLists[i] ;

        while(currentPtr != NULL){

            tempPtr->m_vertex = currentPtr->m_vertex ;

            if (currentPtr->next != NULL){

                tempPtr->next = new AdjListNode ;
                tempPtr = tempPtr->next ;

            }
            else
                tempPtr->next = NULL ;

            currentPtr = currentPtr->next ;
        }
    }
}

Graph::~Graph(){


    //deallocate each array of pointers
    for(int i = 0; i < m_size; i++){
        AdjListNode *deletePtr = m_adjLists[i] ;
        while (deletePtr){
            m_adjLists[i] = m_adjLists[i]->next;
            delete deletePtr;
            deletePtr = m_adjLists[i];
        }
    }
    delete [] m_adjLists ;
}

int Graph::size(){

    return m_size ;

}

const Graph& Graph::operator= (const Graph& rhs){

    if(this != &rhs){

        this->~Graph() ;

        m_size = rhs.m_size ;
        m_adjLists = new AdjListNode*[m_size] ;

        for(int i = 0; i < m_size ; i++){

            AdjListNode *currentPtr = rhs.m_adjLists[i] ;
            m_adjLists[i] = new AdjListNode ;    
            AdjListNode *tempPtr = m_adjLists[i] ;

                while(currentPtr != NULL){

                    tempPtr->m_vertex = currentPtr->m_vertex ;

                    if (currentPtr->next != NULL){

                        tempPtr->next = new AdjListNode ;
                        tempPtr = tempPtr->next ;
                    }
                    else 
                        tempPtr->next = NULL ;

                    currentPtr = currentPtr->next ;
                }
        }
    }
    return *this ;
}

void Graph::addEdge(int u ,int v){

  //out of range exception code
  if(u < 0 || u >= m_size){
    try{
      throw out_of_range ("Edge index u is out of range");
    }
    catch(const out_of_range& oor){
      cerr << "Out of Range error: " << oor.what() << endl;
    }
  }
  else if(v < 0 || v >= m_size){
    try{
      throw out_of_range ("Edge index v is out of range");
    }
    catch(const out_of_range& oor){
      cerr << "Out of Range error: " << oor.what() << endl;
    }
  }
  else if(u == v){
      if(m_adjLists[v]->next == NULL){
          m_adjLists[v]->next = new AdjListNode;
          m_adjLists[v]->next->m_vertex = u;
          //m_adjLists[v]->next->next = NULL;
    }
    else if(m_adjLists[v]->next != NULL){
        AdjListNode *temp = m_adjLists[v]->next; 
        m_adjLists[v]->next = new AdjListNode;
        m_adjLists[v]->next->m_vertex = u;
        m_adjLists[v]->next->next = temp; 
      }
  }
  else{
    if(m_adjLists[u]->next == NULL){  //if the vertice doesnt have an
                                      //existing node 
        m_adjLists[u]->next = new AdjListNode; // creates a new node 
        m_adjLists[u]->next->m_vertex = v;
     //   m_adjLists[u]->next->next = NULL;  //sets that info 
    }
    else if(m_adjLists[u]->next != NULL){
        AdjListNode *temp = m_adjLists[u]->next; //save location of node
        m_adjLists[u]->next = new AdjListNode;
        m_adjLists[u]->next->m_vertex = v;  //sets that info
        m_adjLists[u]->next->next = temp;   //keeps da chain going
    }

    if(m_adjLists[v]->next == NULL){
        m_adjLists[v]->next = new AdjListNode;
        m_adjLists[v]->next->m_vertex = u;
    //    m_adjLists[v]->next->next = NULL;
    }
    else if(m_adjLists[v]->next != NULL){
        AdjListNode *temp = m_adjLists[v]->next; 
        m_adjLists[v]->next = new AdjListNode;
        m_adjLists[v]->next->m_vertex = u;
        m_adjLists[v]->next->next = temp; 
      }
    }
}


void Graph::dump(){
  
  AdjListNode *head;
  
  cout << "Dump out graph (size = " << m_size << "):" << endl;
  
  for(int i = 0; i < m_size; i++){ 
    head = m_adjLists[i]->next;
    cout << "[" << m_adjLists[i]->m_vertex << "]:";
      while(head != NULL){
        cout << " " << head->m_vertex;
        head = head->next;
      } 
     cout << endl;
  }
}


Graph::EgIterator::EgIterator(Graph *Gptr/* = NULL */, bool isEnd/*= false */){

    m_Gptr = Gptr;

    if(Gptr == NULL){
        m_source = -1;
        m_where = NULL;
    }
    else if(isEnd){
        m_source = Gptr->size();
        m_where = NULL;
    }
    else{
        m_source = 0;
        m_where = Gptr->m_adjLists[m_source]->next;
    }
}

bool Graph::EgIterator::operator!= (const EgIterator& rhs){

    //once m_source is incremented to size(), end iteration
    if(m_source == rhs.m_source){
        return false;
    }
    else{
        return true;
    }

}

void Graph::EgIterator::operator++(int dummy){

    bool found = false;
    
    while(!found){
        //go to next edge
        m_where = m_where->next;
        //only happens when we reach the end of the linked listerine
        if(m_where == NULL){
            m_source++;
            //break loop when we reach ultimate end of linked list
            if(m_source == m_Gptr->size()){
                break;
            }
            //redirect m_where to next m_adjList
            m_where = m_Gptr->m_adjLists[m_source]->next;
        }
        //found an edge we need!!!! hooray!!!
        if(m_source <= m_where->m_vertex){
            found = true;
        }
    }
}

pair<int,int> Graph::EgIterator::operator*(){

    if(m_where == NULL){
	    throw out_of_range("EgIterator dereference error.");
    }

    return pair<int,int>(m_source, m_where->m_vertex);

}

Graph::EgIterator Graph::egBegin(){

    return (EgIterator(this, false));

}

Graph::EgIterator Graph::egEnd(){

    return (EgIterator(this, true));

}



Graph::NbIterator::NbIterator(Graph *Gptr, int v, bool isEnd){

    m_Gptr = Gptr;

   if(Gptr == NULL){
        m_source = -1;
        m_where = NULL;
    }
    else if(isEnd){
        m_source = Gptr->size();
        m_where = NULL;
    }   
    else{
        m_source = v; 
        m_where = Gptr->m_adjLists[m_source]->next;
    } 

}

bool Graph::NbIterator::operator!= (const NbIterator& rhs){

    if(m_where == NULL){
        return false;
    }
    else{
        return true;
    }
}

void Graph::NbIterator::operator++(int dummy){

    m_where = m_where->next;
 
}

int Graph::NbIterator::operator*(){

    if(m_where == NULL){
        throw out_of_range("NbIterator dereference error.");
    }
    return m_where->m_vertex;

}

Graph::NbIterator Graph::nbBegin(int v){

    return (NbIterator(this, v, false));

}

Graph::NbIterator Graph::nbEnd(int v){

    return (NbIterator(this, v, true));

}


Graph::AdjListNode::AdjListNode(int v/*=-1*/, Graph::AdjListNode *ptr/*=NULL*/){

  m_vertex = v;
  next = ptr;

}

