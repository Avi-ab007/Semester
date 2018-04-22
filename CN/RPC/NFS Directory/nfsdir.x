struct input {
	char data[1000];
};

struct output {
	char data[1000];
};

program NFSDIR_PROG {
	version DIR_VERS {
		output lsdir(input) = 1;
	} = 1;
} = 0x23451111;