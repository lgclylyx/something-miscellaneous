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
	node* search(const T& e){//search:������������ʱ�����ظýڵ��ָ�룬���򷵻��ڱ��ڵ㣬���ⲿ�ڵ㣻
		node* x=_root;
		_hot=nullptr;
		while(x!=extrnode){
			if(e==x->__keyWord)
				return x;
			else{
				_hot=x;//_hotָ�򷵻ؽڵ�ĸ��ڵ㣬���ظ���Ϊ����ʱ��_hotΪnullptr
			    e < x->__keyWord?x=x->__pLC:x=x->__pRC;
			}
		}
		return extrnode;//����extrnode
	}
	node * insert(const T& e){
		node* r=search(e);//�ҵ������
		if(r!=extrnode) return r;//�ҵ���ͬ��key���Ͳ�����
		node* t=new node(e,_hot,extrnode,extrnode);
		if(!_hot){//���_hotΪnullptr���������
			_root=t;
		}else{//���ǿ�ʱ����
			if(e<_hot->__keyWord)
				_hot->__pLC=t;
			else
				_hot->__pRC=t;
		}
		solveDoubleRed(t);
		return t;
	}

	bool remove(const T& e){
		node* r =search(e);//ȷ����ɾ���ڵ��Ƿ����
		if(r==extrnode) return false;
		node* x=findRMP(r);//�ҵ�ʵ��ɾ���ڵ�
		if(!_hot){//ɾ�����ڵ�
			_root=_root->__pLC!=extrnode?_root->__pLC:_root->__pRC;
			delete x;
			if(_root!=extrnode&&_root->__nodeColor==red)
				_root->__nodeColor=black;
		}else{
			enum color rnodeColor=x->__nodeColor;//���ʵ�ʴ�ɾ���ڵ���ɫ�����ж��Ƿ�˫�ڣ����ڱ��ڵ㵱����ɫ��ͳһ����
			r=realRM(x,r);//ʵ��ɾ���ڵ�
			if(r->__nodeColor==black&&rnodeColor==black){//˫��
				solveDoubleBlack(r);
			}else{
				if(r!=extrnode)//�����˫�ڣ���r���ڣ���ֱ���ú�
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
			if(!_hot){//��������
				_root->__nodeColor=black;
				return;
			}else{//�ǿղ���
				if(_hot->__nodeColor==red){//˫�����
					if(uncle(x)->__nodeColor==black){//uΪ��ɫ,3+4�ع�
						solveDoubleRedB(x);
						return;
					}else{//uΪ��ɫ
						solveDoubleRedR(x);
						continue;
					}
				}
				return;//����㸸�ڵ�Ϊ��ɫֱ�ӷ���
			}
		}
	}
	void solveDoubleRedB(node* x){//�޸�RRB�������ֻ�ý���һ��3+4������������Ⱦɫ������
		node* p=x->__pParent;
		node* g=p->__pParent;
		if(isLChild(p,g)){
			if(isLChild(x, p)){
				p->__pParent=g->__pParent;
				if(g->__pParent){//���µľֲ����ڵ㣬���ӵ��µĸ��ڵ�
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
		if(_root==g)//�ڸ��ڵ����任�����
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
		x=g;//��������룬ת����g
		_hot=g->__pParent;
	}
	node* findRMP(node* x){//����ʵ��ɾ���ڵ�;�����ܷ���extrnode
		node* sRoot=x->__pRC;
		node* r=x;
		while(sRoot!=extrnode){
			r=sRoot;
			sRoot=sRoot->__pLC;
		}
		_hot=r->__pParent;
		return r;
	}
	node* realRM(node* x,node* r){//ʵ��ɾ������,�������ʵ��ɾ���ڵ���ӽڵ�͸��ڵ�,���ر�ɾ���ڵ������ڵ�
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
	void solveDoubleBlack(node* x){//TODO����Ӧ����ô����
		while(true){
			node* p=x!=extrnode?x->__pParent:_hot;
			node* s=p->__pLC==x?p->__pRC:p->__pLC;//s������Ϊ�գ�����Υ��������ڸ߶�����
			if(s->__nodeColor==black){
				if(s->__pLC->__nodeColor==red){//BB1-1
					node* t=s->__pLC;
					if(isLChild(s,p)){
						s->__pParent=p->__pParent;
						if(p->__pParent){//���µľֲ����ڵ㣬���ӵ��µĸ��ڵ�
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
						if(p->__pParent){//���µľֲ����ڵ㣬���ӵ��µĸ��ڵ�
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
						if(p->__pParent){//���µľֲ����ڵ㣬���ӵ��µĸ��ڵ�
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
						if(p->__pParent){//���µľֲ����ڵ㣬���ӵ��µĸ��ڵ�
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
				if(p->__pParent){//���µľֲ����ڵ㣬���ӵ��µĸ��ڵ�
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
