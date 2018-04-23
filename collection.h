#ifndef _COLLECTION_H
#define _COLLECTION_H
#include<iostream>
#include"linkedlist.h"
#include"piece.h"
using namespace std;
class Piece;
template<typename T>
class Collection{
public:
	~Collection();
	List<T> list;
	void add(T);
	void remove(T);
	void remove(Collection<T> *);
	void removeHelper(T *);
	void print();
	void clear();
	Collection();
	Collection(Piece *);
	Piece *piece;
};
template<typename T>
Collection<T>::~Collection(){
	//list.clear();
}
template<typename T>
Collection<T>::Collection(){
}
template<typename T>
Collection<T>::Collection(Piece *p){
	piece=p;
}
template<typename T>
void Collection<T>::add(T item){
	list.insert(item);
}
template<typename T>
void Collection<T>::removeHelper(T *obj){
	list.remove(obj);
}
template<typename T>
void Collection<T>::remove(Collection<T> *items){
	printf("removing multiple items\n");
	list.remove(&items->list);
/*
	for(auto p=items->list.begin();p!=items->list.end();p++){
		printf("removing ");
		(*p)->print();
		printf("\n");
		list.remove(*p);
	}
*/
}
template<typename T>
void Collection<T>::remove(T item){
	list.remove(item);
}
template<typename T>
void printHelper(T *data){
	//printf("%x\n",data);
	data->print();
}
template<typename T>
void Collection<T>::clear(){
	list.clear();
}
template<typename T>
void Collection<T>::print(){
	list.apply(printHelper);
//	for(T p:list)	p->print();
/*
	for(auto p=list.begin();p!=list.end();p++){
		(*p)->display();
	}
*/
	printf("\n");
}
#endif
