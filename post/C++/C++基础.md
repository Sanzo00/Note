---
typora-copy-images-to: img
---

## 类的结构

对于一个类来说：

1、数据部分private

2、尽量使用const，避免调用时出错

3、尽可能的传入和返回引用

4、构造函数使用初始化列表

![image-20200820174019765](img/image-20200820174019765.png)



## 函数重载

> C++支持函数重载，但是有默认值的参数和无参的函数在调用时，会出现二义性问题。

```c
class Test{
public:
    Test(): a(0), b(0) {
        cout << "no" << endl;
    }

    Test(int a_=0, int b_=0): a(a_), b(b_) {
        cout << "have" << endl;
    }

private:
    int a, b;
};

Test t1;	// 创建对象
Test t2();	// 声明函数
```



> 相同class的各个object互为friend（友元），可以直接访问私有成员

```cpp
class Test{
public:
    Test(int _a, int _b): a(_a), b(_b) {}
    int func(const Test &t) {
        return t.a + t.b;
    }

private:
    int a, b;
};
```



> +=重载

```cpp
class complex{
public:
    complex(double r = 0, double i = 0) 
        : re(r), im(i) { }
    complex& operator += (const complex&);
    double real() const { return re; }
    double imag() const { return im; }
private:
    double re, im;
    friend complex& __doapl(complex*, const complex&);
};

inline complex&
__doapl(complex* ths, const complex& r) {
    ths->re += r.re;
    ths->im += r.im;
    return *ths;
}

inline complex&
complex::operator += (const complex& r) {
    return __doapl(this, r);
}
```



> 加号重载

加号重载的时候，会返回一个local object，所以不能返回引用。这里返回的使临时对象`typename()`

```cpp
inline complex
operator + (const complex& x, const complex& y) {
    return complex(x.real() + y.real(), x.imag() + y.imag());
}

inline complex
operator + (const complex& x, double y) {
    return complex(x.real() + y, x.imag());
}

inline complex
operator + (double x, const complex& y) {
    return complex(x + y.real(), y.imag());
}
```



> <<重载

```cpp
ostream&
operator << (ostream& os, const complex& x) {
    return os << "(" <<  x.real() << "," << x.imag() << ")";
}
```



> ++重载

```cpp
class Clock{
public:
    Clock(int hour = 0, int minute = 0, int second = 0);
    void showTime() const;
    Clock& operator++ ();      // 前置
    Clock operator++ (int);   // 后置

private:
    int hour, minute, second;
};

Clock& Clock::operator ++ () {
  	second++;
    if (second >= 60) {
        second = 0;
        minute++;
        if (minute >= 60) {
            minute = 0;
            hour = (hour + 1) % 24;
        }
    }
    return *this;
}

Clock Clock::operator ++ (int) {
    Clock old = *this;
    ++(*this);  // 调用前置++
    return old;
}
```





## 拷贝构造/赋值

```cpp
inline 
String::String(const String& str) {
    m_data = new char[strlen(str.m_data) + 1];
    strcpy(m_data, str.m_data);
}
```



```cpp
inline
String& String::operator=(const String& str) {
    if (this == &str) return *this;
    delete[] m_data;
    mdata = new char[strlen(str.m_data) + 1];
    strcpy(m_data, str.m_data);
    return *this;
}
```



## 移动构造

适应MinGw和visual stdio的结果不同。

使用移动构造，在函数返回局部对象时，减少临时变量的创建。

```cpp
#include <iostream>
using namespace std;

class IntNum {
public:
    IntNum(int x = 0) : ptr(new int(x)) {
        cout << "Calling constructor..." << endl;
    }
    IntNum(const IntNum& t) : ptr(new int(*t.ptr)) {
        cout << "Calling copy constructor..." << endl;
    }
     IntNum(IntNum &&t): ptr(t.ptr) { // 移动构造
         t.ptr = nullptr;
         cout << "Calling move constructor..." << endl;
     }
    int getInt() {
        return *ptr;
    }
    ~IntNum() {
        delete ptr;
        cout << "Destruting..." << endl;
    }

private:
    int* ptr;
};


IntNum getNum() { // 返回一个临时变量
    IntNum a;
    return a;
}

int main() {


    IntNum ret = getNum();

    cout << ret.getInt() << endl;

    return 0;
}
```



