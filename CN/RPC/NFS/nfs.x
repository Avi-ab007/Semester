struct param {
	char data[1000];
};

program NFS_PROG {
	version NFS_VERS {
		param readFile(param) = 1;
	} = 1;
} = 0x23451111;