# java-to-kernel

```
$ sudo yum install -y kernel-devel-`uname -r`
$ sudo yum install -y gcc gcc-c++
$ sudo yum install -y java-11-openjdk java-11-openjdk-devel
```

kernel module
```
$ cd module
$ make
$ sudo insmod hirakida.ko
```

java app
```
$ ./gradlew clean build
$ sudo ./gradlew run
```
