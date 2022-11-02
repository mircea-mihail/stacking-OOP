#include <iostream>
using namespace std;

//where to delete[]: =operator
//                   setters
//                   destructors

//to always delete before new allocation, except constructors

//last in first out container
class stack{
    int cur;
    int *els;

    static int stack_track;
    static int stack_total;

public:
    //basic constructor
    stack();
    //copy constructor
    stack(const stack &rhs);

    //print all
    void pall() const;
    //bcopy and scopy are meant to change the stack
    void bcopy();
    void scopy();

    //getting 2 [[nodiscard]] warnings, but maybe I don't always want to use the return value of my function
    [[nodiscard]] int getCur()const;
    [[nodiscard]] const int* getEls()const;
    static int get_stack_track();
    static int get_stack_total();

    void setCur(int a);
    void setEls(int *a);
    static void set_stack_track(int a);
    static void set_stack_total(int a);

    int top() const;
    //pop and push are meant to change the stack
    int pop();
    int push(int a);
    int len() const;

    //== means they have the same amount of elements and
    //also the same values in the same order
    bool operator == (const stack &rhs) const;
    bool operator!= (const stack &rhs) const;
    stack& operator= (const stack &rhs);
    
    int operator>> (int toBeAdded);
    int operator<< (int);

    friend ostream& operator<<(ostream &os, stack &s);
    friend istream& operator>>(istream &is, stack &s);

    ~stack();
};

int stack::stack_track = 0;
int stack::stack_total = 1;

int main(){
    stack *b; bool ballocated = false;
    int a, bv;
    bool check = true;

    stack *v;

    v = new stack[1];

    cout << "pick a build value ";
    cin >> bv;
    v[stack::get_stack_track()].push(bv);

    while(check){
        //basic utility
        cout << "\n1 -- top       2 -- pop       3 -- push       4 -- length       5 -- terminate\n";
        //messing with multiple stacks
        cout << "11 stack id    22 rm stack    33 new stack    44 pick stack     55 clear all\n";
        cout << "12 a == b ?    21 a != b ?    31  pop  w <<   41 push w >>      51 do nothing\n";
        //kind of illegal in a stack? + streams
        cout << "111 get pos    222 get sptr   333 cout w <<   444 cin w >>      555 print all\n\n";
        cin >> a;
        switch(a){
            case(111):
                cout << "the current position: " << v[stack::get_stack_track()].getCur() << endl;
                break;
            case(222):
                cout << "the pointer to the current stack: " << v[stack::get_stack_track()].getEls() << endl;
                break;
            case(333):
                cout << v[stack::get_stack_track()];
                break;
            case(444):
                cout << "cin >> ";
                cin >> v[stack::get_stack_track()];
                break;
            case(555):
                v[stack::get_stack_track()].pall();
                break;

            case(11):
                cout << "current stack: " << stack::get_stack_track() << endl;
                break;
            case(22):
                if(stack::get_stack_total() == 1) {
                    cout << "unable to delete the only stack\n";
                    break;
                }
                if(ballocated)
                    delete[] b;
                b = new stack[stack::get_stack_total() - 1]; ballocated = true;
                for(int i = 0; i < stack::get_stack_track(); i++) {
                    b[i] = v[i];
                }//copied everything to "stack_track"
                for(int i = stack::get_stack_track() + 1; i < stack::get_stack_total(); i++) {
                    b[i - 1] = v[i];
                }//copied everything from "stack_track + 1 to the end

                //stack_total --;
                stack::set_stack_total(stack::get_stack_total() - 1);

                delete[] v;
                v = new stack[stack::get_stack_total()];
                for(int i = 0; i < stack::get_stack_total(); i++) {
                    v[i] = b[i];
                }

                if(stack::get_stack_track() != 0) {
                    //stack_track -= 1;
                    stack::set_stack_track(stack::get_stack_track() - 1);
                }
                else {
                    //stack_track = 0;
                    stack::set_stack_track(0);
                }
                cout << "current stack: "<< stack::get_stack_track() << endl;

                break;
            case(33):
                if(ballocated)
                    delete[] b;
                b = new stack[stack::get_stack_total() + 1]; ballocated = true;
                for(int i = 0; i < stack::get_stack_total(); i++) {
                    b[i] = v[i];
                }

                delete[] v;
                v = new stack[stack::get_stack_total() + 1];
                for(int i = 0; i < stack::get_stack_total(); i++) {
                    v[i] = b[i];
                }
                //stack_track = stack_total;
                stack::set_stack_track(stack::get_stack_total());
                //stack_total ++;
                stack::set_stack_total(stack::get_stack_total() + 1);
                cout << "pick a build value ";
                cin >> bv;
                v[stack::get_stack_track()].push(bv);
                break;
            case(44):
                cout << "what stack to switch to? (0 to " << stack::get_stack_total()-1 << ") ";
                int saux;
                cin >> saux;
                if(saux > stack::get_stack_total()-1 || saux < 0) {
                    cout << "bad input\n";
                    break;
                }
                else {
                    //stack_track = saux;
                    stack::set_stack_track(saux);
                }
                    break;
            case(55):
                delete[] v;
                v = new stack[1];
                //stack_track = 0;
                //stack_total = 1;
                stack::set_stack_track(0);
                stack::set_stack_total(1);
                break;

            case(12):
                cout << "which stacks to compare? (0 - " << stack::get_stack_total()-1 << ") ";
                int m, n;
                cin >> m >> n;
                if(m < 0 || n < 0 || m > stack::get_stack_total()-1 || n > stack::get_stack_total()-1) {
                    cout << "bad input\n";
                    break;
                }
                if(v[m] == v[n])
                    cout << "the stacks are the same\n";
                else
                    cout << "the stacks differ\n";
                break;
            case(21):
                cout << "which stacks to compare? (0 - " << stack::get_stack_total()-1 << ") ";
                int m1, n1;
                cin >> m1 >> n1;
                if(m1 < 0 || n1 < 0 || m1 > stack::get_stack_total()-1 || n1 > stack::get_stack_total()-1) {
                    cout << "bad input\n";
                    break;
                }
                if(v[m1] != v[n1])
                    cout << "the stacks differ\n";
                else
                    cout << "the stacks are the same\n";
                break;
            case(31):
                v[stack::get_stack_track()] << 0;
                break;
            case(41):
                cout << "input value needed ";
                int aux1;
                cin >> aux1;
                v[stack::get_stack_track()] >> aux1;
                break;
            case(51):
                break;

            case(1):
                v[stack::get_stack_track()].top();
                break;
            case(2):
                v[stack::get_stack_track()].pop();
                break;
            case(3):
                cout << "input value needed ";
                int aux;
                cin >> aux;
                v[stack::get_stack_track()].push(aux);
                break;
            case(4):
                v[stack::get_stack_track()].len();
                break;
            case(5):
                check = false;
                cout << "thanks for \"playing\"\n"; break;

            default: cout << "bad input\n";
        }
    }
    delete[] v;
    if(ballocated)
        delete[] b;
    return 0;
}

