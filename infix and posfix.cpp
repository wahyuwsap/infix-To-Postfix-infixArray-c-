#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

bool Operator(char c){
    return ( c == '*' || c == '/' || c == '+' || c == '-' || c == '%');
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

int main(){
    string input;
    getline(cin, input);
    vector<string> infix = KataInfix(input);
    
    for(const string& hasil : infix){
        cout << hasil << " ";
    }
    cout << endl;
    return 0;
}
