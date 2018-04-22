struct data {
	int size;
	int array[100];
};

program ARRAY_SUM {
	version SUM_VERS {
		int arr_sum(data) = 1;
	} = 1;
} = 0x23451111;