## 内存管理

new：先分配内存，再调用构造函数

![image-20200820184248635](img/image-20200820184248635.png)

delete：先调用析构函数，再释放内存

![image-20200820184408185](img/image-20200820184408185.png)



在申请空间的时候，系统会给出额外的空间（上下的cookie），方便回收处理。

申请的空间要是16的倍数，不够的补充，这样转成16进制，就可以借用最后一位表示内存是借出还是回收。

![image-20200820185033124](img/image-20200820185033124.png)

new[]和delete[]搭配

![image-20200820190026215](img/image-20200820190026215.png)

![image-20200820190241751](img/image-20200820190241751.png)





> 默认的new和delete操作会分解成operator new() 和operator delete()

![image-20200821174250533](img/image-20200821174250533.png)

> 重载全局的new、delete

![image-20200821174343119](img/image-20200821174343119.png)

> 重载类中的new、delete

![image-20200821174358076](img/image-20200821174358076.png)

![image-20200821174409139](img/image-20200821174409139.png)





![image-20200821175918349](img/image-20200821175918349.png)







## static、this

函数处理多个对象的时候，通过this来获取不同对象的地址。

static修饰的成员数据只存在一份，static修饰的函数称为静态函数，静态函数没有this指针，只能处理静态数据。

![image-20200820214827633](img/image-20200820214827633.png)



![image-20200820215137001](img/image-20200820215137001.png)



## 模板 

> 类模板，调用的时候需要指定类型。

```cpp
template<typename T>
class complex{
public:
    complex(T r = 0, T i = 0)
        : re(r), im(i) { }
    complex& operator += (const complex&);
    T real() const { return re; }
    T imag() const { return im; }
private:
    T re, im;
    friend complex& __doapl(complex*, const complex&);
};

complex<double> c1(2, 3);
complex<int> c2(1, 2);
```





```cpp
#include <iostream>
using namespace std;

template <class T>
class Store{
private:
    T item;
    bool haveValue;
public:
    Store();
    T &getElem();
    void putElem(const T &x);
};

// 类外定义成员函数
template <class T>
Store<T>::Store(): haveValue(false) {}

template <class T>
T &Store<T>::getElem() {
    if (!haveValue) {
        cout << "No item present!" << endl;
        exit(1);
    }
    return item;
}

template <class T>
void Store<T>::putElem(const T &x){
    haveValue = true;
    item = x;
}
```



```cpp
// 动态数组类模板
#include <iostream>
#include <cassert>
using namespace std;

template<class T>
class Array{
private:
    T* list;
    int size;

public:
    Array(int sz = 50);         // 构造
    Array(const Array<T> &a);   // 复制构造
    ~Array();                   // 析构
    Array<T>& operator = (const Array<T> &rhs); // 重载 =
    T& operator[] (int i);                      // 重载[]
    const T& operator[] (int i) const;
    operator T*();                              // 重载到T*类型转换
    operator T*() const;
    int getSize() const;
    void resize(int sz);
};

template <class T> Array<T>::Array(int sz) {
    assert(sz >= 0);
    size = sz;
    list = new T[size];
}

template <class T> Array<T>::~Array() {
    delete[] list;
}

template <class T> Array<T>::Array(const Array<T> &a) {
    size = a.size;
    list = new T[size];
    for (int i = 0; i < size; ++i) {
        list[i] = a.list[i];
    }
}

template<class T> Array<T>& Array<T>::operator = (const Array<T> &rhs) {
    if (&rhs == this) return *this;
    if (size < rhs.size()) {
        size = rhs.size();
        delete[] list;
        list = new T[size];
    }
    for (int i = 0; i < size; ++i) {
        list[i] = rhs[i];
    }
    return *this;
}

template<class T> T& Array<T>::operator[] (int i) {
    assert(i >= 0 && i < size);
    return list[i];
}

template<class T> const T& Array<T>::operator[] (int i) const {
    assert(i >= 0 && i < size);
    return list[i];
}

template<class T> Array<T>::operator T*() {
    return list;
}

template<class T> Array<T>::operator T*() const{
    return list;
}

template<class T> int Array<T>::getSize() const{
    return size;
}

template<class T> void Array<T>::resize(int sz) {
    assert(sz >= 0);
    if (sz == size) return;

    T* newList = new T[sz];
    for (int i = 0; i < min(sz, size); ++i) {
        newList[i] = list[i];
    }
    delete[] list;
    list = newList;
    size = sz;
}
```



