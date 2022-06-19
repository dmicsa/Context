Context c;
I n{10};
c["Int"] = makePair(n);
R r{10.12};
c["Real64"] = makePair(r);
S s{"Cucu"};
c["String"] = makePair(s);

cout << extract<I>(c, "Int", DIM_WHERE) << '\n';
cout << extract<R>(c, "Real64", DIM_WHERE) << '\n';
cout << extract<S>(c, "String", DIM_WHERE) << '\n';
cout << extract<R>(c, "String", DIM_WHERE) << '\n'; // Wrong type!
