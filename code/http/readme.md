[toc]
# httprequest类
类对象
**public**:
枚举
- 解析状态：REQUSET_LINE, HEADERS, BODY, FINISH
- http请求状态码：NO_REQUSET, GET_REQUEST, BAD_REQUEST, NO_RESOURCE, FORBIDDENT_REQUEST, FILE_REQUEST, INTERNAL_ERROR, CLOSED_CONNECTION

函数
- 构造函数
- 析构函数
- 初始化函数
- 解析函数
- 获取请求的资源路径
- 获取请求方法
- 获取http请求的版本号
- 输入key, 获取post请求的value
- 判断是否保持连接

**private**:
函数
- 解析请求行
- 解析请求头
- 解析请求数据
- 解析请求路径
- 解析post请求
- 解析post请求中的数据
- 用户验证，static

变量
- 解析状态枚举类型，解析状态
- 请求方法，请求资源路径，http请求版本号，请求正文(body)
- 请求头，哈希表，保存请求头中的key-value
- post请求
- 默认的HTML页面，static, unordered_set类型
- 默认的HTML页面tag, 

## MYSQL_FIELD
每一列
MYSQL_FIELD是一个结构体，它用于表示MySQL中的结果集中的一个字段（column）。它包含了关于该字段的信息，如字段名称、类型、长度、精度等。

在MySQL C API中，当你执行一个SELECT语句并获取结果集后，你可以通过调用mysql_fetch_field()函数来获取每个字段的MYSQL_FIELD结构体。你可以使用这个结构体来获取关于该字段的信息，例如它的名称、类型和长度，以及它是否可以为空等等。


## MYSQL_RES
整个查询结果集
MYSQL_RES是一个结构体，用于表示MySQL查询结果集。在MySQL C API中，当你执行一个SELECT语句并获取结果集后，MySQL会将结果集存储在MYSQL_RES结构体中，并返回该结构体的指针。你可以通过调用mysql_store_result()或者mysql_use_result()函数来获取MYSQL_RES结构体。

MYSQL_RES结构体包含了一个或多个MYSQL_ROW结构体的数组，每个MYSQL_ROW结构体表示结果集中的一行数据。你可以通过调用mysql_fetch_row()函数来获取下一行数据。

## mysql语句

### mysql_query()
mysql_query() 是 MySQL C API 中的一个函数，用于执行一个 SQL 查询语句并返回查询结果。

函数原型如下：
`int mysql_query(MYSQL *mysql, const char *query);`
其中，mysql 参数是一个 MYSQL* 类型的指针，代表一个 MySQL 连接对象；query 参数是一个 C 字符串，代表要执行的 SQL 查询语句。

当函数调用成功时，它会返回0，表示查询执行成功。否则，它会返回非零值，表示查询执行失败。在查询执行失败时，可以通过调用 mysql_error() 函数来获取错误信息。

### mysql_free_result()
mysql_free_result() 是 MySQL C API 中的一个函数，用于释放先前通过调用 mysql_store_result() 函数获取的查询结果集。
函数原型如下：
`void mysql_free_result(MYSQL_RES *result);`
其中，result 参数是一个 MYSQL_RES* 类型的指针，代表要释放的查询结果集对象。

使用 mysql_store_result() 函数获取查询结果集时，该结果集被保存在 MySQL 连接对象中，并且会一直占用连接资源，直到显式地调用 mysql_free_result() 函数释放它。如果在调用该函数之前关闭了 MySQL 连接，那么结果集也会自动被释放。


### mysql_store_result()

mysql_store_result()函数接受一个MySQL连接对象作为参数，并返回一个指向MYSQL_RES结果集结构体的指针。函数原型如下：
`MYSQL_RES *mysql_store_result(MYSQL *mysql);`
其中，mysql参数是一个指向已连接到MySQL服务器的MYSQL对象的指针。

mysql_store_result()函数的返回值有以下几种情况：

当查询成功并返回结果集时，函数返回一个指向MYSQL_RES结构体的指针。您可以使用这个指针来检索和处理结果集的行和列数据。

