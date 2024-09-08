const double pi=acos(-1);
typedef complex<double> cp;
const int N=(1<<17);
struct FFT
{
  // n has to be same as a.size()
  int n,rev[N];
  cp omega[N],iomega[N];
  void init(int _n) {
    n=_n;
    for(int i=0;i<n;i++) {
      omega[i]=cp(cos(2*pi/n*i),sin(2*pi/n*i));
      iomega[i]=conj(omega[i]);
    }
    int k=log2(n);
    for(int i=0;i<n;i++) {
      rev[i]=0;
      for(int j=0;j<k;j++) if(i&(1<<j))
        rev[i]|=(1<<(k-j-1));
    }
  }
  void tran(vector<cp> &a,cp* xomega)
  {
    for(int i=0;i<n;i++) if(i<rev[i])
      swap(a[i],a[rev[i]]);
    for(int len=2;len<=n;len<<=1) {
      int mid=len>>1,r=n/len;
      for(int j=0;j<n;j+=len) {
        for(int i=0;i<mid;i++) {
          cp t=xomega[r*i]*a[j+mid+i];
          a[j+mid+i]=a[j+i]-t;
          a[j+i]+=t;
        }
      }
    }
  }
  void fft(vector<cp> &a) {tran(a,omega);}
  void ifft(vector<cp> &a) {
      tran(a,iomega);
      for(int i=0;i<n;i++) a[i]/=n;
  }
};

