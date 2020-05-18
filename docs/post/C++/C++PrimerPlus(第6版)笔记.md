# C++ Pirmer Plus (第6版) 笔记

## 第2章 开始学习

- main()被启动代码调用，而启动代码有编译器添加到程序中，是程序和操作系统的桥梁。

- C++中函数的括号为空与在括号中使用void是等效的，在C中括号空着意味着对是否接受参数保持沉默。

- void main()，返回值为空，但不是当前标准的强制的一个选项，在一些系统不能工作。

- ANSI/ISO C++标准规定，如果编译器到达末尾时没有遇到返回语句，认为main()函数有 `return 0；`结尾。只适用于main函数。

- main()作为函数的入口，存在一些例外的情况，在Windows下，可以编写动态链接库（DLL）模块，这是其他程序可以使用的代码，由于DLL不是独立的程序，所以不需要main()。用与专用环境的程序，机器人中的控制芯片，可能不需要main()。

- C++的注释符为`//`，C的注释符为`/* */`，C++同时支持两种注释，C99标准也在C语言中添加了`//`注释，尽量使用C++注释，不实际到结尾符号与起始符号的正确配对。

- 老式C的头文件保留了`.h`扩展名（C++中仍可以使用），C++的头文件没有扩展名，有些C头文件被转换为C++头文件，这些文件进行重命名，去掉了`.h`后缀并在前面添加前缀c（表明来自C语言）。

- 命名空间可以解决，同名函数的问题。命名空间的使用方式一般为：

  - 将`using namespace std;`放在函数定义前，文件中所有函数都可以使用命名空间`std`中的元素。
  - 将`using namespace std;`放在特定的函数中，函数能使用名称空间std中的所有元素。
  - 特定的函数中使用类似`using std::cout`这样的编译指令，然函数能够使用指定的元素。
  - 不适用编译指令`using`，在需要使用命名空间`std`中的元素时，使用前缀`std::`。

- `endl`确保程序继续运行前刷新输出（将其立即显示到屏幕上），使用`\n`不能提供这样的保证。

- 标记：一行代码中不可分割的元素。通常使用空格、制表符、回车将两个标记分开，括号和逗号不需要使用空白分开的标记。

  空白：空格、制表符、回车。

  ```c
  return 0; 	// false
  return(0);	// true;
  ```

- `int a;`，指定了需要的内存、内存单元的名称。变量需要声明，一些语言支持使用时创建新的变量，而不是显示的进行声明，问题是如果错误的拼写变量名，将在不知情的情况下创建一个新的变量。

- 函数原型只描述函数接口，函数定义包含了函数的代码。C和C++将库函数的原型和定义分开了。库文件中包含了函数的编译代码，头文件中包含了原型。

  C++库函数存储在库文件中，编译器编译程序时，必须在库文件中搜索使用的函数，可能由于编译器不能自动搜索数学库提示错误，可以在编译时指定库文件`g++ main.cpp -lm`。

- 关键字是C++专用的，不能作为变量名。main不是关键字，可以作为变量名，但是可能会引发错误。



## 第3章 处理数据

   - C++内置的整型：unsigned long、long、unsigned int、int、unsigned short、short、char、unsigned char、signed char、bool、unsigned long long、long long。

     表示各种整型的系统限制的climits文件。

     ```c
     #include <iostream>
     #include <climits>
     using namespace std;

     int main() {

         cout << "char的位数:" << CHAR_BIT << endl;      // 8
         cout << "char的最大值:" << CHAR_MAX << endl;    // 127
         cout << "char的最小值:" << CHAR_MIN << endl;    // -128

         cout << "signed char的最大值:" << SCHAR_MAX << endl;    // 127
         cout << "signed char的最小值:" << SCHAR_MIN << endl;    // -128
         cout << "unsigned char的最大值:" << UCHAR_MAX << endl;  // 255

         cout << "short的最大值:" << SHRT_MAX << endl;           // 32767
         cout << "short的最小值:" << SHRT_MIN << endl;           // -32768
         cout << "unsigned short的最大值:" << USHRT_MAX << endl; //  65535

         cout << "int的最大值:" << INT_MAX << endl;          // 2147483647
         cout << "int的最小值:" << INT_MIN << endl;          // -2147483648
         cout << "unsigned int最大值:" << UINT_MAX << endl;  // 4294967295

         cout << "long的最大值:" << LONG_MAX << endl;                // 2147483647
         cout << "long的最小值:" << LONG_MIN << endl;                // -2147483648
         cout << "unsigned long的最大值:" << ULONG_MAX << endl;      // 4294967295
         cout << "long long的最大值:" << LLONG_MAX << endl;          // 9223372036854775807
         cout << "long long的最小值:" << LLONG_MIN << endl;          // -9223372036854775808
         cout << "unsigned long long的最小值:" << ULLONG_MAX << endl;// 18446744073709551615

         return 0;
     }
     ```

     C++内置的浮点型：float、double、long double。float最少32位，double最少64位，long double为80、96、128位。

     表示浮点类型的系统限制的cfloat或float.h文件中。

     ```c
     cout << "double的有效位:" << DBL_DIG << endl;        // 15
     cout << "float的有效位:" << FLT_DIG << endl;         // 6
     cout << "long double的有效位:" << LDBL_DIG << endl;  // 18

     // 在不损失精度的前提下, 基于基数FLT_RADIX的数的最大数字个数
     #define DBL_MANT_DIG    53
     #define FLT_MANT_DIG    24
     #define LDBL_MANT_DIG   64

     // 最大最小的指数位数
     #define DBL_MAX_10_EXP  +308
     #define FLT_MAX_10_EXP  +38
     #define LDBL_MAX_10_EXP  +4932

     #define DBL_MIN_10_EXP  -307
     #define FLT_MIN_10_EXP  -37
     #define LDBL_MIN_10_EXP  -4931
     ```

   - C++类型分为：基本类型（整数、浮点数）和复合类型（数组、字符串、指针、结构）。

   - 变量名的命名规则：

     - 名称中只能使用子字母、数字、下划线。
     - 名称的第一个字符不能是数字。
     - 区分字母的大小写。
     - 不能将C++的关键字用作名称。
     - 以两个下划线或下划线加大写字母开头的保留使用（编译器及其使用的资源）。以一个下划线开头的名称保留给实现，用作全局标识符。
     - C++对名称的长度没有限制，有些平台有长度限制。

   - 字节的含义依赖于实现，一些系统中可能不是8位。

   - sizeof，对类型名（int）使用用sizeof运算符时，应将类型名放到括号中，如果对变量名使用运算符，括号是可选的。

   - C++11有一种{}的初始化方式，适用于数组和结构，在C++98中也可以用于单值变量。

     ```c
     int a = {1};    // 1
     int b {2};      // 2
     int c {};       // 0
     ```

   - 整型字面值

     - 第一个数字为`1-9`表示十进制数

     - 第一位为`0`第二位为`1-7`表示八进制数

     - `0x`或`0X`开始的为16进制数

     ```c
     int hex = 0x10; // 16
     int oct = 010;  // 8
     int num = 10;   // 10
     ```

   - 编译器如何直到常量的类型？

     - 可以在数字后面加后缀来指明类型

       ```c
       l, L 表示long常量
       u, U 表示unsigned int常量
       ll, LL表示long long常量
       ull, ULL表示unsigned long long常量
       ```

     - 不带后缀的数字，通过数字大小来使用最小类型来表示。

   - 浮点数的存储，计算机将浮点数分为两部分：一部分表示值，另一部分表示缩放。

     书写的时候有两种方式：

     - 使用小数点的方式
     - 使用E表示法

     ```c
     double a = 0.015;
     double a = 1.5E-2;
     ```

   - C++有3中浮点类型：float、double、long double。

   - 强制类型转化

     ```c
     (typeName) value;
     typeName (value);
     ```

     另外C++还有四种强制类型转换运算符：

     ```c
     static_cast<>();
     dynamic_cast<>();
     const_cast<>();
     reinterpert_cast<>();
     ```

   - C++没有提供防止超出整型范围的情况，可以使用`climits`来确定限制。

   - 将long赋值给double，不会出现误差，long的最多10位而double的有效位有15。

     long long赋值给double，会出现误差，long long可以提供19位的数字。




