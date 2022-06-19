Context c;
cout << "----------------\n";
{ // using manual names for VariableHolder
	VariableHolder<I> vh1(c, "I1", 10, DIM_WHERE);
	VariableHolder<I> vh2(c, "I2", 15, DIM_WHERE);
	cout << "Checkpoint: A";
	print(c);
	cout << extract<I>(c, "I1", DIM_WHERE) << '\n';
	cout << extract<I>(c, "I2", DIM_WHERE) << '\n';
}
cout << "Checkpoint: B";
print(c);

cout << "----------------\n";
{ // using automatic names.VariableHolder
	DIM_AUTO_VARIABLE_HOLDER(I, c, "I1", 20);
	DIM_AUTO_VARIABLE_HOLDER(I, c, "I2", 25);
	cout << "Checkpoint: C";
	print(c);
	cout << extract<I>(c, "I1", DIM_WHERE) << '\n';
	cout << extract<I>(c, "I2", DIM_WHERE) << '\n';
}
cout << "Checkpoint: D";
print(c);

cout << "----------------\n";
{ // using automatic names.VariableHolder
	DIM_AUTO_VARIABLE_HOLDER(I, c, "I1", 20);
	DIM_AUTO_VARIABLE_HOLDER(I, c, "I2", 25);
	cout << "Checkpoint: E";
	print(c);
	cout << extract<I>(c, "I1", DIM_WHERE) << '\n';
	cout << extract<I>(c, "I2", DIM_WHERE) << '\n';

	cout << "Assign them to new values.\n";
	extract<I>(c, "I1", DIM_WHERE) = 21;
	extract<I>(c, "I2", DIM_WHERE) = 26;
	cout << "Checkpoint: F";
	print(c);
	cout << extract<I>(c, "I1", DIM_WHERE) << '\n';
	cout << extract<I>(c, "I2", DIM_WHERE) << '\n';
}
cout << "Checkpoint: G";
print(c);

cout << "----------------\n";
cout << "Checkpoint: H";
cout << extract<I>(c, "I2", DIM_WHERE) << '\n'; // Throws!