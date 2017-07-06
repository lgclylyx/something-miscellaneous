#include <Windows.h>
#include <fstream>
#include <string>
#include <iostream>
void TraversalDisk(const std::string& path,int deep);
int main(){
	std::string a("C:\\Users\\Administrator\\Desktop\\TraversalDisk\\TraversalDisk");
	TraversalDisk(a,0);
	system("pause");
	return 0;
}

void TraversalDisk(const std::string& path, int deep){
	//std::ofstream out((path+".txt").c_str());
	std::ofstream out("C:\\Users\\Administrator\\Desktop\\list.txt",std::ios::app|std::ios::out);
	std::string szFind;
	WIN32_FIND_DATA findFileData;
	BOOL bRet;
	szFind=path;
	szFind=szFind+"\\*.*";
	HANDLE hFind=::FindFirstFile(szFind.c_str(),&findFileData);
	if(INVALID_HANDLE_VALUE==hFind)
		return;
	if(deep==0){
		std::cout<<path<<"\n";
		out<<path<<std::endl;
	}
	while(true){
		if(findFileData.cFileName[0]!='.'){
			for(int i=0;i<=deep;i++){
				std::cout<<"\t";
				out<<"\t";
			}
			std::cout<<findFileData.cFileName<<"\n";
			out<<findFileData.cFileName<<std::endl;
			if(findFileData.dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY){
				szFind=path+"\\"+findFileData.cFileName;
				TraversalDisk(szFind,deep+1);
			}
		}
		bRet = ::FindNextFile(hFind, &findFileData);
		if(!bRet)
			break;
	}
	out.close();
	::FindClose(hFind);
}