Context c;

I n{10};
c["i"] = makePair(n);
R r{10.12};
c["r"] = makePair(r);
S s{"Cucu"};
c["s"] = makePair(s);

cout << extract<I>(c, "i", DIM_WHERE) << '\n';
cout << extract<R>(c, "r", DIM_WHERE) << '\n';
cout << extract<S>(c, "s", DIM_WHERE) << '\n';
cout << extract<R>(c, "s", DIM_WHERE) << '\n'; // Wrong type!
