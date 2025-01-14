#include<algorithm>
int main() {
    freopen("in.txt", "r", stdin);
    SqList L;  
	InitList(L); //初始化列表 
	//文件末尾代表EOF, 在文件末尾自动结束循环 
	while (scanf("%s %s %d", L.elem[L.length].no, L.elem[L.length].name, &L.elem[L.length].score) != EOF){
			L.length++;
	}
 	//进行输出 
	 for(int i = 0; i < L.length; i++){
		printf("%s %s %d\n", L.elem[i].no, L.elem[i].name, L.elem[i].score);
	}
	freopen("CON","r",stdin); //切换到从控制台输入数据 
}

#include <iostream>
#include <fstream>    //头文件
using namespace std;

#include <bits/stdc++.h>
using namespace std;
int main() {
    freopen("test.in","r",stdin);//设置 cin scanf 这些输入流都从 test.in中读取
    freopen("test.out","w",stdout);//设置 cout printf 这些输出流都输出到 test.out里面去
    //写待测程序，即标程
}