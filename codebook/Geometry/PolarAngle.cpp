int cmp(pdd a,pdd b,bool same=1){ //polar angle sort
  #define is_neg(k) (sign(k.Y)<0||(sign(k.Y)==0&&sign(k.X)<0))
  int A=is_neg(a),B=is_neg(b);
  if(A!=B) return A<B;
  if(sign(a^b)==0) return (same?abs2(a)<abs2(b):-1);
  return sign(a^b)>0;
}
