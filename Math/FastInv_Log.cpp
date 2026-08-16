// https://maspypy.com/o1-mod-inv-mod-pow
// needs HashMap, mul, po
int mod = 998244353, g; // g = primitive root
const int K = 1<<21; // mod ^ (2/3)
const int U = 10, N = 1<<U; // sqrt(n)
array<int, 2*K + 1> iv;
array<pii, 2*K + 1> frac; 
void build_inv(){
	iv[K+1] = 1;
	for(int i=2;i<=K;i++){
		int q = (mod + i - 1) / i;
		iv[K+i] = mul(iv[K + i * q - mod], q); 
	}
	for(int i=0;i<K;i++){
		iv[i] = mod - iv[2 * K - i];
	}
}
void build_frac(){
	vector<array<int, 4> > q;
	q.push_back({0, 1, 1, 1});
	while(q.size()){
		auto [a, b, c, d] = q.back();
		q.pop_back();
		if(b + d < (N<<1)){
			q.push_back({a, b, a+c, b+d});
			q.push_back({a+c, b+d, c, d});
			continue;
		}
		auto s = ((ll)a * mod) / (N * b);
		auto t = ((ll)c * mod) / (N * d);
		frac[t] = pii(c, d);
		frac[s] = pii(a, b);
		if(s < t) fill(frac.begin() + s + 1, frac.begin() + t, pii(min(a, c), min(b, d)));
	}
}
int inv(int x){
	auto [c, b] = frac[x >> U];
	int a = (ll)x * b - (ll)c * mod;
	return mul(iv[K + a], b);
}
vector<int> build_lpf(int w){
	vector<int> pr, lpf(w);
	for(int i=2;i<w;i++){
		if(!lpf[i]){
			lpf[i] = i;
			pr.push_back(i);
		}
		for(auto h:pr){
			if(h * i >= w) break;
			lpf[h*i] = lpf[i];
			if(i % h == 0) break;
		}
	}
	return lpf;
}
array<int, 2 * K + 1> lg;
void build_log(){
	const int K2 = 1<<17; // mod ^ (1/2);
	auto lpf = build_lpf(K + 1); 
	safe;
	HashMap<unsigned int> hs(K2);
	for(int i=0, nw = 1; i <= K2; i++, nw = mul(nw, g)) hs[nw] = i;
	lg[K+1] = 0;
	int s = po(g, mod - 1 - K2);
	for(int i=2;i<=K;i++){
		if(lpf[i] != i){
			lg[K+i] = (lg[K+lpf[i]] + lg[K+i/lpf[i]]) % (mod-1);
			continue;
		}
		else if(i < 100){
			for(ll j=0, nw = i; ; j+=K2, nw = mul(nw, s)){
				int r = hs.get(nw, -1);
				if(r != -1){
					lg[K+i] = (r + j) % (mod - 1);
					break;
				}
			}
			continue;
		}
		else if(1ll * i * i > mod){
			int q = mod / i, r = mod - i * q;
			lg[K+i] = ((lg[K+r] + (mod-1) / 2 - lg[K+q]) % (mod-1) + (mod-1)) % (mod-1);
			continue;
		}	
		while (1) {
			int k = rnd() % mod;
			ll ans = mod - 1 - k;
			int x = mul(i, po(g, k));
			auto div = [&](int q) -> void { x /= q, ans += lg[K + q]; };
			for (int q : {2, 3, 5, 7, 11, 13, 17, 19}) {
				while (x % q == 0) div(q);
			}
			if (x >= K) continue;
			while (i < x && x < K && lpf[x] < i) div(lpf[x]);
			if (1 < x && x < i) div(x);
			if (x == 1) {
				lg[K + i] = ans % (mod - 1);
				break;
			}
		}
	}
	for(int i=0;i<K;i++){
		lg[i] = (lg[2 * K - i] + (mod-1) / 2) % (mod-1);
	}
}
int calc_log(int x){
	auto [c, b] = frac[x >> U];
	int a = (ll)x * b - (ll)c * mod;
	return (lg[K + a] - lg[K + b] + (mod - 1)) % (mod-1);
}
void init(){
	build_frac();
	build_inv();
	build_log();
}
// fast pow when