## 第4章 复合类型

- 数组的初始化

  ```c
  int cars[4] = {1, 2, 3, 4}; // 只能在定义的时候初始化
  int cars[4] = {1, 2}; // 其他元素默认为0
  int cars[4] {1, 2, 3, 4}; // C++支持
  ```

  数组的初始化禁止缩窄转化

  ```c
  long plifs[] = {1, 2, 3.0}; // not allowed
  ```
  将浮点数转化为long是缩窄操作，不能通过编译。

- 字符常量和字符串常量
字符串常量和字符常量不能相互转化，`'a'`是字符常量，`"a"`是字符串常量，它是`'a'`和`'\0'`组成的字符串，`"a"`表示字符串所在的内存地址。

  ```c
  char c = "a"; // not allow，尝试将内存地址赋值给c
  ```

- 字符串拼接

  ```c
  cout << "hello " "world" << endl;
  cout << "hello world" << endl;
  ```

- cin读取字符串
cin读取字符串使用空白（空格、制表符、换行符）来确定字符串结束的位置。
  - getline
  通过回车输入的换行符来确定输入结尾，`cin.getline`又两个参数，一个是用来存储输入行的数组名，一个是读取的字符数，如果参数是是20，最多读取19个字符，最后一个字符用来存储空字符。
  `getline`在读取到指定数目的字符或遇到换行符时停止读取。

    ```c
    int main() {

        char s[10];
        cin.getline(s, 10);
        cout << s << endl;

        string t;
        getline(cin, t);
        cout << t << endl;
        return 0;
    }
    ```

  - get()

    get()和getline的参数解实相同，但是get()不会跨过换行符，如果连续读取字符串，需要手动读取换行符。

    ```c
    cin.get(s, 10);
    cin.get(); // 读取换行符
    cin.get(t, 10);
    ```

    还有一种使用get()的方式，将两个类成员函数拼接起来，应为cin.get()返回的是一个cin对象。

    ```c
    cin.get(s, 10).get();
    cin.getline(s, 10).getline(t, 10);
    ```

- 原始(raw)字符串

  再原始字符串中，字符表示机子，`\n`表示的就是字符`\n`，而不是换行。使用就是将字符串放到`R"(string)"`中。

  ```c
  int main() {

      cout << "\\n (hello) \\t" << endl;
      cout << R"(\n (hello) \t )" << endl;

      return 0;
  }
  ```

- 结构体的每个成员都有一个位字段。
  ```c
  struct T{
      int a : 4; // 4 bits
      char b : 8; // 8 bits
  };
  ```

- 共用体（union）

  union是一种数据结构，可以存储不同的数据类型，但是同时只能存储一种数据类型。union的空间大小是最大的成员空间。

  ```c
  union U{
      int a;
      long long b;
      double c;
  };

  U test;
  cout << sizeof(test) << endl; // 8
  cout << sizeof(test.a) << endl; // 4
  cout << sizeof(test.b) << endl; // 8
  cout << sizeof(test.c) << endl; // 8
  ```

  当数据使用多种格式，但不会同时使用的时候，可以节省空间。
  ```c
  struct Home{
      char tv[10];
      int type;
      union id{
          int id_num;
          char id_char[10];
      }id_val;
  };

  Home home;
  if (home.type == 1) {
      cin >> home.id_val.id_num;
  }else {
    cin >> home.id_val.id_char;
  }
  ```

  可以使用匿名共用体，简化操作。
  ```c
  struct Home{
      char tv[10];
      int type;
      union {
          int id_num;
          char id_char[10];
      };
  };

  Home home;
  if (home.type == 1) {
      cin >> home.id_num;
  }else {
    cin >> home.id_char;
  }
  ```

