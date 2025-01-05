#include<bits/stdc++.h>
#include<fstream>
#include<sstream>
#include<vector>
#include<string>
#include<map>
#include<conio.h>
#include<windows.h>
#include <chrono>
#include <thread>
using namespace std;

void update_data();

void set_echo(bool enable) {
    HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE); 
    DWORD mode;
    GetConsoleMode(hStdin, &mode);

    if (enable) {
        mode |= ENABLE_ECHO_INPUT; //打开
    } else {
        mode &= ~ENABLE_ECHO_INPUT; //关闭
    }

    SetConsoleMode(hStdin, mode);
}

struct account{
    string user;
    string name;
    string id;
    string password;
    double monney;
    int is_lock_card;
};

vector<account> users;
int total_number;
int current_number;
int send_to_number;
int error_number;

string show_first(){
    cout << "\033[2J\033[H" << flush;
    cout<<"--------------------------------------------------"<<endl;
    cout<<"  delete(by input 'q')              ——lyk Bank——"<<endl<<endl;
    cout<<"     Welcome to lyk Bank  "<<endl;
    cout<<endl;
    cout<<"     Please Insert your card:";
    char ch;
    string user;
    while(user.size()<19){
        ch=_getch();
        if(ch>='0' && ch<='9'){
            user+=ch;
            cout<<(char)ch;
        }
        if(ch=='q' && !user.empty()){
            cout<<"\b \b";
            user.pop_back();
        }
    }
    cout<<endl;
    return user;
}

void show_main_menu(){
    cout << "\033[2J\033[H" << flush;
    cout<<"--------------------------------------------------"<<endl;
    cout<<"                                    ——lyk Bank——"<<endl;
    cout<<"     Bank card owner name:"<<users[current_number].name<<endl;
    cout<<"     Bank card id:"<<users[current_number].user<<endl<<endl;
    cout<<"  Main Menu:"<<endl;
    cout<<"     1 - View my balance"<<endl;
    cout<<"     2 - Withdraw cash"<<endl;
    cout<<"     3 - Deposit funds"<<endl;
    cout<<"     4 - transfer balance"<<endl;
    cout<<"     5 - change password"<<endl;
    cout<<"     6 - Exit"<<endl<<endl;
    cout<<"  Enter a choice:";
}

void show_in_error(){
    cout << "\033[2J\033[H" << flush;
    cout<<"--------------------------------------------------"<<endl;
    cout<<"  return(by input 'q')              ——lyk Bank——"<<endl<<endl;
    cout<<endl<<"     password error!"<<endl<<endl;
    char ch;
    string md;
    while(md.size()<1){
        ch=_getch();
        if(ch=='q'){
            md+=ch;
        }
    }
    cout<<endl;
}

void show_lock_card(){
    cout << "\033[2J\033[H" << flush;
    cout<<"--------------------------------------------------"<<endl;
    cout<<"  return(by input 'q')               ——lyk Bank——"<<endl<<endl;
    cout<<endl<<"     Due to your wrong password 3 times"<<endl<<endl;
    cout<<"     your bank card has been frozen"<<endl<<endl;
    char ch;
    string md;
    while(md.size()<1){
        ch=_getch();
        if(ch=='q'){
            md+=ch;
        }
    }
    cout<<endl;
}

void check_get_in(string in_user){
    
    for(int i=0;i<total_number;i++){
        if(users[i].user==in_user)  current_number=i;
    }
    if(error_number>=3){
        users[current_number].is_lock_card=1;
        update_data();
    }
    if(users[current_number].is_lock_card==1) {
        show_lock_card();
        return;
        }
    string in_password;
    char ch;
    cout << "\033[2J\033[H" << flush;
    cout<<"--------------------------------------------------"<<endl;
    cout<<"  delete(by input 'q')             ——lyk Bank——"<<endl<<endl;
    cout<<"     Insert successfully "<<endl<<endl;
    cout<<"     Enter a six-digit passcode:";

    while(in_password.size()<6){
        ch=_getch();
        if(ch>='0' && ch<='9'){
            in_password+=ch;
            cout<<'*';
        }
        if(ch=='q' && !in_password.empty()){
            cout<<"\b \b";
            in_password.pop_back();
        }
    }
    cout<<endl;

    int fa=0;
    for(int i=0;i<total_number;i++){
        if(users[i].password==in_password){
            fa=1;
            // show_main_menu();
        }
    }
    if(fa==0){
        show_in_error();
        error_number++;
        check_get_in(in_user);
    }
}

void show_monney(){
    cout << "\033[2J\033[H" << flush;
    cout<<"--------------------------------------------------"<<endl;
    cout<<"  return(by input 'q')     ——lyk Bank——"<<endl<<endl;
    cout<<"     your balance:"<<users[current_number].monney<<endl<<endl;
    char ch;
    string md;
    while(md.size()<1){
        ch=_getch();
        if(ch=='q'){
            md+=ch;
        }
    }
    cout<<endl;
}

