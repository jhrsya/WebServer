## 线程池相关
这个实现只是一个简单的线程池示例，还有许多需要完善和优化的地方。例如，线程池的任务队列可以使用一个更高效的并发队列实现，以提高性能；线程的异常处理可以更加完善，以确保程序的稳定性；线程池的调度策略可以根据任务类型和优先级进行优化，以提高整个程序的效率。



## mysql_real_connect()
mysql_real_connect函数是MySQL C API中用于连接MySQL服务器的函数，其参数依次为：

    MYSQL *mysql: 已初始化的MYSQL对象指针，通过此函数会得到一个连接对象。

    const char *host: MySQL服务器主机名或IP地址，如果连接到本地MySQL服务器，则可以将其设置为"localhost"或"127.0.0.1"。

    const char *user: MySQL用户名。

    const char *passwd: MySQL用户密码。

    const char *db: 连接到的数据库名。

    unsigned int port: MySQL服务器端口号，默认为3306。

    const char *unix_socket: UNIX域套接字文件路径名，可以用于本地MySQL服务器连接。

    unsigned long clientflag: 连接选项标志，例如设置了CLIENT_SSL，则使用SSL安全连接。

此函数返回一个MYSQL对象指针，如果连接失败，将返回NULL并设置相应的错误代码，可以通过mysql_errno和mysql_error函数获取错误信息。

## mysql_init()
mysql_init函数是MySQL C API中用于初始化MYSQL对象的函数，其参数为已分配的MYSQL对象指针。

该函数初始化MYSQL对象的各个成员变量，并尝试连接到MySQL服务器。如果连接成功，该函数返回初始化后的MYSQL对象指针，否则返回NULL并设置相应的错误代码，可以通过mysql_errno和mysql_error函数获取错误信息。

## sem_init()
int sem_init(sem_t *sem, int pshared, unsigned int value);
其中，sem是指向要初始化的信号量的指针，pshared表示信号量的类型，value表示信号量的初始值。
在使用信号量时，可以使用sem_wait函数来获取信号量，使用sem_post函数来释放信号量。
在SqlConnPool中，当客户端请求连接时，可以通过调用sem_wait函数来等待空闲连接，当有连接被释放时，可以通过调用sem_post函数来增加信号量的值，表示连接池中的空闲连接数量增加了。


## RAII(Resource Acquisition Is Initialization)
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