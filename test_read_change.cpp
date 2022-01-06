#include <tchar.h>
#include <windows.h>
#include <Psapi.h>

#include <iostream>
#include <string>
#include<iomanip>  

#define MAX_PROC_NUM 1024

#pragma comment(lib, "psapi.lib ")

using std::cout;
using std::endl;
using std::string;

void ShowProcessInfo(DWORD pid) {
    /*
    Opens an existing local process object.

    @dwDesiredAccess:the access to the process object. This access right is
    checked against the security descriptor for the process. This parameter can
    be one or more of the process access rights. PROCESS_ALL_ACCESS
    所有能获得的权限 (STANDARD_RIGHTS_REQUIRED (0x000F0000L) | SYNCHRONIZE  (0x00100000L) | 0xFFFF)
        PROCESS_CREATE_PROCESS  需要创建一个进程 0x0080
        PROCESS_CREATE_THREAD   需要创建一个线程 0x0002
        PROCESS_DUP_HANDLE      重复使用DuplicateHandle句柄
        PROCESS_QUERY_INFORMATION   获得进程信息的权限，如它的退出代码、优先级 (0x0400)
        PROCESS_QUERY_LIMITED_INFORMATION
    获得某些信息的权限，如果获得了PROCESS_QUERY_INFORMATION，也拥有PROCESS_QUERY_LIMITED_INFORMATION权限
        PROCESS_SET_INFORMATION    设置某些信息的权限，如进程优先级
        PROCESS_SET_QUOTA 设置内存限制的权限，使用SetProcessWorkingSetSize
        PROCESS_SUSPEND_RESUME     暂停或恢复进程的权限
        PROCESS_TERMINATE          终止一个进程的权限，使用TerminateProcess
        PROCESS_VM_OPERATION  操作进程内存空间的权限(可用VirtualProtectEx和WriteProcessMemory) (0x0008)
        PROCESS_VM_READ 读取进程内存空间的权限，可使用ReadProcessMemory  (0x0010)
        PROCESS_VM_WRITE 读取进程内存空间的权限，可使用WriteProcessMemory (0x0020)
        SYNCHRONIZE                等待进程终止(0x00100000L)
    @bInheritHandle:If this value is TRUE, processes created by this process
    will inherit the handle. Otherwise, the processes do not inherit this
    handle.
    @dwProcessId:The identifier of the local process to be opened

    @return: If the function succeeds, the return value is an open handle to the
    specified process.If the function fails, the return value is NULL.

    If the specified process is the System Idle Process (0x00000000), the
    function fails and the last error code is ERROR_INVALID_PARAMETER. If the
    specified process is the System process or one of the Client Server Run-Time
    Subsystem (CSRSS) processes, this function fails and the last error code is
    ERROR_ACCESS_DENIED because their access restrictions prevent user-level
    code from opening them
    */
    cout << "Pid: " << pid;

    auto hProcess = OpenProcess(PROCESS_ALL_ACCESS, false, pid);
    if (hProcess == NULL) return;

    TCHAR moduleBaseName[MAX_PROC_NUM] = {0};
    memset(moduleBaseName, 0, MAX_PROC_NUM * sizeof(TCHAR));
    /*
    GetModuleBaseName: Retrieves the base name of the specified module.

    @hProcess:A handle to the process that contains the module
    @hModule:A handle to the module. If this parameter is NULL, this function
    returns the name of the file used to create the calling process.
    @lpBaseName:A pointer to the buffer that receives the base name of the
    module.
    @nSize:The size of the lpBaseName buffer, in characters

    @return: If the function succeeds, the return value specifies the length of
    the string copied to the buffer, in characters.If the function fails, the
    return value is zero
    */
    if (GetModuleBaseName(hProcess, NULL, moduleBaseName, MAX_PROC_NUM)) {
        cout << " Name: " << moduleBaseName;
    }

    memset(moduleBaseName, 0, MAX_PROC_NUM * sizeof(TCHAR));
    /*
    Retrieves the fully qualified path for the file containing the specified
    module

    GetModuleBaseName获取当前进程已加载模块的文件的完整路径，该模块必须由当前进程加载。如果想要获取另一个已加载模块的文件路径，可以使用GetModuleFileNameEx函数

    @hProcess：A handle to the process that contains the module.The handle must
    have the PROCESS_QUERY_INFORMATION or PROCESS_QUERY_LIMITED_INFORMATION
    access rights
    @other param same to GetModuleBaseName
    */
    if (GetModuleFileNameEx(hProcess, NULL, moduleBaseName, MAX_PROC_NUM)) {
        cout << " File: " << moduleBaseName;
    }

    cout << endl;
    // Closes an open object handle.: If the function succeeds, the return value is nonzero.If the function fails, the return value is zero.
    CloseHandle(hProcess);
}

