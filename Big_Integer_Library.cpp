#include<bits/stdc++.h>
using namespace std;

string add(string s, string t){
	//Add 2 bigints; s1 is bigger and s2 smaller bigint
	string s1;string s2;
	if(s.size()<=t.size()){ 
		s1=t; s2=s; 
	}
	else{  
		s1=s; s2=t;
	}  
	int carry=0;
	//Store result in s3; s3 can be of maximum size s1(larger bigint)+1
	string  s3(s1.size()+1,0);
	//Start adding from end keeping carry
	for(int i=s1.size();i>=s1.size()-s2.size()+1;i--){
		int p=s1[i-1]-48;
		int q=s2[-s1.size()+s2.size()+i-1]-48;
		s3[i]=(p+q+carry)%10+48;
		carry=(p+q+carry)/10;
	}
	//When small bigint ends, propagate carry to rest of bigint
	for(int i=s1.size()-s2.size();i>0;i--){
		int p=s1[i-1]-48;
		s3[i]=(p+carry)%10+48;
		carry=(p+carry)/10;
	}
	//If last carry 0, remove first bit in s3
	if(carry==0){
		s3.erase(s3.begin());
	}
	//If last carry not 0, keep it in first bit of s3
	else{
		s3[0]=carry+48;   
	}

	return s3;
}

string muls(string a,int b){
	//Multiply bigint a with one digit int b
  	string s="";
	int carry=0;
	int arr[a.size()+1];
	for(int i=a.size();i>=1;i--){
		int p=a[i-1]-48;
		arr[i]=(p*b+carry)%10;
		carry=(p*b+carry)/10;
	}
	arr[0]=carry;

	if(arr[0]==0){
		for(int i=1;i<a.size()+1;i++){
			char c=arr[i]+48;
	   		s+=c;
		}
	}
	else{
		for(int i=0;i<a.size()+1;i++){
			char c=arr[i]+48;
	   		s+=c;
	   }

	}
	return s;
}

vector<string> gen(string s){
	//Multiply bigint with each digit from 1 to 9 and stores it in a vector
	vector<string> v(10);
	v[0]="0";
	for(int i=1;i<10;i++)
	v[i]=muls(s,i);
	return v;
}

string mul(string s, string t){   
	//Multiply 2 bigints
	string sum="0";
	string s1;string s2;
	string zeros="";
	if(s.size()<=t.size()){  
		s1=t; s2=s; 
	}
	else{
	  s1=s; s2=t;
	}  
	vector<string> v=gen(s1);
	//Multiple smaller bigint(s2) with each digit of larger bigint(s2) and add all results
	for(int i=s2.size()-1;i>=0;i--){ 
		string s=v[s2[i]-48]+zeros;
		sum=add(sum,s);
		zeros+="0";
	}
	return sum;
}

bool greaterthan(string a, string b){
	//Tells which bigint is greater; used in gcd
    if(a==b) return 0;
    else if(a.size()>b.size()) return 1;
    else if(a.size()<b.size())  return 0;
   
    else{
	    int i=0;
	    while(a[i]==b[i]){
	      i++;
	    }
	    int p=a[i]-'0';
	    int q=b[i]-'0';
	    return p>q;
    }
}

string factorial(string s){
	//Multiple numbers from s to 1
	string t="1";
	string q="2";
	for(int i=stoi(s)-1;i>0;i--){
		t=mul(t,q);
		q=add(q,"1");
	}
	return t;
}

string div2(string s1){   
	//Division by 2 result 
	if(s1=="1"||s1=="0") {return "0";}
	int carry=0;
	for(int i=0;i<s1.size();i++){
		int p=s1[i]-48;
		if(p%2==0) {
		    s1[i]=((p+carry)/2)+48;
		    carry=0;
		}
		else {
			s1[i]=((p+carry)/2)+48;  
			carry=10;
		}
	}
	if(s1[0]=='0'){
		s1.erase(s1.begin());
	}
	return s1;
}

string pow(string a,string b){ 
	//Fast exponentitation algo 
	if(b=="0") return "1";
	if(b=="1")  return a;
	if(b[b.size()-1]%2==0)  return mul( pow(a,div2(b)), pow(a,div2(b)) );
	else return mul(a,mul( pow(a,div2(b)), pow(a,div2(b)) ));
}

string diff(string a,string b){
	//Subtraction of 2 bigints; used in gcd
	if(a==b) return "0";
	int borrow=0;
	int sa=a.size();
	int sb=b.size();
	for(int i=0;i<sa-sb;i++){
		b='0'+b;
	}
	string ans(a.size(),0);
	for(int i=a.size()-1;i>=0;i--){
		int p=a[i]-'0'-borrow;
		borrow=0;
		int q=b[i]-'0';
		//  cout<<p<<" "<<q;
		if(p>=q){
			ans[i]=(p-q)+'0';
		}
		else	{
			ans[i]=(p+10-q)+'0';
			borrow=1;
		}
	}
	int z=0;
	while(ans[z]=='0'){
		ans.erase(ans.begin());
	}
	return ans;
}  

string gcd(string a, string b){
	
    if (a == "0")
       return b;
    while (b !="0"){
    	if (greaterthan(a,b))
           a = diff(a,b);
        else
           b = diff(b,a);
    }
    return a;
}
  
int main()
{
	cout<<"No. of test cases:";
	int t; cin>>t;
	int arr[t];
	string a[t];
	string b[t];
	for(int i=0;i<t;i++){
		cout<<"Select opeartion:1(fast exp), 2(gcd), 3(fact)";
		cin>>arr[i];
		cin.ignore();
		if(arr[i]==1){
			cout<<"Enter 2 bigints:\n";
			getline(cin,a[i]);
			getline(cin,b[i]);
		}
		if(arr[i]==2){
			cout<<"Enter 2 bigints: \n";
			getline(cin,a[i]);
			getline(cin,b[i]);
		}
		if(arr[i]==3){
			cout<<"Enter 1 bigint:\n";
			getline(cin,a[i]);
		}
	}

	for(int i=0;i<t;i++){
		if(arr[i]==1){
			cout<<"\nfast exp:"<<pow(a[i],b[i])<<endl;
		}
		if(arr[i]==2){
			cout<<"gcd:"<<gcd(a[i],b[i])<<endl;
		}
		if(arr[i]==3){
			cout<<"fact:"<<factorial(a[i])<<endl;
		}
	}
	return 0;

}