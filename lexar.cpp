#include <iostream>
#include <fstream>
#include <string>
#include <unordered_set>
using namespace std;

bool check_letter(char ch)
{
  return (ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z');
}
bool check_Digit(char ch)
{
  return ch >= '0' && ch <= '9';
}
bool check_valid_identifer(const string &input)
{
  if (input[0] == '_')
  {
    for (int i = 1; i < input.size(); i++)
    {
      if (!check_letter(input[i]) && !check_Digit(input[i]) && input[i] != '_')
        return false;
    }
    return true;
  }
  else
  {
    bool check = false;
    for (int i = 1; i < input.size(); i++)
    {
      if (!check_letter(input[i]) && !check_Digit(input[i]) && input[i] != '_')
        return false;
      if (input[i] == '_' && check == false)
      {
        check = true;
      }
    }
    if (check == true)
      return true;
    else
      return false;
  }
}
bool check_valid_number(const string &input)
{
  for (int i = 0; i < input.size(); i++)
  {
    if (!check_Digit && input[i] != '.' && input[i] != 'E' &&
        input[i] != 'e' && input[i] != '+' && input[i] != '-')
    {
      return false;
    }
  }
  return true;
}
bool check_operator(const string &input)
{
  if (input.size() == 1)
  {
    return (input[0] == '*' || input[0] == '+' || input[0] == '/' || input[0] == '-' ||
            input[0] == '%' || input[0] == ':');
  }
  else if (input.size() == 2)
  {
    return ((input == "!=") || (input == "<>") || (input == "==") ||
            (input == ">>") || (input == "<<") || (input == "++") ||
            (input == "=+") || (input == "&&") || (input == "||") ||
            (input == "=>") || (input == "=<") || (input == "::") ||
            (input == "--"));
  }
  else if (input.size() == 3)
  {
    return (input == "=:=");
  }
  return false;
}
bool check_punctuation(const string &input)
{
  return (input.size() == 1 && (input[0] == '[' || input[0] == ']' || input[0] == '{' ||
                                input[0] == '}' || input[0] == '(' || input[0] == ')' ||
                                input[0] == '<' || input[0] == '>'));
}
unordered_set<string> keywords = {
    "loop", "agar", "magar", "asm", "else", "new", "this", "auto",
    "enum", "operator", "throw", "bool", "explicit", "private", "true", "break", "export", "protected",
    "try", "case", "extern", "public", "typedef", "catch", "false", "register", "typeid", "char", "float",
    "typename", "class", "for", "return", "union", "const", "friend", "short", "unsigned", "goto", "signed", "using",
    "continue", "if", "sizeof", "virtual", "default", "inline", "static", "void", "delete", "int", "volatile", "do", "long",
    "struct", "double", "mutable", "switch", "while", "namespace", "do", "round", "iif"};

string check_input_type(const string &input)
{

  if (keywords.find(input) != keywords.end())
  {
    return "Keyword";
  }
  else if (check_letter(input[0]) || input[0] == '_')
  {
    if (check_valid_identifer(input))
      return "Identifier";
  }
  else if (check_Digit(input[0]) || input[0] == '-' || input[0] == '+')
  {
    if (check_valid_number(input))
      return "Number";
  }
  else if (check_operator(input))
  {
    return "Operator";
  }
  else if (check_punctuation(input))
  {
    return "Punctuation";
  }
  return "Invalid";
}
int main()
{
  cout << "welcome to scanner!!\nwait openening your file!!\n"
       << endl;
  ifstream fin;
  ofstream fout, eout;
  fin.open("input.txt");
  fout.open("output.txt");
  eout.open("error.txt");

  if (!fin || !fout || !eout)
  {
    cout << "file not opened!!" << endl;
    exit(-1);
  }
  fout << "Token Type \t Value " << endl;
  string input_buffer;
  while (fin >> input_buffer)
  {
    cout << "scanning...\n";
    string type = check_input_type(input_buffer);
    if (type != "Invalid")
    {
      fout << type << "\t" << input_buffer << endl;
    }
    else
    {
      eout << "Invalid input: " << input_buffer << endl;
    }
  }
  fin.close();
  fout.close();
  eout.close();
  cout << "the generated token are in output file and errors are in error file" << endl;
  return 0;
}
