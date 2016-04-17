#include <fstream>
#include <iostream>
#include <sys/stat.h>
#include <unistd.h>
#include <string>
using namespace std;
int main(int argc, char const *argv[])
{
	if(argc<=2)
	{
		cout<<&argv[0][2]<<": missing operand after '"<<&argv[0][2]<<"'"<<endl;
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
	if(argv[3]!=NULL)
	{
		cout<<&argv[0][2]<<": invalid --ignore-initial value '"<<argv[3]<<"'"<<endl;
		return 0;
	}
	for(int i=1;i<argc;i++)
	{

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
    }
    ifstream fin1,fin2;
    fin1.open(argv[1]);
    fin2.open(argv[2]);
    string s1,s2;
    int num=1,line=0;
    while(!fin1.eof()&&!fin2.eof())
    {
    	line++;
    	getline(fin1,s1);
    	getline(fin2,s2);
    	for(int i=0;i<s1.size()||i<s2.size();i++)
    	{
    		if(s1[i]!=s2[i])
    		{
    			num+=line-1;
    			cout<<argv[1]<<" "<<argv[2]<<" differ: byte "<<num<<", line "<<line<<endl;
    			return 0;
    		}
    		else num++;
    	}
    }
    if(fin1.eof()&&fin2.eof()) return 0;
    if(fin1.eof()&&!fin2.eof()) cout<<&argv[0][2]<<": EOF on "<<argv[1]<<endl;
    else cout<<&argv[0][2]<<": EOF on "<<argv[2]<<endl;
    fin1.close();
    fin2.close();
	return 0;
}