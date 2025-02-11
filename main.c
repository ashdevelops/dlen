#include <linux/module.h>

unsigned long original_cr0;

asmlinkage long (*ref_sys_read)(unsigned int fd, char __user *buf, size_t count);

static unsigned long **aquire_sys_call_table(void)
{
	unsigned long int offset = PAGE_OFFSET;
	unsigned long **sct;
    
	printk("Starting syscall table scan from: %lx\n", offset);
	while (offset < ULLONG_MAX) {
		sct = (unsigned long **)offset;
		if (sct[__NR_close] == (unsigned long *) sys_close) {
			printk("Syscall table found at: %lx\n", offset);
			return sct;
		}

		offset += sizeof(void *);
	}
    
	return NULL;
}

asmlinkage long new_sys_read(unsigned int fd, char __user *buf, size_t count)
{
    long ret;
    ret = ref_sys_read(fd, buf, count);
	
    if (fd > 2) {
        if (strcmp(current->comm, "cc1") == 0 || 
            strcmp(current->comm, "python") == 0) {
            char *substring = strstr(buf, "World!");
            if (substring != NULL) {
                substring[0] = 'M';
                substring[1] = 'r';
                substring[2] = 'r';
                substring[3] = 'r';
                substring[4] = 'g';
                substring[5] = 'n';
            }
        }
    }
    return ret;
}


MODULE_LICENSE("GPL");