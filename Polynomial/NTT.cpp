//(2^16)+1, 65537, 3
//7*17*(2^23)+1, 998244353, 3
//1255*(2^20)+1, 1315962881, 3
//51*(2^25)+1, 1711276033, 29
// only works when sz(A) + sz(B) - 1 <= MAXN
// implement add, po, mul, inv first
template<int N, int RT>
struct NTT{
	int w[N];
	NTT() {
		int dw = po(RT, (mod-1) / N);
		w[0] = 1;
		for(int i=1;i<N;i++) w[i] = mul(w[i-1], dw);
	}
	void bitrev(vector<int>& a, int n){
		int i=0;
		for(int j=1; j<n-1; j++) {
			for(int k=n>>1; (i^=k) < k; k>>=1);
			if(j<i) swap(a[i], a[j]);
		}
	}
	void operator()(vector<int>& a,int n, bool ix = false){
		bitrev(a,n);
		for(int L=2;L<=n;L<<=1){
			int dx = N/L, dl = L>>1;
			for(int i=0;i<n;i+=L){
				for(int j=i, x=0; j<i+dl; j++, x+=dx){
					int tmp = mul(a[j+dl], w[x]);
					a[j+dl] = a[j];
					add(a[j+dl], -tmp);
					add(a[j], tmp);
				}
			}
		}
		if(ix){
			reverse(a.begin()+1, a.begin()+n);
			int invn = inv(n);
			for(int i=0;i<n;i++) a[i] = mul(a[i], invn);
		}
	}
};


