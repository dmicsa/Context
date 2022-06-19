Context c;
I n{10};
c["I"] = makePair(n);
R r{-22.212};
c["R"] = makePair(r);
S s{"Cucu"};
c["S"] = makePair(s);

print(c);
cout << extract<I>(c, "I", DIM_WHERE) << '\n';
cout << extract<R>(c, "R", DIM_WHERE) << '\n';
cout << extract<S>(c, "S", DIM_WHERE) << '\n';