#ifndef HIRAKIDA_IOCTL_H
#define HIRAKIDA_IOCTL_H

#include <linux/ioctl.h>

#define HIRKIDA_BUF_SIZE 256

struct hirakida_ioctl_data {
    unsigned char buf[HIRKIDA_BUF_SIZE];
};

#define HIRKIDA_IOC_TYPE 'h'

#define HIRKIDA_IOW _IOW(HIRKIDA_IOC_TYPE, 1, struct hirakida_ioctl_data)
#define HIRKIDA_IOR _IOR(HIRKIDA_IOC_TYPE, 2, struct hirakida_ioctl_data)

#endif /* HIRAKIDA_IOCTL_H */