> 函数模板，调用的时候不需要指定类型，编译器会对函数模板进行参数推导。

```cpp
template <class T>
inline
const T& min(const T& a, const T& b) {
    return a < b ? a : b;
}

stone r1(2, 3), r2(2, 5), r3;
r3 = min(r1, r2);
```



> 成员模板，一般用于大型的构造函数中，使得类更加弹性

![image-20200821153942404](img/image-20200821153942404.png)

![image-20200821153954929](img/image-20200821153954929.png)

![image-20200821154257535](img/image-20200821154257535.png)







> 模板特化specialization，对特定类型特化行为

![image-20200821154437661](img/image-20200821154437661.png)

> 个数偏特化

![image-20200821154957529](img/image-20200821154957529.png)



> 范围偏特化，范围T缩小为T*

![image-20200821155007020](img/image-20200821155007020.png)



> 模板模板参数

![image-20200821155339067](img/image-20200821155339067.png)



![image-20200821155450039](img/image-20200821155450039.png)

![image-20200821155639339](img/image-20200821155639339.png)





## 组合与继承

> 组合 Composition has-a

组合是一个类内部包含另一个类的对象。

![image-20200821082634127](img/image-20200821082634127.png)

![image-20200821082823844](img/image-20200821082823844.png)

构造由内而外，默认调用内部的默认构造函数，可以自己指定；析构由外而内。编译器自己调度。

![image-20200821083138797](img/image-20200821083138797.png)



> 委托 Delegation

一个类中包含另一个类的指针，这样可以将类的实现由另一个类完成，对应PIMPL（Pointer to Implementation）手法。

降低模板耦合

降低编译器以来，提高编译速度

接口与实现分离，提高接口稳定性

![image-20200821084507969](img/image-20200821084507969.png)



> 继承 Inheritance is-a

继承时，子类拥有父类的数据，构造的时候也是由内而外，析构由外而内。

父类的析构函数要设置为虚函数。

![image-20200821091004544](img/image-20200821091004544.png)

![image-20200821085544089](img/image-20200821085544089.png)



模板方法

![image-20200821101536148](img/image-20200821101536148.png)

观察者模型

![image-20200821101626352](img/image-20200821101626352.png)



原型模式

![image-20200821102939873](img/image-20200821102939873.png)



## 转换函数

![image-20200821105045087](img/image-20200821105045087.png)



## 显示/隐式转换

> 使用一个参数的构造函数进行隐式转换

![image-20200821105657721](img/image-20200821105657721.png)



> 隐式转换和转换函数同时存在，可能会存在二义性。

![image-20200821105744604](img/image-20200821105744604.png)



> 声明构造只能显式构造

![image-20200821110236205](img/image-20200821110236205.png)





## 可变参数模板

```c
void print() {}

template <typename T, typename... Types>
void print(const T& firstArg, const Types&... args) {
    cout << "last variadic: " << sizeof...(args) << endl;
    cout << firstArg << endl;
    print(args...);
}

print(2, 2.3, "hello", "world");
/*
    last variadic: 3
    2
    last variadic: 2
    2.3
    last variadic: 1
    hello
    last variadic: 0
    world
*/
```



## 虚函数

non-virtual函数，不希望derived class重新定义（override重写）

