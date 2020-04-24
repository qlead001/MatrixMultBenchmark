void benchmark1(double A[], double B[], double C[], int n) {
    int i, j, k;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            for (k = 0; k < n; k++) {
                C[i*n+j]+=A[i*n+k]+B[k*n+j];
            }
        }
    }
}

void benchmark2(double A[], double B[], double C[], int n) {
    int i, j, k;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            register double t = C[i*n+j];
            for (k = 0; k < n; k++) {
                t+=A[i*n+k]+B[k*n+j];
            }
            C[i*n+j] = t;
        }
    }
}

void benchmark3(double A[], double B[], double C[], int n) {
    int i, j, k;
    for (i = 0; i < n; i+=2) {
        for (j = 0; j < n; j+=2) {
            register double c1 = C[i*n+j], c2 = C[(i+1)*n+j],
                            c3 = C[i*n+(j+1)], c4 = C[(i+1)*n+(j+1)];
            for (k = 0; k < n; k+=2) {
                register double a1 = A[i*n+k], a2 = A[(i+1)*n+k],
                                a3 = A[i*n+(k+1)], a4 = A[(i+1)*n+(k+1)],
                                b1 = B[k*n+j], b2 = B[(k+1)*n+j],
                                b3 = B[k*n+(j+1)], b4 = B[(k+1)*n+(j+1)];
                c1 += a1*b1 + a3*b2; c2 += a2*b1 + a4*b2;
                c3 += a1*b3 + a2*b4; c4 += a2*b3 + a4*b4;
            }
            C[i*n+j] = c1; C[(i+1)*n+j] = c2;
            C[i*n+(j+1)] = c3; C[(i+1)*n+(j+1)] = c4;
        }
    }
}
