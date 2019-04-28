#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 通讯录，需要在代码中表示若干个人
typedef struct PersonInfo {
    char name[1024];
    char phone[1024];
} PersonInfo;

#define  SIZE 1000

typedef struct AddrBook {
    // SIZE 表示的是通讯录中信息的上限
    PersonInfo person_info[SIZE];
    // 需要标注出哪些信息是有意义的，哪些信息是没有意义的
    // 通讯录并不是程序一启动，里面的 1000 条数据都是有意义的
    // [0, size) 有意义的区间
    int size;
} AddrBook;

AddrBook g_addr_book;

enum {
    EXIT = 0,
    ADD,
    DEL,
    MODIFY,
    FIND,     // 查找某条记录
    PRINT,    // 打印所有内容
    CLEAR,    // 清空所有内容
};

void Init() {
    g_addr_book.size = 0;
    // 数组初始化
    //  1. 定义时使用 {} 进行初始化
    //  2. 若数组定义时未进行初始化，那么在后边的初始化时就不能使用 {}
    //     进行初始化了，此时有以下两种方法进行初始化
    //     a) for 循环对每个元素一一进行初始化
    // for (int i = 0; i < SIZE; ++i) {
    //     strcpy(g_addr_book.person_info[i].name, "");
    //     strcpy(g_addr_book.person_info[i].phone, "");
    // }

    //     b) 使用 memset 将数组中的是每一个元素都设置成 0
    memset(g_addr_book.person_info, 0x0, sizeof(g_addr_book.person_info));
}

int Menu() {
    // TODO 打印出给用户提供的操作，
    // 并且提示用户进行输入，
    // 把用户输入的结果时返回出来
    printf("================================\n");
    printf("1. 添加\n");
    printf("2. 删除\n");
    printf("3. 修改\n");
    printf("4. 查找\n");
    printf("5. 显示\n");
    printf("6. 清除\n");
    printf("0. 退出\n");
    printf("================================\n");
    printf("请输入您的选择: ");
    int choice = 0;
    scanf("%d", &choice);
    return choice;
}

void AddPersonInfo() {
    // 添加一个用户信息到通讯录中
    // 提示用户输入相关的用户信息，然后把对应的数据更新到数组中
    if(g_addr_book.size >= SIZE) {
        printf("当前通讯录已满，插入失败!\n");
        return;
    }
    printf("添加一个新用户！\n");
    printf("请输入用户名: ");
    // 下标为 size 的位置就是我们需要放置的新元素的位置
    scanf("%s", g_addr_book.person_info[g_addr_book.size].name);
    printf("请输入电话号码: ");
    scanf("%s", g_addr_book.person_info[g_addr_book.size].phone);
    ++g_addr_book.size;
    printf("插入成功!\n");
    return;
}

// 按照用户信息的编号进行删除
void DelPersonInfo() {
    printf("删除指定的记录!\n");
    printf("请输入要删除的条目的编号: ");
    int num = 0;
    scanf("%d", &num);
    if (num < 0 || num >= g_addr_book.size) {
        printf("输入的编号不合法！删除失败!\n");
        return;
    }
    // 此时采取一种比较简单的方案
    // 1. 如果用户要删除的是最后一个元素，那么就直接 --size 
    if (num == g_addr_book.size - 1) {
        // 这个元素的内容需要覆盖掉，覆盖或者不覆盖都可以。
        --g_addr_book.size;
    } else {
        // 2. 如果用户要删除的是某个中间位置的元素，
        //    就把最后一个元素填充到该位置上，再删除最后一个元素
        strcpy(g_addr_book.person_info[num].name, 
                g_addr_book.person_info[g_addr_book.size - 1].name);
        strcpy(g_addr_book.person_info[num].phone, 
                g_addr_book.person_info[g_addr_book.size - 1].phone);
        --g_addr_book.size;
    }
    // 简化代码
    // if (num != g_addr_book.size - 1) {
    //    strcpy(g_addr_book.person_info[num].name,
    //            g_addr_book.person_info[g_addr_book.size - 1].name);
    //    strcpy(g_addr_book.person_info[num].phone, 
    //            g_addr_book.person_info[g_addr_book.size - 1].phone);
    // }
    // --g_addr_book.size;
    printf("删除成功!\n");
    return;
}

// 修改某个用户信息. 用户输入一个进行修改的编号，然后根据编号进行修改
void ModifyPersonInfo() {
    printf("修改某条记录!\n");
    printf("请输入要修改的信息的编号: ");
    int num = 0;
    scanf("%d", &num);
    if (num < 0 || num >= g_addr_book.size) {
        printf("输入的编号不合法，修改失败!\n");
        return;
    }
    printf("请输入新的用户名: ");
    scanf("%s", g_addr_book.person_info[num].name);
    printf("请输入新的电话号码: ");
    scanf("%s", g_addr_book.person_info[num].phone);
    printf("修改成功!\n");
}

// 根据用户名查找对应的电话号码
void FindPersonInfo() {
    printf("查找电话号码!\n");
    printf("请输入要查找的姓名: ");
    char name[1024] = { 0 };
    scanf("%s", name);
    int count = 0;
    for (int i = 0; i < g_addr_book.size; ++i) {
        if (strcmp(name, g_addr_book.person_info[i].name) == 0) {
            printf("找到一条结果! 电话号码为: %s\n", 
                    g_addr_book.person_info[i].phone);
            ++count;
        }
    }
    if (count == 0) {
        printf("没找到指定的姓名!\n");
    } else {
        printf("查找成功! 共找到 %d 条记录\n", count);
    }
}

// 打印所有的用户信息
void PrintPersonInfo() {
    printf("打印所有的用户信息!\n");
    for (int i = 0; i < g_addr_book.size; ++i) {
        printf("%d [%s] %s\n", i, g_addr_book.person_info[i].name,
                g_addr_book.person_info[i].phone);
    }
    printf("打印完成! 共打印了 %d 条记录!\n", g_addr_book.size);
    return;
}


void ClearPersonInfo() {
    printf("清楚所有用户信息!\n");
    printf("您真的要删除所有用户信息吗? (y/n) \n");
    char input[1024] = { 0 };
    scanf("%s", input);
    if (strcmp(input, "y") != 0) {
        printf("已经取消了删除操作!\n");
        return;
    }
    g_addr_book.size  = 0;
    printf("清空成功!\n");
}

// 按照姓名进行排序
// void Sort()  {
//
// }

int main() {
    // 1. 先创建一个 通讯录 的变量，并且也需要对这个变量进行初始化
    Init();
    while (1) {
        // 2. 进入循环，打印一个用户菜单，并且提示用户进行操作
        //    增删查改
        int choice = Menu();
        // 3. 用户输入了相应的编号之后，就调用对应的操作函数，完成具体的增删查改
        switch (choice) {
            case ADD:
                AddPersonInfo();
                break;
            case DEL:
                DelPersonInfo();
                break;
            case MODIFY:
                ModifyPersonInfo();
                break;
            case FIND:
                FindPersonInfo();
                break;
            case PRINT:
                PrintPersonInfo();
                break;
            case CLEAR:
                ClearPersonInfo();
                break;
            case EXIT:
                printf("GoodBye!\n");
                return 0;
            default:
                break;
        }
    }
}
