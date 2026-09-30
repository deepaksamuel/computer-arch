int main(int n) {
    int s = 0;
    for (int i = 0; i < n; i++) {
        int k = 2 * 3;        // constant expression
        s += i * i + k - 6;   // k - 6 is always 0
    }
    return s;
}