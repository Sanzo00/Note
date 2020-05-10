## explicit关键字

explicit关键字用于修饰只有一个参数的类构造函数，explicit是显式，对应的implicit是隐式的。默认的类构造函数是隐式的。

explicit对只有一个参数的构造函数有效 (多个参数如果除了第一个参数,剩下的都有默认值也行), 多个参数不存在隐式转换.

- 默认隐式转换

    ```c
    class A {
    public:
        A(int x) { // 默认隐式构造
            this->x = x;
        }
        int x;
    };

    A a = 10; // 正确 
    /* 	等价于:
        A a(10);

        A temp(10);
        A a = temp;
    */
    ```



- 显示转换

    ```c
    class A {
    public:
        explicit A(int x) { // 显示构造
            this->x = x;
        }
        int x;
    };

    A a = 10; // 出错
    ```

