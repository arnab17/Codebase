#include<bits/stdc++.h>
using namespace std;

#define MAX 100009

int arr[MAX],mark[MAX];

map<int,int>mp,len;
map<int,int>::iterator ii,in;
map<int,pair<int,int> >st,ed;
map<int,pair<int,int> >::iterator im;

int main(){
	//freopen("inp.txt","r",stdin);
	int n,i,num;
	scanf("%d",&n);
	
	memset(mark,0,sizeof mark);
	
	for(i=0;i<n;++i){
		scanf("%d",&num);
		mp.insert(make_pair(num,i));
	}
	
	if(n==1){
		printf("%d",(mp.begin()->first+1));
	}
	else{
		int ref_loc=0,ans=-1;
		for(ii=mp.begin();ii!=mp.end();++ii){
			int val=ii->first;
			int pos=ii->second;
			if(ii==mp.begin()){
				mark[pos]=1;
				ed.insert(make_pair(pos,make_pair(pos,1)));
				st.insert(make_pair(pos,make_pair(pos,1)));
				len.insert(make_pair(1,1));
			}
			else{
				int f1=0,f2=0;
				if(pos-1>=0&&mark[pos-1]==0) f1=1;
				if(pos+1<n&&mark[pos+1]==0) f2=1;
				if(f1==1&&f2==1){
					mark[pos]=1;
					ed.insert(make_pair(pos,make_pair(pos,1)));
					st.insert(make_pair(pos,make_pair(pos,1)));
					in=len.find(1);
					if(in!=len.end())
						in->second+=1;
					else
						len.insert(make_pair(1,1));
				}
				else if(f1==0&&f2==0){
					int lb,rb,sz;
					mark[pos]=1;
					if(pos-1>=0){
						im=ed.find(pos-1);
						lb=im->second.first;
						sz=im->second.second;
						st.erase(lb);
						ed.erase(im);
						in=len.find(sz);
						in->second--;
						if(in->second==0) len.erase(in);
						sz+=1;
					}
					else{
						lb=pos;
						sz=1;
					}
					if(pos+1<n){
						im=st.find(pos+1);
						rb=im->second.first;
						ed.erase(rb);
						in=len.find(im->second.second);
						in->second--;
						if(in->second==0) len.erase(in);
						sz+=im->second.second;
						st.erase(im);
					}
					else{
						rb=pos;
					}
					ed.insert(make_pair(rb,make_pair(lb,sz)));
					st.insert(make_pair(lb,make_pair(rb,sz)));
					in=len.find(sz);
					if(in!=len.end())
						in->second+=1;
					else
						len.insert(make_pair(sz,1));
				}
				else if(f1==0){
					int lb,rb,sz;
					mark[pos]=1;
					if(pos-1>=0){
						im=ed.find(pos-1);
						lb=im->second.first;
						sz=im->second.second;
						st.erase(lb);
						ed.erase(im);
						in=len.find(sz);
						in->second--;
						if(in->second==0) len.erase(in);
						sz+=1;
						rb=pos;
					}
					else{
						lb=pos;
						rb=pos;
						sz=1;
					}
					ed.insert(make_pair(rb,make_pair(lb,sz)));
					st.insert(make_pair(lb,make_pair(rb,sz)));
					in=len.find(sz);
					if(in!=len.end())
						in->second+=1;
					else
						len.insert(make_pair(sz,1));
				}
				else if(f2==0){
					int lb,rb,sz;
					mark[pos]=1;
					if(pos+1<n){
						im=st.find(pos+1);
						rb=im->second.first;
						ed.erase(rb);
						in=len.find(im->second.second);
						in->second--;
						if(in->second==0) len.erase(in);
						sz=im->second.second+1;
						lb=pos;
						st.erase(im);
					}
					else{
						lb=pos;
						rb=pos;
						sz=1;
					}
					ed.insert(make_pair(rb,make_pair(lb,sz)));
					st.insert(make_pair(lb,make_pair(rb,sz)));
					in=len.find(sz);
					if(in!=len.end())
						in->second+=1;
					else
						len.insert(make_pair(sz,1));
				}
			}
			if(len.size()==1){
				if(ed.size()>ref_loc){
					ans=val+1;
					ref_loc=ed.size();
				}
			}
		}
		printf("%d",ans);
	}
	return 0;
}
