const int N=1e6+1;
ll fac[N], facp[N], inv[N];
void build() {
	for (int i : {0, 1})
		fac[i] = facp[i] = inv[i] = 1;
	for (int i = 2; i < N; ++i) {
		inv[i] = mod - inv[mod % i] * (mod / i) % mod;
		fac[i] = fac[i - 1] * i % mod;
		facp[i] = facp[i - 1] * inv[i] % mod;
	}
}
