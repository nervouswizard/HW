#include<bits/stdc++.h>
using namespace std;
const int INF = 1e9+7;
int *a;
double S;
double Merge_sort(int l, int r){
	S = clock();
	if(l==r) return 0;
	int m = (l+r)>>1;
	Merge_sort(l, m);
	Merge_sort(++m, r);
	int pl = l, pm = m, pr = r;
	queue<int> q;
	while(pl<m&&pm<=pr){
		if (a[pl]<a[pm])
			q.push(a[pl++]);
		else
			q.push(a[pm++]);
	}
	while(pl<m)
		q.push(a[pl++]);
	while(pm<=pr)
		q.push(a[pm++]);
	for (int i=l;i<=r;i++){
		a[i] = q.front();
		q.pop();
	}
	return (clock()-S)/CLOCKS_PER_SEC;
}
int main(){
	srand(time(NULL));
	a = new int [10000];
	for (int i=0;i<10000;i++){
		a[i] = rand();
	}
	cout << Merge_sort(0, 9999);
	for (int i=0;i<10000;i++){
		cout << a[i] <<" ";
	}
	delete [] a;
}