- 枚举

  C++的enum是另一种创建符号常量的方法，可以替换const，允许定义新的类型。

  ```cpp
  int main() {

    enum Day {Mon, Tue, Wed, Thu, Fri, Sta, Sun};
    enum {Mon, Tue, Wed, Thu, Fri, Sta, Sun}; // 如果不创建新的变量，可以省略名称
    Day day = Tue;
    Day day2 = (Day)10; // 默认只能用定义的变量来赋值，需要强转

    day++; // invalid, enum没有算术运算符

    cout << day << endl; // 1
    cout << day2 << endl; // 10

    return 0;
  }
  ```

  enum可以通过赋值运算来显式的设置枚举的值，也可以之定义部分的值，其他未初始化的枚举值比前面的枚举值大1.
  ```cpp
  int main() {

    enum Day {one = 1, two = 2, fout = 4, eight = 8};

    enum sep {first, second = 100, third};
    cout << first << endl;  // 0
    cout << second << endl; // 100
    cout << third << endl;  // 101

    return 0;
  }
  ```

- 指针和C++的基本原理

  面向对象编程与传统的过程性编程的区别在于，OOP强调的是再运行阶段而不是编译阶段进行决策。

  运行阶段决策提供了灵活性，例如分配数组空间时，可以使用new来动态申请需要的空间。

- 动态数组的申请和释放

  ```cpp
  int *arr = new int [10];
  delete[] arr;
  ```

- delete的使用规则

  - 不要使用delete释放不是new分配的内存。
  - 不要使用delete释放同一个内存块两次。
  - 如果使用new[]为数组分配内存，应使用delete[]来释放。
  - 对空指针使用delete是安全的。

- 数组也是用指针来是实现：arr[i] <==> *(arr+1)

  使用cout打印arr和&arr的结果是一样的，但是意义不同，arr是arr[0]的地址，&arr是整个arr的地址。可以用arr+1和&arr+1做验证。

  ```cpp
  int main() {
    int a[10];
    cout << a << endl;      // 0x61fee8
    cout << &a << endl;     // 0x61fee8

    cout << a+1 << endl;    // 0x61feec
    cout << &a + 1 << endl; // 0x61ff10
    return 0;
  }
  ```


- 自动存储、静态存储、动态存储

  - 自动存储：函数内部定义的变量使用自动存储空间，再所属函数被调用时自动产生，函数结素后消亡。

    自动变量是局部变量，它的作用域是包含它的代码块，代码块就是被包含在花括号中的一段带啊吗。

    自动变量通常存储在栈中，执行代码块的时候，将变量依次加入到栈中，离开代码块的时候按照后进先出的顺序释放变量。

  - 静态存储：在整个程序执行期间都存在，声明静态变量的两种方式：一种式在函数外面你定义，一种是在声明变量的时候使用关键字static。

  - 动态存储：new和delete运算符提供了一种更加灵活的方法，它管理一个内存池，在C++中称为自由存储区或堆，声明周期不完全受程序或函数的生存时间控制。

    在栈中自动添加和删除机制使得占用的内存是连续的，但new和delete的相互影响可能导致占用的自由存储区不连续。



- ```c
  cout << (int*) "Hello world!" << endl;
  ```

  这句代码有效，打印的结果是字符串常量的地址。



## 第5章 循环和关系表达式

- 逗号运算符

  ```c
  cata = 17, 240; // 解释为 (cata = 17), 240; 240不起作用

  cata = (17, 240); // cata = 240;
  ```



- 使用clock()和头文件ctime来创建延迟循环。

  ```c
  #include <ctime>
  #include <iostream>
  using namespace std;

  int main() {

      cout << "Enter sec: ";
      float sec;
      cin >> sec;
      clock_t delay = sec * CLOCKS_PER_SEC;
      clock_t start = clock();

      while (clock() - start < delay);
      cout << "done" << endl;

      return 0;
  }
  ```

- 读取字符，直到EOF的输入循环的基本设计。

  ```cpp
  cin.get(ch);
  while (cin.fail() == false) {
    cout << ch;
    cin.get(ch);
  }

  while(cin >> ch) {
    cout << ch;
  }
  ```

- 入口条件循环：在程序运行前进行检查，如果条件满足则进入循环。例如：for，while。
  出口条件循环：在处理循环体之后进行检查，如果条件为false也会执行依次循环体。例如：do-while




## 第6章 分治语句和逻辑运算符

- 字符函数库
  | 函数名称 | 返回值 |
  | ---- | ---- |
  |isalnum() | 如果参数是字母数字，即字母或者数字，函数返回true|
  |isalpha() | 如果参数是字母，函数返回true|
  |iscntrl() | 如果参数是控制字符，函数返回true|
  |isdigit() | 如果参数是数字（0－9），函数返回true|
  |isgraph() | 如果参数】】是除空格之外的打印字符，函数返回true|
  |islower() | 如果参数是小写字母，函数返回true|
  |isprint() | 如果参数是打印字符（包括空格），函数返回true|
  |ispunct() | 如果参数是标点符号，函数返回true|
  |isspace() | 如果参数是标准空白字符，如空格、换行符、水平或垂直制表符，函数返回true|
  |isupper() | 如果参数是大写字母，函数返回true|
  |isxdigit()| 如果参数是十六进制数字，即0－9、a－f、A－F，函数返回true|
  |tolower()|  如果参数是大写字符，返回其小写，否则返回该参数|
  |toupper()|  如果参数是小写字符，返回其大写，否则返回该参数|

- 文件的读取

  ```cpp
  #include <fstream>
  #include <iostream>
  using namespace std;
  
  int main() {
  
      ifstream in;
      in.open("out.txt");
      int n, cnt = 0;
      if (in.is_open() == false) {
          cout << "文件打开失败" << endl;
          return -1;
      }
  
      while (in >> n) {
          cnt++;
      }
  
      if (in.eof()) { // EOF
          cout << "文件末尾\n";
      }else if (in.fail()) { // EOF或类型不匹配
          cout <<"数据类型不匹配\n";
      }else { // 未知错误
          cout << "未知错误\n";
      }
  
      cout << cnt << endl;
      in.close();
  
      return 0;
  }
  ```

  

