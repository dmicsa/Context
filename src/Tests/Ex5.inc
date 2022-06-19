Context c;

DIM_AUTO_VARIABLE_HOLDER(I, c, "I", 10);
cout << extract<I>(c, "I", DIM_WHERE) << '\n';
{
	I i{20};
	DIM_AUTO_SWAP_KEY(i, c["I"].first);
	cout << extract<I>(c, "I", DIM_WHERE) << '\n';
}
cout << extract<I>(c, "I", DIM_WHERE) << '\n';