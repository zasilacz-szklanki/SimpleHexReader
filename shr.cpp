#include<iostream>
#include<fstream>
#include<windows.h>

using namespace std;

void setcolor(int color){
	const HANDLE h=GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h,color);
}
int getFileSize(ifstream* file){
	int size=0;
	char z=0;
	while(!file->eof()){
		file->get(z);
		size++;
	}	
	return size-1;
}
void help(){
	setcolor(0x0d);
	cout<<"Help yourself\n";
	setcolor(0x0f);
}
void version(){
	setcolor(0x0b);
	cout<<"Simple Hex Editor verion 0.1\n";
	setcolor(0x0f);
}

int main(int argc,char** argv){
	const char* filename="#";
	char find=127;
	if(argc>1){
		for(int i=1;i<argc;i++){
			//cout<<i<<'\t'<<argv[i]<<'\n';
			if(string(argv[i])=="--file" && i<argc-1 && argv[i+1][0]!='-' &&  argc>2){
				filename=argv[i+1];
			}	
			else if(string(argv[i])=="--find" && i<argc-1 && argv[i+1][0]!='-'){
				find=(char)stoi(string(argv[i+1]),nullptr,16);
			}
			else if(string(argv[i])=="--help"){
				help();
				return 0;
			}
			else if(string(argv[i])=="--version"){
				version();
				return 0;
			}
		}
	}
	else{
		setcolor(0x04);
		cout<<"\nError: no input file\n\n";
		setcolor(0x0f);
		return 0;
	}
	if(filename=="#"){
		setcolor(0x04);
		cout<<"\nError: no input file\n\n";
		setcolor(0x0f);
		return 0;
	}

	setcolor(0x0e);
	cout<<"\nFile: "<<filename<<'\n';
	setcolor(0x0f);

	char z=0;
	ifstream plik(filename,ios::binary);
	int line=0,total=0;
	string buff="";

	cout<<hex<<'\n';
	setcolor(0x0a);
	cout<<line<<'\t';
	setcolor(0x0f);

	int n=getFileSize(&plik);
	plik.close();
	plik.open(filename,ios::binary);	

	for(int i=0;i<n;i++){
		plik.get(z);
		if(abs((int)z)<16){
			cout<<"0";	
		}

		if(abs((int)z)==(int)find){
			setcolor(0x50);
			cout<<abs((int)z);
			setcolor(0x0f);
			cout<<" ";
		}
		else{
			cout<<abs((int)z)<<" ";
		}

		if((int)z>=32 && (int)z<=126){
			buff+=z;
		}
		else{
			buff+='.';
		}

		line++;
		if(line%16==0 && i!=n-1){
			cout<<'\t';
			for(string::iterator it=buff.begin();it!=buff.end();it++){
				if(*it==(char)find){
					setcolor(0x50);
					cout<<*it;
					setcolor(0x0f);
				}
				else{
					cout<<*it;
				}
			}
			cout<<'\n';
			setcolor(0x0a);
			cout<<line<<'\t';
			setcolor(0x0f);
			buff="";
		}
		total++;
	}
	if(line%16!=0){
		cout<<string(3*(16-line%16),' ');
	}
	cout<<'\t';

	for(string::iterator it=buff.begin();it!=buff.end();it++){
		if(*it==(char)find){
			setcolor(0x50);
			cout<<*it;
			setcolor(0x0f);
		}
		else{
			cout<<*it;
		}
	}

	cout<<dec<<"\n\n";
	setcolor(0x0e);
	cout<<"Size: "<<line<<" byte(s)";
	setcolor(0x0f);
	cout<<"\n\n";

	plik.close();
	return 0;
}
