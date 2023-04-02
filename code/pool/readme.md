[toc]
# 数据库连接池
数据库连接池类拥有的函数(功能)：
- public:
    成员函数
    - 获得数据库实例（单例模式），使用一个实例统一管理所有的数据库连接
    - 获得数据库连接
    - 释放数据库连接
    - 获取现在剩余连接个数
    - 初始化数据库连接池
    - 关闭数据库连接池
- private:
    成员函数
    - 构造函数和析构函数（类不能被实例化）

    成员变量
    - 最大连接个数
    - 已经使用的连接的个数
    - 数据库连接池中剩余的连接个数
    - 数据库连接池队列，有一个数据库连接需求，就从这个队列中取出来给它连接
    - 互斥锁
    - 信号量


## 信号量
sem_init(): sem_init(sem_t *sem, int pshared, unsigned int value);
- sem：一个指向sem_t类型的指针，指向将要被初始化的信号量。
- pshared：指定信号量的共享方式，其取值如下：
0：信号量只能由同一进程内的线程共享（线程之间共享）。
非0：信号量可以在不同进程之间共享（进程之间共享），这时候需要使用pthread_mutexattr_setpshared()函数将属性值设置为PTHREAD_PROCESS_SHARED。
- value：指定信号量的初始值。

sem_wait(&sem): sem_wait()函数会尝试对指定的信号量进行减一操作，如果此时信号量的值为0，则该函数会一直阻塞，直到信号量的值大于0。如果成功执行了减一操作，函数将立即返回。

sem_post(&sem): sem_post()函数会对指定的信号量进行加一操作，如果此时有其他进程或线程正在等待该信号量，则会唤醒其中一个进程或线程。


## mysql
### MYSQL *mysql_init(MYSQL *mysql)
用于初始化一个MYSQL结构体，以便用于与MySQL服务器建立连接。
参数说明：
- mysql：一个指向MYSQL结构体的指针，指向将要被初始化的结构体。如果该参数为NULL，则mysql_init()函数会自动分配和初始化一个新的结构体。

返回值：
- 如果成功，返回一个指向MYSQL结构体的指针。
- 如果失败，返回NULL。


### mysql_real_connect()函数
用于连接到MySQL数据库服务器。
```c++
MYSQL *mysql_real_connect(MYSQL *mysql, const char *host,
                          const char *user, const char *password,
                          const char *db, unsigned int port,
                          const char *unix_socket, unsigned long client_flag);

```
参数说明：
- mysql：一个指向MYSQL结构体的指针，指向要连接到的MySQL服务器。该结构体必须通过mysql_init()函数初始化。
- host：MySQL服务器的主机名或IP地址。
- user：连接到MySQL服务器所使用的用户名。
- password：连接到MySQL服务器所使用的密码。
- db：连接到MySQL服务器后要使用的默认数据库名。
- port：MySQL服务器的端口号。默认3306
- unix_socket：连接到MySQL服务器所使用的Unix套接字路径。如果该参数为NULL，则使用TCP/IP协议连接。
- client_flag：客户端标志，用于设置连接选项。通常可以设置为0。

返回值：
- 如果成功，返回一个指向MYSQL结构体的指针。
- 如果失败，返回NULL，并通过mysql_error()函数获取错误信息。

### mysql_close()函数
用于关闭与MySQL服务器的连接，并释放由mysql_init()和mysql_real_connect()分配的内存。
void mysql_close(MYSQL *mysql)
参数说明：
- mysql：一个指向MYSQL结构体的指针，指向要关闭连接的结构体。

### mysql_library_end()
用于关闭MySQL客户端库，释放与库相关的资源。
void mysql_library_end(void)



# 线程池相关
这个实现只是一个简单的线程池示例，还有许多需要完善和优化的地方。例如
- 可以在 ThreadPool 类中添加一个成员变量，表示活跃线程数。这样可以在运行时监控线程池的使用情况，并在必要时进行扩容或缩减。
- 目前，线程池的线程数量在创建时固定。可以考虑添加一些成员函数，用于动态地调整线程池中的线程数量。这将使得线程池能够更好地适应不同的工作负载。
- 可以为 ThreadPool 类添加一个成员函数，用于等待所有已添加的任务完成。这将使得用户在需要等待所有任务完成后，再执行其他操作时更加方便。
- 当任务队列为空时，线程会一直等待。可以考虑添加一个可配置的超时选项，如果在指定时间内没有新任务，线程将自动退出。这样可以在低负载时节省系统资源。
- 在 AddTask 函数中，可以考虑添加一些错误处理机制，例如当线程池已关闭时，不允许添加新任务。
- 可以考虑使用 std::packaged_task 和 std::future，以便支持返回值和异常处理。这将使得线程池更加通用，可以处理返回值的任务。
- 考虑在 ThreadPool 类中添加一个优先级队列，以便用户可以根据任务的优先级执行。这样，更重要的任务可以优先执行，提高程序的响应速度。

### 线程池类
public:
函数
- 显示构造函数，构造即初始化
- 默认构造函数
- 右值应用，移动构造函数
- 析构函数
- 模板方法，给任务队列添加任务

private:
变量
- 结构体：互斥锁，条件变量，是否关闭线程池，任务队列
- 一个结构体实例


### 移动构造函数
在 C++11 标准中，移动语义是一种新特性，允许程序员将资源（如堆上分配的内存）从一个对象移动到另一个对象，从而避免了不必要的复制和分配开销，提高了程序的效率。

在使用移动语义时，通常需要注意以下几点：
- 对于移动语义的对象，移动后源对象应该被设置为一个有效但未定义的状态（如可以被销毁，但不能访问其成员），而移动后目标对象应该获取原来源对象的状态。
- 在实现移动构造函数时，通常需要考虑移动对象的所有成员（包括指针、引用、容器等），以确保资源被正确地转移。
- 移动语义通常应该和移动语义相对应的移动赋值运算符一起使用，以确保正确的资源管理。

总之，移动构造函数是 C++11 中的一个重要特性，可以避免不必要的复制和分配开销，提高程序的效率。


# mysqlconnRAII
RAII类：
public:
函数：
- 构造函数：获取数据库连接
- 析构函数：释放数据库连接

private:
变量
- mysql类
- 数据库连接池类



RAII(Resource Acquisition Is Initialization)
pool::sqlconnRAII.h
RAII(资源获取即初始化)。它的基本思想是：当我们需要使用某个资源时，就立即获取该资源，并在资源被不再需要时自动释放该资源。这种技巧的目的是确保资源的正确管理，避免因为程序逻辑错误或异常情况导致资源泄漏。

在这个代码中，SqlConnRAII类通过在构造函数中获取MySQL连接，在析构函数中释放MySQL连接，来实现RAII机制。这样，当程序员使用这个类的实例时，无需手动管理MySQL连接的获取和释放，RAII机制会自动帮我们管理连接。这样可以避免因为程序员的疏忽或忘记释放连接而导致的资源泄漏等问题，提高了程序的健壮性和可维护性。

可以这样使用SqlConnRAII这个类
```c++
int main(){
    //获得数据库连接池实例
    SqlConnPool* pool = SqlConnPool::Instance();
    //连接池初始化
    pool->Init("localhost", 3306, "root", "password", "database", 10);
    MYSQL* sql;
    {
        SqlConnRAII db_conn(&sql, &pool);
        //这里可以使用sql对象进行数据库操作
    }
    //离开上面的{}代码块是，SqlConnRAII的析构函数会自动释放sql对象
}
```