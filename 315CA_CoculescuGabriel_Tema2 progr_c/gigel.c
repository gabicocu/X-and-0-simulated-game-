// Copyright 2018 Coculescu Gabriel(gabrielcoculescu@yahoo.ro)
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
// functie pentru verificare daca indicii sunt valizi
int validarepoz(int n, int x, int y) {
    if (x < 0 || x > n || y < 0 || y > n) {
            return 0;
    } else {
        return 1;
    }
}

void miniboard(char a[][100], char b[10][10], int n, int x, int y, int *k) {
    int l, c, i, j, m, li, ci, lf, cf, ok = 1, ok1 = 1;
    char ch;
    ch = a[x][y];
    m = sqrt(n + 1);// m=nr de linii si de coloane din macroboard
    l = x / m; // l si c reprezinta linia si coloana asociata miniboardului
    c = y / m; // unde se afla elementul de coordonate x si y
    if (b[l][c] != '-') {
            ok = 0;
    } // verificam daca miniboardul nu era deja castigat anterior
    if (ok) { // daca nu era castigat deja
        li = l * m; // li si ci reprezinta linia de inceput,respectiv coloana
        ci = c * m; // de inceput a miniboardului de unde face parte a[x][y]
        lf = li + m - 1; // lf si cf linia de sfarsit si coloana de sfarsit
        cf = ci + m - 1;
        // ok1 = 1 presupun ca miniboardul se castiga pe linie
        for (j = ci; j <= cf; j++) {
            if (a[x][j] != ch) {
                ok1 = 0;
            }
        } // parcurgerea liniei,daca nu e facuta de un jucator atunci ok1 = 0
        if (ok1) {
                b[l][c] = ch;
                *k = 1;
            }
        // daca linia este facuta atunci se adauga jucatorul pe pozitia b[l][c]
            ok1 = 1;  // ok1 = 1 presupun ca miniboardul se castiga pe coloana
        for (i = li; i <= lf; i++) {
            if (a[i][y] != ch) {
                ok1 = 0;
            }
        } // parcurgerea coloanei,daca nu e facuta de un jucator atunci ok1 = 0
        if (ok1) {
                b[l][c] = ch;
                *k = 1;
        }
        // daca se face coloana atunci se adauga jucatorul pe pozitia b[l][c]
        ok1 = 1; // ok1 = 1 presupun ca miniboardul se castiga pe diag princ
        i = li;
        j = ci;
        while (i <= lf && j <= cf) {
            if (a[i][j] != ch) {
                ok1 = 0;
            }
            i++;
            j++;
        } // parcurgerea diag,daca nu e facuta de un jucator atunci ok1 = 0
        if (ok1) {
                b[l][c] = ch;
                *k = 1;
        }
        // daca se face diag atunci se adauga jucatorul pe pozitia b[l][c]
        ok1 = 1; // ok1 = 1 presupun ca miniboardul se castiga pe diag sec
        while (li <= lf && cf >= ci) {
            if (a[li][cf] != ch) {
                ok1 = 0;
            }
            li++;
            cf--;
        } // parcurgerea diag,daca nu e facuta de un jucator atunci ok1 = 0
        if (ok1) {
                b[l][c] = ch;
                *k = 1;
        }
         // daca se face diag atunci se adauga jucatorul pe pozitia b[l][c]
    }
}

// functie de adaugare
void adaug(char a[100][100], int n, int *x, int *y, char ch, int *ok) {
    int i, l2, c2, l1, c1;
    // ok este initial 1 daca se poate adauga devine 0
    for (i = 0; i <= n; i++) { // parcurgerea diagonalelor
        if (*ok == 0) {
            break; // daca s-a adaugat un element se opreste cautarea
        }
        l1 = 0; c1 = i;
// linia si coloana de inceput a diagonalei deasupra celei principale din board
        l2 = i; c2 = 0;
// linia si coloana de inceput a diagonalei de sub cea principala din board
        while (l1 <= n && c1 <= n && *ok == 1) {
            if (a[l1][c1] == '1') {
                a[l1][c1] = ch; // se adauga elem
                *x = l1; * y = c1; // se schimba indicii
                *ok = 0;
            }
            l1++; c1++;
        }  // se parcurge diag de deasupra
        while (l2 <= n && c2 <= n && *ok == 1) {
            if (a[l2][c2] == '1') {
                a[l2][c2] = ch; // se adauga elem
                *x = l2; *y = c2; // se schimba indicii
                *ok = 0;
            }
            l2++; c2++;
        } // se parcurge diag de dedesubt
    }
}

