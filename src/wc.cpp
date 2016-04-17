#include <fstream>
#include <iostream>
#include <sys/stat.h>
#include <unistd.h>
#include <cstring>
using namespace std;
int main(int argc, char const *argv[])
{
	for (int i = 1; i < argc; ++i)
	{
		if(strcmp(argv[i],"-l")!=0&&strcmp(argv[i],"-w")!=0&&strcmp(argv[i],"-c")!=0&&argv[i][1]=='-')
			{
				cout<<&argv[0][2]<<": invalid option -- '"<<&argv[i][1]<<"'"<<endl;
				return 0;
			}
	}
	if(argv[1]==NULL||argv[2]==NULL) cout<<cout<<&argv[0][2]<<": missing operand "<<endl;
	struct stat info;
    stat(argv[i],&info);
        if(access(argv[i],F_OK)!= 0)  
            {
                cout<<&argv[0][2]<<": "<<argv[i]<<": No such file or directory"<<endl;
                return 0;
            }
        else if(access(argv[i],R_OK)!= 0) 
            {
                cout<<&argv[0][2]<<": "<<argv[i]<<": Permission denied"<<endl;
                return 0;
            }
        else if(S_ISDIR(info.st_mode))
            {
                cout<<&argv[0][2]<<": "<<argv[i]<<": Is a directory"<<endl;
                return 0;
            }
    ifstream fin;
    fin.open(argv[2]);
    int num=0,line=0;
    string s;
    	while(!fin.eof())
    	{	
    	line++;
    	getline(fin,s);
    	}
    if(strcmp(argv[1],"-l")==0)
    {
    	cout<<line-1<<" "<<argv[2]<<endl;
    }
    fin.close();
    fin.open(argv[2]);
    if(strcmp(argv[1],"-w")==0)
    {
    	char s1,s2;
    	fin.get(s1);
    	while(!fin.eof())
    	{	
    		fin.get(s2);
    		if((s1!=' '&&s1!='\n'&&s1!='\t')&&(s2==' '||s2=='\t'||s2=='\n')) num++;
    		s1=s2;
    	}
    	if(s1!=' '&&s1!='\n') num++;
    	cout<<num<<" "<<argv[2]<<endl;
    }
    if(strcmp(argv[1],"-c")==0)
    {
    	string s;
    	while(!fin.eof())
    	{
    	getline(fin,s);
    	num+=s.size();
    	}
    	cout<<num-1+line<<" "<<argv[2]<<endl;
    }
	fin.close();
	return 0;
}