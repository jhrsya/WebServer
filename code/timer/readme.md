# <arpa/inet.h> 
<arpa/inet.h> 是一个 C 语言标准库头文件，其名称为“Internet address manipulation routines”，用于 IP 地址和端口号之间的转换，主要包含以下函数：

    inet_addr：将字符串形式的 IPv4 地址转换为网络字节序的整数值。
    inet_ntoa：将网络字节序的整数值转换为点分十进制字符串形式的 IPv4 地址。
    inet_aton：将字符串形式的 IPv4 地址转换为网络字节序的整数值，并存储在指定的结构体 in_addr 中。
    inet_ntop：将网络字节序的整数值或结构体 in_addr 转换为点分十进制字符串形式的 IPv4 或 IPv6 地址。
    inet_pton：将字符串形式的 IPv4 或 IPv6 地址转换为网络字节序的整数值或结构体 in_addr。
此外，该头文件还包含了一些其他相关的宏和数据类型定义，例如：

    INADDR_ANY：表示任意 IP 地址。
    in_addr_t：表示 IPv4 地址的整数类型。
    in_port_t：表示端口号的整数类型。
    sockaddr_in：表示 IPv4 套接字地址的结构体类型。
总之，<arpa/inet.h> 提供了一些方便的函数和数据类型，可以帮助我们在网络编程中对 IP 地址和端口号进行转换和处理。

# <functional> 
<functional> 是一个 C++ 标准库头文件，它定义了一些函数对象类和函数适配器，可以用于将函数作为参数传递、保存和调用，以及将函数接口进行适配和扩展。

该头文件中包含的一些常用类和函数适配器有：

    std::function：函数对象类，可以用于保存和调用任意可调用对象（函数指针、函数对象、Lambda 表达式等）。
    std::bind：函数适配器，可以将函数对象的参数进行绑定，生成一个新的可调用对象。
    std::placeholders：占位符，可以用于标识绑定的参数位置，提高函数对象的复用性。
    std::mem_fn：成员函数适配器，可以将成员函数转换为可调用对象，以便作为参数传递或保存。
此外，<functional> 还包含了一些其他函数对象类和函数适配器，例如 std::plus、std::minus、std::multiplies、std::divides 等，可以用于表示加法、减法、乘法和除法等运算。

总之，<functional> 提供了一些方便的函数对象类和函数适配器，可以帮助我们在 C++ 中更加灵活和高效地使用函数，并提高代码的可读性和可维护性。

# function<void()>
typedef std::function<void> TimeoutCallBack; 回调函数
std::function<void()> 是一个函数对象类型，它可以保存任意可调用对象，包括函数指针、函数对象、Lambda 表达式等，并提供了一些成员函数，例如 operator()，可以用于调用保存的可调用对象。而 void() 是一个函数类型，表示一个无参无返回值的函数。

下面的代码定义了一个使用 TimeoutCallBack 类型的函数，它接受一个 TimeoutCallBack 类型的回调函数参数，然后在指定的延时时间后调用该回调函数：
```c++
void setTimeout(int delay, TimeoutCallBack callback) {
    std::this_thread::sleep_for(std::chrono::milliseconds(delay));
    callback();
}

void myCallback() {
    std::cout << "Hello, world!" << std::endl;
}

int main() {
    setTimeout(1000, myCallback);  // 延时 1 秒后调用 myCallback
    return 0;
}

```
这样，1 秒后就会输出 "Hello, world!"。其中，myCallback 就是一个符合 TimeoutCallBack 类型的回调函数，它被作为参数传递给 setTimeout 函数，并在延时结束后被调用。


# <chrono> 
<chrono> 是一个 C++ 标准库头文件，它提供了时间处理的相关类和函数，包括时间点（time point）、时间段（duration）、时钟（clock）、定时器（timer）等。

该头文件中包含的一些常用类和函数有：

    std::chrono::system_clock：系统时钟类，提供了当前系统时间的相关操作，可以用于获取当前时间、延时等操作。
    std::chrono::steady_clock：稳定时钟类，提供了单调递增的时间，可以用于计时、性能分析等操作。
    std::chrono::duration：时间段类，表示一段时间，可以用于计算时间间隔和时间差等操作。
    std::chrono::time_point：时间点类，表示时间的一个具体点，可以用于表示某一时刻的时间戳，以及计算时间间隔和时间差等操作。
    std::chrono::duration_cast：时间单位转换函数，可以将一个时间段转换为指定的时间单位。
    std::chrono::time_point_cast：时间点精度转换函数，可以将一个时间点转换为指定的时间精度。
    std::chrono::high_resolution_clock：高分辨率时钟类，提供了更高精度的计时，可以用于性能测试和调优等操作。
此外，<chrono> 还包含了一些其他时间处理的函数和常量，例如 std::chrono::milliseconds、std::chrono::seconds、std::chrono::microseconds 等时间单位，以及 std::chrono::duration_values、std::chrono::ceil、std::chrono::floor 等常用函数。

总之，<chrono> 提供了一些方便的时间处理类和函数，可以帮助我们在 C++ 中更加精确和高效地处理时间，从而实现各种计时、延时、定时等操作。
