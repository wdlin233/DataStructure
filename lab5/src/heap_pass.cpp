#include "heap.h"
#define LEFT true
#define RIGHT false

#define LIST_SIZE 2000

Heap::~Heap()
{
    delete[] arr;
    num = 0;
}



Heap::Heap(Heap &other)
{
    arr = new Player_info[2000];
    for (int i = 0; i < 2000; i++)
    {
        arr[i] = other.arr[i];
    }
    num = other.num;
}

Heap &Heap::operator=(Heap &other)
{
    arr = new Player_info[2000];
    for (int i = 0; i < 2000; i++)
    {
        arr[i] = other.arr[i];
    }
    num = other.num;
    return *this;
}

void swap(Player_info &a, Player_info &b) {
    Player_info temp = a;
    a = b;
    b = temp;
}

void Heap::heapify_up()
{
    int index = num - 1;
    if (index < 0) return;
    int father = 0;
    while (true)
    {
        father = get_father(index);
        if (father >= 0 && arr[index] < arr[father])
        {
            swap(arr[index], arr[father]);
            index = father;
            continue;
        }
        return;
    }
}

void Heap::heapify_down()
{
    int index = 0;
    int left, right, smallest;
    while (true)
    {
        left = get_child(LEFT, index);
        right = get_child(RIGHT, index);
        if ((0 <= left && left < num) && (0 <= right && right < num))
        {
            smallest = (arr[left] < arr[right]) ? left : right;
        }
        else if (0 <= left && left < num)
        {
            smallest = left;
        }
        else
        {
            smallest = right;
        }
        if (0 <= smallest && smallest < num && arr[index] > arr[smallest])
        {

                swap(arr[index], arr[smallest]);
                index = smallest;
                continue;
        }
        return;
    }
}

int Heap::get_child(bool direction, int index)
{
    if (!(0 <= index && index < num))
        return -1;
    int child;
    child = direction == LEFT ? 2 * index + 1 : 2 * index + 2;
    if (0 <= child && child < num)
    {
        return child;
    }
    else
        return -1;
}

int Heap::get_father(int index)
{
    if (!(0 <= index && index < num) || !index) return -1;
    int father = (index - 1) / 2;
    if (0 <= father && father < num)
    {
        return father;
    }
    else
        return -1;
}

int Heap::insert(Player_info &p)
{
    if (num < LIST_SIZE)
    {
        arr[num] = p;
        heapify_up();
        num += 1;
        return 1;
    }
    else if (p > arr[0]) {
            arr[0] = p;
            heapify_down();
            return 1;
        }
    return 0;
}

Player_info *Heap::sort()
{
    int num_copy = num;
    while (1)
    {
        num -= 1;
        if (num <= 0)
            break;
        swap(arr[0], arr[num]);
        heapify_down();
    }
    num = num_copy;

    Player_info *result = new Player_info[LIST_SIZE];
    for (int i = 0; i < num; i++)
        result[i] = arr[i];
    return result;
}

/*
 =========================================================
 ================ WARNING ===== 警告 ======================
 ===Please Do Not Modify Any of the Following Functions===
 ===================请不要修改以下函数=======================
 =========================================================
 */

int Heap::get_num() const
{
    return num;
}

Heap::Heap()
{
    num = 0;
    arr = new Player_info[LIST_SIZE];
}

void Heap::print()
{
    for (int i = 0; i < num; i++)
    {
        arr[i].print();
    }
    printf("\nSize of the heap is %d\n", num);
}

Player_info::Player_info()
{
    username = std::string("#");
    uid = 0;
    score = 0;
}

Player_info::~Player_info()
{
}

Player_info::Player_info(Player_info &other)
{
    username = std::string((other.username));
    score = other.score;
    uid = other.uid;
}

Player_info::Player_info(std::string in_name, long in_uid, int in_score)
{
    username = std::string(in_name);
    score = in_score;
    uid = in_uid;
}

Player_info &Player_info::operator=(Player_info &other)
{
    username = std::string((other.username));
    score = other.score;
    uid = other.uid;
    return *this;
}

int Player_info::get_score() const
{
    return score;
}

const std::string &Player_info::get_name() const
{
    return username;
}

bool Player_info::operator==(Player_info &other) const
{
    if (score == other.score)
    {
        return true;
    }
    return false;
}

bool Player_info::operator!=(Player_info &other) const
{
    if (score == other.score)
    {
        return false;
    }
    return true;
}

bool Player_info::operator<(Player_info &other) const
{
    if (score < other.score)
    {
        return true;
    }
    return false;
}

bool Player_info::operator<=(Player_info &other) const
{
    if (score <= other.score)
    {
        return true;
    }
    return false;
}

bool Player_info::operator>(Player_info &other) const
{
    if (score > other.score)
    {
        return true;
    }
    return false;
}

bool Player_info::operator>=(Player_info &other) const
{
    if (score >= other.score)
    {
        return true;
    }
    return false;
}

void Player_info::print()
{
    printf("[%ld]%s - %d\n", uid, username.c_str(), score);
    return;
}