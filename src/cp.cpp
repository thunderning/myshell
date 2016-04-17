#include <fstream>
#include <iostream>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>  
#include <cstring>
#include <sys/types.h>
using namespace std;
string name;
void copy(string sta,string des)
{
	int flag=0;
	if(des[des.size()-1]=='/')
    	{
    		if(sta.find('/')==string::npos) des+=sta;
    		else des+=sta.substr(sta.rfind('/'),100);
    	}
	struct stat info1,info2;
    stat(sta.c_str(),&info1);
    stat(des.c_str(),&info2);
    if(access(sta.c_str(),F_OK)!= 0)  
    {
    		cout<<name<<": "<<sta<<": No such file or directory"<<endl;
    		flag=1;
    }
    else if(access(sta.c_str(),R_OK)!= 0) 
    {
    	cout<<name<<": "<<sta<<": Permission denied"<<endl;
    	flag=1;
    }
    if(access(des.c_str(),F_OK)==0&&access(des.c_str(),W_OK)!=0)
    {
    	cout<<name<<": "<<des<<": Permission denied"<<endl;
    	flag=1;
    }
    if(flag) return;
    else
    {
    	ifstream fin;
    	ofstream fout;
    	fin.open(sta.c_str());
    	fout.open(des.c_str());
    	if(!fout.good()) cout<<name<<": "<<des<<": No such file or directory"<<endl;
    	else
    	{
    		while(!fin.eof())
    		{
    			string s;
    			getline(fin,s);
    			fout<<s<<endl;
    		}
    	}
    	return;
    }
}
void copydir(string sta,string des)
{
	if(des[des.size()-1]=='/')
    	{
    		if(sta.find('/')==string::npos) des+=sta;
    		else des+=sta.substr(sta.rfind('/'),100);
    	}
    mkdir(des.c_str(), S_IRWXU | S_IRWXG | S_IRWXO);
	DIR *d=opendir(sta.c_str());
	dirent *source;
	while((source = readdir(d)) != NULL)
    {
        //把当前目录.，上一级目录..及隐藏文件都去掉，避免死循环遍历目录
        string s(source->d_name);
        if(s.find('.')==0)
            continue;
        struct stat info;
        stat(s.c_str(),&info);
    	if(S_ISDIR(info.st_mode)) 
    	{
    		copydir(sta+"/"+s,des+"/"+s);
    	}
    	else copy(sta+"/"+s,des+"/"+s);
    }
    closedir(d);
    
	return;
}
int main(int argc, char const *argv[])
{
	name=&argv[0][2];
	if(argc==1) cout<<&argv[0][2]<<": missing file operand"<<endl;
	else for(int i=1;i<argc;)
	{
		if(argv[i]==NULL)
			{
				if(i==1) cout<<&argv[0][2]<<": missing file operand"<<endl;
				return 0;
			}
		if (argv[i][0]=='-'&&argv[i][1]=='r')
		{
			if(argv[i+1]==NULL) cout<<&argv[0][2]<<": missing file operand"<<endl;
			else if(argv[i+2]==NULL) cout<<&argv[0][2]<<": missing destination file operand after '"<<argv[2]<<"'"<<endl;
			else
			{
						struct stat info;
        				stat(argv[i+1],&info);
        				if(access(argv[i+1],F_OK)!= 0)  
            			{
                				cout<<&argv[0][2]<<": "<<argv[i+1]<<": No such file or directory"<<endl;
            			}
        				else if(access(argv[i+1],R_OK)!= 0) 
            			{
                			cout<<&argv[0][2]<<": "<<argv[i+1]<<": Permission denied"<<endl;
            			}
        				else if(S_ISDIR(info.st_mode))
            			{
                			copydir(argv[i+1],argv[i+2]);
            			}
            			else copy(argv[i+1],argv[i+2]);
            			i+=3;
			}
		}
		else if(argv[i][0]=='-')
		{
			cout<<&argv[0][2]<<": invalid option -- '"<<&argv[i][1]<<"'"<<endl;
			return 0;
		}
		else
		{
			
			if(argv[i+1]==NULL) cout<<&argv[0][2]<<": missing destination file operand after '"<<argv[i]<<"'"<<endl;
			else
			{
				struct stat info;
        		stat(argv[i],&info);
        		if(S_ISDIR(info.st_mode)) 
        			{
        				cout<<name<<": omitting directory '"<<argv[i]<<"'"<<endl;
        				return 0;
        			}
        				else copy(argv[i],argv[i+1]);
            	i+=3;
			}
		}
	}
	return 0;
}