void show_after_get_out_monney(){
    cout << "\033[2J\033[H" << flush;
    cout<<"--------------------------------------------------"<<endl;
    cout<<"  return(by input 'q')     ——lyk Bank——"<<endl<<endl;
    cout<<"     success to withdraw balance"<<endl<<endl;
    cout<<"     your balance:"<<users[current_number].monney<<endl;
    char ch;
    string md;
    while(md.size()<1){
        ch=_getch();
        if(ch=='q'){
            md+=ch;
        }
    }
    cout<<endl;
}

void show_after_get_in_monney(){
    cout << "\033[2J\033[H" << flush;
    cout<<"--------------------------------------------------"<<endl;
    cout<<"  return(by input 'q')     ——lyk Bank——"<<endl<<endl;
    cout<<"     success to deposit balance"<<endl<<endl;
    cout<<"     your balance:"<<users[current_number].monney<<endl;
    char ch;
    string md;
    while(md.size()<1){
        ch=_getch();
        if(ch=='q'){
            md+=ch;
        }
    }
    cout<<endl;
}

void get_out_monney(){
    cout << "\033[2J\033[H" << flush;
    cout<<"--------------------------------------------------"<<endl;
    cout<<"  delete(by input 'q')              ——lyk Bank——"<<endl<<endl;
    cout<<"     Amount to be withdrawn:";
    char ch;
    string get_out_amount;
    while(1){
        ch=_getch();
        if(ch=='\r'){
            if(!get_out_amount.empty() && get_out_amount!="."){
                break;
            }else{
                cout<<"\nensure your amount:";
                get_out_amount.clear();
            }
        }
        if((ch>='0' && ch<='9') || (ch=='.' && get_out_amount.find('.')== string::npos)){
            get_out_amount+=ch;
            cout<<ch;
        }
        if(ch=='q' && !get_out_amount.empty()){
            cout<<"\b \b";
            get_out_amount.pop_back();
        }
    }
    cout<<endl<<endl;
    double amount=stod(get_out_amount);
    if(amount>users[current_number].monney){
        cout << "\033[2J\033[H" << flush;
        cout<<"--------------------------------------------------"<<endl;
        cout<<"  return(by input 'q')              ——lyk Bank——"<<endl;
        cout<<"  again(by input 'e')               ——lyk Bank——"<<endl<<endl;
        cout<<"     Withdraw failed"<<endl<<endl;
        cout<<"     Due to your not enough balance"<<endl;
        char ch;
        string mid_in;
        while(mid_in.size()<1){
            ch=_getch();
            if(ch=='e' || ch=='q'){
                mid_in+=ch;
                cout<<ch;
            }
        }
        cout<<endl;
        if(mid_in=="e"){
            get_out_monney();
        }else{
            return;
        }
    }else{
    users[current_number].monney-=amount;
    update_data();
    show_after_get_out_monney();  
    }
    
    }

void get_in_monney(){
    cout << "\033[2J\033[H" << flush;
    cout<<"--------------------------------------------------"<<endl;
    cout<<"  delete(by input 'q')             ——lyk Bank——"<<endl<<endl;
    cout<<"     Amount to be deposited:";
    char ch;
    string get_in_amount;
    while(1){
        ch=_getch();
        if(ch=='\r'){
            if(!get_in_amount.empty() && get_in_amount!="."){
                break;
            }else{
                cout<<"\nensure your amount:";
                get_in_amount.clear();
            }
        }
        if((ch>='0' && ch<='9') || (ch=='.' && get_in_amount.find('.')== string::npos)){
            get_in_amount+=ch;
            cout<<ch;
        }
        if(ch=='q' && !get_in_amount.empty()){
            cout<<"\b \b";
            get_in_amount.pop_back();
        }
    }
    cout<<endl<<endl;
    double amount=stod(get_in_amount);
    users[current_number].monney+=amount;
    update_data();
    show_after_get_in_monney();
    
}

void show_after_transfer(){
    cout << "\033[2J\033[H" << flush;
    cout<<"--------------------------------------------------"<<endl;
    cout<<"  return(by input 'q')               ——lyk Bank——"<<endl<<endl;
    cout<<"     Transfer successful"<<endl<<endl;
    cout<<"     Your balance:"<<users[current_number].monney<<endl;
    char ch;
    string md;
    while(md.size()<1){
        ch=_getch();
        if(ch=='q'){
            md+=ch;
        }
    }
    cout<<endl;
}

