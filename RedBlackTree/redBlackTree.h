#ifndef _redBlackTree_h
#define _redBlackTree_h

#include <iostream>
#include <queue>
#include <cmath>

template <typename T>
class RBT{
private:
	enum color {red,black};
	struct node {
		T __keyWord;
		node* __pParent;
		node* __pLC;
		node* __pRC;
		enum color __nodeColor;
		node(T t, node* pP, node* pL , node* pR , enum color C = red) :__keyWord(t), __pParent(pP), __pLC(pL), __pRC(pR), __nodeColor(C) {}
	};
public:
	RBT():_hot(nullptr){
		extrnode=new node(-1, nullptr, nullptr, nullptr,black);
		_root=extrnode;
	}
	~RBT(){
		void clear();
		delete extrnode;
	}
	node* search(const T& e){//search:当搜索到该项时，返回该节点的指针，否则返回哨兵节点，即外部节点；
		node* x=_root;
		_hot=nullptr;
		while(x!=extrnode){
			if(e==x->__keyWord)
				return x;
			else{
				_hot=x;//_hot指向返回节点的父节点，返回根或为空树时，_hot为nullptr
			    e < x->__keyWord?x=x->__pLC:x=x->__pRC;
			}
		}
		return extrnode;//返回extrnode
	}
	node * insert(const T& e){
		node* r=search(e);//找到插入点
		if(r!=extrnode) return r;//找到相同的key，就不插入
		node* t=new node(e,_hot,extrnode,extrnode);
		if(!_hot){//如果_hot为nullptr则空树插入
			_root=t;
		}else{//树非空时插入
			if(e<_hot->__keyWord)
				_hot->__pLC=t;
			else
				_hot->__pRC=t;
		}
		solveDoubleRed(t);
		return t;
	}

	bool remove(const T& e){
		node* r =search(e);//确定待删除节点是否存在
		if(r==extrnode) return false;
		node* x=findRMP(r);//找到实际删除节点
		if(!_hot){//删除根节点
			_root=_root->__pLC!=extrnode?_root->__pLC:_root->__pRC;
			delete x;
			if(_root!=extrnode&&_root->__nodeColor==red)
				_root->__nodeColor=black;
		}else{
			enum color rnodeColor=x->__nodeColor;//获得实际待删除节点颜色，已判断是否双黑，将哨兵节点当做黑色，统一处理
			r=realRM(x,r);//实际删除节点
			if(r->__nodeColor==black&&rnodeColor==black){//双黑
				solveDoubleBlack(r);
			}else{
				if(r!=extrnode)//如果非双黑，且r存在，则直接置黑
					r->__nodeColor=black;
			}
		}
		return true;
	}

