# std::copy

```c
copy(start, end, dest);

// 将vector<int> b拷贝到a的后面（追加）
copy(b.begin(), b.end(), back_inserter(a));
// 将vector<int> b拷贝到a的前面
copy(b.begin(), b.end(), a.begin());
```

