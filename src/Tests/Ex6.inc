struct OStream
{
	virtual V print(const SV) = 0;
	virtual ~OStream() {}
};
struct OStream1 : public OStream
{
	virtual V print(const SV v) override { cout << "S1: " << v; }
};
struct OStream2 : public OStream
{
	virtual V print(const SV v) override { cout << "S2: " << v; }
};

Context c;

OStream1 os1;
DIM_AUTO_VARIABLE_HOLDER(OStream &, c, "os", os1);
extract<OStream>(c, "os", DIM_WHERE).print("CUCU!\n");
{
	OStream2 os2;
	// DIM_AUTO_SWAP_KEY(os2, c["os"].first);//is not working yet and I will appreciate help wit it!
	c["os"].first = &os2;
	extract<OStream>(c, "os", DIM_WHERE).print("CUCU!\n");
	c["os"].first = &os1;
}
extract<OStream>(c, "os", DIM_WHERE).print("CUCU!\n");