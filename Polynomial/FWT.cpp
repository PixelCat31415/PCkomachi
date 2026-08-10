/* (op, invop): (oyx: op from y to x)
or: (1, 0, 1, 1), (1, 0, -1, 1)
and: (1, 1, 0, 1), (1, -1, 0, 1)
xor: (1, 1, 1, -1), (1/2, 1/2, 1/2, -1/2) */
void fwt(vector<int>& a, int n, int oxx, int oyx, int oxy, int oyy){ // 2^20, 0.5s
	for(int L=2;L<=n;L<<=1)
		for(int i=0;i<n;i+=L)
			for(int j=i;j<i+(L>>1);j++){
#define x a[j]
#define y a[j+(L>>1)]
				tie(x, y) = pii(mul(x,oxx)+mul(y,oyx), mul(x,oxy)+mul(y,oyy));
				add(x, 0); add(y, 0);
#undef x
#undef y
			}
}

vector<int> subset_conv(vector<int> a, vector<int> b, int L){
	int n = 1<<L; // 2^20, 5.5s, using c-sytle arrays -> 2.1s
	vector<vector<int> > f(L+1, vector<int>(n)), g=f, h=f;
   	vector<int> ct(n), c(n);
	for(int i=1;i<n;i++) ct[i] = ct[i&(i-1)] + 1;
	for(int i=0;i<n;i++) { f[ct[i]][i] = a[i]; g[ct[i]][i] = b[i]; }
	for(int i=0;i<=L;i++) { fwt(f[i], n, 1, 0, 1, 1); fwt(g[i], n, 1, 0, 1, 1); }
	for(int i=0;i<=L;i++)
		for(int j=0;j<=i;++j)
			for(int x=0;x<n;x++)
				add(h[i][x], mul(f[j][x], g[i-j][x]));
	for(int i=0;i<=L;i++) fwt(h[i], n, 1, 0, -1, 1);
	for(int i=0;i<n;i++) c[i] = h[ct[i]][i];	
	return c;
}