virtual函数，希望derived class重新定义（override，重写），他已有默认定义

pure virtual函数，希望derived class一定要重新定义，它没有默认的定义



虚函数在调用的时候，不再像普通函数一样，直接call xxx（静态绑定），而是vptr在vtbl中找到对应虚函数的地址，然后再调用（动态绑定）。

![image-20200821163954952](img/image-20200821163954952.png)



```c
(*(p->_vptr[0]))(p);

A a;
typedef void (*Func)(void);
Func f1 = (Func) *((int*)*(int*)(&a) + 0);
```

![image-20200821172237752](img/image-20200821172237752.png)



```cpp
// 非虚函数，使用父类指针，调用父类的函数
#include <iostream>
using namespace std;

class Base1{
public:
    void display() const {
        cout << "Base1::display()" << endl;
    }
};

class Base2: public Base1{
public:
    void display() const {
        cout << "Base2::display()" << endl;
    }
};

class Derived: public Base2{
public:
    void display() const {
        cout << "Derived::display()" << endl;
    }
};

void func(Base1 *p) {
    p->display();
}

int main() {
    Base1 base1;
    Base2 base2;
    Derived derived;

    func(&base1);
    func(&base2);
    func(&derived);

    return 0;
}
/*
    Base1::display()
    Base1::display()
    Base1::display()
*/
```



## 虚基类

当派生类从多个基类中派生，而这些基类又有共同的基类，则再访问此共同基类中的成员时，将产生冗余，并可能因冗余带来不一致性。

虚基类主要用来解决多继承时可能发生的对同一基类继承多次而产生二义性的问题。

为最远的派生类提供唯一的基类成员，而不重复产生多次复制。

![](img/C++进阶/虚基类.jpg)

虚基类及派生类构造函数：

建立对象时所指定的类称为最远派生类，虚基类的成员由最远派生类的构造函数通过调用虚基类的构造函数进行初始化。

在整个继承结构中，直接或间接继承基类的所有派生类，都必须在构造函数的成员初始化表中为虚基类的构造函数列出参数，如果未列出，则表示调用该虚基类的默认构造函数。

在建立对象时，只有最远的派生类的构造函数调用虚基类的构造函数，其他类对虚基类构造函数的调用被忽略。

```cpp
#include <iostream>
using namespace std;

class Base{
public:
    Base(int x): var0(x){}
    void func0() {
        cout << "member of Base()" << endl;
    }
    int var0;
};

class Base1: virtual public Base{
public:
    Base1(int x): Base(x){}
    int var1;
};

class Base2: virtual public Base{
public:
    Base2(int x): Base(x){}
    int var2;
};

class Derived: public Base1, public Base2{
public:
    Derived(int x): Base(x), Base1(x), Base2(x) {}
    int var;
    void func() {
        cout << "member of Derived" << endl;
    }
};

int main() {

    Derived d(1);
    d.var0 = 2;
    d.func0();

    return 0;
}
```



## 函数指针

函数指针一般用于回调函数。

```cpp
#include <iostream>
using namespace std;

int compute(int a, int b, int (*func)(int, int)) {
    return func(a, b);
}

int max(int a, int b) {
    return a > b ? a : b;
}

int min(int a, int b) {
    return a < b ? a : b;
}

int sum(int a, int b) {
    return a + b;
}

int main() {

    int a= 5, b = 10, res;
    res = compute(a, b, &max);
    cout << "max: " << res << endl;

    res = compute(a, b, &min);
    cout << "min: " << res << endl;

    res = compute(a, b, &sum);
    cout << "sum: " << res << endl;

    return 0;
}
```

```cpp
// 数组指针，fp指向一个数组，++跨越一个数组
char (*fp)[3] = new char[2][3];
// 指针数组
char *a[10];
```



## 前向声明

```cpp
class Fred;

class Barney{
	Fred x; // 错误：类Fred的声明尚未完善，不能创建对象
};

class Fred{
	Barney y;
};
```

可以使用对象指针，来解决这样的问题。

