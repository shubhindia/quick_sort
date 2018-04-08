#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include<sched.h>  //schedulling thread
#include<vector>
#include<pthread.h>  //concurrency
using namespace std;
int n;
struct args
{
int *A;
int f,l;
};
class Quick
{
public:
void Print(int A[],int n);
void swap(int &a,int &b);      //pass by reference value
int Pivote(int A[],int f,int l);
};
void Quick::Print(int A[],int n)
{
for(int i=0;i<n;i++)
cout<<A[i]<<endl;
}

void Quick::swap(int &a,int &b)
{
int temp=a;
a=b;
b=temp;
}

int Quick::Pivote(int A[],int f,int l)
{
int p=f;  //p=temporary variable
int pElement=A[f];
for(int i=f+1;i<=l;i++)
{
if(A[i]<=pElement)
{
p++;
swap(A[i],A[p]);
}
}
//printing the
//swap the elements}
swap(A[p],A[f]);
return p;
}
void* QuickSort(void* Arg)
{
Quick Q;
pthread_t id=pthread_self();
pthread_t thread[2];
args *Ar=(args*)Arg;
int piv;
if(Ar->f < Ar->l)   
{
piv=Q.Pivote(Ar->A,Ar->f,Ar->l);
cout<<"thread: "<<id<<" core:"<<sched_getcpu()<<"pivote:"<<Ar->A[piv]<<endl;
args A1;
A1.A=new int(n);
A1.A=Ar->A;
A1.f=Ar->f;
A1.l=piv-1;
args *X=&A1;
int success=pthread_create(&thread[0],NULL,&QuickSort,(void*)X);
args A2;
A2.A=new int(n);
A2.A=Ar->A;
A2.l=Ar->l;
A2.f=piv+1;
args *Y=&A2;
int success1=pthread_create(&thread[1],NULL,&QuickSort,(void*)Y);
pthread_join(thread[0],NULL);
pthread_join(thread[1],NULL);
}
}
int main()
{
Quick Q;
int N=0,n=0;
vector <int> arr;
string line;
ifstream in("demo.xml");
bool begin_tag = false;
bool begin_tag1 = false;
string tmp; // strip whitespaces from the beginning
while (getline(in,line))
{
tmp="";
for (int i = 0; i < line.length(); i++)
{
if (line[i] == ' ' && tmp.size() == 0)
{
}
else
{
tmp += line[i];
}
}
if (tmp == "<Number>")
{
begin_tag1 = true;
continue;
}
else if (tmp == "</Number>")
{
begin_tag1 = false;
}
if (begin_tag1)
{
n++;
N=atoi(tmp.c_str());  //convert string to number
arr.push_back(N);  //push number as a vector
//cout<<n<<" "<<N<<endl;
}
}
int Arr[n];
for ( int i = 0; i < arr.size(); i++)  //arr=array of vector
{
//cout << arr[i] << "\n";
Arr[i]=arr[i];
}
cout<<"\nBefore Sorting: \n";
Q.Print(Arr,n);
args a;
a.A=new int[n];
a.A=Arr;
a.f=0;
a.l=n-1;
QuickSort(&a);
cout<<endl;
cout<<"\nAfter Sorting: \n";
Q.Print(Arr,n);
return 0;
}

