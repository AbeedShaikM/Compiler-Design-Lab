#include <bits/stdc++.h>

using namespace std;

bool isOperator(char c){
  if(c == '+' || c == '-' || c == '*' || c == '/') return true;
  return false;
}

bool isRelational(char c){
  if(c == '<' || c == '>' || c == '=') return true;
  return false;
}

int main(){
  string s;
  getline(cin, s);

  using data = array<string, 2>;
  vector<data> result;
  int n = s.size();
  
  int i = 0;
  while(i < n){
    string curr = "";
    if(isalpha(s[i])){
      // id
      for(; i < n; i++){
        if(isalnum(s[i])) curr += s[i];
        else break;
      }
      result.push_back({"id", curr});
    }  
    else if(isdigit(s[i])){
      // const
      for(; i < n; i++){
        if(isdigit(s[i])) curr += s[i];
        else break;
      }
      result.push_back({"const", curr});
    }
    else if(isRelational(s[i])){
      // relational
      curr += s[i];
      i++;
      if(i < n and s[i] == '=') curr += s[i], i++;
      result.push_back({curr, "relational"});
    }
    else if(isOperator(s[i])){
      // opr
      curr += s[i];
      result.push_back({curr, "opr"});
      i++;
    }
    else if(s[i] == '(' || s[i] == ')'){
      curr += s[i];
      result.push_back({curr, ""});
      i++;
    }
    else {
      if(s[i] == ' ') ;
      else{
        curr += s[i];
        result.push_back({curr, "UNKNOWN"});
      }
      i++;
    }
  }

  for(auto [x, y]: result){
    cout << "<" << x << ", " << y << ">" << endl;
  }

  return 0;
}