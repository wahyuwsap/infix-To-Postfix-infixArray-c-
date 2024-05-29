#include <iostream>
#include <cstring>
#include <vector>
#include <stack>
using namespace std;

bool Operator(char c){
    return ( c == '*' || c == '/' || c == '+' || c == '-' || c == '%');
}

int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/' || op == '%') return 2;
    return 0;
}   

vector<string> KataInfix(string str){
    vector<string> infix;
    string angka;
    
    for(size_t i = 0; i < str.size() ; i++){
        char opr = str[i];
        
        if(isspace(opr)){
            continue;
        }
        else if(isdigit(opr)){
            angka += opr;
        }
        else if(opr == '-' && (i == 0 || Operator(str[i - 1]))){
            if(Operator(str[i-1]) || str[i+1] == '('){
                infix.push_back("-1");
                infix.push_back("*");
            }else{
                angka += opr;
            }
        }
        else{
            if(!angka.empty()){
                infix.push_back(angka);
                angka.clear();
            }
            infix.push_back(string(1, opr));
        }
    }
    if(!angka.empty()){
        infix.push_back(angka);
    }
    return infix;
}

vector<string> KataPostfix(vector<string>& infix) {
    vector<string> postfix;
    stack<string> opStack;

    for (const string& token : infix) {
        if (isdigit(token[0]) || (token.length() > 1 && isdigit(token[1]))) {
            postfix.push_back(token);
        } else if (token == "(") {
            opStack.push(token);
        } else if (token == ")") {
            while (!opStack.empty() && opStack.top() != "(") {
                postfix.push_back(opStack.top());
                opStack.pop();
            }
            opStack.pop();
        } else {
            while (!opStack.empty() && precedence(opStack.top()[0]) >= precedence(token[0])) {
                postfix.push_back(opStack.top());
                opStack.pop();
            }
            opStack.push(token);
        }
    }

while (!opStack.empty()) {
    postfix.push_back(opStack.top());
    opStack.pop();
}
return postfix;
}

int evaluatepostfix(const vector<string>& postfix){
    stack<int> evalstack;
    
    for(const string& token : postfix) {
    if (isdigit(token[0]) || (token.length() > 1 && isdigit(token[1]))){
        evalstack.push(stoi(token));
    }else{
        int b = evalstack.top();
        evalstack.pop();
        int a = evalstack.top();
        evalstack.pop();
        
        if(token == "+") evalstack.push(a + b );
        else if (token == "-") evalstack.push(a - b);
        else if (token == "*") evalstack.push(a * b);
        else if (token == "/") evalstack.push(a / b);
        else if (token == "%") evalstack.push(a % b);
    }
  }
  return evalstack.top();  
} 

int main(){
    string input;
    getline(cin, input);
    
    vector<string> infix = KataInfix(input);
    vector<string> postfix = KataPostfix(infix);
    
   int result = evaluatepostfix(postfix);
    cout << result << endl;
        
    }
    cout << endl;
    return 0;
}
