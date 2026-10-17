#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// ================= 数据结构 =================
typedef struct Node {
    double coef;   // 系数
    int exp;       // 指数
    struct Node *next;
} Node, *Poly;

// 初始化（带头结点）
Poly init() {
    Poly head = (Poly)malloc(sizeof(Node));
    head->next = NULL;
    return head;
}

// 追加一项
void addTerm(Poly p, double coef, int exp) {
    Node *cur = p;
    while (cur->next) cur = cur->next;
    Node *node = (Node*)malloc(sizeof(Node));
    node->coef = coef;
    node->exp  = exp;
    node->next = NULL;
    cur->next  = node;
}

// 打印
void print(Poly p) {
    Node *cur = p->next;
    if (!cur) { printf("0\n"); return; }

    int first = 1;
    while (cur) {
        double c = cur->coef;
        int e = cur->exp;

        if (!first && c > 0) printf(" + ");
        else if (c < 0)      printf(" - ");

        double ac = fabs(c);
        if (ac != 1.0 || e == 0) printf("%g", ac);

        if (e > 0) {
            printf("x");
            if (e > 1) printf("^%d", e);
        }
        first = 0;
        cur = cur->next;
    }
    printf("\n");
}

// 加法：res = A + B
Poly add(Poly A, Poly B) {
    Poly res = init();
    Node *a = A->next, *b = B->next, *t = res;

    while (a || b) {
        double c = 0;
        int e = 0;

        if (a && b) {
            if (a->exp == b->exp) {
                c = a->coef + b->coef; e = a->exp;
                a = a->next; b = b->next;
            } else if (a->exp < b->exp) {
                c = a->coef; e = a->exp; a = a->next;
            } else {
                c = b->coef; e = b->exp; b = b->next;
            }
        } else if (a) {
            c = a->coef; e = a->exp; a = a->next;
        } else {
            c = b->coef; e = b->exp; b = b->next;
        }

        if (fabs(c) > 1e-6) {
            Node *node = (Node*)malloc(sizeof(Node));
            node->coef = c; node->exp = e; node->next = NULL;
            t->next = node; t = node;
        }
    }
    return res;
}

// 减法：res = A - B
Poly sub(Poly A, Poly B) {
    Poly negB = init();
    for (Node *b = B->next; b; b = b->next)
        addTerm(negB, -b->coef, b->exp);
    Poly res = add(A, negB);
    free(negB);
    return res;
}

// 求值 F(x)
double eval(Poly p, double x) {
    double sum = 0;
    for (Node *cur = p->next; cur; cur = cur->next)
        sum += cur->coef * pow(x, cur->exp);
    return sum;
}

// 清空 
void destroy(Poly p) {
    while (p) {
        Node *t = p;
        p = p->next;
        free(t);
    }
}

int main() {
    Poly F = init();
    addTerm(F, 1, 0);
    addTerm(F, 2, 1);
    addTerm(F, 1, 2);
    printf("F(x) = "); print(F);

    Poly G = init();
    addTerm(G, -2, 1);
    printf("G(x) = "); print(G);

    Poly S = add(F, G);
    printf("F(x) + G(x) = "); print(S);

    Poly D = sub(F, G);
    printf("F(x) - G(x) = "); print(D);

    double x = 1.0;
    printf("x = %g, F(x) = %g\n", x, eval(F, x));

    destroy(F); destroy(G); destroy(S); destroy(D);
    return 0;
}
