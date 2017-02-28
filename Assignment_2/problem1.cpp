#include <bits/stdc++.h>
using namespace std;

int findLongZigZag(int *a, int size) {

  if(size<=2) {
    return size;
  }

  // to track alternate positive and negative sequence.
  int *b = (int *)malloc(sizeof(int)*size);
  // to track length of longest sequence till ith index. 
  int *s = (int *)malloc(sizeof(int)*size);
  int i,j;

  s[0]=1;
  b[0]=a[0];
  b[1]=a[1]-a[0];
  s[1]=2;
  for(i=2;i<size;i++) {
    s[i]=2;
    b[i]=0;
  }

  for(i=2;i<size;i++) {
     for(j=1;j<i;j++) {
        if(b[j]<0) {
           if(a[i] > a[j] && s[i]<=s[j]+1) {
                s[i]=s[j]+1;
                b[i]=a[i]-a[j];
           }
        } else {
          if(a[i] < a[j] && s[i]<=s[j]+1) {
                s[i]=s[j]+1;
                b[i]=a[i]-a[j];
          }
        }
     }
     if(b[i]==0) {
        b[i]=a[i]-a[i-1];
     }
  }

  return s[size-1];
}

int main(){
  int size;
  cin >> size;
  int *a  = new int[size];
  for(int i = 0; i < size; i++)
    cin >> a[i];
  cout << findLongZigZag(a,size) << endl;
}