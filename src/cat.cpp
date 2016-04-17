#include <fstream>
#include <iostream>
#include <sys/stat.h>
#include <unistd.h>
#include <cstring>
using namespace std;
int main(int argc, char const *argv[])
{
	if(argv[1]==NULL)
	{
		string s;
		getline(cin,s);
		cout<<s<<endl;
		return 0;
	}
	for (int i = 1; i < argc; ++i)
	{
		if(argv[i][0]=='-') 
			{
				cout<<&argv[0][2]<<": invalid option -- '"<<&argv[i][1]<<"'"<<endl;
				return 0;
			}
	}
	for(int i=1;i<argc;i++)
	{

		struct stat info;
		stat(argv[i],&info);
		if(access(argv[i],F_OK)!= 0)  cout<<&argv[0][2]<<": "<<argv[i]<<": No such file or directory"<<endl;
		else if(access(argv[i],R_OK)!= 0) cout<<&argv[0][2]<<": "<<argv[i]<<": Permission denied"<<endl;
		else if(S_ISDIR(info.st_mode))
    		{
    			cout<<&argv[0][2]<<": "<<argv[i]<<": Is a directory"<<endl;
    		}
    	else
    	{
    		ifstream fin;
    		fin.open(argv[i]);
    		string s;
    		while(!fin.eof())
    		{
    			getline(fin,s);
    			cout<<s<<endl;
    		}
    	}

    }
	return 0;
}