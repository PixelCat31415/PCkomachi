ll r, rt, ans = 0; // Goal: S(i, k) = sum_{j < i, lpf(j) > p_k} f(j), S(i) = S(i, inf)
				   // Find g s.t. S(i, k) = S(i, k-1) - g(k) (S(i / p_k, k - 1) - S(p_k - 1, k-1))
vector<ll> small, large; // small[i] : S(i) for i = 1 ... r^(1/2), large[i] : S(r/i) for i = 1 ... r^(1/2)
ll get(ll x){ return x <= rt ? small[x] : large[r / x]; }
ll init(ll x){ return x * (x+1) / 2 - 1; } 
void lucy(){
	rt = ll(sqrt(r));
	small.resize(rt + 1); large.resize(rt + 1);
	for(int i=1;i<=rt;i++){
		small[i] = init(i); large[i] = init(r / i);
	}
	for(ll k=2;k<=rt;k++){
		if(small[k] == small[k-1]) continue;
		for(ll i = 1; i <= rt && i * k * k <= r; i++){
			large[i] -= k * (get(r / i / k) - small[k-1]);
		}
		for(ll i = rt; i >= k * k; i--){ 
			small[i] -= k * (small[i/k] - small[k-1]);
		}
	}
}