// functia umplere construieste a si b si nuamara muatarile inteligente
void umplere(char a[][100], char b[10][10], int n, int m, int *n1, int *n2) {
    int i, x, y;
    char ch, ch1 = 'z'; // ch1 reprezinta caracterul citit anterior
    int ok, ok1, ok2, k;
    for (i = 0; i < m; i++) {
    scanf(" %c", &ch); // se citeste caracterul
    scanf("%d", &x);
    scanf("%d", &y); // se citeste pozitia acestuia
    ok = 1; // ok verifica daca se respecta ordinea
    if (i == 0 && ch == '0') {
        printf("NOT YOUR TURN\n");
        ok = 0;
    } // daca primul caracter citit este 0
    if (ch == ch1) {
        printf("NOT YOUR TURN\n");
        ok = 0;
    } // daca nu se respecta ordinea
    if (ok) {
            ok2 = 0; // ok2 arata daca indicii sunt valizi
        if (validarepoz(n, x, y) == 0) {
            printf("INVALID INDEX\n");
            ok2 = 1; // daca indicii sunt invalizi atunci ok2 = 1
        }
         if (validarepoz(n, x, y)) {
            if (a[x][y] == '1') { // daca celula este libera
                a[x][y] = ch; // se adauga caracterul in boardul a
                k = 0; // k verifica daca mutarea este inteligenta
                miniboard(a, b, n, x, y, &k);
                // verificam daca mutarea duce la castigarea miniboardului
                if (k) {
                    if (ch == 'X') {
                        (*n1)++; // n1 numarul de mutari inteligente ale lui X
                    } else {
                        (*n2)++; // n2 numarul de mutari inteligente ale lui 0
                    }
                }
            } else { // daca celula nu este libera
                printf("NOT AN EMPTY CELL\n");
                ok2 = 1;
            }
         }
         if (ok2) { // daca caracterul trebuie adaugat automat
                ok1 = 1; // presupunem ca boardul e plin
                adaug(a, n, &x, &y, ch, &ok1);
                if (ok1) {
                    printf("FULL BOARD\n");
                    break;
                } else {
                    miniboard(a, b, n, x, y, &k);
                    // verificam daca mutarea duce la castigarea miniboardului
                }
            }
        }
        ch1 = ch; // se retine caracterul pentru verificarea ordinii
    }
    }

// functie pentru determinarea castigatorului jocului
void macroboard(char b[10][10], int n, int *nr1, int *nr2) {
    int i, j, ok0, okx;
// ok0 verifica daca castigatorul este 0 si okx daca castigatorul este X
    for (i = 0; i < n; i++) { // parcurgerea linilor
        ok0 = 1; okx = 1; // presupunem ca sunt castigatori
        for (j = 0; j < n; j++) {
            if (b[i][j] != '0') {
                ok0 = 0; // daca linia nu este full de 0
            } // verificarea liniei pt 0
            if (b[i][j] != 'X') {
                okx = 0; // daca linia nu este full de X
            } // verificarea liniei pt 0
        }
        if (ok0) {
            (*nr1)++; // numara de cate ori 0 castiga macroboardul
        }
         if (okx) {
            (*nr2)++; // numara de cate ori X castiga macroboardul
        }
    }
    for (j = 0; j < n; j++) { // parcurgerea coloanei, la fel ca la linii
        ok0 = 1; okx = 1;
        for (i = 0; i < n; i++) {
            if (b[i][j] != '0') {
                ok0 = 0;
            }
            if (b[i][j] != 'X') {
                okx = 0;
            }
        }
        if (ok0) {
            (*nr1)++;
        }
         if (okx) {
            (*nr2)++;
        }
    }
    ok0 = 1; okx = 1;
    i = 0; j = 0; // parcurgerea diagonalei principale
    while (i < n && j < n) {
        if (b[i][j] != '0') {
            ok0 = 0;
        }
        if (b[i][j] != 'X') {
            okx = 0;
        }
        i++;
        j++;
    }
    if (ok0) {
        (*nr1)++;
    }
    if (okx) {
        (*nr2)++;
    }
    ok0 = 1; okx = 1;
    i = 0; j = n-1; // parcurgerea diagonalei secundare
    while (i < n && j >= 0) {
        if (b[i][j] != '0') {
            ok0 = 0;
        }
        if (b[i][j] != 'X') {
            okx = 0;
        }
        i++;
        j--;
    }
    if (ok0) {
        (*nr1)++;
    }
    if (okx) {
        (*nr2)++;
    }
}

int main() {
    char a[100][100]; // a este boardul
    char b[10][10]; // b este macroboardul
    int i, j, m, n, nn, nr1 = 0, nr2 = 0;
    int nrx = 0, nrxc = 0, nro = 0, nroc = 0;
    double rx, ro;
    scanf("%d", &n);
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            b[i][j] = '-';
        }
    } // umplu macroboardul cu caracterul -
    nn = n * n - 1; // linia si coloana boardului
    scanf("%d", &m);
    for (i = 0; i <= nn; i++) {
        for (j = 0; j <= nn; j++) {
            a[i][j] = '1';
        }
    } // umplu boardul cu caracterul 1
    umplere(a, b, nn, m, &nrxc, &nroc);
    // valid umple boardul si miniboardul (apeleaza functia miniboard)
    // si numara mutarile care au dus la castigarea miniboardului
    /*for (i = 0; i <= nn; i++) {
        for (j = 0; j <= nn; j++) {
            printf("%c ",a[i][j]);
        }
        printf("\n");
    }
    printf("%d %d\n",nrxc,nroc);
    */
    for (i = 0; i < n; i++) {
        for (j = 0; j <  n; j++) {
            printf("%c", b[i][j]);
        }
        printf("\n");
    } // afiseaza macrobordul
    macroboard(b, n, &nr1, &nr2); // verifica rezultatul jocului
    if (nr1 != nr2) {
        if (nr1 > nr2) {
            printf("0 won\n");
        } else {
            printf("X won\n");
        }
    } else {
        printf("Draw again! Let's play darts!\n");
    }
    for (i = 0; i <= nn; i++) {
        for (j = 0; j <= nn; j++) {
            if (a[i][j] == '0') {
                nro++; // nro numara nr de 0 din board
            }
            if (a[i][j] == 'X') {
                nrx++; // nrx numara nr de X din board
            }
        }
    }
  //  printf("%d %d\n",nro,nrx);
    rx = (double)nrxc / nrx; // coeficientii de atentie
    ro = (double)nroc / nro;
    if (nrx == 0) {
        printf("X N/A\n");
    } else {
        printf("X %.10lf\n", rx);
    }
    if (nro == 0) {
        printf("0 N/A\n");
    } else {
        printf("0 %.10lf\n", ro);
    }
    return 0;
}
