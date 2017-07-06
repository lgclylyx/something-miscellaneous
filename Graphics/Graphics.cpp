#include <list>
#include <fstream>
#include <iostream>
#include <climits>
#include <string>
#include <sstream>
#include <iomanip>  
#include <cctype>
struct Edge{
	int weight;
	int adjvertex;
	Edge(int w,int adj):weight(w),adjvertex(adj){}
};
struct DjkVertex{
	int id;
	std::list<Edge> adjlist;
	bool known;
	int path;
	int dist;
};

const int Num=7;
const int SV=1;
DjkVertex List[Num];

void GetInt(std::ifstream& in,int& a){
	in>>std::noskipws;
	std::string str("");
	char c;
	while(in>>c&&std::isspace(c))
		;
	while(c>='0'&&c<='9'){
		str=str+c;
		in>>c;//当读入到文件流结束位置时，不会读入EOF标志，而是将指针停留在最后一个元素重复读取
		if(in.peek()==EOF)//peek()用于返回输入流中下一个元素，但不移动文件流指针
			break;
	}
	if(c=='\n')
		in.putback(c);
	std::stringstream trans;
	trans<<str;
	trans>>a;
}
int main(){
	std::ifstream in("in.txt");
	int i=0;
	for(int i=0;i<Num;i++){
		List[i].dist=INT_MAX;
		List[i].id=i+1;
		List[i].known=false;
		List[i].path=0;
		while(true){
			int weight;
			int adjvertex;
			char c;
			in>>std::noskipws;
			while(in>>c&&std::isspace(c)&&c!='\n')
				;
			if(c=='\n'||in.peek()==EOF){
				break;
			}else{
				in.putback(c);
			}
			GetInt(in,adjvertex);
			GetInt(in,weight);
			List[i].adjlist.push_back(Edge(weight,adjvertex));
		}
	}
	std::cout<<"Graphics:"<<std::endl;
	for(int i=0;i<Num;i++){
		std::cout<<"V("<<List[i].id<<")"<<"	"<<"AdjList: ";
		std::list<Edge>::iterator itr=List[i].adjlist.begin();
		for(;itr!=List[i].adjlist.end();itr++){
			std::cout<<itr->adjvertex<<" "<<itr->weight<<" "; 
		}
		std::cout<<std::endl;
	}
	List[SV-1].dist=0;
	for(int i=SV-1;;){
		bool flag=true;
		List[i].known=true;
		std::list<Edge>::iterator itr=List[i].adjlist.begin();
		for(;itr!=List[i].adjlist.end();itr++){
			if(!List[itr->adjvertex-1].known&&itr->weight+List[i].dist<List[itr->adjvertex-1].dist){
				List[itr->adjvertex-1].dist=itr->weight+List[i].dist;
				List[itr->adjvertex-1].path=List[i].id;
			}
		}
		std::cout<<std::endl<<"V("<<List[i].id<<"):"<<std::endl;
		int temp=INT_MAX;
		for(int j=0;j<Num;j++){
			if(List[j].known)
				continue;
			if(List[j].dist<temp){
				flag=false;
				temp=List[j].dist;
				i=j;
			}
		}
		for(int i=0;i<Num;i++){
			std::cout<<"V("<<List[i].id<<")"<<"	";
			if(List[i].known)
				std::cout<<"T"<<"	";
			else
				std::cout<<"F"<<"	";
			if(List[i].dist==INT_MAX)
				std::cout<<"INFINITE"<<"	";
			else
				std::cout<<std::setw(8)<<List[i].dist<<"	";
			std::cout<<List[i].path<<std::endl;
		}
		if(flag)
			break;
	}
	system("pause");
}