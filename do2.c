// Credit: Louis Stuber (IBM Client Center Montpellier)
double do_things2(int i) {
    double j = i / 2;

    for (int t = 0; t < i; ++t) {
        j = (1 + j) * j / t;
    }

    return j;
}
