ll mod_pow(ll base, ll exponent, int mod = MOD) {
    assert(mod > 0 && exponent >= 0);
    base = (base % mod + mod) % mod;
    ll answer = 1 % mod;
    while (exponent) {
        if (exponent & 1) answer = answer * base % mod;
        base = base * base % mod;
        exponent >>= 1;
    }
    return answer;
}