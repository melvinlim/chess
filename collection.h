#ifndef _COLLECTION_H
#define _COLLECTION_H
#include<forward_list>
#include<iostream>
using namespace std;
template<typename T>
class Collection{
public:
	~Collection();
	forward_list<T> list;
	void add(T);
	void remove(T);
	void print();
};
template<typename T>
Collection<T>::~Collection(){
	list.clear();
}
template<typename T>
void Collection<T>::add(T item){
	list.push_front(item);
}
template<typename T>
void Collection<T>::remove(T item){
	list.remove(item);
}
template<typename T>
void Collection<T>::print(){
	for(T p:list)	p->print();
/*
	for(auto p=list.begin();p!=list.end();p++){
		(*p)->display();
	}
*/
	printf("\n");
}
#endif