- 文件的输出

  类似iostream，fstream定义了ofstream类，同时需要将ofstream和文件关联起来，方法是使用open来打开文件，完成后用close将其关闭。

  使用open打开已有的文件，默认将它其长度截断为0，原来的内容将丢失。

  ```cpp
  #include <fstream>
  #include <iostream>
  using namespace std;

  int main() {

    ofstream out; // 定义一个ofstream对象
    out.open("out.txt"); // 将out和文件out.txt关联起来

    int n;
    cin >> n;
    out << n; // 将n输出到文件中

    out.close();

    return 0;
  }
  ````
  
  

## 第7章 函数 C++的编程模块

- 为什么需要函数原型？

  函数原型描述了函数到编译器的接口，将函数返回值类型，以及参数的类型和数量告诉编译器，方便编译器的执行。使得编译器正确的处理函数的返回值，检查使用的参数数目、类型是否正确。

- 指针和const

  指针指向一个常量对象，对象的值不可以修改，指针可以修改。

  指针本身是一个常量，指针本身不能修改，指针指向的值可以修改。

  C++禁止将const地址赋值给非const指针，可以使用强制类型转换来突破这种限制。

- 函数和二维数组

  二维数组作为参数传递的时候，和一维数组一样也是传递的数组的地址，如果函数

  ```cpp
  int sum(int (*arr)[4], int size);

  int sum(int arr[][4], int size);

  int a[100][4];
  int ret = sum(a, 10);     // 前10行
  int ret = sum(a+10, 10);  // 接着后10行
  ```

- 函数指针

  函数的地址是存储其机器语言代码的内存的开始地址。

  函数名就是该函数的地址，一般区分出入的是函数地址还是函数的返回值。

  ```cpp
  solve(func);    // 传入函数的地址
  solve(func()); // 传入函数的返回值
  ```

  函数指针，需要声明函数的返回值类型和函数的参数列表。

  ```cpp
  double func(int);
  double (*p)(int); // p是一个返回值为double，参数为int的函数指针

  p = func;
  double ret = (*p)(5); // 通过函数指针调用函数
  double ret = p(5);    // c++调用函数指针的另一种方式

  ```
  ```cpp
  #include <iostream>
  using namespace std;

  double func(int x) {
    return x + 1.0;
  }

  int main() {

    double (*p)(int) = func;

    double x = func(1);
    double y = (*p)(2);
    double z = p(2);

    cout << "x = " << x << endl;
    cout << "y = " << y << endl;
    cout << "z = " << z << endl;

    return 0;
  }
  ```

  auto只能用与单值初始化，不能用于初始化列表。

  ```cpp
  const double *(*pa[3])(const double*, int) = {f1, f2, f3}; // 这里不能使用auto
  auto pb = pa; // 声明pa之后，再生命同样的数组就可以使用auto

  double *px = pa[0](av, 3);
  double *px = (*pa[0])(av, 3);

  double x = *pa[0](av, 3);
  double x = *(*pa[0])(av, 3);
  ```

  可以创建一个指向函数指针数组的指针，首先他也是一个指针，核心是(*p)[3]。

  ```cpp
  auto p = &pa; // 使用auto

  const double *(*(*pa)[3])(const double*, int); // 指向函数指针数组的指针
  ```

  (*pa)[0]; 表示函数指针，简单的调用方法时(*pa)[0](av, 3), 复杂的时(*(*pa)[0])(av, 3)，而*(*(*pa)[0])(av, 3)指向一个double值。

  使用typedef来简化。
  ```cpp
  typedef const double *(*p_fun)(cosnt double *, int); // p_fun现在是一个类型名

  p_func pa[3] = {f1, f2, f3}; // 创建函数指针数组
  ```
  
  

## 第8章 函数探幽

  - C++内联函数

    在执行函数调用时，程序将在函数调用后立即存储指令的内存空间，将函数参数复制到堆栈中，调转标记函数起点的内存单元，执行函数代码，有返回值的需要将返回值放在寄存器中，然后跳回到被保存的指令处。来回跳跃并记录跳跃位置需要一定的开销。

    C++的内联函数提供另一种方法，内联函数的代码和其他程序的代码内敛起来，内联函数的运行速度比常规函数稍快，但代价时需要占用更多的内存，如果有10处地方调用函数，那么这个函数就有10个副本。

    ```cpp
    inline add(int x, int y) {
      return x + y;
    }
    ```

- 引用

  引用是对变量起一个别名。声明引用时必须进行初始化，

  ```cpp
  #include <iostream>
  using namespace std;

  int main() {

    int a = 10;
    int &b = a;
    cout << b << endl;  // 10

    b += 10;
    cout << a << endl;  // 20

    return 0;
  }
  ```

  如果函数调用的参数不是左值或相应const引用参数的类型不匹配，则C++会创建类型正确的匿名变量，将函数调用的参数的值传递给匿名变量，并让参数来引用这个匿名变量。注意参数要使用const来修饰，匿名对象不能被修改。

  ```cpp
  #include <iostream>
  using namespace std;

  int func(const int &x) {
    return x * x;
  }

  int main() {

    long a = 2;
    cout << func(2) << endl;
    cout << func(a) << endl;

    return 0;
  }
  ```

- 应尽可能使用const

  - 使用const可以避免无意中修改数据的编程错误。
  - 使用const使函数能够处理const和非const实参，否则只能接受非const数据。
  - 使用const引用使函数能够正确生成并使用临时变量。

- 默认参数在设计类的时候，可以减少定义的析构函数、方法以及方法重载的数量。


### 函数模板

- 模板不会创建任何函数，只是告诉编译器如何定义函数。

  ```cpp
  #include <iostream>
  using namespace std;

  template <typename T>
  void Swap(T &x, T &y) {
    T temp = x;
    x = y;
    y = temp;
  }

  int main() {

    int a = 1, b = 2;
    double x = 1.1, y = 2.2;

    Swap(a, b);
    Swap(x, y);

    cout << a << " " << b << endl;
    cout << x << " " << y << endl;

    return 0;
  }
  ```

- 函数模板也可以重载。

  ```cpp
  #include <iostream>
  using namespace std;
  
  template <typename T>
  void Swap(T &x, T &y) {
    T temp = x;
    x = y;
    y = temp;
  }
  
  template <typename T>
  void Swap(T *a, T *b, int n) {
    for (int i = 0; i < n; ++i) {
      Swap(a[i], b[i]);
    }
  }
  
  template <typename T>
  void showArr(T *arr, int n) {
    for (int i = 0; i < n; ++i) {
      cout << arr[i] << " ";
    }
    cout << endl;
  }
  
  int main() {
  
    int a = 1, b = 2;
    int arr1[5] = {1, 2, 3, 4, 5};
    int arr2[5] = {5, 4, 3, 2, 1};
  
    Swap(a, b);
    Swap(arr1, arr2, 5);
    cout << a << " " << b << endl;
    showArr(arr1, 5);
    showArr(arr2, 5);
  
    return 0;
  }
  ```

#### 显式具体化

  对于一些模板函数，不能完全满足自己的需求，例如交换两个结构体，只是想交换其中一些值，这可以用显式具体化来解决。

  优先级关系时：非模板函数 > 显式具体化模板函数 > 模板函数

  ```cpp
