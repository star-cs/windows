# 创建线程
CreateThread 和 _beginthreadex 都是用来创建线程的函数，但它们分别属于不同的库和层次：

    CreateThread
        来源：CreateThread 是 Windows API 的一部分，直接在操作系统级别创建线程。
        功能：它提供了创建和管理线程的基本功能，包括设置线程优先级、线程安全性、线程上下文等。
        使用：通常用于需要直接访问底层系统功能或与 Windows API 紧密集成的应用程序中。
        资源管理：CreateThread 不会自动管理与线程相关联的 CRT 资源，如错误号 (errno) 或其他线程局部存储变量。

    _beginthreadex
        来源：_beginthreadex 是 Microsoft C Runtime (CRT) 库的一部分，它是对 CreateThread 的封装，提供了更高层次的线程创建功能。
        功能：除了提供基本的线程创建功能外，_beginthreadex 还负责初始化和清理 CRT 环境，确保每个线程都有其自己的 CRT 状态。
        使用：在使用 C/C++ 编译器（如 Visual C++）编写的程序中，推荐使用 _beginthreadex，因为它处理了与线程相关的 CRT 资源管理，防止内存泄漏。
        资源管理：_beginthreadex 内部会为每个新线程分配一个数据结构（通常称为 tiddata），用于存储线程特有的 CRT 数据。当线程结束时，通过 _endthreadex 函数自动清理这些资源。

主要区别总结：

    库依赖：CreateThread 直接调用 Windows API，而 _beginthreadex 是 CRT 的一部分，它内部调用了 CreateThread。
    资源管理：_beginthreadex 处理了线程特有的 CRT 资源管理，包括分配和释放线程数据结构，而 CreateThread 则不负责这些任务。
    线程局部存储：_beginthreadex 保证每个线程都有自己的 CRT 环境，包括线程局部的错误号和其他全局变量，避免了多线程间的数据冲突。
    调用建议：在使用 Microsoft Visual C++ 编译器时，建议使用 _beginthreadex 和 _endthreadex 来创建和结束线程，以确保正确处理 CRT 资源。

在现代 C++ 编程中，更推荐使用 C++11 标准库中的 <thread>，它提供了更高级、更易于使用且跨平台的线程管理接口。