	void travel()const{
		std::queue<node*> queues;
		node* sRoot=_root;
		queues.push(sRoot);
		int i=0,j=0;
		while(!queues.empty()){
			sRoot=queues.front();
			queues.pop();
			if(sRoot!=extrnode){
				std::cout<<sRoot->__keyWord<<" "<<sRoot->__nodeColor<<"    ";
				queues.push(sRoot->__pLC);
				queues.push(sRoot->__pRC);
				i++;
			}
			else{
				std::cout<<-1<<" "<<black<<"    ";
				i++;
			}
			if(double(i)>=pow(2.0,double(j))){
				std::cout<<std::endl;
				j++;
				i=0;
			}
		}
	}

private:
	void solveDoubleRed(node* x){
		while(true){
			if(!_hot){//空树插入
				_root->__nodeColor=black;
				return;
			}else{//非空插入
				if(_hot->__nodeColor==red){//双红情况
					if(uncle(x)->__nodeColor==black){//u为黑色,3+4重构
						solveDoubleRedB(x);
						return;
					}else{//u为红色
						solveDoubleRedR(x);
						continue;
					}
				}
				return;//插入点父节点为黑色直接返回
			}
		}
	}
	void solveDoubleRedB(node* x){//修复RRB的情况，只用进行一次3+4操作，和两次染色操作，
		node* p=x->__pParent;
		node* g=p->__pParent;
		if(isLChild(p,g)){
			if(isLChild(x, p)){
				p->__pParent=g->__pParent;
				if(g->__pParent){//将新的局部根节点，连接到新的父节点
					if(isLChild(g, g->__pParent))
						g->__pParent->__pLC=p;
					else
						g->__pParent->__pRC=p;
				}
				connect34(x->__pLC,x,x->__pRC,p,p->__pRC,g,g->__pRC);
				p->__nodeColor=black;
				g->__nodeColor=red;
			}else{
				x->__pParent=g->__pParent;
				if(g->__pParent){
					if(isLChild(g, g->__pParent))
						g->__pParent->__pLC=x;
					else
						g->__pParent->__pRC=x;
				}
				connect34(p->__pLC,p,x->__pLC,x,x->__pRC,g,g->__pRC);
				x->__nodeColor=black;
				g->__nodeColor=red;
			}
		}else{
			if(isLChild(x,p)){
				x->__pParent=g->__pParent;
				if(g->__pParent){
					if(isLChild(g, g->__pParent))
						g->__pParent->__pLC=x;
					else
						g->__pParent->__pRC=x;
				}
				connect34(g->__pLC,g,x->__pLC,x,x->__pRC,p,p->__pRC);
				x->__nodeColor=black;
				g->__nodeColor=red;
			}else{
				p->__pParent=g->__pParent;
				if(g->__pParent){
					if(isLChild(g, g->__pParent))
						g->__pParent->__pLC=p;
					else
						g->__pParent->__pRC=p;
				}
				connect34(g->__pLC,g,p->__pLC,p,x->__pLC,x,x->__pRC);
				p->__nodeColor=black;
				g->__nodeColor=red;
			}
		}
		if(_root==g)//在根节点做变换的情况
			_root=g->__pParent;
	}
	void connect34(node* t0,node* a,node* t1,node* b,node* t2,node* c,node* t3){
		a->__pLC=t0;if(t0!=extrnode) t0->__pParent=a;
		a->__pRC=t1;if(t1!=extrnode) t1->__pParent=a;
		c->__pLC=t2;if(t2!=extrnode) t2->__pParent=c;
		c->__pRC=t3;if(t3!=extrnode) t3->__pParent=c;
		b->__pLC=a;
		b->__pRC=c;
		a->__pParent=b;
		c->__pParent=b;
	}
	void solveDoubleRedR(node* & x){
		node* p=x->__pParent;
		node* g=p->__pParent;
		node* u=uncle(x);
		p->__nodeColor=black;
		u->__nodeColor=black;
		g->__nodeColor=red;
		x=g;//插入点由想，转移至g
		_hot=g->__pParent;
	}
	node* findRMP(node* x){//返回实际删除节点;不可能返回extrnode
		node* sRoot=x->__pRC;
		node* r=x;
		while(sRoot!=extrnode){
			r=sRoot;
			sRoot=sRoot->__pLC;
		}
		_hot=r->__pParent;
		return r;
	}
	node* realRM(node* x,node* r){//实行删除操作,链接相关实际删除节点的子节点和父节点,返回被删除节点的替代节点
		r->__keyWord=x->__keyWord;
		if(isLChild(x,_hot)){
			_hot->__pLC=x->__pLC!=extrnode?x->__pLC:x->__pRC;
			if(_hot->__pLC!=extrnode)
				_hot->__pLC->__pParent=_hot;
			r=_hot->__pLC;
		}else{
			_hot->__pRC=x->__pLC!=extrnode?x->__pLC:x->__pRC;
			if(_hot->__pRC!=extrnode)
				_hot->__pRC->__pParent=_hot;
			r=_hot->__pRC;
		}
		delete x;
		return r;
	}
	void solveDoubleBlack(node* x){//TODO：不应该这么复杂
		while(true){
			node* p=x!=extrnode?x->__pParent:_hot;
			node* s=p->__pLC==x?p->__pRC:p->__pLC;//s不可能为空，否则违反红黑树黑高度性质
			if(s->__nodeColor==black){
				if(s->__pLC->__nodeColor==red){//BB1-1
					node* t=s->__pLC;
					if(isLChild(s,p)){
						s->__pParent=p->__pParent;
						if(p->__pParent){//将新的局部根节点，连接到新的父节点
							if(isLChild(p, p->__pParent))
								p->__pParent->__pLC=s;
							else
							    p->__pParent->__pRC=s;
						}
						connect34(t->__pLC,t,t->__pRC,s,s->__pRC,p,x);
						s->__nodeColor=p->__nodeColor;
						p->__nodeColor=black;
						t->__nodeColor=black;
						if(p==_root)
							_root=s;
					}else{
						t->__pParent=p->__pParent;
						if(p->__pParent){//将新的局部根节点，连接到新的父节点
							if(isLChild(p, p->__pParent))
								p->__pParent->__pLC=t;
							else
								p->__pParent->__pRC=t;
							}
						connect34(x,p,t->__pLC,t,t->__pRC,s,s->__pRC);
						t->__nodeColor=p->__nodeColor;
						p->__nodeColor=black;
						if(p==_root)
							_root=t;
					}
					return;
				}else if(s->__pRC->__nodeColor==red){//BB1-2
					node* t=s->__pRC;
					if(isLChild(s,p)){
						t->__pParent=p->__pParent;
						if(p->__pParent){//将新的局部根节点，连接到新的父节点
							if(isLChild(p, p->__pParent))
								p->__pParent->__pLC=t;
							else
								p->__pParent->__pRC=t;
						}
						connect34(s->__pLC,s,t->__pLC,t,t->__pRC,p,x);
						t->__nodeColor=p->__nodeColor;
						p->__nodeColor=black;
						if(p==_root)
							_root=t;
					}else{
						s->__pParent=p->__pParent;
						if(p->__pParent){//将新的局部根节点，连接到新的父节点
							if(isLChild(p, p->__pParent))
								p->__pParent->__pLC=s;
							else
								p->__pParent->__pRC=s;
						}
						connect34(p->__pLC,p,s->__pLC,s,t->__pLC,t,t->__pRC);
						s->__nodeColor=p->__nodeColor;
						p->__nodeColor=black;
						t->__nodeColor=black;
						if(p==_root)
							_root=s;
					}
					return;
				}else{//BB2
					if(p->__nodeColor==red){//BB2-1
						s->__nodeColor=red;
						p->__nodeColor=black;
						return;
					}else{//BB2-2
						s->__nodeColor=red;
						x=p;
						if(x==_root)
							return;
					}
				}
			}else{//BB3
				s->__pParent=p->__pParent;
				if(p->__pParent){//将新的局部根节点，连接到新的父节点
					if(isLChild(p, p->__pParent))
						p->__pParent->__pLC=s;
					else
						p->__pParent->__pRC=s;
				}
				p->__pLC=s->__pRC;
				s->__pRC->__pParent=p;
				s->__pRC=p;
				p->__pParent=s;
				s->__nodeColor=black;
				p->__nodeColor=red;
				if(p==_root)
					_root=s;
			}
		}
	}
	bool isLChild(node* x,node* p){
		return p->__pLC==x?true:false;
	}
	node* uncle(node* x){
		node* p=x->__pParent;
		node* g=p->__pParent;
		if(isLChild(p,g))
			return g->__pRC;
		else
			return g->__pLC;
	}

	void clear(){
		while(_root!=extrnode)
			remove(_root->__keyWord);
	}
private:
	node* _root;
	node* _hot;
	node* extrnode;
};

#endif
