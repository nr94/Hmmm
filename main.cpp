#include <iostream>
#include <string>
#include <fstream>
using namespace std;
template<typename Type>
class node{
    template<class S> friend class Stack;
    friend class Queue;
    private:
        node *link;
        Type data;
    public:
        node(node *lnk = NULL, Type dat = NULL): link{lnk}, data(dat){};
        ~node(){}
        Type getData(){return data;}
        node *getLink(){return link;}
};
template <typename Type>
class Stack{
    private:
        node<Type> *TOS;
        int size;
    public:
        Stack(node<Type> *tos = NULL, int s = 0): TOS(tos), size(s){};
        ~Stack(){}
        void push(Type data){
            TOS = new node<Type>(TOS, data);
            size++;
        }
        Type pop(){
            if(TOS != NULL){
                node<Type> *templink = TOS;
                TOS = TOS->link;
                size--;
                Type data = templink->data;
                delete templink;
                return data;
            }
            return 0;
        }
        char peek(){return TOS->data;}
        int getSize(){return size;}
};

class Queue{
    private:
        node<char> *head;
        node<char> *tail;
        int size;
    public:
        Queue(node<char> *h = NULL, node<char> *t = NULL, int s = 0): head(h),tail(t), size(s){};
        ~Queue(){}
        void enQueue(char data){
            if(size == 0){
                head = new node<char>(head, data);
                tail = head;
            }
            else{
                node<char> *temp = tail;
                tail = new node<char>(NULL, data);
                temp->link = tail;
            }
            size++;
        }
        char deQueue(){
            if(head != NULL){
                node<char> *templink = head;
                head = head->link;
                size--;
                char data = templink->data;
                delete templink;
                return data;
            }
            return 0;
        }
        int getSize(){return size;}
};
int precedence(char op){
    if(op == '+' || op == '-')
        return 1;
    else if (op == '(')
        return 3;
    else
        return 2;
}
int main(){
    Stack<char> opStack;
    Queue postFixQ;
    string equation;
    ifstream file ;
    file.open("input.txt");
    while(!file.eof()){
        getline (file,equation);
        for(int i = 0; i < equation.size(); i++){
            if (equation[i] > '0' && equation[i] <= '9'){
                postFixQ.enQueue(equation[i]);
            }
            else if (equation[i] == '(' || equation[i] == '['){
                opStack.push(equation[i]);
            }
            else if(equation[i] == ')'){
                char c = opStack.pop();
                while(c!= '('){
                    postFixQ.enQueue(c);
                    c = opStack.pop();
                }
            }
            else if(equation[i] == ']'){
                char c = opStack.pop();
                while(c!= '['){
                    postFixQ.enQueue(c);
                    c = opStack.pop();
                }
            }
            else if(equation[i] == '~'){
                for(int i = 0; i < opStack.getSize(); i++){
                    char c = opStack.pop();
                    postFixQ.enQueue(c);
                }
            }
            else{
                if (opStack.getSize() > 0){
                    if(precedence(equation[i]) > precedence(opStack.peek()))
                        postFixQ.enQueue(opStack.pop());
                }
                opStack.push(equation[i]);
            }
        }
        int len = postFixQ.getSize();
        Stack<int> numStack;
        for(int i = 0; i < len; i++){
            char c = postFixQ.deQueue();
            cout << c;
            if(c > '0' && c <='9')
                numStack.push(int(c)-48);
            else{
                if(c == '+')
                    numStack.push(numStack.pop() + numStack.pop());
                else if(c == '-')
                    numStack.push(numStack.pop() - numStack.pop());
                else if(c == '*')
                    numStack.push(numStack.pop() * numStack.pop());
                else
                    numStack.push(numStack.pop() / numStack.pop());
            }
        }
        cout << endl;
        cout << "Result of Equation: " << numStack.pop() << endl;
    }
    file.close()
    return 0;
}