```cpp
class Fred;

class Barney{
	Fred *x;
};

class Fred{
	Barney y;
};
```



## 智能指针

- unique_ptr

  不允许多个指针共享资源，可以使用标准库中的move函数转移指针

- shared_ptr

  多个指针共享资源

- weak_ptr

  可复制shared_ptr，但构造或释放对资源不产生影响

```c
// shared_ptr的封装
#include <iostream>
using namespace std;

template<class T>
class SharedPtr{
public:
    SharedPtr() : ptr((T*) 0), count(0) {
        cout << "defalut construct";
    }
    SharedPtr(T* t) : ptr(t), count(new int(1)) {
        cout << "create " << *ptr << " " << *count << endl;
    }
    SharedPtr(const SharedPtr &t) : ptr(t.ptr), count(&(++(*t.count))) {
        cout << "copy construct " << *ptr << " " << *count << endl;
    }
    SharedPtr& operator = (const SharedPtr &t) {
        if (this == &t) return *this;
        ++(*t.count);
        if ((*count)-- == 0) {
            delete ptr;
            delete count;
        }
        ptr = t.ptr;
        count = t.count;
        cout << "operator = " << *ptr << " " << *count << endl;
        return *this;
    }
    ~SharedPtr() {
        if (ptr && --(*count) == 0) {
            cout << *ptr << " default destructor" << endl;
            delete ptr;
            delete count;
        }
    }

    T& operator*() {
        if (count == 0) return (T*)0;
        return *ptr;
    }

    T* operator->() {
        if (count == 0) return 0;
        return ptr;
    }

private:
    T *ptr;
    int *count;
};


int main() {

    SharedPtr<string> p1(new string("abc"));
    SharedPtr<string> p2(p1);
    SharedPtr<string> p3(new string("fff"));
    p3 = p2;

    return 0;
}

/*
    create abc 1
    copy construct abc 2
    create fff 1
    operator = abc 3
    abc default destructor
*/
```





## 流类库与输入输出

### 输出流对象

![](img/C++进阶/流对象.jpg)

输出流：

- ostream
- ofstream
- ostringstream

输出流对象：

- cout，标准输出。
- cerr，标准错误输出，没有缓冲，发送给它的内容立即被输出。
- clog，类似cerr，但有缓冲，缓冲满时再输出。

```cpp
// 标准输出重定向
#include <iostream>
#include <ostream>
#include <streambuf>
#include <fstream>
using namespace std;

int main() {


    ofstream fout("b.out");
    streambuf* pOld = cout.rdbuf(fout.rdbuf());
    
    for (int i = 1; i < 5; ++i) {
        cout << i << endl;
    }

    cout.rdbuf(pOld);
    return 0;
}
```



构造输出流对象:

```cpp
ofstream myFile("filename");

ofstream myFile;
myFile.open("filename");

myFile.open("filename", ios_base::out|ios_base::binary);
```

![](img/C++进阶/文件输出流成员函数.jpg)

![](img/C++进阶/操纵符.jpg)

```cpp
#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;

int main() {

    vector<double> arr{1.0, 2.01, 2.0323};

    for (int i = 0; i < arr.size(); ++i) {
        cout << setw(7) << arr[i] << endl;
    }

    return 0;
}
```

```cpp
#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;

int main() {

    vector<double> arr{1.0, 2.01, 2.0323};

    for (int i = 0; i < arr.size(); ++i) {
        cout.width(7);
        cout << arr[i] << endl;
    }

    return 0;
}
```

![](img/C++进阶/setiosflags.jpg)

```cpp
#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;

int main() {

    vector<double> arr{1.0, 2.01, 2.0323};
    string names[] = {"bob", "Alice", "AI"};

    for (int i = 0; i < arr.size(); ++i) {
        cout << setiosflags(ios_base::left) // 左对齐
             << setw(7) << names[i]
             << resetiosflags(ios_base::left) // 重置
             << setw(10) << arr[i] << endl;
    }
    return 0;
}
```

![](img/C++进阶/精度.jpg)

