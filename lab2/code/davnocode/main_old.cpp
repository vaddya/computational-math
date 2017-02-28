//�������� ���������    TDECOMP_1
#include <iostream>
#include "../matrix.h"
#include <math.h>
#define size 3
using namespace std;
void main ()
{
	MATRIX(system);
	VECTOR(vect,size);
    float cond[size];
    float work[size];
    int ipvt[size];
// ������ ������� �������	
    system[0][0]=9.1;   
    system[1][0]=3.8;
    system[2][0]=4.1;
    //system[3][0]=0.250000;    
    
    system[0][1]=5.6;  
    system[1][1]=5.1;   
    system[2][1]=5.7;
	//system[3][1]=0.200000;    

    system[0][2]=7.8;
    system[1][2]=2.8;
    system[2][2]=1.2;
	//system[3][2]=1.0/6.0;

	//system[0][3]=0.250000;
    //system[1][3]=0.200000;
    //system[2][3]=1.0/6.0;
	//system[3][3]=1.0/7.0;
   
    vect[0]=0.0;
    vect[1]=0.0;
    vect[2]=1.0;
	//vect[3]=2.0;  


decomp(size,system,cond,ipvt,work);

    cout<<"cond="<<endl;
	cout<<cond[0]<<endl<<endl;
// ����� ��������������� - �������� cond[0]    
solve(size,system,vect,ipvt);

    cout<<"X:"<<endl;
    for(int i=0;i<size;i++)
	{cout<<vect[i]<<endl<<endl;}
    

         }
