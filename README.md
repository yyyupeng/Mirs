## 介绍
- Mirs是一个采用c++编写，基于事件驱动的小型Web服务器，支持GET、POST请求以及动态网页的处理。
## 运行环境
- 系统：ubuntu19.10
- 处理器：Intel® Core™ i5-7200U CPU @ 2.50GHz × 4
- 内存：7.7 GiB
- 编译器：gcc version 9.2.1
## 特性
- 基于Reactor + 非阻塞I/O + 线程池设计
- 线程池基于one loop per thread的设计思想
- 使用RAII机制对锁进行封装，使线程更加安全
- 使用状态机解析HTTP请求，显得结构清晰、易于理解
- 使用小根堆 + unordered_map实现定时器以关闭超时连接
- 使用智能指针管理对象，避免内存泄漏
- 使用bind + function实现回调函数，基于事件驱动
- 参考STL，实现自己的内存池，进一步优化性能
- 实现LFU缓存，加快客户访问速度
- 基于双缓冲技术实现简单的异步日志功能
## 目录说明
| 名称 | 说明 |
|--|--|
| base | 基础支持 |
| image | 测试截图 |
| log | 日志 |
| net | 网络 |
| test | 功能测试 |
## 安装及运行
运行前请先安装CMake（2.8及以上版本）
```
cd server
cmake .
make
./Server
```
## 测试
- 基础功能

![image --index](https://raw.githubusercontent.com/yyyupeng/Mirs/main/image/index.png)
	+ 图片

![image --photo](https://raw.githubusercontent.com/yyyupeng/Mirs/main/image/photo.png)
	+ 音频

![image --music](https://raw.githubusercontent.com/yyyupeng/Mirs/main/image/music.png)
	+ 动态网页

![image --submit](https://raw.githubusercontent.com/yyyupeng/Mirs/main/image/submit.png)
