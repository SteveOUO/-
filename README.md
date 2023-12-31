# 复现Green ORAM论文源代码

这个文件是体系结构作业大作业——复现论文的Readme

原论文名称：Exploiting Data Locality in Memory for ORAM to Reduce

原论文介绍：

Green ORAM is a locality-aware ORAM primitive that exploits space locality of data in the physical memory for improving Path ORAM to obtain better performance while maintaining security. We implement the simulation of Green ORAM by revising the USIMM simulator.

USIMM is the Utah SImulated Memory Module, a cycle-accurate memory system simulator follows JEDEC DDR3-1600 specification. The USIMM simulator can be download in [this page](http://utaharch.blogspot.com/2012/02/usimm.html). We use the newest 1.3 version and mainly modify the `main.c` and `scheduler.c` in the `src` folder to implement Green ORAM. We provide two kinds of stash: single-path-stash and multi-path-stash in our implement.



## Environment

- Linux version 5.4.0-70-generic (buildd@lgw01-amd64-039)
- gcc version 7.5.0
- Ubuntu 7.5.0-3ubuntu1~20.04



## Dataset

在复现过程中我使用了作者使用的数据集以及对数据集进行指令访问地址局部性加强化（Local版本）以及将指令访问地址完全随机化（Random版本）的数据集，可以在下面网址下载所用数据集

We select the dataset used in 2012 memory scheduling championship (MSC). Each workload contains 500 million representative instructions selected from the PARSEC and commercial benchmark with a methodology similar to Simpoint. The whole dataset can be downloaded in [this page](https://www.cs.utah.edu/~rajeev/jwac12/results_table.html).



## Preprocess

当把所需要的原始数据集下载到`input`文件夹后，若只使用原始版本的数据集可以直接跳过这一步，如果要复现Local版本数据集以及Random版本数据集请继续下面流程：

1. 将要使用的的数据集存放到`input`文件夹中

2. 修改`transLocal.cpp`和`transRandom.cpp`中的workload数组,将数据集中相应的workload名字加上(如果使用的是2012 memory scheduling championship (MSC)Dataset，可以跳过这一步)

```cpp
// 创建一个包含文件名的数组
vector<string> filenames = {"black", "face", "ferret", "fluid", "freq", "stream", "swapt", "comm1", "comm2", "comm3", "comm4", "comm5"};
```


Then run the code as follow:

```sh
$ cd -/input
// 转换成Local版本
$ g++ transLocal.cpp -o transLocal
$ ./transLocal
// 转换成Random版本
$ g++ transRandom.cpp -o transRandom
$ ./transRandom
```

运行完代码后对应的数据集（work_load + _Local/_Random）会保存在`input`文件夹当中

## Set Green ORAM mode

代码中提供了两个函数 `get_read_num_oram_single()` 用于常见的1路径隐蔽存储器（1-path-stash）和 `get_read_num_oram_multi()` 用于3路径隐蔽存储器（3-path-stash）。这两个函数也是与ORAM（Oblivious RAM，隐蔽随机存取存储器）相关功能的入口。

代码中默认使用的是3-path-stash `get_read_num_oram_multi()`，如果无须修改可直接跳过这一步

We provide function `get_read_num_oram_single()` for common 1-path-stash and `get_read_num_oram_multi()` for 3-path-stash. These two functions are also the entrance of the ORAM relative functions.



As default, we use the 3-path-stash and call `get_read_num_oram_multi()` in `main()`. You can call  `get_read_num_oram_single()` for common stash. You can also comment out this line for the basic simulation without ORAM.



## Set simulation instructions

The simulations instructions are set in file `run_GreenORAM`. In each instruction, you need to appoint the memory channel size, the input file and the output file. You can write an instruction as follow:

```sh
bin/usimm input/1channel.cfg input/black > output/black_GreenORAM
```

在复现代码中我已经编写了相应使用所有的workload进行测试的代码，分别是`run_GreenORAM`使用原数据集、`run_GreenORAM_LOCAL`使用Local版本数据集以及`run_GreenORAM_RANDOM`使用Random版本数据集，可以跳过这一步直接执行最后一步



## Make and run

After the preparations above, you can compile the project and run the simulation with the following commands:

```sh
$ cd ../src
$ make clean
$ make
$ chmod 777 ../bin/usimm
$ cd ..
$ chmod 777 ./run_GreenORAM
$ chmod 777 ./run_GreenORAM_LOCAL
$ chmod 777 ./run_GreenORAM_RANDOM
$ ./run_GreenORAM
$ ./run_GreenORAM_LOCAL
$ ./run_GreenORAM_RANDOM 
```
运行每一个run_GreenORAM需要较长时间（1个小时左右），请耐心等待，若助教时间有限可以直接查看随邮件发送的复现结果文件夹，里面存放了我的复现结果
复现得到的结果会保存在`output`文件夹中，以workload_GreenORAM、workload_GreenORAM_Local、workload_GreenORAM_Random命名