void send_monney(){
    cout << "\033[2J\033[H" << flush;
    cout<<"--------------------------------------------------"<<endl;
    cout<<"  delete(by input 'q')             ——lyk Bank——"<<endl<<endl;
    cout<<"     Card id to transfer:";
    char ch;
    string id;
    while(id.size()<19){
        ch=_getch();
        if(ch>='0' && ch<='9'){
            id+=ch;
            cout<<ch;
        }
        if(ch=='q' && !id.empty()){
            cout<<"\b \b";
            id.pop_back();
        }
    }
    string id2;
    cout<<endl<<endl<<"     ensure the card id to transfer:";
    while(id2.size()<19){
        ch=_getch();
        if(ch>='0' && ch<='9'){
            id2+=ch;
            cout<<ch;
        }
        if(ch=='q' && !id2.empty()){
            cout<<"\b \b";
            id2.pop_back();
        }
    }
    cout<<endl<<endl;
    if(id!=id2){
        cout << "\033[2J\033[H" << flush;
        cout<<"--------------------------------------------------"<<endl;
        cout<<"  return(by input 'q')     ——lyk Bank——"<<endl;
        cout<<"  again(by input 'e')     ——lyk Bank——"<<endl<<endl;
        cout<<"     card to transfer is not same"<<endl<<endl;
        char ch;
        string mid_in;
        while(mid_in.size()<1){
            ch=_getch();
            if(ch=='e' || ch=='q'){
                mid_in+=ch;
                cout<<ch;
            }
        }
        cout<<endl;
        if(mid_in=="e"){
            send_monney();
        }else{
            return;
        }
        return;
    }else{
    cout<<"     Amount to be transfered:";
    string transfer_monney;
    while(1){
        ch=_getch();
        if(ch=='\r'){
            if(!transfer_monney.empty() && transfer_monney!="."){
                break;
            }else{
                cout<<"\nensure your amount:";
                transfer_monney.clear();
            }
        }
        if((ch>='0' && ch<='9') || (ch=='.' && transfer_monney.find('.')== string::npos)){
            transfer_monney+=ch;
            cout<<ch;
        }
        if(ch=='q' && !transfer_monney.empty()){
            cout<<"\b \b";
            transfer_monney.pop_back();
        }
    }
    cout<<endl<<endl;
    double amount=stod(transfer_monney);
    int fa=0;
    for(int i=0;i<total_number;i++){
        if(users[i].user==id) {
        send_to_number=i;
        fa=1;
    }
    }
    if(fa==0){
        cout << "\033[2J\033[H" << flush;
        cout<<"--------------------------------------------------"<<endl;
        cout<<"  return(by input 'q')     ——lyk Bank——"<<endl;
        cout<<"  again(by input 'e')     ——lyk Bank——"<<endl<<endl;
        cout<<"     card to transfer not exit"<<endl<<endl;
        char ch;
        string mid_in;
        while(mid_in.size()<1){
            ch=_getch();
            if(ch=='e' || ch=='q'){
                mid_in+=ch;
                cout<<ch;
            }
        }
        cout<<endl;
        if(mid_in=="e"){
            send_monney();
        }else{
            return;
        }
        return;
    }
    if(amount>users[current_number].monney){
        cout << "\033[2J\033[H" << flush;
        cout<<"--------------------------------------------------"<<endl;
        cout<<"  return(by input 'q')               ——lyk Bank——"<<endl;
        cout<<"  again(by input 'e')                ——lyk Bank——"<<endl<<endl;
        cout<<"     Transfer failed"<<endl<<endl;
        cout<<"     Due to your not enough balance"<<endl<<endl;
        char ch;
        string mid_in;
        while(mid_in.size()<1){
            ch=_getch();
            if(ch=='e' || ch=='q'){
                mid_in+=ch;
                cout<<ch;
            }
            
        }
        cout<<endl;
        if(mid_in=="e"){
            send_monney();
        }else{
            return;
        }
    }else if(users[send_to_number].is_lock_card==1){
        cout << "\033[2J\033[H" << flush;
        cout<<"--------------------------------------------------"<<endl;
        cout<<"  return(by input 'q')               ——lyk Bank——"<<endl;
        cout<<"  again(by input 'e')                ——lyk Bank——"<<endl<<endl;
        cout<<"     Transfer failed"<<endl<<endl;
        cout<<"     Due to frozen goal bank card "<<endl;
        char ch;
        string mid_in;
        while(mid_in.size()<1){
            ch=_getch();
            if(ch=='e' || ch=='q'){
                mid_in+=ch;
                cout<<ch;
            }
           
        }
        cout<<endl;
        if(mid_in=="e"){
            send_monney();
        }else{
            return;
        }
    }else{
    users[current_number].monney-=stod(transfer_monney);
    users[send_to_number].monney+=stod(transfer_monney);
    update_data();
    show_after_transfer();
    }
    
}
}

