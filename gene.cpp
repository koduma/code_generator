#include <stdio.h>
int main(){
        int max = 0, a;
        for (int i = 0; i < 2; i++) {
                scanf("%d", &a);
                if (a > max) max = a;
        }
        printf("%d\n", max);
        return 0;

}
int max(int a, int b) {
  if (a >= b)
    return a;
  else
    return b;
}
