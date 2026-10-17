#include <iostream>
using namespace std;

int main(){
	int score = 0;
	cout << "0~10分;请打分:" << endl;
	cin >> score;
	switch(score){
		case 10:
			cout<<"优秀"<<endl;
			break;
		case 9:
			cout<<"优秀"<<endl;
			break;
		case 8:
			cout<<"良好"<<endl;
			break;
		case 7:
			cout<<"良好"<<endl;
			break;
		case 6:
			cout<<"良好"<<endl;
			break;
		default:
		 	cout<<"差"<<endl;
			break;
	}
	
	cin.get();
	return 0;
} 
