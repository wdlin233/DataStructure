#include "vector.h"
#include "worker.h"
#include <string>
#include <iostream>
#include <cstdlib>

/*提示：这里的 data 是一个指向指针的指针。
 在操作指针前请三思！
 如果你不知道的话：malloc 的功能和 new 类似，
 这里使用 malloc 是为了方便空间不足时进行扩展。
 不用担心，扩展函数已为你写好。
 －－前一位实习生
 */

int vector::insert(Worker *new_worker) {
    if(size==length)
    {
        expand();		
        *(data+length)=new_worker;
		length += 1;
        return 1;
    }
    else
    {		
        *(data+length)=new_worker;
		length += 1;
        return 0;
    }
}

Worker *vector::get(int index) {
	if (index >= 0 && index < length)
	{
		return *(data + index);
	}
	else
		return nullptr;
}

//TODO
Worker *vector::remove(int index) {
	if (index >= 0 && index < length)
	{
		Worker *tmp = *(data + index);
		for (int i = index; i < length-1; i++)
		{
			*(data + i) = *(data + i + 1);
		}
		length -= 1;
		return tmp;
	}
	else
		return nullptr;
}

/*以下内容不建议修改。*/

vector::~vector() {
    for (int i = 0; i < length; i++) {
        delete *(data+i);
    }
    free(data);
}

vector::vector(int input_size) {
    size = input_size;
    length = 0;
    data = (Worker **)calloc(sizeof(Worker *), input_size);
}

void vector::expand() {
    size = size * 2;
    data = (Worker **)realloc(data, sizeof(Worker *) * size);
    return;
}

void vector::print() {
    std::cout << "Current vector:\n";
    for (int i = 0; i < length; i++) {
        std::cout << "[" << i << "] ";
        (*(data+i))->print();
    }
    std::cout << "Current vector Ends\n";
}