stack::stack(){
    cur = -1;
    els = nullptr;
}

stack::stack(const stack &rhs) {
    cur = rhs.cur;
    //constructor so no delete before allocation
    els = new int[cur + 1];
    for (int i = 0; i <= cur; i++)
        els[i] = rhs.els[i];
}

int stack::getCur()const{
    return cur;
}

const int* stack::getEls()const{
    return els;
}

int stack::get_stack_track(){
    return stack_track;
}

int stack::get_stack_total(){
    return stack_total;
}

void stack::setCur(int a){
    cur = a;
}

void stack::setEls(int *a){
    delete[] els;
    els = a;
}

void stack::set_stack_track(int a){
    stack_track = a;
}

void stack::set_stack_total(int a){
    stack_total = a;
}

void stack::pall() const{
    cout << "the whole array is ";
    if(cur == -1)
        cout << "empty";
    else
        cout << '\n';
    for(int i = 0; i <= cur; i++)
        cout << els[i] << ' ';
    cout << endl;
}

void stack::bcopy(){
    int *aux;
    aux = new int[cur+2];
    for(int i = 0; i <= cur; i++)
        aux[i] = els[i];

    delete[] els;
    els = new int[cur+2];
    for(int i = 0; i <= cur; i++)
        els[i] = aux[i];

    delete[] aux;
}

void stack::scopy(){
    int *aux;
    aux = new int[cur];
    for(int i = 0; i < cur; i++)
        aux[i] = els[i];

    delete[] els;
    els = new int[cur];
    for(int i = 0; i < cur; i++)
        els[i] = aux[i];

    delete[] aux;
}

int stack::top() const{
    if(cur == -1) {
        cout << "the stack is empty" << endl;
        return -1;
    }
    else {
        cout << "val " << els[cur] << " on pos " << cur << endl;
        return els[cur];
    }
}

int stack::pop(){
    if(cur == -1) {
        return cur;
    }
    else {
        if(cur == 0){
            cur--;
            delete[] els;
            return cur;
        }
        else{
            scopy();
            cur --;
            return cur;
        }
    }
}

int stack::push(int a){
    if(cur == -1)//it means that the stack is empty
        els = new int[1];
    else
        bcopy();
    cur ++;
    els[cur] = a;
    return cur;
}

int stack::len()const{
    cout << "length: " << cur+1 << endl;
    return cur + 1;
}

bool stack::operator== (const stack &rhs) const{
    if (cur != rhs.cur)
        return false;
    for(int i = 0; i <= cur; i++){
        if(els[i] != rhs.els[i])
            return false;
    }
    return true;
}

bool stack::operator != (const stack &rhs) const{
    if(*this == rhs)
        return false;
    return true;
}

//warning untreatable with current knowledge
stack& stack::operator= (const stack &rhs){
    if(*this != rhs){
        cur = rhs.cur;
        delete[] els;
        els = new int[cur +1];
        for(int i = 0; i <= cur; i++)
            els[i] = rhs.els[i];
    }
    return *this;
}

int stack::operator>> (int toBeAdded){
    return (*this).push(toBeAdded);
}

int stack::operator<< (int){
    return (*this).pop();
}

ostream& operator<<(ostream &os, stack &s) {
    if (!s.els) {
        os << "cout << the stack is empty\n";
        return os;
    }

    os << "cout << ";
    s.top();

    return os;
}

istream& operator>>(istream &is, stack &s) {
    int tval;
    is >> tval;
    s.push(tval);

    return is;
}

stack::~stack(){
    if(cur != -1)
        delete[] els;
}