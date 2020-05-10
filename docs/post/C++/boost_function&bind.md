# boost::function/bind

## boost::function

头文件：<boost/function.hpp>

boost::function是一个函数模板，可以代替具有相同返回类型，相同参数和相同参数个数的不同函数，和函数指针有些类似，用于封装函数，定义之后可以多次调用

```c
// 简单的例子
typedef boost::function<int(int ,int)> function_type;

int Max(int a, int b) {
	return a > b ? a : b;
}

int main() {

	function_type p = &Max;
	int ans = p(1, 2);
	cout << ans << endl; 	// 输出2

	return 0;
}
```



## boost::bind

头文件：<boost/bind.hpp>

boost::bind和boost::function结合，可以做到函数指针做不到的绑定，可以指向任何函数，包括成员函数

bind接受的第一个参数是一个可调用的对象，包括函数，函数指针，函数对象，成员函数指针，之后bind最多接受9个参数，参数量要和绑定的函数参数数量相同，bind绑定之后返回一个函数对象，内部保存了函数拷贝，具有operator()，返回类型自动为绑定的返回类型。在发生调用的时候，函数对象把之前存储的参数转发给函数完成调用

```c
#include <iostream>
#include <boost/bind.hpp>
#include <boost/function.hpp>
using namespace std;

int Max(int a, int b) {
	return a > b ? a : b;
}

int main() {

	boost::function<int()> f;
	f = boost::bind(&Max, 1, 2);
	cout << f() << endl;		// 输出2

	boost::function<int(int, int)> f1;
	f1 = boost::bind(&Max, _1, _2);
	cout << f1(1, 2) << endl;	// 输出2

	//int ret = boost::bind(&Max, _1, _2)(1, 2);
	//cout << ret << endl;		// 输出2

	return 0;
}
```



```c
#include <iostream>
#include <boost/bind.hpp>
#include <boost/function.hpp>
using namespace std;

class A {
public:
	void fun1() {
		cout << "hello A" << endl;
	}
	void fun2(int a, int b, int c) {
		cout << a << " " << b << " " << c << endl;
	}
};

int main() {

	A a;
	boost::function<void()> f;
	f = boost::bind(&A::fun1, &a);
	f();		// 输出 hello A

	f = boost::bind(&A::fun2, &a, 1, 2, 3);
	f();		// 输出 1 2 3

	boost::function<void(int, int)> f1;
	f1 = boost::bind(&A::fun2, &a, _1, 2, _2);
	f1(1, 3);	// 输出1 2 3

	return 0;
}
```

