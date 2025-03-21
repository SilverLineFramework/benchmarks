/*  eigen.c    CCMATH mathematics library source code.
 *
 *  Copyright (C)  2000   Daniel A. Atkinson    All rights reserved.
 *  This code may be redistributed under the terms of the GNU library
 *  public license (LGPL). ( See the lgpl.license file for details.)
 * ------------------------------------------------------------------------
 */
#include <stdlib.h>
#include <math.h>

void trnm(double *a,int n)
{ double s,*p,*q;
  int i,j,e;
  for(i=0,e=n-1; i<n-1 ;++i,--e,a+=n+1){
    for(p=a+1,q=a+n,j=0; j<e ;++j){
      s= *p; *p++ = *q; *q=s; q+=n;
     }
   }
}

int qrevec(double *ev,double *evec,double *dp,int n)
{ double cc,sc,d,x,y,h,tzr=1.e-15;
  int i,j,k,m,mqr=8*n;
  double *p;
  for(j=0,m=n-1;;++j){
    while(1){ if(m<1) return 0; k=m-1;
      if(fabs(dp[k])<=fabs(ev[m])*tzr) --m;
      else{ x=(ev[k]-ev[m])/2.; h=sqrt(x*x+dp[k]*dp[k]);
        if(m>1 && fabs(dp[m-2])>fabs(ev[k])*tzr) break;
	    if((cc=sqrt((1.+x/h)/2.))!=0.) sc=dp[k]/(2.*cc*h); else sc=1.;
        x+=ev[m]; ev[m--]=x-h; ev[m--]=x+h;
        for(i=0,p=evec+n*(m+1); i<n ;++i,++p){
	      h=p[0]; p[0]=cc*h+sc*p[n]; p[n]=cc*p[n]-sc*h;
         }
       }
     }
    if(j>mqr) return -1;
    if(x>0.) d=ev[m]+x-h; else d=ev[m]+x+h;
    cc=1.; y=0.; ev[0]-=d;
    for(k=0; k<m ;++k){
      x=ev[k]*cc-y; y=dp[k]*cc; h=sqrt(x*x+dp[k]*dp[k]);
      if(k>0) dp[k-1]=sc*h;
      ev[k]=cc*h; cc=x/h; sc=dp[k]/h; ev[k+1]-=d; y*=sc;
      ev[k]=cc*(ev[k]+y)+ev[k+1]*sc*sc+d;
      for(i=0,p=evec+n*k; i<n ;++i,++p){
        h=p[0]; p[0]=cc*h+sc*p[n]; p[n]=cc*p[n]-sc*h;
       }
     }
    ev[k]=ev[k]*cc-y; dp[k-1]=ev[k]*sc; ev[k]=ev[k]*cc+d;
   }
  return 0;
}

void housev(double *a,double *d,double *dp,int n)
{ double sc,x,y,h;
  int i,j,k,m,e;
  double *qw,*qs,*pc,*p;
  qs=(double *)calloc(n,sizeof(double));
  for(j=0,pc=a; j<n-2 ;++j,pc+=n+1){
    m=n-j-1;
    for(i=1,sc=0.; i<=m ;++i) sc+=pc[i]*pc[i];
    if(sc>0.){ sc=sqrt(sc);
      if((x= *(pc+1))<0.){ y=x-sc; h=1./sqrt(-2.*sc*y);}
      else{ y=x+sc; h=1./sqrt(2.*sc*y); sc= -sc;}
      for(i=0,qw=pc+1; i<m ;++i){
        qs[i]=0.; if(i) qw[i]*=h; else qw[i]=y*h;
       }
      for(i=0,e=j+2,p=pc+n+1,h=0.; i<m ;++i,p+=e++){
        qs[i]+=(y=qw[i])* *p++;
	for(k=i+1; k<m ;++k){
          qs[i]+=qw[k]* *p; qs[k]+=y* *p++;
         }
        h+=y*qs[i];
       }
      for(i=0; i<m ;++i){
	qs[i]-=h*qw[i]; qs[i]+=qs[i];
       }
      for(i=0,e=j+2,p=pc+n+1; i<m ;++i,p+=e++){
        for(k=i; k<m ;++k) *p++ -=qw[i]*qs[k]+qs[i]*qw[k];
       }
     }
    d[j]= *pc; dp[j]=sc;
   }
  d[j]= *pc; dp[j]= *(pc+1); d[j+1]= *(pc+=n+1);
  free(qs);
  for(i=0,m=n+n,p=pc; i<m ;++i) *p-- =0.;
  *pc=1.; *(pc-=n+1)=1.; qw=pc-n;
  for(m=2; m<n ;++m,qw-=n+1){
    for(j=0,p=pc,*pc=1.; j<m ;++j,p+=n){
      for(i=0,qs=p,h=0.; i<m ;) h+=qw[i++]* *qs++;
      for(i=0,qs=p,h+=h; i<m ;) *qs++ -=h*qw[i++];
     }
    for(i=0,p=qw+m; i<n ;++i) *(--p)=0.;
    *(pc-=n+1)=1.;
   }
}

void eigen(double *a,double *ev,int n)
{ double *dp;
  dp=(double *)calloc(n,sizeof(double));
  housev(a,ev,dp,n);
  qrevec(ev,a,dp,n); trnm(a,n);
  free(dp);
}
