# 动手写数据结构(d2ds)

强调**动手实践**的数据结构开源[书 + 代码]

## 文档/书籍

[在线阅读](https://sunrisepeak.github.io/d2ds/)

## 代码练习

用dslings的**编译器驱动开发模式**来进行代码练习

### dslings自动检测

```bash

xmake dslings

```

### 正确提示

🌏Progress: [=>--] 1/3

[Target: 0.d2ds]

✅ Successfully ran tests/d2ds.cpp!

🎉   The code is compiling!   🎉

Output:
====================
Hello D2DS

====================

Book: https://sunrisepeak.github.io/d2ds

### 错误提示

```text
🌏Progress: [>---] 0/3

[Target: 0.d2ds]

❌ Error: Compilation/Running failed for tests/d2ds.cpp:

 The code exist some error!

Output:
====================
[ 25%]: cache compiling.release tests/d2ds.cpp
error: tests/d2ds.cpp:8:5: error: ‘vaL’ was not declared in this scope; did you mean ‘val’?
    8 |     vaL = 2;
      |     ^~~
      |     val
  > in tests/d2ds.cpp


====================

Book: https://sunrisepeak.github.io/d2ds

```

---

[开源课程]() | [DStruct开源库]()