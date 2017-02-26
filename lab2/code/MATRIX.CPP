#include <math.h>
#include "matrix.h"


  void solve (
		   int n,
		   MATRIX(a),
		   N_TYPE * b  ,
		   int * ipvt
				   )

{
	int kb,km1,nm1,kp1,i,k,m;
	N_TYPE t                        ;
	if (n ==1)  {
			 b[1-1]=b[1-1] / a[1-1][1-1];
			 return;
		   }
	nm1=n-1;
      for (k=1;k<=nm1;k++)
      {
			     kp1=k+1;
			     m=ipvt[k-1];
			     t=b[m-1];
			     b[m -1]=b[k-1];
			     b[k-1]=t;
			     for (i=kp1;i<=n;i++) b[i-1]=b[i-1] + a[i-1][k-1]*t;
		       }
    for (kb=1 ;kb<=nm1;kb++) {
			      km1=n-kb;
			      k=km1 + 1;
			      b[k-1]=b[k-1]/a[k-1][k-1];
			      t=-b[k-1];
			      for (i=1;i<=km1;i++) b[i-1]=b[i-1] + a[i-1][k-1]*t;
			}
	  b[1-1]=b[1-1] / a[1-1][1-1];
	}






 void decomp(
		   int n ,
		   MATRIX(a),
		   N_TYPE * cond ,
		   int * ipvt ,
		   N_TYPE * work
				   )
{
	int nm1,i,j,k,kp1,kb,km1,m;
	N_TYPE ek,t,anorm,ynorm,znorm;
	ipvt[n-1]=1;
	if (n == 1)  {
			  *cond=1.0;
			  if (a[1-1][1-1] != 0.0)  return;
					   else {
						  *cond=(float)1.0e+32;
						  return;
						}
			};
	nm1=n-1;
	anorm=0.0;
	for (j=1 ;j<= n;j++)
	{
			      t=0.0;
			      for (i=1 ;i<=n;i++) t=t+(float)fabs(a[i-1][j-1]);
			      if (t > anorm) anorm=t;
       }
      for (k=1;k<=nm1;k++)
      {
	    kp1=k + 1;
	    m=k;
	    for (i=kp1;i<=n;i++)
			 if (fabs(a[i-1][k-1]) > fabs(a[m-1][k-1]))
				m=i;
	    ipvt[k-1]=m;
	    if (m != k) ipvt[n-1]=-ipvt[n-1];
	    t=a[m-1][k-1];
	    a[m-1][k-1]=a[k-1][k-1];
	    a[k-1][k-1]=t;
	    if (t !=  0.0) {
	    for (i=kp1 ;i<=n;i++) a[i-1][k-1]=-a[i-1][k-1]/t;
	    for (j=kp1 ;j<=n;j++) {
				   t=a[m-1][j-1];
				   a[m-1][j-1]=a[k-1][j-1];
				   a[k-1][j-1]=t;
				   if (t != 0.0) for (i=kp1 ;i<=n;i++)
					  a[i-1][j-1]=a[i-1][j-1] + a[i-1][k-1]*t;
				      }
				   }
			     }
      for (k=1;k<=n;k++) {
				   t=0.0;
				   if (k != 1) {
						    km1=k-1;
						    for (i=1;i<=km1;i++)
						 t=t + a[i-1][k-1] * work[i-1];
						  }
			       ek=1.0;
	     if (t < 0.0) ek=-1.0;
	     if (a[k-1][k-1] == 0.0) {
				    *cond=(float)1.0E+20;
				    return;
			       };
	     work[k-1]=-(ek+t)  / a[k-1][k-1];
		    }
	 for (kb=1;kb<=nm1;kb++) {
		k=n-kb;
		t=0.0;
		kp1=k + 1;
		for (i=kp1;i<=n;i++) t=t + a[i-1][k-1] * work[k-1];
		work[k-1]=t;
		m=ipvt[k-1];
		if (m != k) {
				 t=work[m-1];
				 work[m-1]=work[k-1];
				 work[k-1]=t;
			      }
		       }
	ynorm=0.0;
	for (i=1;i<=n;i++)  ynorm=ynorm + (float)fabs(work[i-1]);
	solve(n,a,work,ipvt);
	znorm=0.0;
	for (i=1;i<=n;i++) znorm=znorm + (float)fabs(work[i-1]);
	*cond=anorm*znorm/ynorm;
	if (*cond < 1.0)	 *cond=1.0;
	return;
}

