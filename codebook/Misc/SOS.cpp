//memory optimized, super easy to code.
rep(i, (1 << N)) F[i] = A[i];
rep(i, N) rep(mask, (1 << N)) {
  if(mask & (1<<i)) F[mask] += F[mask^(1<<i)];
}
