#include <iostream> 
#include <vector>
#include <boost/any.hpp>

using namespace std;

class a{
  public:
    int global;
    int aaa(){
        return(global);
    }
    virtual void ccc()=0;
};

class b:public a{
  public:
    int xdd;
    int bbb(){
        return(global);
    }
    void ccc(){
        cout<<"virtual[b] O_O\n";
    }
};

class c:public a{
    void ccc(){
        cout<<"virtual[c] O_O\n";
    }
};

int main(){
    
    b obiekt;
    c obi;
    a* wsk;
    wsk=&obiekt;
    (wsk)->ccc();
    (wsk)->ccc();
    
    /*
    a x;
    b y;
    y.xdd=9;
    cout<<y.xdd<<"\n";
    y.global=9;
    cout<<y.global<<"\n";
    //cout<<y.aaa()<<"\n";
    */
    /*
    vector<a*> x;
    b y;
    a z;
    x.push_back(&z);
    x.push_back(&y);
    */
/*    
    std::vector<boost::any> miscArray;
    
    a tester;
    miscArray.push_back(new int);
    miscArray.push_back(new a);
    miscArray.push_back(new b);//NIE UZYWAJ NEW!!!!!!!!!!
    miscArray.push_back(tester);
    
    miscArray[0]=5;
    int tmp;
    //tmp=boost::any_cast<int>(miscArray[0]);
    tmp=boost::any_cast<a>(miscArray[3]).global;
    cout<<tmp<<"\n";
*/    
    /*
    boost::any a = 1;
    std::cout << boost::any_cast<int>(a) << '\n';
    */
}