unsigned int ReadOtherProcess(HANDLE hProcess, DWORD base, void* ret, int size) {
    /*
    ReadProcessMemory是一个内存操作函数， 其作用为根据进程句柄读入该进程的某个内存空间
    当函数读取成功时返回1，if fail -> 0
    @hProcess:A handle to the process with memory that is being read. The handle must have PROCESS_VM_READ access to the process.
    @lpBaseAddress:A pointer to the base address in the specified process from which to read. Before any data transfer occurs, the system verifies that all data in the
                   base address and memory of the specified size is accessible for read access, and if it is not accessible the function fails
    @lpBuffer:A pointer to a buffer that receives the contents from the address space of the specified process
    @nSize:The number of bytes to be read from the specified process.
    @lpNumberOfBytesRead:A pointer to a variable that receives the number of bytes transferred into the specified buffer. If lpNumberOfBytesRead is NULL, the parameter is ignored.
    */
    SIZE_T ret_len = 0;
    ReadProcessMemory(hProcess, (LPCVOID)base, (LPVOID)ret, size, &ret_len);
    return ret_len;
}
unsigned int WriteOtherProcess(HANDLE hProcess, DWORD base, void* ret, int size) {
    /*
    Writes data to an area of memory in a specified process. The entire area to be written to must be accessible or the operation fails.

    @hProcess:A handle to the process memory to be modified. The handle must have PROCESS_VM_WRITE and PROCESS_VM_OPERATION access to the process.
    @lpBaseAddress:A pointer to the base address in the specified process to which data is written. Before data transfer occurs, the system verifies that all data in the base
                address and memory of the specified size is accessible for write access, and if it is not accessible, the function fails.
    @lpBuffer:A pointer to the buffer that contains data to be written in the address space of the specified process
    @nSize:The number of bytes to be written to the specified process.
    @lpNumberOfBytesWritten:A pointer to a variable that receives the number of bytes transferred into the specified process.
                This parameter is optional. If lpNumberOfBytesWritten is NULL, the parameter is ignored.
    
    @return: If the function succeeds, the return value is nonzero.If the function fails, the return value is 0 (zero). 
    */
    SIZE_T ret_len = 0;
    WriteProcessMemory(hProcess, (LPVOID)base, (LPVOID)ret, size, &ret_len);
    return ret_len;
}

unsigned int GetAllProcessPid(DWORD* dwProcessIdentify, int sizeofdwProcessIdentify) {
    DWORD dwTrueBytes = 0;
    /*
        EnumProcesses:成功返回非零数,失败返回零,可以使用函数
       GetLastError获取错误信息 三个参数: DWORD 类型的数组指针
       lpidProcess；DWORD 数组用于保存当前运行的进程 IDs 该数组的大小尺寸 cb；
        以及一个指向 DWORD 的指针 pBytesRrturned，它接收返回数据的长度。
    */
    if (!EnumProcesses(dwProcessIdentify, sizeofdwProcessIdentify * sizeof(DWORD), &dwTrueBytes)) {
        cout << "enum process fail " << endl;
        return 0;
    }
    return dwTrueBytes / sizeof(DWORD);
}

void ShowAllProcessInfo(){
    DWORD dwProcessIdentify[MAX_PROC_NUM] = {0};

    auto nProcessNum = GetAllProcessPid(dwProcessIdentify, MAX_PROC_NUM);
    for (int i = 0; i < nProcessNum; ++i) {
        ShowProcessInfo(dwProcessIdentify[i]);
    }
}

DWORD GetDesiredPidByName(string fname) {
    DWORD dwProcessIdentify[MAX_PROC_NUM] = {0};

    auto nProcessNum = GetAllProcessPid(dwProcessIdentify, MAX_PROC_NUM);

    for (int i = 0; i < nProcessNum; ++i) {
        auto pid=dwProcessIdentify[i];
        auto hProcess = OpenProcess(PROCESS_ALL_ACCESS, false, pid);
        if (hProcess == NULL) continue;

        char moduleBaseName[MAX_PROC_NUM] = {0};
        memset(moduleBaseName, 0, MAX_PROC_NUM * sizeof(char));

        if (GetModuleBaseName(hProcess, NULL, moduleBaseName, MAX_PROC_NUM)) {
            if(fname == string(moduleBaseName)){
                CloseHandle(hProcess);  
                return pid;
            }
        }
        if(hProcess!=NULL)CloseHandle(hProcess);        
    }
    return 0;
}

void TestWinChange(string fname){
    auto pid=GetDesiredPidByName(fname);

    auto hProcess = OpenProcess(PROCESS_ALL_ACCESS, false, pid);
    if(hProcess==NULL){
        cout<<"Can't find proc: "<<fname<<endl;
        return;
    }
    cout<<"Find Process: "<<fname<<" PID: "<<pid<<endl;
    unsigned int kep=0;

    DWORD base=0x006a9ec0;
    int len_once=sizeof(kep);

    if(ReadOtherProcess(hProcess, base, &kep, 4)){
        cout<<"ReadBase: "<<std::hex<<base;
        cout<<": "<<std::dec<< kep<<endl;
    }else{
        //〖299〗-仅完成部分的 ReadProcessMemoty 或 WriteProcessMemory 请求。
        cout<<"Error Reading Process: "<<fname<<" Error: "<< GetLastError()<<  endl;
    }

    if(hProcess!=NULL) CloseHandle(hProcess);  
}

int main() {
    TestWinChange("test_win.exe");

    return 0;
}