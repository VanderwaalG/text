#include<iostream.h>
#include<fstream>
#include<cstdlib>
#include<cstring>
#include<cmath>
using namespace std;
const int strSize=256;
typedef char** HuffmanCode;
typedef struct{
	char ch;
	int weight;
	int parent,lchild,rchild;
}*HuffmanTree,HuffmanNode;
void findChars(char* fileName,int *charCount,int &n){
	for(int i=0;i<strSize;i++){
		charCount[i]=0;
	}
	char str1[256];
	ifstream fileln;
	fileln.open(fileName);
	while(!fileln.eof()){
		fileln.getline(str1,256);
		for(int i=0;i<strlen(str1);i++){
			charCount[str1[i]]++;
		}
	}
	cout<<"文件里出现的字符及字符出现的次数如下："<<endl;
	cout<<"------------------------------------"<<endl;
	for(int i=0;i<256;i++){
		if(charCount[i]!=0){
			n++;
			cout<<((char)i)<<charCount[i]<<endl;
		}
	}
	cout<<"文件里字符种类的数量："<<n<<endl;
	cout<<"------------------------------------"<<endl;
	fileln.close();
}
void select(HuffmanTree &HT,int n,int &s1,int &s2){
	int temp=65535,tempi=0;
	for(int i=1;i<=n;i++){
		if(!HT[i].parent){
			if(temp>HT[i].weight){
				temp=HT[i].weight;
				tempi=i;
			}
		}
	}
	s1=tempi;
	temp=65535,tempi=0;
	for(int i=1;i<=n;i++){
		if(!HT[i].parent&&i!=s1){
			if(temp>HT[i].weight){
				temp=HT[i].weight;
				tempi=i;
			}
		}
	}
	s2=tempi;
}
void CreateHuffmanTree(HuffmanTree &HT,int n,int *charCount){
	if(n<=1) return;
	int m=2*n-1;
	HT=new HuffmanNode[m+1];
	for(int i=1;i<=m;i++){
		HT[i].parent=0;
		HT[i].lchild=0;
		HT[i].rchild=0;
		HT[i].weight=0;
	}
	int i=1,j=0;
	while(i<=n){
		if(charCount[j]!=0){
			HT[i].ch=(char(j));
			HT[i].weight=charCount[j];
			i++;
			j++;
		}else{
			j++;
		}
	}
 
	cout<<"存储结构HT的初态："<<endl;
	cout<<"______________________________________________________"<<endl;
	cout<<"\t"<<"结点i"<<"\t"<<"weight"<<"\t"<<"parent"<<"\t"<<"lchild"<<"\t"<<"rchild"<<endl;
	for(int i=1;i<=m;i++){
		cout<<"\t"<<i<<"\t"<<HT[i].weight<<"\t"<<HT[i].parent<<"\t"<<HT[i].lchild<<"\t"<<HT[i].rchild<<endl;
	}
	cout<<"_______________________________________________________"<<endl;
	int s1,s2;
	for(i=n+1;i<=m;i++){
		select(HT,i-1,s1,s2);
		HT[s1].parent=i;
		HT[s2].parent=i;
		HT[i].lchild=s1;
		HT[i].rchild=s2;
		HT[i].weight=HT[s1].weight+HT[s2].weight;
	}
	cout<<"存储结构HT的终态："<<endl;
	cout<<"______________________________________________________"<<endl;
	cout<<"\t"<<"结点i"<<"\t"<<"weight"<<"\t"<<"parent"<<"\t"<<"lchild"<<"\t"<<"rchild"<<endl;
	for(int i=1;i<=m;i++){
		cout<<"\t"<<i<<"\t"<<HT[i].weight<<"\t"<<HT[i].parent<<"\t"<<HT[i].lchild<<"\t"<<HT[i].rchild<<endl;
	}
	cout<<"_______________________________________________________"<<endl;
	cout<<"创建成功！"<<endl; 
}
void CreateHuffmanCode(HuffmanTree& HT,HuffmanCode &HC,int n){
	HC=new char*[n+1];
	char *cd=new char[n];
	cd[n-1]='\0';
	for(int i=1;i<=n;i++){
		int start=n-1;
		int c=i;
		int f=HT[c].parent;
		while(f!=0){
			start--;
			if(HT[f].lchild==c) cd[start]='0';
			else cd[start]='1';
			c=f;
			f=HT[f].parent;
		}
		HC[i]=new char[n-start];
		strcpy(HC[i],&cd[start]);
	} 
	cout<<"每个字符对应的哈夫曼编码如下："<<endl;
	for(int i=1;i<=n;i++){
		cout<<HT[i].ch<<":"<<HC[i]<<endl;
	}
	delete cd;
}
void Coding(HuffmanTree &HT,HuffmanCode &HC,int n,char *fileName,char *defile){
	ifstream infile;
	infile.open(fileName);
	ofstream ofile;
	ofile.open(defile);
	char ch;
	infile>>noskipws;
	while(infile>>ch){
		for(int i=1;i<=n;i++){
			if(HT[i].ch==ch){
				ofile<<HC[i];
			}
		}
	}
	cout<<"编码成功！可到文件"<<defile<<"查看"<<endl;
	ofile.close();
	infile.close();
}
void deCode(char *fileName,char *deCode,HuffmanCode &HC,HuffmanTree &HT,int n){
	char buf[1024];
	ifstream infile;
	ofstream fout;
	infile.open(fileName);
	fout.open(deCode);
	while(!infile.eof()){ 
		memset(buf,-1,sizeof(buf));
		infile.getline(buf,1024);
	}
	infile.close();
	int m=2*n-1;
	int f=m,j=0,i=0;
	char *tmp=new char[n];
	for(int i=0;i<1024&&buf[i]!=-1;i++){
		if(buf[i]=='0'){
			f=HT[f].lchild;
		}
		if(buf[i]=='1'){
			f=HT[f].rchild;
		}
		if(f<=n){
			tmp[i]=HT[f].ch;
			fout<<HT[f].ch;
			f=m;
		}
	}
	cout<<"解码成功! 可到文件"<<deCode<<"查看"<<endl; 
	fout.close();
} 
int main()
{
	cout<<"**************************************************************"<<endl; 
	cout<<"*             1.选择需要进行编码的文件                       *"<<endl; 
	cout<<"*             2.建立哈夫曼树                                 *"<<endl; 
	cout<<"*             3.建立密码本并对文件编码                       *"<<endl; 
	cout<<"*             4.选择需要进行解码的文件并进行解码             *"<<endl; 
	cout<<"*                                                            *"<<endl; 
	cout<<"**************************************************************"<<endl; 
	HuffmanTree HT;
	HuffmanCode HC;
	int qq,n=0;
	int charCount[strSize];
	char filename[20];
	char defile[20];
	while(true){
		cout<<"\t--请选择功能--："<<endl;
		cin>>qq;
		if(qq==1){
			cout<<"请输入需要进行编码的文件名：";
			cin>>filename; 
			findChars(filename,charCount,n);
		}else if(qq==2){
			CreateHuffmanTree(HT,n,charCount);
		}else if(qq==3){
			cout<<"请输入需要进行编码的文件名：";
			cin>>filename;
			cout<<"请输入编码需要存放的文件名："; 
			cin>>defile;
			CreateHuffmanCode(HT,HC,n);
			Coding(HT,HC,n,filename,defile); 
		}else if(qq==4){
			cout<<"请输入要进行解码的文件名：";
			cin>>filename;
			cout<<"请输入解码后存放的文件名：";
			cin>>defile;
			deCode(filename,defile,HC,HT,n);
		}else{
			return 0;
		}
	}
}
