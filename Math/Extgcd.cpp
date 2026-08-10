// ax+ny = 1, ax+ny == ax == 1 (mod n)
void extgcd(ll x, ll y, ll &g, ll &a, ll &b) {
	if (y == 0) g = x, a = 1, b = 0;
	else extgcd(y, x % y, g, b, a), b -= (x / y) * a;
}
