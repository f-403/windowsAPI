# Windows 作业对象（Job Object）主要用于**对一组进程进行统一管理和控制**，适合以下几种典型情境：

---

## 作业对象的常见使用情境

### 1. **统一管理多进程应用**

* 多进程程序（比如服务器、后台任务）启动多个子进程，使用作业对象绑定，方便整体控制和资源管理。
* 父进程退出时，确保所有子进程一起被终止，防止子进程“孤儿化”。

### 2. **资源限制和配额控制**

* 通过作业对象限制一组进程的CPU使用率、内存用量、作业时间等，避免进程组消耗过多系统资源。
* 常用于沙盒环境、虚拟化容器、资源管理软件。

### 3. **安全隔离**

* 作业对象可以限制进程权限，防止进程越权访问系统资源。
* 用于安全软件、杀毒软件限制可疑程序行为。

### 4. **后台任务和守护进程管理**

* 使一组后台进程不受控制台信号干扰，便于稳定运行。
* 适合服务程序或长期运行的后台任务。

### 5. **进程组统一终止**

* 利用 `TerminateJobObject`，一键终止整个作业内所有进程，方便快捷。
* 比单独结束进程更安全，防止遗漏。

### 6. **系统工具和管理程序**

* 系统级任务管理器或监控软件利用作业对象做进程分组和状态统计。
* 方便实现复杂进程生命周期管理。

---

### 总结

| 使用情境    | 说明               |
| ------- | ---------------- |
| 多进程应用管理 | 统一控制多个子进程        |
| 资源限制与配额 | 控制CPU、内存、句柄等资源使用 |
| 安全隔离    | 限制进程权限和行为        |
| 后台任务与服务 | 稳定运行无控制台干扰       |
| 统一终止    | 批量结束相关进程         |
| 系统管理工具  | 进程分组管理与监控        |

---


# Windows 作业对象（Job Object）常用API汇总

