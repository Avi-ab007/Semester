struct numbers {
	int a;
	int b;
};

program ADD_PROG {
	version ADD_VERS_1 {
		int add(numbers) = 1;
	} = 1;

	version ADD_VERS_2 {
		int add(numbers) = 1;
	} = 2;
} = 0x23451111;
