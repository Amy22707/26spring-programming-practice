#include<bits/stdc++.h>
using namespace std;
int n,k;
int a[200005];
int main(){
    scanf("%d%d",&n,&k);
    for(int i=0;i<n;i++){
        scanf("%d",&a[i]);
    }
    sort(a,a+n);
    int ans=0;
    int idx=0;
    while(idx<n){
        int goal=a[idx]+k;
        while(idx+1<n and a[idx+1]<=goal){
            idx+=1;
        }
        ans+=1;
        int right=a[idx]+k;
        while(idx<n and a[idx]<=right){
            idx+=1;
        }
    }
    printf("%d",ans);
    return 0;
}