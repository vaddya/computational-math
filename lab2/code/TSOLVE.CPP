#include <stdio.h>
#include <conio.h>
#include "matrix.h"
#include <math.h>
#define O_ROW            1
#define O_COLUMN         2

MATRIX(SourceM);
MATRIX(BaseM);
MATRIX(ObrM);
MATRIX(Res);
VECTOR(CurrBV,4);
VECTOR(CurrXV,4);
VECTOR(work2,4);

int n=4;
void PrintMatrix(MATRIX(d));
void MakeMatrix(double a);
void MakeBaseMatrix(MATRIX(m));
N_TYPE n_abs(N_TYPE n);
void Vector2Matrix(VECTOR(v,4) , MATRIX(m),int pos,int orient,int n);
void Matrix2Vector(VECTOR(v,4) , MATRIX(m),int pos,int orient,int n);
void MultiMatrix(MATRIX(m1),MATRIX(m2),MATRIX(m3));
void DecMatrix(MATRIX(m1),MATRIX(m2));
N_TYPE norma(MATRIX(m));

N_TYPE norma(MATRIX(m))
{
 N_TYPE res=0;
 for (int i=0;i<n;i++)
  for (int j=0;j<n;j++)
   res+=m[i][j]*m[i][j];
 res=(float)sqrtl(res);
 return res;
}

void DecMatrix(MATRIX(m1),MATRIX(m2))
{
 for (int i=0;i<n;i++)
  for (int j=0;j<n;j++)
  {
   m1[i][j]-=m2[i][j];
  }
}

N_TYPE n_abs(N_TYPE n)
{
 return(n>0 ? n : -n);
}

void MultiMatrix(MATRIX(m1),MATRIX(m2),MATRIX(m3))
{
 for(int k=0;k<n;k++)
  for (int j=0;j<n;j++)
   {
    m3[k][j]=0;
    for(int i=0;i<n;i++)
     m3[k][j]+=m1[k][i]*m2[i][j];
   }
}

void MakeBaseMatrix(MATRIX(m))
{
 for (int i=0;i<n;i++)
  for (int j=0;j<n;j++)
  if (i!=j) m[i][j]=0; else m[i][j]=1;
}

void PrintMatrix(MATRIX(d),int n)
{
 printf("\nMatrix:\n");
 for (int i=0;i<n;i++)
 {
  if (i==0) printf("%c",218);
  else
  if (i==(n-1)) printf("%c",192);
  else
  printf("%c",179);
  for (int j=0;j<n;j++)
        {
        printf(FORMAT_STR,d[i][j]);
        }
   if (i==0) printf("%c",191);
  else
  if (i==(n-1)) printf("%c",217);
  else
  printf("%c",179);
  printf("\n");
 }
}

void PrintVector(VECTOR(d,4),int n)
{
 printf("\nVector:\n");
 for (int i=0;i<n;i++)
   printf(FORMAT_STR,d[i]);
}

void MakeMatrix(double a)
{
 int i,j;
 for (i=0;i<4;i++)
  for (j=0;j<4;j++)
	SourceM[i][j]=0;
 for (i=0;i<4;i++)
  SourceM[i][i]=pow(a,n_abs((float)(n-2*(i+1))/2));
 for (j=0;j<4;j++)
  SourceM[0][j]=SourceM[0][0]/pow(a,(j+1));
 for (j=0;j<4;j++)
  SourceM[n-1][j]=SourceM[n-1][n-1]/pow(a,(j+1));
 for (j=0;j<4;j++)
  SourceM[j][0]=SourceM[0][j];
 for (j=0;j<4;j++)
  SourceM[j][n-1]=SourceM[n-1][j];
}

void Vector2Matrix(VECTOR(v,4),MATRIX(m),int pos,int orient,int n)
{
 for (int i=0;i<n;i++)
  if (orient==O_ROW)
    m[pos][i]=v[i];
   else
    m[i][pos]=v[i];
}

void Matrix2Vector(VECTOR(v,4),MATRIX(m),int pos,int orient,int n)
{
 for (int i=0;i<n;i++)
  if (orient==O_ROW)
    v[i]=m[pos][i];
   else
    v[i]=m[i][pos];
}

void main(void)
{
 N_TYPE cond;
 N_TYPE SData[]={1.01,1.001,1.0001};
 int work1[10];
 for (int k=0;k<3;k++)
 {
 for(int h=0;h<10000;h++)
 {
 MakeMatrix(SData[k]);
 MakeBaseMatrix(BaseM);
 decomp(4,SourceM,&cond,work1,work2);
 for (int i=0;i<4;i++)
 {
  Matrix2Vector(CurrBV,BaseM,i,O_COLUMN,4);
  solve(4,SourceM,CurrBV,work1);
  Vector2Matrix(CurrBV,ObrM,i,O_COLUMN,4);
 }
 MakeMatrix(SData[k]);
 MultiMatrix(ObrM,SourceM,Res);
 DecMatrix(BaseM,Res);
 }
 printf("Condition A=%.2e",cond);
 PrintMatrix(BaseM,4);
 printf("Norma Res=%e\n"
"--------------------------------------------------------------------------\n",
norma(BaseM));
 getchar();
 }
}

