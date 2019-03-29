#include<bits/stdc++.h>
using namespace std;
int main()
{
	int n;
	cout<<"enter the length of message\n";
	cin>>n;

	int r=0;
	while((1<<r)<(r+n+1))
	{
		r++;
	}

	string msg;
	cout<<"enter the message\n";
	cin>>msg;
	cout<<"number of redundant bits -->  ";
	cout<<r<<endl;

	int message[n+r+1];
	int k=0;
	for(int i=1;i<=(n+r);i++)
	{
		if(i && (!(i&(i-1))))
			message[i]=-1;
		else
			message[i]=msg[k++]-'0';
	}
	for(int i=1;i<=r;i++)
	{
		int cnt=0;
		for(int j=1;j<=(n+r);j++)
		{
			if((j & (1<<(i-1))) && (message[j]==1))
				cnt++;	
		}
		if(cnt&1)
			message[(1<<(i-1))]=1;
		else
			message[(1<<(i-1))]=0;
	}
	cout<<"encoded message is\n";
	for(int i=1;i<=(n+r);i++)
			cout<<message[i]<<"  ";
	cout<<"entered received message to check error\n";
	cin>>msg;
	int ans=0;

	for(int i=1;i<=r;i++)
	{
		int cnt=0;
		for(int j=1;j<=(n+r);j++)
		{
			if((j & (1<<(i-1))) && (msg[j-1]=='1'))
				cnt++;	
		}
		if(cnt&1)
			ans+=(1<<(i-1));
	}
	if(ans==0)
		cout<<"No error found\n";
	else
	{
		cout<<"Error at bit no-->  "<<ans<<endl;;
	}

	return 0;
}