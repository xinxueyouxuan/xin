#include <iostream>
using namespace std;

int main(){
	/*
		\a -->警报 
		\b -->退格(BS),将当前位置移到前一列 
		\f -->换页(FF),将当前位置移动到下页开头 
		\n -->换行(IF),将当前位置移动到下一行开头 
		\r -->回车(CR) 
		\t -->水平制表(HT) 
		\v -->垂直制表(VT) 
		\\ -->字符 ‘\ ’ 
		\' -->字符 ‘' ’ 
		\" -->字符 ‘" ’ 
		\? -->代表一个 ‘? ’ 
		\0 -->
	*/
	
	cout<<"水平制表\t"<<endl;
	cout<<"换行\n";
	cout<<"反斜杠\\"<<endl;
	
	
	system("pause");
	return 0;
}