// template <> void Swap<>(person &x, person &y)
template <>
void Swap<person>(person &x, person &y) {
    int temp = x.age;
    x.age = y.age;
    y.age = temp;
}
  ```

  ```cpp
#include <iostream>
#include <cstring>
using namespace std;

struct person{
    char name[10];
    int age;
};

void Swap(person& x, person &y) {
    char temp[10];
    strcpy(temp, x.name);
    strcpy(x.name, y.name);
    strcpy(y.name, temp);
}

template <typename T>
void Swap(T &x, T &y) {
    T temp = x;
    x = y;
    y = temp;
}

template <>
void Swap<person>(person &x, person &y) {
    int temp = x.age;
    x.age = y.age;
    y.age = temp;
}

void show(const person &x) {
    cout << "name: " << x.name << endl;
    cout << "age:  " << x.age << endl;
}

int main() {

    person a{"bob", 18};
    person b{"alice", 20};

    Swap(a, b);
    show(a);
    show(b);

    return 0;
}
  ```

#### 实例化和具体化

模板并非函数定义，最初编译器只能通过隐式实例化，C++允许显式实例化，可以直接命令编译器生成特定的实例。
  ```cpp
template void Swap<int>(int, int);
  ```

显式具体化需要在template后面加上<>。
  ```cpp
template <> void Swap<int>(int &, int &);
template <> void Swap<>(int &, int &);
  ```

在同一个文件中使用同一种类型的显式实例和显式具体化将出错。

还可以通过函数来创建显式实例化。

  ```cpp
#include <iostream>
#include <cstring>
using namespace std;

template <typename T>
T Add(T a, T b) {
    return a + b;
}

int main() {

    int a = 10;
    double b = 10.5;
    cout << Add<int>(a, b) << endl;     // 20
    cout << Add<double>(a, b) << endl;  // 20.5

    return 0;
}
  ```

虽然模板和函数调用不匹配，因为模板要求函数参数的类型相同，通过使用Add<int>(a, b)，可以强制为int类型实例化。

#### 编译器如何选择使用那个函数版本

  对于函数重载、函数模板和函数模板重载，c++需要一个定义良好的策略，来决定为函数调用使用那一个函数定义，这个过程称为重载解析。这个过程大致的流程是：

  - 创建候选函数列表，其中包含与被调用函数名称相同的函数和函数模板。

  - 使用候选函数列表创建可行函数列表，这些都是参数数目正确的函数，有一个隐式转换序列。

  - 确定是否有最佳的可行函数，如果有就使用，否则函数调用失败。

  对于函数may('B');首先寻找候选者，即命名为may()的函数和函数模板，然后寻找哪些可以用一个参数调用的函数。

  ```cpp
void may(int);                          // #1
float may(float, float = 3);            // #2
void may(char);                         // #3  
char* may(const char *);                // #4
char may(const char &);                 // #5
template <class T> void may(const T &); // #6
template <class T> void may(T *);       // #7
  ```

  只考虑参数，不考虑返回值，其中两个候选的函数（#4 #7）是不可行的，因为整型类型不能隐式转化为指针类型。剩下的函数模板（#6）可以用来生成具体化，T被替换为char。剩下五个可行的函数。

  接下来编译器必须确定那个可行函数是最佳的，首先查看为使桉树调用参数与可行的候选函数的参数匹配所需要进行的转换。

  1. 完全匹配。但常规函数优先于模板。
  2. 提升转化，例如：char和shorts自动转化为int，float自动转化为double。
  3. 标准转换。例如：cint转化为char，long转化为double。
  4. 用户自定义的转换，例如类声明中定义的转换。

  按照上面的优先级，#3、#5、#6 的优先级最高，因为他们都是完全匹配的，然后是#1、#2。其中#3和#5的优先级高于#6因为#6是模板函数。

#### 完全匹配和最佳匹配

  通常有两个完全匹配时一种错误，但是也存在例外。

  完全匹配允许的无关紧要的转化

|从实参  |到形参  |
|--|--|
| Type | Type& |
|Type&  | Type |
|Type[]  | *Type |
|Type(argument-list)  | Type(*) (argument-list)|
|Type  |const Type  |
|Type  | volatile Type |
|Type*  |const Type |
|Type*  | volatile Type* |

  假如有下面的函数：
  ```cpp
