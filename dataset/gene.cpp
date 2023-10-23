//abc202_f
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define ll long long
#define rep(i,l,r)for(int i=(l);i<(r);i++)
#define MOD 1000000007
#define add(x,y)(x=(x+(y))%MOD)
typedef struct point{ll x,y;}P;
int jisho_sort(const void*pp,const void*qq){
	P *p=(P*)pp, *q=(P*)qq;
	if(p->x < q->x)return -1;
	if(p->x > q->x)return  1;
	if(p->y < q->y)return -1;
	return 1;
}
int arg_sort(const void*pp,const void*qq){
	P *p=(P*)pp, *q=(P*)qq;
	double pt=atan2(p->y,p->x);
	double qt=atan2(q->y,q->x);
	if(pt<qt)return -1;
	return 1;
}
ll crossproduct(P p,P q,P o){return (p.x-o.x)*(q.y-o.y)-(p.y-o.y)*(q.x-o.x);}
ll isin_triangle(P a,P b,P c,P p){
	//点pが三角形abcの内部(境界含む)にあれば1、外部にあれば0を返す
	ll x=crossproduct(a,b,p);
	ll y=crossproduct(b,c,p);
	ll z=crossproduct(c,a,p);
	return x<=0&&y<=0&&z<=0 || x>=0&&y>=0&&z>=0;
}
void printpoint(P p){printf("%lld %lld\n",p.x,p.y);}
P data[90];
ll p2[90];
int main(){
	p2[0]=1;
	rep(i,1,85)p2[i]=p2[i-1]*2%MOD;
	
	int n;
	scanf("%d",&n);
	rep(i,0,n)scanf("%lld%lld",&data[i].x,&data[i].y);
	qsort(data,n,sizeof(P),jisho_sort);
	ll ans=0;
	
	rep(i,0,n-1){
		ll dp[82][82][2]={};
		//dp[j][k][f]=iスタート、直前2点がjkで、面積*2%2がfとなる点の選び方
		//iが原点となるようにi+1以降を移動
		P data2[90];
		int cnt=0;
		rep(j,i,n){
			data2[cnt].x=data[j].x-data[i].x;
			data2[cnt].y=data[j].y-data[i].y;
			cnt++;
		}
		qsort(data2+1,cnt-1,sizeof(P),arg_sort);
		
		rep(j,1,cnt)dp[0][j][0]=1;
		
		rep(j,1,cnt)rep(k,j+1,cnt){
			int inner=0;
			rep(a,j+1,k)inner+=isin_triangle(data2[0],data2[j],data2[k],data2[a]);
			ll s=llabs(crossproduct(data2[0],data2[j],data2[k]));
			rep(pre,0,j)if(crossproduct(data2[k],data2[pre],data2[j])>0){
				add(dp[j][k][0],dp[pre][j][  s%2 ]*p2[inner]);
				add(dp[j][k][1],dp[pre][j][!(s%2)]*p2[inner]);
			}
			add(ans,dp[j][k][0]);
		}
	}
	
	printf("%lld\n",ans);
}
