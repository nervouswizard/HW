#include<bits/stdc++.h>
#include <time.h>
#include<memory.h>
using namespace std;
const int INF = 2147483647;
int a[1000000], n, heap[1000001], top, temp[1000000], t[1000000];
int s[]{10,10000,50000,100000,200000,300000,400000,500000,600000,700000,800000,900000,1000000};
timespec S, E;
bool cmp(int a, int b){
	return a<b;
}
void print(){
	for (int i=0;i<n;i++){
		cout << a[i] <<" ";
	}
	cout << "\n";
}
string test(){
//	print();
//	for (int i=0;i<n;i++) cout << t[i] << " ";
//	cout << "\n";
	for (int i=0;i<n;i++)
		if (t[i]!=a[i]) return " BAD!";
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
void Heap_sort(){
	top=0;
	for(int i=0;i<n;i++){
		push(a[i]);
	}
	for (int i=0;i<n;i++){
		a[i] = heap[1];
		pop();
	}
}
void Merge_sort(int l, int r){
	if(l==r) return;
	int m = (l+r)>>1;
	Merge_sort(l, m);
	Merge_sort(m+1, r);
	int* leftArr(new int [m - l + 2]);//6
	int* rightArr(new int [r - m + 1]);//6
	memcpy(leftArr, a + l, (m - l + 1)* sizeof(int));
	memcpy(rightArr, a + (m+1), (r - m)* sizeof(int));
	leftArr[m - l + 1 ] = INF;
	rightArr[r - m ] = INF;
	int idxLeft(0), idxRight(0); 
	for(int i(l); i <= r; ++i) {
		if(leftArr[idxLeft] < rightArr[idxRight]){
			a[i] = leftArr[idxLeft++];
		}
		else{
			a[i] = rightArr[idxRight++];
		}
	}
	delete[] leftArr;
	delete[] rightArr;
}
void Quick_sort(int l, int r){
	if (r-l<1) return;
	int ii, j;
	for (ii=l-1, j=l;j<r;j++)
		if(a[j]<a[r])
			swap(a[++ii], a[j]);
	swap(a[++ii], a[r]);
	Quick_sort(l, ii-1);
	Quick_sort(ii+1, r);
}
void Shell_sort(){
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
		for (int i = gap;i<n;i++){
			int te = a[i];
			int j;
			for (j = i;j>=gap&&a[j - gap] > te;j-=gap)
				a[j] = a[j - gap];
			a[j] = te;
		}
	}
}
int main(){
	srand(time(NULL));
	long double rt;
	for (int i=0;i<13;i++){
		n = s[i];
		for (int j=0;j<n;j++)
			temp[j] = ( rand() << 15 ) | rand();
		cout << n << ":\n";
		copy(temp, temp+n, t);
		sort(t, t+n, cmp);
		
		copy(temp, temp+n, a);
		clock_gettime(CLOCK_MONOTONIC, &S);
		Heap_sort();
		clock_gettime(CLOCK_MONOTONIC, &E);
		rt = diff(S, E);
		test();
		cout << fixed << setprecision(10) << rt << test() << "\n";
		
		copy(temp, temp+n, a);
		clock_gettime(CLOCK_MONOTONIC, &S);
		Merge_sort(0, n-1);
		clock_gettime(CLOCK_MONOTONIC, &E);
		rt = diff(S, E);
		test();
		cout << fixed << setprecision(10) << rt << test() << "\n";
		
		copy(temp, temp+n, a);
		clock_gettime(CLOCK_MONOTONIC, &S);
		Quick_sort(0, n-1);
		clock_gettime(CLOCK_MONOTONIC, &E);
		rt = diff(S, E);
		test();
		cout << fixed << setprecision(10) << rt << test() << "\n";
		
		copy(temp, temp+n, a);
		clock_gettime(CLOCK_MONOTONIC, &S);
		Shell_sort();
		clock_gettime(CLOCK_MONOTONIC, &E);
		rt = diff(S, E);
		test();
		cout << fixed << setprecision(10) << rt << test() << "\n";
	}
}
