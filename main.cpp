#include <iostream>
#include <string>
#include <pwd.h>
#include <unistd.h>
#include <cstdlib>
#include <vector>
#include <dirent.h>    
#include <sys/stat.h>
#include <fstream>
using namespace std;

vector<string> shelll;

string getcate()
{
	char a[260];
	getcwd(a,260);
	struct passwd *pwd;
	pwd = getpwuid(getuid());
	char hhname[30];
	gethostname(hhname,sizeof(hhname));
	string thiscate,pname(pwd->pw_name),hname(hhname);
	thiscate+=pwd->pw_name;
	thiscate+="@";
	thiscate+=hname;
	thiscate+=":";
	int i=0,flag=0;
	for(;pwd->pw_name[i]!='\0';i++);
	for(int j=6;a[j]!='/';j++)
		if (a[j]!=pwd->pw_name[j-6])
		{
			flag=1;
			break;
		}
	if(flag==0)
	{
		thiscate+='~';
		thiscate+=&a[i+6];
	}
	else thiscate+=a;
	if(pname=="root") thiscate+="# ";
	else thiscate+="$ ";
	return thiscate;
}
//获得当前目录

void getall()
{
	DIR *d=opendir("src");
	dirent *source;
	while((source = readdir(d)) != NULL)
    {
        //把当前目录.，上一级目录..及隐藏文件都去掉，避免死循环遍历目录
        string s(source->d_name);
        if(s.find('.')==0)
            continue;
        shelll.push_back(s); //保存遍历到的文件名
    }
    closedir(d);
    for (int i = 0; i < shelll.size(); ++i)
    {
    	shelll[i]=shelll[i].substr(0,shelll[i].find('.'));

    }
    ofstream fout;
    fout.open("makefile");
    fout<<"all:";
    for (int i = 0; i < shelll.size(); ++i)
    {
    	fout<<"bin/"<<shelll[i]<<" ";
    }
    fout<<endl;
    for (int i = 0; i < shelll.size(); ++i)
    {
    	fout<<"bin/"<<shelll[i]<<":src/"<<shelll[i]<<".cpp"<<endl;
    	fout<<"\t"<<"g++ -o bin/"<<shelll[i]<<" src/"<<shelll[i]<<".cpp"<<endl;
    }
    fout<<"clean:"<<endl<<"\trm *.o";
    fout.close();
    system("make");
    return ;
}
//获得全部命令
bool checkit(string str,string com)
{
	int dis=100,length;
	if(str.size()<com.size()) length=com.size();
	else length=str.size();
	for (int i = 0; i< str.size(); ++i)
	{
		for(int j=0;j<com.size();++j)
		{
			int k=0;
			for(;str[i+k]==com[j+k];k++);
			if(dis>length-k) dis=length-k;
		}
	}
	if (dis<=2)
	{
		return true;
	}
	return false;
}

bool check(string str)
{
	for (int i = 0; i < shelll.size(); ++i)
	{
		if(shelll[i]==str) return true;
	}
	int flag=0;
	for (int i = 0; i < shelll.size(); ++i)
	{
		if(checkit(str,shelll[i])) 
			{
				if(flag==0)
					{
						cout<<"No command '"<<str<<"' found, did you mean:"<<endl;
						flag=1;
					}
				cout<<" Command '"<<shelll[i]<<"'\n";
			}
	}
	cout<<str<<": command not found"<<endl;
	return false;
}
//判断是否错误语句，若是则比较与已知语句的距离，对距离小于2的进行提示，否则提示输入错误

void mycp();
//读入参数并进行判断，若无参数作0记录，若参数数目不符合要求则输出提示，否则进行复制操作（注意文件权限）

void mycmp();
//读入文件路径，进行比较操作（注意若无文件应输出提示）

void mywc();
//读入参数并进行判断，若无参数或参数数目不符合要求则输出提示，否则进行对应统计操作（注意文件权限）

void mycat();
//进行打印操作（注意文件存在判断）

void myman();
//读入命令，调用check函数进行判断，进行输出help操作

int main()
{
	cout<<"---------------------------------------------------------------------"<<endl;
	cout<<"---------------------------Hello world !-----------------------------"<<endl;
	cout<<"---------------------Welcome to my shell class!----------------------"<<endl;
	cout<<"---------------------------------------------------------------------"<<endl;
	string thiscate=getcate();
	getall();
	cout<<thiscate;
	string shel,shelall;
	getline(cin,shelall);
	shel=shelall.substr(0,shelall.find(' '));
	while(shel!="exit")	
	{
		if(check(shel)==true)                //判断是否错误语句
		 {
		 	string cmd="./bin/";
		 	cmd+=shelall;
			system(cmd.c_str());
		 }
		cout<<thiscate;
		getline(cin,shelall);
		shel=shelall.substr(0,shelall.find(' '));
	}
	cout<<"---------------------------------------------------------------------"<<endl;
	cout<<"------------------Thanks for using my shell class!-------------------"<<endl;
	cout<<"-------------------------bye-bye world!------------------------------"<<endl;
	cout<<"---------------------------------------------------------------------"<<endl;
	return 0;
}
