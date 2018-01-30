struct numbers{
	int a;
	int b;
};
program rpc_prog{
	version rpc_add{
		int add(numbers)=1;
	}=1;
}=0x23451111;
