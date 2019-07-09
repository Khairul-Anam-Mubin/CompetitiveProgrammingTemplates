//take to string as numbers and returns the product of these two numbers to strings
// On worst case BigintProd take O(n^2) complexity
string BigintProd(string str1,string str2)
{
    if(str1.size() < str2.size())
        swap(str1,str2);
    
    int len1=(int)str1.size(); 
    int len2=(int)str2.size();
    int carry=0,cnt=1;
    string prod,pro;

    for(int i=len2-1; i>=0; i--){
        carry=0;
        for(int j=len1-1; j>=0; j--){
            int x = (str2[i] - '0') * (str1[j] - '0') + carry;
            carry=x/10;
            x=x%10;
            prod.push_back(x+'0');
        }
        if(carry)
            prod.push_back(carry+'0');
        reverse(prod.begin(),prod.end());
        if(cnt==1){
            pro=prod;
            cnt++;
            prod.clear();
        }
        else{
            pro=BigintSum(pro,prod);
            prod.clear();
        }
        for(int k=len2-1;k>=i;k--){
            prod.push_back('0');
        }
    }
    //return "0" if any multiply apply with 0
    if(pro[0]=='0' && pro.size()>1)
        pro="0";
    return pro;
}
// works in O(n) ..
string BigintSum(string str1,string str2)
{
    if(str1.size() < str2.size())
        swap(str1,str2);
    
    int len1=(int)str1.size(); 
    int len2=(int)str2.size();
    int n=len2;
    int carry=0;
    string sum;

    for(int i=len1-1, j=len2-1; i>=0 ; i--, j--){
        int x;
        if(n){
            x = str1[i] - '0' + str2[j] - '0' + carry;
            n--;
        }
        else{
            x = str1[i] - '0' + carry;
        }
        carry=x/10;
        x=x%10;
        sum.push_back(x+'0');
    }
    if(carry)
        sum.push_back(carry+'0');
    reverse(sum.begin(),sum.end());

    return sum;
}
