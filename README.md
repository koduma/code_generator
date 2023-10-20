# code_generator
# c言語のプログラムを書くc++プログラムです
## g++ -O2 -std=c++11 make_c.cpp -o make_c

# コード生成例

#### #include <stdio.h>
#### int main(){
#### int max = 0, a;
#### for (int i = 0; i < 2; i++) {
#### scanf("%d", &a);
#### if (a > max) max = a;
#### }
#### printf("%d\n", max);
#### return 0;
#### }
#### int max(int a, int b) {
  #### if (a >= b)
  #### return a;
  #### else
  #### return b;
#### }
