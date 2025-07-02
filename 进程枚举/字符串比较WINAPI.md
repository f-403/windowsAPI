
# Windows 字符串比较（WinAPI 方法）

---

## 📑 目录

1. [lstrcmpW - 宽字符区分大小写比较](#lstrcmpw---宽字符区分大小写比较)  
2. [lstrcmpiW - 宽字符不区分大小写比较](#lstrcmpiw---宽字符不区分大小写比较)  
3. [lstrcmpA - ANSI 字符串区分大小写比较](#lstrcmpa---ansi-字符串区分大小写比较)  
4. [lstrcmpiA - ANSI 字符串不区分大小写比较](#lstrcmpia---ansi-字符串不区分大小写比较)  

---

## lstrcmpW - 宽字符区分大小写比较

```cpp
int lstrcmpW(
  LPCWSTR lpString1,  // 指向第一个宽字符字符串（以 null 结尾）
  LPCWSTR lpString2   // 指向第二个宽字符字符串（以 null 结尾）
);
```

**功能**：比较两个以 null 结尾的宽字符（Unicode）字符串，区分大小写。

**返回值**：

- 0 ：两个字符串相等
- <0：第一个字符串按字典序小于第二个字符串
- >0：第一个字符串按字典序大于第二个字符串

👉 [MSDN：lstrcmpW](https://learn.microsoft.com/en-us/windows/win32/api/winbase/nf-winbase-lstrcmpw)

### 示例代码

```cpp
#include <windows.h>
#include <iostream>

int main() {
    LPCWSTR str1 = L"HelloWorld";
    LPCWSTR str2 = L"HelloWorld";
    LPCWSTR str3 = L"helloworld";

    int result1 = lstrcmpW(str1, str2);
    int result2 = lstrcmpW(str1, str3);

    wprintf(L"str1 vs str2 比较结果: %d\n", result1);  // 输出 0
    wprintf(L"str1 vs str3 比较结果: %d\n", result2);  // 非 0，区分大小写
    return 0;
}
```

---

## lstrcmpiW - 宽字符不区分大小写比较

```cpp
int lstrcmpiW(
  LPCWSTR lpString1,
  LPCWSTR lpString2
);
```

**功能**：比较两个以 null 结尾的宽字符字符串，不区分大小写。

**返回值**：

- 0 ：两个字符串相等（忽略大小写）
- <0：第一个字符串字典序小于第二个字符串
- >0：第一个字符串字典序大于第二个字符串

👉 [MSDN：lstrcmpiW](https://learn.microsoft.com/en-us/windows/win32/api/winbase/nf-winbase-lstrcmpiw)

### 示例代码

```cpp
#include <windows.h>
#include <iostream>

int main() {
    LPCWSTR str1 = L"HelloWorld";
    LPCWSTR str2 = L"helloworld";

    int result = lstrcmpiW(str1, str2);

    wprintf(L"忽略大小写比较结果: %d\n", result);  // 输出 0，表示相等
    return 0;
}
```

---

## lstrcmpA - ANSI 字符串区分大小写比较

```cpp
int lstrcmpA(
  LPCSTR lpString1,
  LPCSTR lpString2
);
```

**功能**：比较两个以 null 结尾的 ANSI 字符串，区分大小写。

**返回值**：

- 0 ：两个字符串相等
- <0：第一个字符串字典序小于第二个字符串
- >0：第一个字符串字典序大于第二个字符串

👉 [MSDN：lstrcmpA](https://learn.microsoft.com/en-us/windows/win32/api/winbase/nf-winbase-lstrcmpa)

### 示例代码

```cpp
#include <windows.h>
#include <iostream>

int main() {
    LPCSTR str1 = "HelloWorld";
    LPCSTR str2 = "HelloWorld";
    LPCSTR str3 = "helloworld";

    int result1 = lstrcmpA(str1, str2);
    int result2 = lstrcmpA(str1, str3);

    printf("str1 vs str2 比较结果: %d\n", result1);  // 输出 0
    printf("str1 vs str3 比较结果: %d\n", result2);  // 非 0，区分大小写
    return 0;
}
```

---

## lstrcmpiA - ANSI 字符串不区分大小写比较

```cpp
int lstrcmpiA(
  LPCSTR lpString1,
  LPCSTR lpString2
);
```

**功能**：比较两个以 null 结尾的 ANSI 字符串，不区分大小写。

**返回值**：

- 0 ：两个字符串相等（忽略大小写）
- <0：第一个字符串字典序小于第二个字符串
- >0：第一个字符串字典序大于第二个字符串

👉 [MSDN：lstrcmpiA](https://learn.microsoft.com/en-us/windows/win32/api/winbase/nf-winbase-lstrcmpia)

### 示例代码

```cpp
#include <windows.h>
#include <iostream>

int main() {
    LPCSTR str1 = "HelloWorld";
    LPCSTR str2 = "helloworld";

    int result = lstrcmpiA(str1, str2);

    printf("忽略大小写比较结果: %d\n", result);  // 输出 0，表示相等
    return 0;
}
```
