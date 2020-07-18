#define max(n1,n2) n1>n2?n1:n2
int freq[200]={0},mx=0,i,j,len=0;

for(i=0;s[i];++i){
    if(freq[s[i]-0]){
       for(j=i-len;(s[j]!=s[i]);++j){
           --freq[s[j]-0];
           --len;
       }
        --freq[s[j]-0];
        --len;
        --i;
    }
    else{
        ++len;
        ++freq[s[i]-0];
    }
    mx=max(mx,len);
}
return mx;