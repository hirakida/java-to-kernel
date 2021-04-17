#include <linux/fs.h>
#include <linux/kernel.h>
#include <linux/miscdevice.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <asm/uaccess.h>
#include "hirakida_ioctl.h"

MODULE_AUTHOR("hirakida");
MODULE_LICENSE("GPL v2");

struct hirakida_data {
    unsigned char buf[HIRKIDA_BUF_SIZE];
};

static long hirakida_ioctl(struct file *file, unsigned int cmd, unsigned long arg) {
    struct hirakida_data *p;
    struct hirakida_ioctl_data ioctl_data;

    p = file->private_data;
    memset(&ioctl_data, 0, sizeof(ioctl_data));

    printk("hirakida_ioctl\n");

    switch (cmd) {
        case HIRKIDA_IOW:
            if (copy_from_user(&ioctl_data, (void __user *)arg, sizeof(ioctl_data)) != 0) {
                return -EFAULT;
            }

            strncpy(p->buf, ioctl_data.buf, HIRKIDA_BUF_SIZE);
            break;
        case HIRKIDA_IOR:
            strncpy(ioctl_data.buf, p->buf, HIRKIDA_BUF_SIZE);

            if (copy_to_user((void __user *)arg, &ioctl_data, sizeof(ioctl_data)) != 0) {
                return -EFAULT;
            }
            break;
        default:
            printk(KERN_WARNING "unsupported command %d\n", cmd);
            return -EFAULT;
    }
    return 0;
}

static int hirakida_open(struct inode *inode, struct file *file) {
    struct hirakida_data *p;

    p = kmalloc(sizeof(struct hirakida_data), GFP_KERNEL);
    if (p == NULL) {
        printk(KERN_ERR  "kmalloc\n");
        return -ENOMEM;
    }
    memset(p, 0, sizeof(struct hirakida_data));

    file->private_data = p;

    return 0;
}

static int hirakida_close(struct inode *inode, struct file *file) {
    if (file->private_data) {
        kfree(file->private_data);
        file->private_data = NULL;
    }

    return 0;
}

static ssize_t hirakida_read(struct file *file, char __user *buf, size_t count, loff_t *f_pos) {
    struct hirakida_data *p;

    p = file->private_data;

    if (count > HIRKIDA_BUF_SIZE) {
        count = HIRKIDA_BUF_SIZE;
    }

    if (copy_to_user(buf, p->buf, count) != 0) {
        return -EFAULT;
    }

    return count;
}

static ssize_t hirakida_write(struct file *file, const char __user *buf, size_t count, loff_t *f_pos) {
    struct hirakida_data *p;

    p = file->private_data;

    if (count > HIRKIDA_BUF_SIZE) {
        count = HIRKIDA_BUF_SIZE;
    }

    if (copy_from_user(p->buf, buf, count) != 0) {
        return -EFAULT;
    }

    return count;
}

static struct file_operations hirakida_fops = {
        .open    = hirakida_open,
        .release = hirakida_close,
        .read    = hirakida_read,
        .write   = hirakida_write,
        .unlocked_ioctl = hirakida_ioctl,
        .compat_ioctl   = hirakida_ioctl,
};

static struct miscdevice hirakida_dev = {
        .minor = MISC_DYNAMIC_MINOR,
        .name  = "hirakida",
        .fops  = &hirakida_fops,
};

static int hirakida_init(void) {
    int ret;
    printk("hirakida_init\n");

    ret = misc_register(&hirakida_dev);
    if (ret != 0) {
        printk(KERN_ERR "misc_register = %d\n", ret);
        return -1;
    }

    return 0;
}

static void hirakida_exit(void) {
    printk("hirakida_exit\n");
    misc_deregister(&hirakida_dev);
}

module_init(hirakida_init);
module_exit(hirakida_exit);