## 目录
- [1. 创建作业对象（CreateJobObject）](#1-创建作业对象createjobobject)
- [2. 打开已存在作业对象（OpenJobObject）](#2-打开已存在作业对象openjobobject)
- [3. 关联进程到作业对象（AssignProcessToJobObject）](#3-关联进程到作业对象assignprocesstojobobject)
- [4. 设置作业对象信息（SetInformationJobObject）](#4-设置作业对象信息setinformationjobobject)
- [5. 查询作业对象信息（QueryInformationJobObject）](#5-查询作业对象信息queryinformationjobobject)
- [6. 终止作业对象中所有进程（TerminateJobObject）](#6-终止作业对象中所有进程terminatejobobject)
- [7. 判断进程是否属于某作业对象（IsProcessInJob）](#7-判断进程是否属于某作业对象isprocessinjob)

---

## 1. 创建作业对象（CreateJobObject）

```cpp
HANDLE CreateJobObject(
  LPSECURITY_ATTRIBUTES lpJobAttributes,
  LPCWSTR               lpName
);
````

### 参数说明

* `lpJobAttributes`
  指向 `SECURITY_ATTRIBUTES` 结构体，定义作业对象的安全属性，通常传 `NULL` 表示默认。
* `lpName`
  作业对象的名称，可为 `NULL`。非空时，可以通过名字打开该作业对象。

### 返回值

* 成功返回作业对象句柄（`HANDLE`），失败返回 `NULL`。

### MSDN

[CreateJobObjectW](https://learn.microsoft.com/en-us/windows/win32/api/jobapi2/nf-jobapi2-createjobobjectw)

### 示例

```cpp
HANDLE hJob = CreateJobObject(NULL, NULL);
if (hJob == NULL) {
    // 错误处理
}
```

---

## 2. 打开已存在作业对象（OpenJobObject）

```cpp
HANDLE OpenJobObject(
  DWORD   dwDesiredAccess,
  BOOL    bInheritHandle,
  LPCWSTR lpName
);
```

### 参数说明

* `dwDesiredAccess`
  期望访问权限，如 `JOB_OBJECT_ALL_ACCESS`。
* `bInheritHandle`
  是否允许子进程继承该句柄，`TRUE` 或 `FALSE`。
* `lpName`
  作业对象名称，必须与创建时的名称一致。

### 返回值

* 成功返回作业对象句柄，失败返回 `NULL`。

### MSDN

[OpenJobObjectW](https://learn.microsoft.com/en-us/windows/win32/api/jobapi2/nf-jobapi2-openjobobjectw)

### 示例

```cpp
HANDLE hJob = OpenJobObject(JOB_OBJECT_ALL_ACCESS, FALSE, L"MyJobObject");
if (hJob == NULL) {
    // 错误处理
}
```

---

## 3. 关联进程到作业对象（AssignProcessToJobObject）

```cpp
BOOL AssignProcessToJobObject(
  HANDLE hJob,
  HANDLE hProcess
);
```

### 参数说明

* `hJob`
  作业对象句柄。
* `hProcess`
  需要加入作业的进程句柄，需拥有 `PROCESS_SET_QUOTA` 权限。

### 返回值

* 成功返回非零值，失败返回零。

### MSDN

[AssignProcessToJobObject](https://learn.microsoft.com/en-us/windows/win32/api/jobapi2/nf-jobapi2-assignprocesstojobobject)

### 示例

```cpp
BOOL bResult = AssignProcessToJobObject(hJob, hProcess);
if (!bResult) {
    // 错误处理
}
```

---

## 4. 设置作业对象信息（SetInformationJobObject）

```cpp
BOOL SetInformationJobObject(
  HANDLE             hJob,
  JOBOBJECTINFOCLASS JobObjectInfoClass,
  LPVOID             lpJobObjectInfo,
  DWORD              cbJobObjectInfoLength
);
```

### 参数说明

* `hJob`
  作业对象句柄。
* `JobObjectInfoClass`
  指定设置信息的类型，如：

  * `JobObjectExtendedLimitInformation`（扩展限制信息）
  * `JobObjectBasicLimitInformation`（基本限制信息）
  * `JobObjectCpuRateControlInformation`（CPU 速率控制）
* `lpJobObjectInfo`
  指向对应结构体的指针。
* `cbJobObjectInfoLength`
  结构体大小（字节数）。

### 返回值

* 成功返回非零，失败返回零。

### MSDN

[SetInformationJobObject](https://learn.microsoft.com/en-us/windows/win32/api/jobapi2/nf-jobapi2-setinformationjobobject)

### 示例（限制作业内进程最大内存为100MB）

```cpp
JOBOBJECT_EXTENDED_LIMIT_INFORMATION jeli = {0};
jeli.BasicLimitInformation.LimitFlags = JOB_OBJECT_LIMIT_PROCESS_MEMORY;
jeli.ProcessMemoryLimit = 100 * 1024 * 1024; // 100MB

BOOL bSet = SetInformationJobObject(hJob, JobObjectExtendedLimitInformation, &jeli, sizeof(jeli));
if (!bSet) {
    // 错误处理
}
```

---

## 5. 查询作业对象信息（QueryInformationJobObject）

```cpp
BOOL QueryInformationJobObject(
  HANDLE             hJob,
  JOBOBJECTINFOCLASS JobObjectInfoClass,
  LPVOID             lpJobObjectInfo,
  DWORD              cbJobObjectInfoLength,
  LPDWORD            lpReturnLength
);
```

### 参数说明

* `hJob`
  作业对象句柄。
* `JobObjectInfoClass`
  查询的信息类型（同 `SetInformationJobObject`）。
* `lpJobObjectInfo`
  指向缓冲区，接收查询结果。
* `cbJobObjectInfoLength`
  缓冲区大小。
* `lpReturnLength`
  接收实际写入数据大小的指针（可为 `NULL`）。

### 返回值

* 成功返回非零，失败返回零。

### MSDN

[QueryInformationJobObject](https://learn.microsoft.com/en-us/windows/win32/api/jobapi2/nf-jobapi2-queryinformationjobobject)

### 示例（查询作业内进程数量）

```cpp
JOBOBJECT_BASIC_ACCOUNTING_INFORMATION info = {0};
DWORD retLen = 0;
BOOL bQuery = QueryInformationJobObject(hJob, JobObjectBasicAccountingInformation, &info, sizeof(info), &retLen);
if (bQuery) {
    printf("作业内进程累计运行时间（100ns单位）：%llu\n", info.TotalUserTime.QuadPart);
} else {
    // 错误处理
}
```

---

## 6. 终止作业对象中所有进程（TerminateJobObject）

```cpp
BOOL TerminateJobObject(
  HANDLE hJob,
  UINT   uExitCode
);
```

### 参数说明

* `hJob`
  作业对象句柄。
* `uExitCode`
  作业中所有进程退出码。

### 返回值

* 成功返回非零，失败返回零。

### MSDN

[TerminateJobObject](https://learn.microsoft.com/en-us/windows/win32/api/jobapi2/nf-jobapi2-terminatejobobject)

### 示例

```cpp
BOOL bTerm = TerminateJobObject(hJob, 0);
if (!bTerm) {
    // 错误处理
}
```

---

## 7. 判断进程是否属于某作业对象（IsProcessInJob）

```cpp
BOOL IsProcessInJob(
  HANDLE hProcess,
  HANDLE hJob,
  PBOOL  Result
);
```

### 参数说明

* `hProcess`
  进程句柄。
* `hJob`
  作业对象句柄，通常传 `NULL` 表示判断是否属于任意作业。
* `Result`
  指向 BOOL 的指针，接收结果，`TRUE` 表示属于，`FALSE` 表示不属于。

### 返回值

* 成功返回非零，失败返回零。

### MSDN

[IsProcessInJob](https://learn.microsoft.com/en-us/windows/win32/api/jobapi2/nf-jobapi2-isprocessinjob)

### 示例

```cpp
BOOL bInJob = FALSE;
BOOL bResult = IsProcessInJob(hProcess, NULL, &bInJob);
if (bResult && bInJob) {
    // 进程属于某作业
} else {
    // 不属于或失败
}
```

---

# 总结

Windows 作业对象通过这些API可以方便地创建、管理和限制一组相关进程，实现资源控制、统一终止和生命周期管理等功能。

你说的“查看进度”通常指的是了解这两个进程的运行状态或完成情况，Windows 作业对象本身并不直接提供“进度百分比”这类细粒度信息，但可以通过以下几种方式监控和判断：

---

## 1. **查询作业对象的进程信息**

你可以用 `QueryInformationJobObject` 查询作业中活跃的进程数，判断是否还有进程未结束。

示例：获取作业中活跃进程数（使用 `JobObjectBasicAccountingInformation`）

```cpp
JOBOBJECT_BASIC_ACCOUNTING_INFORMATION info = {0};
DWORD retLen = 0;
BOOL success = QueryInformationJobObject(hJob, JobObjectBasicAccountingInformation, &info, sizeof(info), &retLen);
if (success) {
    // info.ActiveProcesses 是作业中当前活跃的进程数量
    printf("活跃进程数: %lu\n", info.ActiveProcesses);
}
```

* 如果活跃进程数为0，说明所有进程已结束。
* 如果大于0，说明仍有进程在运行。

---

## 2. **分别监控各个进程状态**

* 通过 `WaitForSingleObject(hProcess, 0)` 或 `GetExitCodeProcess` 查看每个进程是否已结束。
* `GetExitCodeProcess` 返回值是 `STILL_ACTIVE` 表示进程还在运行。

```cpp
DWORD exitCode;
if (GetExitCodeProcess(hProcess, &exitCode)) {
    if (exitCode == STILL_ACTIVE) {
        printf("进程还在运行\n");
    } else {
        printf("进程已退出，退出码: %lu\n", exitCode);
    }
}
```

---

## 3. **“进度”信息需要进程自己报告**

* Windows 作业对象和系统本身不会跟踪进程内“任务完成百分比”。
* 如果需要显示“进度”，通常是程序内部设计进度上报，比如写共享内存、管道、文件或消息机制，主控进程读取这些信息。

---

## 总结

| 方式                        | 说明                   |
| ------------------------- | -------------------- |
| QueryInformationJobObject | 查询作业内活跃进程数量，判断进程整体状态 |
| GetExitCodeProcess        | 查询单个进程是否结束           |
| 进程内部通信                    | 设计进程自己报告进度，如管道或共享内存  |

---
