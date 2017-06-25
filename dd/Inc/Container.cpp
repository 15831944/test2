#include "stdafx.h"
#include "Container.h"


using namespace Leaf::Container;

template <class T>
nLink<T>::nLink()
{
	head = new node<T>;
	head->next = head->prior = NULL;
}

template <class T>
nLink<T>::~nLink()
{
	DestoryLink();
}

template <class T>
void nLink<T>::ClearLink()
{
	node<T> *p = head->next,*q = NULL;
	while(p){
		q = p->next;
		delete p;
		p = q;
	}
	head->next = NULL;
}

template <class T>
void nLink<T>::DestoryLink()
{
	ClearLink();
	if(head){
		delete head;
		head = NULL;
	}
}

template <class T>
void nLink<T>::PrintLink()
{
	node<T> *p = head->next;
	while(p){
		cout<<p->data<<" ";
		p = p->next;
	}
	cout<<endl;
}

template <class T>
bool nLink<T>::AppendLink(T e)
{
	node<T> *p = head,*s = NULL;
	s = new node<T>;
	if(s == NULL)
		return false;
	s->data = e;
	s->next = s->prior = NULL;
	while(p->next){
		p = p->next;
	}
	p->next = s;
	s->prior = p;
	return true;
}

template <class T>
int nLink<T>::Length()
{
	int i = 0;
	node<T> *p = head->next;
	while(p)
	{
		++i;
		p = p->next;
	}
	return i;
}

template <class T>
bool nLink<T>::InsertLink(int pos , T e)
{
	node<T> *p = head , *s = NULL;
	int j = 0;
	s = new node<T>;
	if(s == NULL)
		return false;
	s->data = e;
	s->prior = s->next = NULL;
	while(p && j < pos -1)
	{
		++j;
		p = p->next;
	}
	if(p == NULL || j > pos - 1)
	{
		return false;
	}
	s->next = p->next;
	if(p->next != NULL){	//当p是最后一个节点时，p->next == NULL
		p->next->prior = s;
	}
	p->next = s;
	s->prior = p;
	return true;
}

template <class T>
bool nLink<T>::DeleteNode(int pos)
{
	if(pos < 1 || pos > Length())
	{
		return false;
	}
	node<T> *p = head;	//p 为要删除的节点
	int j = 0;
	while(p && j < pos)
	{
		++j;
		p = p->next;
	}
	//要注意删除的是不是尾节点
	if(p && p->next == NULL){
		p->prior->next = NULL;
		delete p;
		p = NULL;
	}else{
		p->prior->next = p->next;
		p->next->prior = p->prior;
		delete p;
		p = NULL;
	}
	return true;
}

template <class T>
bool nLink<T>::DeleteNode(T e)
{
	node<T> *p = head->next;
	while(p){
		if(p->data == e){
			break;
		}
		p = p->next;
	}
	if(p == NULL){
		cout<<"not found the elem :"<< e <<endl;
		return false;
	}
	//判读要删除的是不是尾节点
	if(p->next == NULL){
		p->prior->next = NULL;
	}else{
		p->prior->next = p->next;
		p->next->prior = p->prior;
	}
	delete p;
	p = NULL;
	return true;
}

//////////////////////////////////////////////////////////////////////////
//