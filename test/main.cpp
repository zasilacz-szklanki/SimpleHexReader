#include<iostream>
#include<fstream>
#include<string>
#include<cstdlib>

using namespace std;

string decToHex(int number){
	string ret="";
	int reszta=0;

	while(number>=1){
		reszta=number%16;
		if(reszta<=9){
			ret+=char(reszta+'0');
		}
		else{
			ret+=char(reszta+'A'-10);
		}
		number/=16;
	}

	if(ret.length()==1){
		ret+='0';
	}

	for(int i=0;i<ret.length()/2;i++){
		swap(ret[i],ret[ret.length()-i-1]);
	}
	
	/*if(ret=="20"){
		ret="00";
	}*/

	return ret;
}

void showFile(string str,int col=4){
	cout<<"00\t";
	for(int i=0;i<str.length();i++){
		cout<<decToHex((int)(str[i]))<<" ";
		if(i%col==col-1){
			cout<<'\n';
			cout<<decToHex(i+1)<<'\t';
		}
	}
}


int main(){
	ifstream plik("test.b",ios::binary);
	string buff="";
	string str="";	

	/*for(int i=0;i<=1024;i++){
		cout<<i<<'\t'<<decToHex(i)<<'\n';
	}*/
	while(!plik.eof()){
		getline(plik,buff);
		//print_string(str);
		str+=buff;
	}
	showFile(str,16);
	plik.close();	
	return 0;
}
