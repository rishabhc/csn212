#include <iostream>
#include <vector>
using namespace std;

//max length of increasing subsequence
int count(vector<int> A, int n){
    int ans=1;
    int dp[n];//no. of subsequence ending with position n
    for(int i=0;i<n;i++)
    dp[i]=1;
    for(int i=1;i<n;i++){
        for(int j=i-1;j>=0;j--){
            if(A[i]>A[j])
            dp[i]=max(dp[i],dp[j]+1);
        }
        ans = max(ans,dp[i]);
    }
    return ans;
}

int main() {
    /*int A[] = {1,5,2,4,8,6};//new int[6];
    //A = {1,5,2,4,8,6};
    cout<<count(A,6);*/
    int t,n,x,min,index=0;
    cin>>t;
    while(t--){
       min=100000;
       cin>>n;
       vector<int> num;
       vector<int> new_num;
       for(int i=0;i<n;i++){
           cin>>x;
           num.push_back(x);
           if(x<min){
               index=i;
               min=x;
           }
       }
       for(int i=0;i<n;i++){
           new_num.push_back(num[(i+index)%n]);
       }
       cout<<count(new_num,n)<<endl;
    }
    return 0;
}
