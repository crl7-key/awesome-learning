#ifndef INC_MAx_HEAP_BASIC_H_
#define INC_MAx_HEAP_BASIC_H_

#include <algorithm>
#include <cassert>

// 大顶堆:每个父节点的值要大于其两个子节点的值
// 任一结点的关键码均大于等于它的左右孩子的关键码,其中堆顶的元素最大。（任一路径中的元素升序排列）
template<typename Item>
class MaxHeap {
public:
    MaxHeap(int m_capacity) {
        m_data = new Item[m_capacity + 1];
        m_count = 0;
        this->m_capacity = m_capacity;
    }

     /** 
      * 传入一个数组,将n个元素逐个插入到一个空堆中，算法复杂度是O(nlogn)
      * heapify的过程，算法复杂度为O(n)
      **/
    MaxHeap(Item arr[],int n){
        m_data = new Item[n+1];
        m_capacity = n;

        for(int i = 0;i < n;i ++)
            m_data[i+1] = arr[i];
        m_count = n;

        // 从不是叶子节点操作  
        for(int i = m_count / 2;i >= 1;i--)
            down_update(i);
    }

    ~MaxHeap() {
        delete [] m_data;
        m_data = nullptr;
        m_count = 0;
    }

    int size() {
        return m_count;
    }

    bool is_empty() {
        return m_count == 0;
    }

    // 插入子节点
    void insert(Item item) {
        //assert( m_count + 1 < m_capacity);
        m_data[m_count + 1] = item;

        up_update(m_count+1);
        m_count++;
    }

     // 提取根节点-最大值,与最后一个元素进行交换,m_count--,之后进行down_update操作,即堆的删除最值操作
    Item extractMax() {
       // assert(m_count > 0);
        Item ret = m_data[1];

        std::swap(m_data[1],m_data[m_count]);
        m_count--;
        down_update(1);
        return ret;
    }

     // 获取最大值
    Item getMax() {
       // assert(m_count > 0);
        return m_data[1];
    }

private:
    Item *m_data;  // 存储数据的数组
    int  m_count;   // 现有元素数量
    int m_capacity; // 最大容量

    // 向上调整
    void up_update(int element) {
        // 当前元素值大于其父节点值的时候
        while(element > 1 && m_data[element / 2] < m_data[element]) {
            std::swap(m_data[element/2],m_data[element]);  // 将最大值和其父节点交换
            element /= 2;
        }
    }

    // 向下调整
    void down_update(int element) {
         while( 2 * element <= m_count ) {  // 与子节点比较
            int j = 2 * element;            // 在此轮循环中,m_data[element] 和m_data[j]交换位置
            if(j+1 <= m_count && m_data[j+1] > m_data[j])
                j ++;
            // data[j]是data[2 * element]和data[2 * element+1]中的最大值
            
            if(m_data[element] >= m_data[j])
                break;
            std::swap(m_data[element],m_data[j]);
            element = j;

        }   
    }
};

#endif // !INC_MAx_HEAP_BASIC_H_