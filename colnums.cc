#include <iostream>
#include <queue>
using namespace std;

int main(){
  char op;
  int num;
  priority_queue<int> queue;
  while (cin >> op){
    if ((queue.empty()) and (op != 'S')){
      cout << "error!" << endl;
      if ((op == 'D') or (op == 'I')) cin >> num;
    }
    else{
      if (op == 'A') cout << queue.top() << endl;
      if (op == 'S'){
	cin >> num;
	queue.push(num);
      }
      else if (op == 'R')queue.pop();
      else if (op == 'I'){
	cin >> num;
	int x = queue.top();
	queue.pop();
	queue.push(num+x);
      }
      else if (op == 'D'){
	cin >> num;
	int x = queue.top();
	queue.pop();
	queue.push(x-num);
      }
    }
  }
}

