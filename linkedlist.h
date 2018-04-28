#ifndef _LINKEDLIST_H
#define _LINKEDLIST_H
#include<stdio.h>
#include<string.h>
template<typename T>
class Node{
public:
	Node *next;
	T item;
	Node()	{
		next=0;
		item=0;
	};
	Node(T item){
		this->item=item;
		this->next=0;
	}
	~Node(){
		if(item)
			delete item;
	}
};
template<typename T>
class List{
private:
public:
	int size;
	Node<T> *root;
	List(List<T> *l){
		root=new Node<T>();
		size=0;
		copy(l);
	}
	List(){
		root=new Node<T>();
		size=0;
	}
	~List(){
		Node<T> *ptr=root;
		Node<T> *tmp;
		while(ptr->next){
			tmp=ptr->next;
			delete ptr;
			ptr=tmp;
		}
		delete ptr;
	}
	T top(){
		if(root->next)
			return root->next->item;
		return 0;
	}
	//T &operator[](int n){
	T atIndex(int n){
		if(n>=size){
			printf("atIndex tried to access invalid index\n");
			return 0;
		}
		Node<T> *ptr=root;
		for(int i=0;i<=n;i++){
			ptr=ptr->next;
		}
		return ptr->item;
	}
	void insert(T item){
		Node<T> *tmp=root->next;
		root->next=new Node<T>(item);
		root->next->next=tmp;
		++size;
	}
	void insertAtEnd(T item){
		Node<T> *ptr=root;
		while(ptr->next){
			ptr=ptr->next;
		}
		ptr->next=new Node<T>(item);
		++size;
	}
	void apply(void (*f)(T)){
		Node<T> *ptr=root;
		while(ptr->next){
			ptr=ptr->next;
			f(ptr->item);
		}
	}
	Node<T> *find(T item){
		Node<T> *ptr=root;
		while(ptr->next){
			ptr=ptr->next;
			if((ptr->item)==item){
				return ptr;
			}
		}
		return 0;
	}
	Node<T> *pop(){
		if(size==0)	return 0;
		Node<T> *ret=root->next;
		root->next=root->next->next;
		size--;
		return ret;
	}
	void deepRemove(List<T> *items){
		Node<T> *ptr=items->root;
		while(ptr->next){
			deepRemove(ptr->next->item);
			ptr=ptr->next;
		}
	}
	void remove(List<T> *items){
		Node<T> *ptr=items->root;
		while(ptr->next){
			remove(ptr->next->item);
			ptr=ptr->next;
		}
	}
	void deepRemove(T item){
		Node<T> *ptr=root;
		Node<T> *ret;
		while(ptr->next){
			if((ptr->next->item)==item){
				ret=ptr->next;
				ptr->next=ptr->next->next;
				size--;
				delete ret;
				return;
			}
			ptr=ptr->next;
		}
	}
	Node<T> *remove(T item){
		Node<T> *ptr=root;
		Node<T> *ret;
		while(ptr->next){
			if((ptr->next->item)==item){
				ret=ptr->next;
				ptr->next=ptr->next->next;
				size--;
				return ret;
			}
			ptr=ptr->next;
		}
		return 0;
	}
	void copy(List<T> *list){
		size=list->size;
		Node<T> *ptr=list->root;
		Node<T> *sPtr=root;
		while(ptr->next){
			ptr=ptr->next;
			sPtr->next=new Node<T>(ptr->item);
			sPtr=sPtr->next;
		}
	}
	void deepCopy(List<T> *list){
		size=list->size;
		Node<T> *ptr=list->root;
		Node<T> *sPtr=root;
		T item;
		while(ptr->next){
			ptr=ptr->next;
			item=(T)malloc(100);
			std::memcpy(item,ptr->item,100);
			sPtr->next=new Node<T>(item);
			sPtr=sPtr->next;
		}
	}
	//shallow clear
	void deepClear(){
		Node<T> *ptr=root->next;
		Node<T> *prev;
		while(ptr){
			prev=ptr;
			ptr=ptr->next;
			delete prev;
		}
		size=0;
	}
	//shallow clear
	void clear(){
		root->next=0;
		size=0;
	}
};
#endif