如果查询没有返回结果集（例如，如果查询是一个UPDATE或DELETE语句），则该函数返回NULL。

如果发生错误（例如，连接到MySQL服务器失败或查询语法错误），则该函数返回NULL，并设置相应的错误代码和错误消息。您可以使用mysql_errno()和mysql_error()函数来检查和处理这些错误。

需要注意的是，一旦调用了mysql_store_result()函数，就需要调用mysql_free_result()函数来释放结果集内存。如果您忘记调用mysql_free_result()函数，则会导致内存泄漏。

### mysql_fetch_row()
mysql_fetch_row()是一个用于从MySQL查询结果中获取一行数据并以C/C++语言中的数组形式返回的函数。它属于MySQL C API中的函数，可用于从MySQL数据库中获取数据并将其处理为程序可以使用的形式。

函数原型如下：
`MYSQL_ROW mysql_fetch_row(MYSQL_RES *result);`

其中，result 参数是由先前的MySQL查询返回的结果集，返回值是一个由查询结果中当前行的字段值组成的数组。

使用mysql_fetch_row()函数的步骤如下：

- 使用mysql_query()函数来执行SELECT语句或其他查询语句，并将结果集保存在一个MYSQL_RES类型的变量中。

- 在结果集中使用mysql_fetch_row()函数来获取每一行数据，并以数组形式返回。

- 在处理完结果集后，使用mysql_free_result()函数释放结果集所占用的内存。

以下是一个示例代码：
```c++
MYSQL_RES *result = mysql_store_result(mysql); // 执行查询并获取结果集
MYSQL_ROW row;
while ((row = mysql_fetch_row(result))) {  // 循环获取每一行数据
    printf("%s %s %s\n", row[0], row[1], row[2]); // 输出每一行的数据
}
mysql_free_result(result); // 释放结果集内存

```

在上述示例中，我们首先使用mysql_store_result()函数将查询结果保存在一个MYSQL_RES类型的变量中。然后，使用mysql_fetch_row()函数来循环获取每一行数据，并将其以数组形式返回给变量row，并使用printf()函数将其输出。最后，使用mysql_free_result()函数释放结果集所占用的内存。

需要注意的是，mysql_fetch_row()函数返回的数组是基于数字索引的。如果需要基于列名访问数据，则可以使用mysql_fetch_field()函数。此外，需要在使用MySQL C API中的函数时，确保在程序中正确初始化和关闭数据库连接。


## snprintf()
snprintf()函数是一个C语言标准库函数，用于将格式化的字符串输出到一个字符数组中。
`int snprintf(char *str, size_t size, const char *format, ...);
`
snprintf()函数和printf()函数非常类似，但是它允许你指定输出的字符串的长度，并且能够避免缓冲区溢出。snprintf()函数将输出的字符数限制为size - 1，这样就能够保证不会将数据写入超过缓冲区长度的部分，从而避免了缓冲区溢出的问题。

snprintf()函数的参数如下：

- str：指向字符数组的指针，该数组用于存储输出的字符串。
- size：输出缓冲区的最大长度，即能够存储的最大字符数（包括终止符）。
- format：格式化字符串，用于指定输出的格式，可以包含转换说明符（例如%s、%d等）和可选的参数。
- ...：可变参数列表，用于指定与格式化字符串中的转换说明符相对应的值。

snprintf()函数的返回值为输出到缓冲区中的字符数（不包括终止符），如果输出被截断，则返回值为缓冲区的长度。如果发生错误，返回值为负数。
```c++
#include <stdio.h>

int main() {
    char buffer[100];
    int n = snprintf(buffer, sizeof(buffer), "Hello, %s!", "world");
    printf("Output: %s\n", buffer);
    return 0;
}
//输出Hello,world!
```

# http主从状态机

从状态机
![](https://fvector.oss-cn-hangzhou.aliyuncs.com/202303271724571.png)

主状态机
![](https://fvector.oss-cn-hangzhou.aliyuncs.com/202303271725563.png)