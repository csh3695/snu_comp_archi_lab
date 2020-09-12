#include <iostream>

using namespace std;

int isPositive(int x) {
  return (~!x)&((x>>31)&1^1);
}

int getByte(int x, int n) {
    cout << (n<<2) << endl<<endl;
  return (x&(0xff<<(n<<1)))>>(n<<1);
}

int isAsciiDigit(int x) {
    return (((0x2F)+(~x+1))>>31&1)&(((x)+(~(0x3A)+1))>>31&1);
}

int fitsShort(int x) {
  int mask = (1<<31)>>16;
  x = x&mask;
  return (!(x^mask))|(!x);
}

int satMul2(int x) {
  int s = (x>>31);
  int m = ((x<<1)>>31);
  return ((~(s^m))&(x<<1))|(((s^m))&(~(1<<31)^s));
}

int main(){
    int x, y, n, m;
    while(true){
        cin >> x;
        printf("%4x, %4x\n", x, satMul2(x));
    }
    for(x=-10;x<70;x++){
        printf("%4x, %4x\n", x, fitsShort(x));
        //int y = x & 15;
        //y = (~(y&8)|~(y&6));;
        //cout << x << " " << (~((x>>4)^(-4))) << endl;
//        cout <<getByte(0x12345678, 1) << endl;
    }
    return 0;
}