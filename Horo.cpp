

#include "Horo.h"
Horo::Horo(const std::string & path) {
    std::ifstream file(path);
    std::string name;
    std::vector<std::string>  read_names;
    while(std::getline(file,name)){
        Grip* grip= new Grip(name);
        horo.insert(name,grip);
        read_names.push_back(name);



    }
    horo[read_names[0]]->second->left=horo[read_names[read_names.size()-1]]->second;
    horo[read_names[0]]->second->right=horo[read_names[1]]->second;
    for(int i=1;i<read_names.size()-1;i++){
        horo[read_names[i]]->second->left=horo[read_names[i-1]]->second;
        horo[read_names[i]]->second->right=horo[read_names[i+1]]->second;
    }
    horo[read_names[read_names.size()-1]]->second->left=horo[read_names[read_names.size()-2]]->second;
    horo[read_names[read_names.size()-1]]->second->right=horo[read_names[0]]->second;
}

void Horo::proccess_command(const std::string & command) {
    if(command=="release"){
        std::string who;
        std::string to_be_released;
        std::cout<<"Enter the name of the person"<<std::endl;
        std::getline(std::cin,who);
        std::cout<<"Enter neighbours to be released(left, right or both)"<<std::endl;
        std::cin>>to_be_released;
        if(to_be_released=="left"){
            horo[who]->second->isholdingleft=false;
        }
        else if(to_be_released=="right"){
            horo[who]->second->isholdingright=false;
        }
        else if(to_be_released=="both"){
            horo[who]->second->isholdingright=false;
            horo[who]->second->isholdingleft=false;

        }

    }
    else if(command=="grab"){
        std::string who;
        std::string to_be_grabbed;
        std::cout<<"Enter the name of the person"<<std::endl;
        std::getline(std::cin,who);
        std::cout<<"Enter neighbours to be grabbed(left, right or both)"<<std::endl;
        std::cin>>to_be_grabbed;
        if(to_be_grabbed=="left"){
            horo[who]->second->isholdingleft=true;
        }
        else if(to_be_grabbed=="right"){
            horo[who]->second->isholdingright=true;
        }
        else if(to_be_grabbed=="both"){
            horo[who]->second->isholdingright=true;
            horo[who]->second->isholdingleft=true;

        }
    }
    else if(command=="add") {
             std::string who;
             std::string left;
             std::string right;
             std::cout<<"Enter the name of the person to be added, and the names of two adjacent dancers."
                        " \n Pres Enter after each name "<<std::endl;

             std::getline(std::cin,who);
             std::getline(std::cin,left);
             std::getline(std::cin,right);
             try {
                 add(who, left, right);
             }
             catch(...){
                 std::cout<<"Invalid names"<<std::endl;
             }

         }

    else if(command=="remove"){
          std::string who;
          std::cout<<"Enter the name of the person to be removed"<<std::endl;
          std::getline(std::cin,who);
          remove(who);
    }
    else if(command=="info"){
          std::string who;
          std::cout<<"Enter the name of the person"<<std::endl;
          std::getline(std::cin,who);
          try{
             info(who);
          }
          catch (...){
              std::cout<<"Invalid name"<<std::endl;
          }

    }
    else if(command=="swap"){
        std::string A;
        std::string B;
        std::cout<<"Enter the names of people to be swapped.\n Press Enter after each name."<<std::endl;
        std::getline(std::cin,A);
        std::getline(std::cin,B);
        try {
            swap(A, B);
        }
        catch(...){
            std::cout<<"Invalid names"<<std::endl;
        }
    }
    else {
        std::cout<<"Invalid command"<<std::endl;
    }
}

void Horo::print() {
    Grip *start = horo.getdata();
    Grip * first=start;
    while (start->right!=first) {
        std::cout << start->name << std::endl;
        start = start->right;
    }
    std::cout<<start->name<<std::endl;

}
Horo::~Horo(){

    free();

}

void Horo::add(const std::string &who, const std::string &left, const std::string &right) {//Не може да се танцува с гръб към хорото!
    if(horo[left]->second->right==horo[right]->second){
        Grip * grip=new Grip(who);
        grip->left=horo[left]->second;
        grip->right=horo[right]->second;
        horo[left]->second->right=grip;
        horo[left]->second->isholdingright=true;
        horo[right]->second->left=grip;
        horo[right]->second->isholdingleft=true;
        if(horo.insert(who,grip)){
            std::cout<<"Inserted"<<std::endl;
        }
        else{
            std::cout<<"Name already exists"<<std::endl;
        }
    }
    else{
        std::cout<<"Left and right are not adjacent"<<std::endl;
    }


}

void Horo::info(const std::string & str) {
    Grip* left=horo[str]->second->left;
    Grip* right=horo[str]->second->right;
    std::cout<<left->name;
    horo[str]->second->isholdingleft ? std::cout<<"<---" : std::cout<<"---";
    if(horo[str]->second->left->isholdingright)
        std::cout<<">";
    std::cout<<str;
    if(horo[str]->second->right->isholdingleft)
        std::cout<<"<";
    horo[str]->second->isholdingright ? std::cout<<"--->" : std::cout<<"---";
    std::cout<<right->name<<std::endl;


}

void Horo::remove(const std::string & who) {
    if(horo[who]->second->isholdingright||horo[who]->second->isholdingleft){
        std::cout<<"This won't be easy!"<<std::endl;
        return;
    }
    horo[who]->second->left->right=horo[who]->second->right;
    horo[who]->second->right->left=horo[who]->second->left;
    delete horo[who]->second;
    if(horo.erase(who)){
        std::cout<<"Free at last"<<std::endl;
    }
    if(horo.getsize()<3){
                      std::cout<<"and the music stops"<<std::endl;
                      exit(EXIT_FAILURE);
    }
    

}

void Horo::swap(const std::string & A, const std::string & B) {
    if (horo[A]->second->left == horo[B]->second) {
        if (horo[A]->second->isholdingleft&&horo[B]->second->isholdingright){
            horo[B]->second->right=horo[A]->second->right;
            horo[A]->second->right=horo[B]->second;
            horo[A]->second->left=horo[B]->second->left;
            horo[B]->second->left=horo[A]->second;

        }
    }

    else if (horo[A]->second->right==horo[B]->second){
        if(horo[A]->second->isholdingleft&&horo[B]->second->isholdingleft) {
            horo[B]->second->left = horo[A]->second->left;
            horo[A]->second->right = horo[B]->second->right;
            horo[A]->second->left = horo[B]->second;
            horo[B]->second->right = horo[A]->second;
        }
    }
    else {
        std::cout<<"Not adjacent"<<std::endl;
    }


}

void Horo::free() {
    Grip* init=horo.getdata();
    Grip* cur =init;
    Grip* temp;
    while(init->right!=cur){
        temp=init;
        init=init->right;
        delete temp;
    }
    delete init;
}

void Horo::copy(const Horo & other) {
    Grip* init=other.horo.getdata();
    Grip* cur =init;
    while(init->right!=cur){
        horo.insert(init->name,init);
        init=init->right;
    }
    horo.insert(init->name,init);


}

Horo::Horo(const Horo & other) {
    copy(other);

}

Horo& Horo::operator=(const Horo & rhs) {
   if(this==&rhs){
       return *this;
   }
   free();
   copy(rhs);
   return *this;
}


Horo::Grip::Grip(const std::string & str) :name(str)
        ,left(nullptr)
        ,right(nullptr)
        ,isholdingleft(true)
        ,isholdingright(true)
        {}
