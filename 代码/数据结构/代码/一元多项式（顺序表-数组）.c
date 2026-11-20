#include <stdio.h>
#include <math.h>

#define MAX 100

typedef struct Term{
    double coef;
    int exp;
} Term;

typedef struct Poly{
    Term t[MAX];
    int len;
} Poly;

void init(Poly *p) { p->len = 0; }

void addTerm(Poly *p, double coef, int exp) {
    if (p->len < MAX) {
        p->t[p->len].coef = coef;
        p->t[p->len].exp  = exp;
        p->len++;
    }
}

//打印函数 
void print(Poly p) {
    if (p.len == 0) { printf("0\n"); return; }

    int first = 1;
    for (int i = 0; i < p.len; i++) {
        double c = p.t[i].coef;
        int e = p.t[i].exp;

        if (!first && c > 0) printf(" + ");
        else if (c < 0)      printf(" - ");

        double ac = fabs(c);
        if (ac != 1.0 || e == 0) printf("%g", ac);

        if (e > 0) {
            printf("x");
            if (e > 1) printf("^%d", e);
        }
        first = 0;
    }
    printf("\n");
}

//函数求和 
Poly add(Poly A, Poly B) {
    Poly res; init(&res);
    int i = 0, j = 0;

    while (i < A.len || j < B.len) {
        double c = 0;
        int e = 0;

        if (i < A.len && j < B.len) {
            if (A.t[i].exp == B.t[j].exp) {
                c = A.t[i].coef + B.t[j].coef; e = A.t[i].exp;
                i++; j++;
            } else if (A.t[i].exp < B.t[j].exp) {
                c = A.t[i].coef; e = A.t[i].exp; i++;
            } else {
                c = B.t[j].coef; e = B.t[j].exp; j++;
            }
        } else if (i < A.len) {
            c = A.t[i].coef; e = A.t[i].exp; i++;
        } else {
            c = B.t[j].coef; e = B.t[j].exp; j++;
        }

        if (fabs(c) > 1e-6) addTerm(&res, c, e);
    }
    return res;
}

//函数做差 
Poly sub(Poly A, Poly B) {
    Poly negB; init(&negB);
    for (int i = 0; i < B.len; i++)
        addTerm(&negB, -B.t[i].coef, B.t[i].exp);
    return add(A, negB);
}

//函数求值 
double eval(Poly p, double x) {
    double sum = 0;
    for (int i = 0; i < p.len; i++)
        sum += p.t[i].coef *pow(x, p.t[i].exp);
    return sum;
}

int main() {
    Poly F; init(&F);
    addTerm(&F, 1, 0);
    addTerm(&F, 2, 1);
    addTerm(&F, 1, 2);
    printf("F(x) = "); print(F);

    Poly G; init(&G);
    addTerm(&G, -2, 1);
    printf("G(x) = "); print(G);

    Poly S = add(F, G);
    printf("两函数取和F(x) + G(x) = "); print(S);

    Poly D = sub(F, G);
    printf("两函数做差F(x) - G(x) = "); print(D);

    double x = 1.0;
    printf("函数取值x = %g, F(x) = %g\n", x, eval(F, x));

    return 0;
}
