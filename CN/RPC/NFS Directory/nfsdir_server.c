/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include "nfsdir.h"
#include <dirent.h>

output *
lsdir_1_svc(input *argp, struct svc_req *rqstp)
{
	static output  result;

	struct dirent** namelist; 
	int n = scandir(argp->data, &namelist, NULL, alphasort);
	strcpy(result.data, namelist[n-1]->d_name);
	strcat(result.data, "\n");
	n--;
	while (n--) {
		strcat(result.data, namelist[n]->d_name);
		strcat(result.data, "\n");
	}

	return &result;
}
