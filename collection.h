#ifndef _COLLECTION_H
#define _COLLECTION_H
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
	void deepRemove(T);
	void deepRemove(Collection<T> *);
	void remove(T);
	void remove(Collection<T> *);
	void removePiece(Piece *);
	void removeHelper(T *);
	void print();
	void printAll();
	void clear();
	void deepClear();
	Node<T> *find(T);
	bool isEmpty();
	T randomElement();
	Collection();
	Collection(Piece *);
	Collection(Collection<T> *);
	Piece *piece;
	int size();
	int index;
	T nextElement();
};
template<typename T>
int Collection<T>::size(){
	return list.size;
}
template<typename T>
Node<T> *Collection<T>::find(T item){
	return list.find(item);
}
template<typename T>
bool Collection<T>::isEmpty(){
	return(list.size==0);
}
template<typename T>
T Collection<T>::nextElement(){
	index=(index+1)%list.size;
	return list.atIndex(index);
}
template<typename T>
T Collection<T>::randomElement(){
	srand(time(0));
	int randval=rand()%list.size;
	T ret=list.atIndex(randval);
	return ret;
}
template<typename T>
void Collection<T>::removePiece(Piece *piece){
	Node<T> *p=list.root;
	while (p->next){
		p=p->next;
		T sptr=p->item;
		sptr->attackers->remove(piece);
	}
}
template<typename T>
Collection<T>::~Collection(){
	//list.clear();
}
template<typename T>
Collection<T>::Collection(){
	index=0;
}
template<typename T>
Collection<T>::Collection(Collection<T> *p){
	index=0;
	list.deepCopy(&p->list);
}
template<typename T>
Collection<T>::Collection(Piece *p){
	index=0;
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
void Collection<T>::deepRemove(Collection<T> *items){
	list.deepRemove(&items->list);
}
template<typename T>
void Collection<T>::remove(Collection<T> *items){
	list.remove(&items->list);
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
void Collection<T>::deepClear(){
	list.deepClear();
}
template<typename T>
void Collection<T>::clear(){
	list.clear();
}
template<typename T>
void printAllHelper(T *data){
	data->printAll();
}
template<typename T>
void Collection<T>::printAll(){
	list.apply(printAllHelper);
}
template<typename T>
void Collection<T>::print(){
	list.apply(printHelper);
	printf(" (%d)",list.size);
//	for(T p:list)	p->print();
/*
	for(auto p=list.begin();p!=list.end();p++){
		(*p)->display();
	}
*/
//	printf("\n");
}
#endif