struct blot{
    int a;
    char b[10];
}
blot ink = {25, "spots"};
  ```

  在这种情况下，下面的原型都是完全匹配的：
  ```cpp
void func(blot);          // #1
void func(const blot);    // #2
void func(blot &);        // #3
void func(const blot &);  // #4
  ```
  这样就存在了多个完全匹配，编译器无法重载解析过程，如果没有最佳可行函数，编译器将生成一条错误，该消息可能会使用“ambiguous”二义性这样的词语。

  但是有些时候，仍然可以完成解析，执行cont数据的指针和引用优先于const指针和引用参数匹配。加入上面只定义了#3、#4，那么#3的优先级高于#4。const和非const之间的区别之适用于指针和引用指向的数据。如果自定义#1、#2就是出现二义性错误。
  ```cpp
#include <iostream>
#include <cstring>
using namespace std;

struct blot{
    int a;
    char b[10];
};

// void func(blot){
//   cout << "func(blot)\n";
// }
//
//
// void func(const blot){
//   cout << "func(const blot)\n";
// }

void func(blot&){
    cout << "func(blot&)\n";
}

void func(const blot&){
    cout << "func(const blot&)\n";
}

int main() {

    blot tmp;
    func(tmp);

    return 0;
}
  ```

  另一种情况就是，非模板函数优先级高于模板函数，如果同时模板函数，则较为具体的模板函数优先级高。也就是显式具体化的优先级高于模板隐式生成的具体化。

  最具体（most specialized）并不一定时显式具体化，而是指编译器推断使用那种类型执行的转化最少。例如：
  ```cpp
template <typename T> void func(T t);   // #1
template <typename T> void func(T* t);  // #2

struct blot{
    int a;
    char b[10];
};
blot tmp;
func(&tmp);

func<blot*>(blot* t); // #1
func<blot>(blot* t);  // #2
  ```
  对于func(&temp)来说上面两个函数模板都是匹配的，但是函数#2指明了参数是一个指针类型，而#1是将指针作为参数，对于编译器来说#2更加更加具体，转化的操作最少。

#### 自己选择使用那个函数

```cpp
#include <iostream>
#include <cstring>
using namespace std;

template <typename T>
T lesser(T a, T b) {    // # 1
  cout << "#1 template" << endl;
  return a < b ? a : b;
}

int lesser(int a, int b) {  // #2
  cout << "#2 not template" << endl;
  a = a < 0 ? -a : a;
  b = b < 0 ? -b : b;
  return a < b ? a : b;
}

int main(){
  int a = -10, b = 20;
  double x = 1.5, y = 2.5;
  cout << lesser(a, b) << endl; // #2，非模板函数优先级高
  cout << lesser<>(a, b) << endl; // #1，指定使用模板函数
  cout << lesser(x, y) << endl; // #1，与模板函数匹配
  cout << lesser<int>(x, y) << endl; // #1，显式实例化，将double强转为int

  return 0;
}
```



#### 如何确定类型

  ```cpp
template <typename T1, typename T2>
void ft(T1 x, T2 y) {
    ?type? xy = x + y;
}
  ```
  如何确定x+y的类型，是T1还是T2？

  C++11提供了关键字decltype关键字，来解决这个问题。
  ```cpp
int x;
decltype(x) y; // 使y和x具有相同的类型
  ```

  使用decltype解决xy的类型，有两种写法：
  ```cpp
decltype(x+y) xy;
xy = x + y;

decltype(x+y) xy = x + y; // 合并在一起