```cpp
#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;

int main() {

    vector<double> arr{1.0, 2.01, 2.0323};
    string names[] = {"bob", "Alice", "AI"};

    cout << setiosflags(ios_base::fixed);
    for (int i = 0; i < arr.size(); ++i) {
        cout << setiosflags(ios_base::left) // 左对齐
             << setw(7) << names[i]
             << resetiosflags(ios_base::left)
             << setw(10) << setprecision(1) << arr[i] << endl;
    }
    return 0;
}
```



### 向文本输出

```cpp
#include <iostream>
#include <fstream>
using namespace std;

struct Date{
    int mon, day, year;
};

int main() {
    Date dt = {7, 21, 2020};

    ofstream file("data.txt", ios_base::binary);
    file.write(reinterpret_cast<char*>(&dt), sizeof(dt));
    file.close();

    return 0;
}
```



### 向字符串输出

```cpp
#include <iostream>
#include <sstream>
using namespace std;

template <class T>
inline string toString(const T &v) {
    ostringstream os;
    os << v;
    return os.str();
}

int main() {

        string s = toString(5);
        string t = toString(1.2);
        cout << s << " " << t << endl;

    return 0;
}
```

```cpp
#include <iostream>
#include <sstream>
using namespace std;

int main() {

        string s = to_string(5);
        string t = to_string(1.2);
        cout << s << " " << t << endl;

    return 0;
}
```



### 输入流对象

```cpp
ifstream myFile("filename");

ifstream myFile;
myFile.open("filename");

myFile.open("filename", ios_base::in | ios_base::binary);
```

![](img/C++进阶/输入流函数.jpg)

![](img/C++进阶/输入流函数1.jpg)

```cpp
#include <iostream>
using namespace std;

int main() {
    char ch;
    while ((ch = cin.get()) != EOF) {
        cout.put(ch);
    }
    return 0;
}
```



### 从文本中读入

```cpp
#include <iostream>
#include <fstream>
using namespace std;

struct Date{
    int mon, day, year;
};

int main() {

    Date dt;
    ifstream file("data.txt", ios_base::binary);
    file.read(reinterpret_cast<char*>(&dt), sizeof(dt));
    file.close();
    cout << dt.mon << " " << dt.day << " " << dt.year << endl;

    return 0;
}
```

**设置文件的偏移量**

![](img/C++进阶/seekg.jpg)

**寻找0的位置**

![](img/C++进阶/寻找0的位置.jpg)



### 从字符串输入

```cpp
#include <iostream>
#include <sstream>
using namespace std;

template <class T>
inline T fromString(const string &str) {
    istringstream is(str);
    T v;
    is >> v;
    return v;
}

int main() {

    int v1 = fromString<int>("5");
    double v2 = fromString<double>("1.2");
    cout << v1 << " " << v2 << endl;

    return 0;
}
```



## 异常处理

![](img/C++进阶/异常处理.jpg)

![](img/C++进阶/异常例子.jpg)

![](img/C++进阶/异常接口.jpg)



### 构造和析构

![](img/C++进阶/自动析构.jpg)



### 标准异常类

![](img/C++进阶/标准异常类继承.jpg)

![](img/C++进阶/标准异常类.jpg)

![](img/C++进阶/标准异常类1.jpg)

```cpp
#include <iostream>
#include <cmath>
#include <stdexcept>
using namespace std;

double area(double a, double b, double c) throw(invalid_argument)
{
    if (a <= 0 || b <= 0 || c <= 0)
        throw invalid_argument("the side length should be positive");
    if (a + b <= c || a + c <= b || c + b <= a)
        throw invalid_argument("the side length should fit the triangle inequation");
    double s = (a + b + c) /2;
    return sqrt(s * (s-a)*(s-b)*(s-c));
}

int main() {

    double a, b, c;
    cin >> a >> b >> c;
    try{
        double s = area(a, b, c);
        cout << "Area:" << s << endl;
    }catch(exception &e) {
        cout << "Error: " << e.what() << endl;
    }

    return 0;
}
```

