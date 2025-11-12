// in PAM
/* node */ int dif = 0, slink = 0, g = 0;
vector<int> dp = {0};
// add
if (!st[cur].nxt[c]) {
  // ...
  st[now].dif = st[now].len - st[st[now].fail].len;
  if (st[now].dif == st[st[now].fail].dif)
    st[now].slink = st[st[now].fail].slink;
  else st[now].slink = st[now].fail;
}
dp.pb(0);
for (int x = last; x > 1; x = st[x].slink) {
  st[x].g = dp[n - st[st[x].slink].len - st[x].dif];
  if (st[x].dif == st[st[x].fail].dif)
    st[x].g = min(st[x].g, st[st[x].fail].g);
  dp[n] = min(dp[n], st[x].g + 1);
}
