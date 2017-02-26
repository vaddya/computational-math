 #ifndef _MATRIX
  #define _MATRIX
  #define ndim 25
  #define N_TYPE float
  #define FORMAT_STR "%18.11e "
  #define MATRIX(name) N_TYPE name[ndim][ndim]
  #define VECTOR(name,size) N_TYPE name[size]

 void solve (int n,MATRIX(a),N_TYPE * b,int * ipvt);
 void decomp(int n,MATRIX(a),N_TYPE * cond, int * ipvt,N_TYPE * work);
#endif _MATRIX