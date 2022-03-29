#include<bits/stdc++.h>
using namespace std;
const int INF = 1e9+7;
int *a, n, *heap, top=0;
int s[]{10,10000,50000,100000,200000,300000,400000,500000,600000,700000,800000,900000,1000000};
timespec S, E;
string test(int *t){
	int *tt;
	copy(t, t+n, tt);
	sort(tt, tt+n);
	for (int i=0;i<n;i++){
		if (tt[i]!=a[i]) return " BAD!";
	}
	return " NICE!";
}
int power(int a, int x){
	int ans=1;
	for(;x;x>>=1,a=a*a){
		if(x&1)
			ans=ans*a;
	}
	return ans;
}
void print(){
	for (int i=0;i<n;i++){
		cout << a[i] <<" ";
	}
	cout << "\n";
}
long double diff(timespec S, timespec E){
	timespec temp;
	if ((E.tv_nsec-S.tv_nsec)<0) {
		temp.tv_sec = E.tv_sec-S.tv_sec-1;
		temp.tv_nsec = 1000000000+E.tv_nsec-S.tv_nsec;
	} else {
		temp.tv_sec = E.tv_sec-S.tv_sec;
		temp.tv_nsec = E.tv_nsec-S.tv_nsec;
	}
  	return temp.tv_sec + (long double) temp.tv_nsec / 1000000000.0;
}
void push(int d){
	heap[++top] = d;
	for (int i=top;i>1&&heap[i]<heap[i/2];i/=2){
		swap(heap[i],heap[i/2]);
	}
}
void pop(){
	heap[1] = heap[top--];
	for(int i=1;i*2<=top;)
		if (i*2<top && heap[i*2+1]<heap[i] && heap[i*2+1]<heap[i*2])
			swap(heap[i],heap[i*2+1]),i=i*2+1;
		else if(heap[i*2]<heap[i])
			swap(heap[i],heap[i*2]),i=i*2;
		else
			break;
}
long double Heap_sort(){
	clock_gettime(CLOCK_MONOTONIC, &S);
	for(int i=0;i<n;i++){
		push(a[i]);
	}
	for (int i=0;i<n;i++){
		a[i] = heap[1];
		pop();
	}
	clock_gettime(CLOCK_MONOTONIC, &E);
	return diff(S, E);
}
long double Merge_sort(int l, int r){
	clock_gettime(CLOCK_MONOTONIC, &S);
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
	clock_gettime(CLOCK_MONOTONIC, &E);
	return diff(S, E);
}
long double Quick_sort(int l, int r){
	cout << l <<" "<< r<<"\n";
	clock_gettime(CLOCK_MONOTONIC, &S);
	if (r-l<=1) return 0;
	int ii, j;
	for (ii=l-1, j=l;j<r;j++){
		if(a[j]<a[r]){
			cout << a[ii+1] << " ";
			swap(a[++ii], a[j]);
			cout << ii << "\n";
		}
	}
	swap(a[++ii], a[r]);
	print();
	cout << l << " " << ii << " " << r << "\n";
	Quick_sort(l, ii-1);
	Quick_sort(ii+1, r);
	clock_gettime(CLOCK_MONOTONIC, &E);
	return diff(S, E);
}
long double Shell_sort(){
	clock_gettime(CLOCK_MONOTONIC, &S);
	vector<int> v;
	for (int i=1, gap=1;gap<=n;i++){
		v.push_back(gap);
		if(i%2)
			gap = 8*power(2,i)-6*power(2, (i+1)/2)+1;
		else
			gap = 9*(power(2,i)-power(2,i/2))+1;
	}
	reverse(v.begin(), v.end());
	for (int gap:v){
		for (int i = gap;i<n;i++)
			for (int j = i-gap;j>=0;j-=gap)
				if (a[j]>a[j+gap])
					swap(a[j], a[j+gap]);
	}
	clock_gettime(CLOCK_MONOTONIC, &E);
	return diff(S, E);
}
int main(){
	for (int i=0;i<12;i++){
		int *temp;
		srand(time(NULL));
		n = s[i];
		a = new int [n];
		heap = new int [n];
		temp = new int [n];
		for (int j=0;j<n;j++)
			temp[j] = rand();
		cout << n << ":\n";
		copy(temp, temp+n, a);
		print();
		cout << fixed << setprecision(10) << Quick_sort(0, n-1) << test(temp)  << "\n";
		copy(temp, temp+n, a);
		cout << fixed << setprecision(10) << Heap_sort() << test(temp) << "\n";
		copy(temp, temp+n, a);
		cout << fixed << setprecision(10) << Merge_sort(0, n-1) << test(temp)  << "\n";
		copy(temp, temp+n, a);
		cout << fixed << setprecision(10) << Shell_sort() << test(temp)  << "\n";
		delete [] a, heap, temp;
	}
}