void show_after_change_password(){
    cout << "\033[2J\033[H" << flush;
    cout<<"--------------------------------------------------"<<endl;
    cout<<"  return(by input 'q')     ——lyk Bank——"<<endl<<endl;
    cout<<"     change password successful"<<endl<<endl;
    char ch;
    string md;
    while(md.size()<1){
        ch=_getch();
        if(ch=='q'){
            md+=ch;
        }
    }
    cout<<endl;
}

void change_keyword(){
    cout << "\033[2J\033[H" << flush;
    cout<<"--------------------------------------------------"<<endl;
    cout<<"  delete(by input 'q')               ——lyk Bank——"<<endl<<endl;
    cout<<"     Enter original password:";
    char ch;
    string password;
    while(password.size()<6){
        ch=_getch();
        if(ch>='0' && ch<='9'){
            password+=ch;
            cout<<'*';
        }
        if(ch=='q' && !password.empty()){
            cout<<"\b \b";
            password.pop_back();
        }
    }
    cout<<endl<<endl<<"     ensure password:";
    string password2;
    while(password2.size()<6){
        ch=_getch();
        if(ch>='0' && ch<='9'){
            password2+=ch;
            cout<<'*';
        }
        if(ch=='q' && !password2.empty()){
            cout<<"\b \b";
            password2.pop_back();
        }
    }
    cout<<endl;
    if(password!=password2){
        cout << "\033[2J\033[H" << flush;
        cout<<"--------------------------------------------------"<<endl;
        cout<<"  return(by input 'q')               ——lyk Bank——"<<endl;
        cout<<"  again(by input 'e')                ——lyk Bank——"<<endl<<endl;
        cout<<"     password is not same"<<endl<<endl;
        char ch;
        string mid_in;
        while(mid_in.size()<1){
            ch=_getch();
            if(ch=='e' || ch=='q'){
                mid_in+=ch;
                cout<<ch;
            }
        }
        cout<<endl;
        if(mid_in=="e"){
            change_keyword();
        }else{
            return;
        }
        return;
    }else if(password==password2 && password!=users[current_number].password){
        cout << "\033[2J\033[H" << flush;
        cout<<"--------------------------------------------------"<<endl;
        cout<<"  return(by input 'q')               ——lyk Bank——"<<endl;
        cout<<"  again(by input 'e')                ——lyk Bank——"<<endl<<endl;
        cout<<"     password is not right"<<endl<<endl;
        char ch;
        string mid_in;
        while(mid_in.size()<1){
            ch=_getch();
            if(ch=='e' || ch=='q'){
                mid_in+=ch;
                cout<<ch;
            }
        }
        cout<<endl;
        if(mid_in=="e"){
            change_keyword();
        }else{
            return;
        }
        return; 
    }else{
        cout<<endl<<"     input new password:";
        string new_password;
        char ch;
        while(new_password.size()<6){
            ch=_getch();
            if(ch>='0' && ch<='9'){
                new_password+=ch;
                cout<<'*';
            }
            if(ch=='q' && !new_password.empty()){
            cout<<"\b \b";
            new_password.pop_back();
        }
        }
        cout<<endl<<endl;
        users[current_number].password=new_password;
        update_data();
        show_after_change_password();
        
    }
}

void in_choice(){
    while(1){
    show_main_menu();
    char ch;
    string in_choice;
    while(in_choice.size()<1){
        ch=_getch();
        if(ch>='1' && ch<='6'){
            in_choice+=ch;
        }
    }
    cout<<endl;
    if(in_choice=="1") show_monney();
    else if(in_choice=="2") get_out_monney();
    else if(in_choice=="3") get_in_monney();
    else if(in_choice=="4") send_monney();
    else if(in_choice=="5") change_keyword();
    else if(in_choice=="6") break; 
    }
    }

void read_data(){
    ifstream file("users_data.txt");
    string user,name,id,password;
    double monney;
    string mid_string;
    total_number=0;
    while(getline(file,mid_string)){
        stringstream ss(mid_string);
        struct account mid_user;
        ss>>mid_user.user>>mid_user.name>>mid_user.id>>mid_user.password>>mid_user.monney>>mid_user.is_lock_card;
        users.push_back(mid_user);
        total_number++;
    }
    file.close();
}

void update_data(){
    string file="users_data.txt";
    ofstream out_File(file,ios::trunc);
    for(int i=0;i<total_number;i++){
    out_File<<users[i].user<<' '<<users[i].name<<' ';
    out_File<<users[i].id<<' '<<users[i].password<<' ';
    out_File<<users[i].monney<<' '<<users[i].is_lock_card<<' ';
    out_File<<endl;
    }
}

int main(){
    set_echo(false);
    while(1){
    read_data();
    error_number=0;
    string in_user=show_first();
    check_get_in(in_user);
    if(users[current_number].is_lock_card!=1){
        in_choice();
    }
    update_data();
}
return 0;
}