//dp
#include <stdio.h>
#define E (1e-4)
int main(){
    int a, c;
    scanf("%d %d", &a, &c);
    double t = c / 60.0;
    t *= 10;
    t += 0.5;
    int q = (int)t;
    double b = q / 10.0;
    if (b <= 0.2 + E) {
        printf("C 0\n");
        return 0;
    }
    if (a > 1687 && a <= 1912) printf("S");
    else if (a > 112 && a <= 337) printf("NNE");
    else if (a > 1912 && a <= 2137) printf("SSW");
    else if (a > 337 && a <= 562) printf("NE");
    else if (a > 2137 && a <= 2362) printf("SW");
    else if (a > 562 && a <= 787) printf("ENE");
    else if (a > 2362 && a <= 2587) printf("WSW");
    else if (a > 787 && a <= 1012) printf("E");
    else if (a > 2587 && a <= 2812) printf("W");
    else if (a > 1012 && a <= 1237) printf("ESE");
    else if (a > 2812 && a <= 3037) printf("WNW");
    else if (a > 1237 && a <= 1462) printf("SE");
    else if (a > 3037 && a <= 3262) printf("NW");
    else if (a > 1462 && a <= 1687) printf("SSE");
    else if (a > 3262 && a <= 3487) printf("NNW");
    else printf("N");
    printf(" ");
    if (b >= 8 - E && b <= 10.7 + E) printf("5");
    else if (b >= 24.5 - E && b <= 28.4 + E) printf("10");
    else if (b >= 0.3 - E && b <= 1.5 + E) printf("1");
    else if (b >= 10.8 - E && b <= 13.8 + E) printf("6");
    else if (b >= 28.5 - E && b <= 32.6 + E) printf("11");
    else if (b >= 1.6 - E && b <= 3.3 + E) printf("2");
    else if (b >= 13.9 - E && b <= 17.1 + E) printf("7");
    else if (b >= 3.4 - E && b <= 5.4 + E) printf("3");
    else if (b >= 17.2 - E && b <= 20.7 + E) printf("8");
    else if (b >= 5.5 - E && b <= 7.9 + E) printf("4");
    else if (b >= 20.8 - E && b <= 24.4 + E) printf("9");
    else printf("12");
    printf("\n");
    return 0;
}
int max(int a, int b) {
  if (a >= b)
    return a;
  else
    return b;
}