template <typename T1, typename T2>
void ft(T1 x, t2 y) {
    dectltype(x+y) xy = x + y;
}
  ```

 编译器为了实现decltype，必须编译一个核对表。
  对于decltype(expression) var;

1. 如果expression是一个没有用括号的表示符，则var的类型和该标识符的类型相同，包括const等类型的限定符。

     ```cpp
     #include <iostream>
     #include <typeinfo>
     using namespace std;
     
     int main(){
         double x = 5.5;
         double y = 2.5;
         double &rx = x;
         const double *pd;
     
         decltype(x) w;      // w是double类型
         decltype(rx) u = y; // u是double &类型
         decltype(pd) v;     // v是const double *类型
     
         cout << (typeid(w) == typeid(double)) << endl;
         cout << (typeid(u) == typeid(double&)) << endl;
         cout << (typeid(v) == typeid(const double *)) << endl;
     
         return 0;
     }
     ```

     可以使用typeid(type).name()打印变量的类型。

     

  2. 如果expression是一个函数调用，则var的类型与函数的返回类型相同。实际不会调用函数，编译器只是通过查看函数的原型确定返回类型。

     ```cpp
     #include <iostream>
     #include <typeinfo>
     using namespace std;
     
     long getSize(int x) {
         cout << "getSize(int)" << endl;
         return 1L;
     }
     
     int main(){
     
         decltype(getSize(2)) u ;      // u是long类型
         cout << (typeid(u) == typeid(long)) << endl;
     
         return 0;
     }
     ```

     

  3. 如果强两步都没有匹配，expression就是使用括号括起来的标识符。如果expression是左值，则var为指向其类型的引用。

     ```cpp
     #include <iostream>
     #include <typeinfo>
     using namespace std;
     
     int main(){
     
         double x = 1.5;
         decltype((x)) w = x;
         cout << (typeid(w) == typeid(double&)) << endl;
     
         w = 3.5;
         cout << x << endl;  // 3.5
     
         return 0;
     }
     
     decltype(x) w = x;  // w是double类型
     ```

     

  4. 如果前面条件都不满足，则var的类型与expression的类型相同。

     ```cpp
     #include <iostream>
     #include <typeinfo>
     using namespace std;
     
     int main(){
     
         int j = 3;
         int &k = j;
         int &n = j;
     
         decltype(j+6) x;    // x是int类型
         decltype(k + n) y;  // y是int类型，k+n不是引用
         decltype(100L) z;   // z是long类型
     
         cout << (typeid(x) == typeid(int)) << endl;
         cout << (typeid(y) == typeid(int)) << endl;
         cout << (typeid(z) == typeid(long)) << endl;
         return 0;
     }
     ```

     

       decltype可以和typedef一起使用。

       ```cpp
     template <typename T1, typename T2>
     void ft(T1 x, T2 y) {
         typedef decltype(x + y) xytype;
         xytype xy = x + y;
         xytype arr[10];
         xytype &rxy = arr[2];
     }
       ```

       只是用decltype不能解决所有的问题，例如：当函数的返回值类型不确定时：

       ```cpp
     template <typename T1, typename T2>
     ?type? get(T1 x, T2 y) {
         ...
         return x + y;
     }
       ```

      这是不能使用decltype(x+y)作为函数的返回值，因为此时还没有什声明参数x和y，他们不在作用域中，编译器看不到他们，无法使用，必须在声明之后使用decltype。C++为auto增添了一个特性来解决这个问题。

     ```cpp
     auto h(int x, int y) -> double;
     ```

     

      这将返回类型已到了参数声明后面，->double被称为后置返回类型，其中auto是一个占位符，表示后置返回类型提供的类型。这是C++11给auto新增的特性。这样就可以解决函数返回值类型不确定的情况。

     ```cpp
     template <typename T1, typename T2>
     auto get(T1 x, T2 y) -> decltype(x+y){
         ...
         return x + y;
     }
     ```
     



- 那种函数适合定义为内联函数？

  只有一行代码的小型、非递归函数适合作为内联函数。

  

### 编程练习

5. ```cpp
   #include <iostream>
   using namespace std;
   
   template <typename T>
   T max5(T arr[5]) {
     T tmp = arr[0];
     for (int i = 1; i < 5; ++i) {
       if (tmp < arr[i]) {
         tmp = arr[i];
       }
     }
     return tmp;
   }
   
   int main(){
   
     int arr1[5] = {1, 2, 3, 4, 5};
     double arr2[5] = {1.5, 2.5, 3.5, 4.5, 5.5};
   
     cout << max5(arr1) << endl;
     cout << max5(arr2) << endl;
   
     return 0;
   }
   ```

6. ```cpp
   #include <iostream>
   #include <cstring>
   using namespace std;
   
   template <typename T>
   T maxn(T arr[], int size) {
     T temp = arr[0];
     for (int i = 1; i < size; ++i) {
       if (temp < arr[i]) {
         temp = arr[i];
       }
     }
     return temp;
   }
   
   template <>
   const char* maxn (const char* arr[], int size) {
     const char *p = arr[0];
     for (int i = 1; i < size; ++i) {
       if (strlen(p) < strlen(arr[i])) {
         p = arr[i];
       }
     }
     return p;
   }
   
   int main(){
   
     int arr1[6] = {1, 2, 3, 4, 5, 6};
     double arr2[4] = {1.5, 2.5, 3.5, 4.5};
     const char* arr3[5] = {"hello", "world!", "nihao", "shijie", "sanzona"};
   
     cout << maxn(arr1, sizeof(arr1)/sizeof(arr1[0])) << endl;;
     cout << maxn(arr2, sizeof(arr2)/sizeof(arr2[0])) << endl;;
     cout << maxn(arr3, sizeof(arr3)/sizeof(arr3[0])) << endl;;
   
     return 0;
   }
   
   ```





## 第9章 内存模型和名称空间

### 单独编译

- 头文件常包含的内容：

  - 函数原型
  - 使用#define或const定义的符号常量
  - 结构声明
  - 类声明
  - 模板声明
  - 内联函数

- 在包含自己的头文件时使用“”包含，<>是标准头文件。

- 不要将头文件加入到项目列表中，也不要在源代码文件中使用#include包含其他的源文件代码。

- 防止头文件的重复包含，可能在同一个文件中定义同一个结构体两次，导致编译错误。

  ```cpp
  #ifndef XXX_H
  #define XXX_h
  ...
  #endif    
  ```

  这样并不能防止编辑器将头文件包含两次，而是让它忽略除第一次包含之外的所有内容。

- 多个库的链接问题

  C++标准允许每个编译器设计人员以它认为合适的方式实现名称装饰，因此有不同编译器创建的二进制模块很可能无法正确的链接，两个编译器将同一个函数生成不同的修饰名称。在连接编译模块时，要确保所用对象文件或库都是由同一个编译器生成的，如果有源代码，通常可以用自己的编译器重新编译源代码来消除链接问题。

  

### 存储持续性、作用域、链接性

- C++4种不同的存储数据的方案：

  - 自动存储：函数内部定义的变量使用自动存储空间，再所属函数被调用时自动产生，函数结素后消亡。

    自动变量是局部变量，它的作用域是包含它的代码块，代码块就是被包含在花括号中的一段带啊吗。

    自动变量通常存储在栈中，执行代码块的时候，将变量依次加入到栈中，离开代码块的时候按照后进先出的顺序释放变量。

  - 静态存储：在整个程序执行期间都存在，声明静态变量的两种方式：一种式在函数外面你定义，一种是在声明变量的时候使用关键字static。

  - 动态存储：new和delete运算符提供了一种更加灵活的方法，它管理一个内存池，在C++中称为自由存储区或堆，声明周期不完全受程序或函数的生存时间控制。

    在栈中自动添加和删除机制使得占用的内存是连续的，但new和delete的相互影响可能导致占用的自由存储区不连续。

  - 线程存储（C++11）：多喝处理器中，CPU同时处理多个执行任务，程序放在并行处理的多个线程中，使用thread_local声明的变量，则他的生命周期和所属的线程一样长。

- 单定义规则

  变量只能有一次定义，C++提供两种变量的声明，一种是定义声明，简称定义，他给变量分配存储空间，一种是引用声明，简称声明，使用关键字extern，不进行初始化。

  ```cpp
  // file1
  int err = 2;
  
  // file2
  static int err = 2;
  void func() {
      
      cout << err;
  }
  ```

  这样不违反单定义规则，因为关键字static指出标识符err的链接性为内部，因此并非要提供外部定义。    

  

  ```cpp
  void func() {
    static int n = 0;
    cout << n << endl;
    ++n;
  }
  ```

  静态存储持续性，无链接性。在代码块中使用static时，导致局部变量的存储特性变为静态，着意味值虽然该变量只能在该代码中使用，但是在该代码不处于活动状态时仍然存在，初始化了静态局部变量，程序只是在启动时初始化依次，再次调用不会像自动变量一样再次被初始化。

  

- extern的用法

    ```cpp
    // external.cpp
    #include <iostream>
    using namespace std;

    double warming = 0.3;

    void update(double dt);
    void local();

    int main() {

        cout << "Global warming is " << warming << " degree.\n";
        update(0.1);
        cout << "Global warming is " << warming << " degree.\n";
        local();
        cout << "Global warming is " << warming << " degree.\n";

        return 0;
    }

    // support.cpp
    #include <iostream>
    using namespace std;
    extern double warming;

    void update(double dt) {
        // extern double warming;
        warming += dt;
        cout << "Update global warming to " << warming;
        cout << " degrees.\n";
    }

    void local() {
        double warming = 0.8;
        cout << "Local warming = " << warming << " degrees.\n";
        cout << "But global warming = " << ::warming;
        cout << " degrees.\n";
    }
    ```
    
    在support可以使用在external种定义的变量warming，当修改warming时，在原文件中也相应的修改。如果在local中定义了与全局变量同名的局部变量，局部变量会隐藏全局变量。
    
    C++提供了作用域解析运算符（::），放在变量名前面， 表示使用变量的全局变量版本。



- 存储说明符

  - auto，C++11之前表示变量为自动变量，C++11之后用于自动类型推断。
  - register在C++11之前表示声明中的指示寄存器存储，在C++11之后显式的指出变量时自动的。
  - static用在作用域为整个文件中声明时，表示内部链接性；用作局部变量中，表示局部变量的存储为静态的。
  - extern表明式引用声明，声明引用在其他地方定义的变量。
  - thread_local指出变量的持续性与所属线程的持续性相同。thread_local变量之于线程，由于常规变量至于整个程序。
  - mutable的含义突破const的限制，永远处于可变的状态。

- cv-限定符

  cv限定符指的是const和volatile。

  默认情况全局变量式外部链接的，const修饰的全局变量为内部链接的，const定义的常量，使用预处理器将头文件的内容包含到每个源文件中，所有的源文件都将包含这个const常量定义。

  volatile表明，即使程序代码没有对内存进行修改，其值也可能发生变化，该关键字是为了改善编译器的优化能力，如果程序在几条语句中两次使用了某个变量的值，编译器可能不会让程序查找两次这个值，而是将这个值存在寄存器中。这种优化假设变量的值在两次使用之间不会变化，使用关键字volatile就是告诉编译器不要使用这种优化。

- C++在哪里查找函数？
  
如果文件中的函数原型指出函数是静态的，编译器只在该文件中查找函数定义，否则编译器将在所有程序文件中查找。如果找到两个定义，编译器发错错误信息，因为每个外部函数只能有一个函数定义。如果程序文件中没有找到，编译器将在库中搜索。有些编译器和链接器需要显式指出搜索哪些库。
  
- 语言链接性
  
C语言中一个名称对应一个函数，编译器可能将一个函数int func()翻译为_func的形式，称为C语言的链接性。在C++中函数存在重载，一个名称可能对应多个函数，对于int func()编译器可能翻译为\_func\_i的形式，称为C++的语言链接。可以使用函数原型来指明要使用的约定。
  
  ```cpp
  extern "C" void func(int);	// C语言链接
  extern void func(int);		// C++语言链接
  extern "C++" void func(int);	// C++语言链接
  ```
  
- 通常编译器使用三块独立的内存：分别用于静态变量，自动变量，动态存储。
  
- 程序结束时，有new分配的内存通常被释放，但也不是总是这样，在不健壮的操作系统中，在某些情况下，请求大型内存块将导致该代码块在程序结束不会被自动释放，最佳做法时使用delete手动释放。
  




### 定位new运算符

new负责在堆中找到一个满足要求的内存块，new运算符还有另一种变体称为定位new运算符，可以在指定要使用的内存位置。

```cpp
#include <new>
struct chaff{
    char dross[10];
    int slag;
};
char buf1[100];
char buf2[200];
int main() {
    chaff *p1, *p2;
    int *p3, *p4;
    p1 = new chaff;
    p3 = new int[20];
    
    // 使用buff数组作为new的内存空间
    p2 = new (buf1) chaff;
    p4 = new (buf2) int[20];
    
    return 0;
}
```

new定位运算符使用传递给它的地址，他不跟踪哪些内存单元已经被使用，也不查找未使用的内存块，可以指定内存偏移量`p = new (buf + N * sizeof(double)) double[N];`偏移量为N个double个字节。

new定位运算符时返回传递给他的地址，将其强制转换为void*类型，以便能赋值给任何指针类型。



### 名称空间

名称空间可以是全局，也可以位于另一个名称空间，但不能位于代码块中，因此在默认情况下在名称空间中声明的名称的链接性为外部的。可以使用作用域解析运算符(::)使用名称空间来限定该名称。

using声明和using编译指令，using声明使一个名称可用，using编译指令使所有名称可用。

```cpp
using Jill::fetch;		// using声明
using namespace Jill;	// using编译指令
```

using编译指令和using声明，增加了名称冲突的可能性，使用作用域运算符不会存在二义性。

名称空间声明可以嵌套：

```cpp
namespace element{
    namespace fire{
        int flame;
    }
    float water;
}
```

可以给名称空间创建别名：

```cpp
namespace mef = mython::elements::fire;
using mef::flame;
```



