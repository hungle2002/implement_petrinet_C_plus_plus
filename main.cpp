#include<iostream>
#include<string>
using namespace std;
class Node{
public:
    string name;
    string type;
    int token;
    Node* in1;
    Node* in2;
    Node* out1;
    Node* out2;
    int numin, numout;
    Node(string _name){
        this->name = _name;
        token=0;
        numin=1;
        numout=1;
    }
};
void printmarking(Node* arr[], int n){
        cout <<"Current marking: [";
        bool check=0;
    for(int i=0; i<n; i++){
        if(arr[i]->type=="place"){
            if(check){
                cout <<", ";
            }
            check=1;
            cout << arr[i]->token<<"."<<arr[i]->name;
        }
    }
    cout <<"]";
}
void getinital(Node* arr[], int n){
        cout <<endl<< "\tPlease enter the initial marking: "<<endl;
        for(int i=0; i<n; i++){
            if(arr[i]->type == "place"){
            cout << arr[i]->name<<": ";
            int n;
            cin>>n;
            arr[i]->token = n;
            }
        }
}
void display1(Node* arr[], int n){
    bool check=0;
    for(int i=0; i<n; i++){
        if(check){
            cout <<" --> ";
        }
        check=1;
        if(arr[i]->type == "place"){
            cout <<"("<<arr[i]->name<<")";
        }
        else{
            cout <<"["<<arr[i]->name<<"]";
        }
    }
}
void display2(Node* arr[], int n){
    // in nguoc
     bool check=0;
    for(int i=n-1; i>=n/2; i--){
        if(check){
            cout <<" --> ";
        }
        check=1;
        if(arr[i]->type == "place"){
            cout <<"("<<arr[i]->name<<")";
        }
        else{
            cout <<"["<<arr[i]->name<<"]";
        }
    }
    cout <<endl<<"  |                     ^"<<endl;
    cout <<"  v                     |"<<endl;
    // in xuoi
    display1(arr, n/2);
}
void display3(Node* arr[], int n){
     // in nguoc
     cout <<"\t    ";
     bool check=0;
    for(int i=7; i>=5; i--){
        if(check){
            cout <<" --> ";
        }
        check=1;
        if(arr[i]->type == "place"){
            cout <<"("<<arr[i]->name<<")";
        }
        else{
            cout <<"["<<arr[i]->name<<"]";
        }
    }
    cout <<endl<<"\t      |                     ^"<<endl;
    cout <<"\t      v                     |"<<endl;
    // in xuoi
    display1(arr, 5);
    //in phan tu cuoi
    cout <<endl<<"\t      \\                     ^";
    cout <<endl<<"\t        \\                  /";
    cout <<endl<<"\t          \\              /";
    cout <<endl<<"\t            \\          /";
    cout <<endl<<"\t             v       /"<<endl;
    cout << "\t             "<<"("<<arr[8]->name<<")";
}
void set(Node* arr[], int n){
    for(int i=0; i<n; i++){
        if(arr[i]->type == "transition"){
            if(i==0){
                arr[i]->in1 = arr[n-1];
            }
            else{
                arr[i]->in1 = arr[i-1];
            }
            arr[i]->out1 = arr[i+1];
        }
    }
}
void solve(Node* arr[], int n){
    string tmp;
        do{
            cout<<endl<<"\tPlese enter name of transition to fire or \"exit\" to go out"<<endl;
            cin>>tmp;
            // search for
            for(int i=0; i<n; i++){
                if(tmp == arr[i]->name){
                    // check transiotion or place
                    if(arr[i]->type == "place"){
                        cout << "Can't fire the place";
                    }
                    else{
                    if((arr[i]->numin==1 && arr[i]->in1->token>0) || (arr[i]->numin==2 && arr[i]->in2->token>0 && arr[i]->in1->token>0 )){
                    arr[i]->in1->token--;
                    if(arr[i]->numin==2){
                        arr[i]->in2->token--;
                    }
                    arr[i]->out1->token++;
                    if(arr[i]->numout == 2){
                        arr[i]->out2->token++;
                    }
                    printmarking(arr, n);
                    }
                else{
                    cout << "Can't fire this transition due to: ";
                    if(arr[i]->in1->token==0){
                        cout << "("<<arr[i]->in1->name<<") ";
                    }
                    if(arr[i]->numin==2){
                    if(arr[i]->in2->token==0){
                        cout << "("<<arr[i]->in2->name<<") ";
                    }
                    }
                }
                    }
                    break;
                }
            }
        }
        while(tmp!="exit");
}
void count(Node* arr[], int n, string tran_path, int &dem, bool flag){
    dem++;
    if(flag){
    cout <<"The transition path: ["<< tran_path<<"]"<<endl;
    printmarking(arr, n);
    cout << endl<<endl;
    }
    for(int i=0; i<n; i++){
        if(arr[i]->type == "transition"){
            if((arr[i]->numin==1 && arr[i]->in1->token>0) || (arr[i]->numin==2 && arr[i]->in2->token>0 && arr[i]->in1->token>0 )){
                arr[i]->in1->token--;
                if(arr[i]->numin==2){
                arr[i]->in2->token--;
                }
                arr[i]->out1->token++;
                if(arr[i]->numout == 2){
                arr[i]->out2->token++;
                }
                if(tran_path == ""){
                    count(arr, n, arr[i]->name, dem, flag);
                }
                else{
                    count(arr, n, tran_path +", "+arr[i]->name, dem, flag);
                }

                arr[i]->in1->token++;
                if(arr[i]->numin==2){
                arr[i]->in2->token++;
                }
                arr[i]->out1->token--;
                if(arr[i]->numout == 2){
                arr[i]->out2->token--;
                }
        }
    }
}
}
int main(){
    cout << "\tPlease choose Item:"<<endl
         <<"Press 1 for Patient network"<<endl
         <<"Press 2 for Specialist network"<<endl
         <<"Press 3 for Superimposed network"<<endl;
    int citeam;
    cin>> citeam;

    // Patient network
    if(citeam == 1){
        cout <<"\tPatient network"<<endl;
        // create list
        string str[5] = {"wait", "start", "inside", "change", "done"};
        Node* arr[5];
        for(int i=0; i<5; i++){
            arr[i] = new Node(str[i]);
            if(i%2 == 0){
                arr[i]->type = "place";
            }
            else{
                arr[i]->type="transition";
            }
        }
        // set in&out
        set(arr, 5);
        // display frame
        display1(arr, 5);
        // get inital marking
        getinital(arr, 5);
        // current marking
        printmarking(arr, 5);
        // choose transition 
        solve(arr, 5);
    }

    // Specialist network
    else if(citeam==2){
        cout << "\tSpecailist network"<<endl;
        // create list
        string str[6]={"start", "busy", "change", "docu", "end", "free"};
        Node* arr[6];
        for(int i=0; i<6; i++){
            arr[i] = new Node(str[i]);
            if(i%2 == 1){
                arr[i]->type = "place";
            }
            else{
                arr[i]->type="transition";
            }
        }
        //set in && out
        set(arr, 6);
        // display the frame
        display2(arr, 6);
        // get inital marking
        getinital(arr, 6);
        // current marking
        printmarking(arr, 6);
        // choose transition 
        solve(arr, 6);
    }
    // Superimposed network
    else{
        cout <<"\t\tSuperimposed network"<<endl;
        // create list
        string str[9]={"wait", "start", "busy", "change", "done", "docu", "end", "free", "inside"};
        Node* arr[9];
        // 5 phan tu dau
        for(int i=0; i<5; i++){
            arr[i] = new Node(str[i]);
            if(i%2 == 0){
                arr[i]->type = "place";
            }
            else{
                arr[i]->type="transition";
            }
        }
        // 3 phan tu ke
        for(int i=5; i<8; i++){
            arr[i] = new Node(str[i]);
            if(i%2 == 1){
                arr[i]->type = "place";
            }
            else{
                arr[i]->type="transition";
            }
        }
        // phan tu cuoi
            arr[8] = new Node(str[8]);
            arr[8]->type = "place";
        // set in out
        set(arr, 5);
        set(arr+5, 3);
        // free->start, start->inside
        arr[1]->in2 = arr[7];
        arr[1]->out2 = arr[8];
        arr[1]->numin++;
        arr[1]->numout++;
        // inside->change, change->docu
        arr[3]->in2 = arr[8];
        arr[3]->out2 = arr[5];
        arr[3]->numin++;
        arr[3]->numout++;
        // display frame
        display3(arr, 8);
        // get inital marking
        getinital(arr, 9);
        // current marking
        printmarking(arr, 9);
        // choose transition 
        string tmp;
        cout<<endl<<"\tPlease choose purpose"<<endl;
        cout<<"Press 1 to check transition"<<endl;
        cout<<"Press 2 to count reachable marking"<<endl;
        cout<<"Press 3 to print reachable marking"<<endl;
        cin >> tmp;
        if(tmp == "1"){
        solve(arr, 9);
        }
        else if(tmp=="2"){
            int dem=0;
            count(arr, 9, "", dem, 0);
            cout << dem << " reachable marking";
        }
        else{
            int dem=0;
            count(arr, 9, "", dem, 1);
        }
    }
}