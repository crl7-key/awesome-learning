#ifndef HEAP_INDEXMINHEAP_H_
#define HEAP_INDEXMINHEAP_H_

#include <algorithm>
#include <cassert>

// 最小索引堆
template<typename Item>
class IndexMinHeap{
public:
    // 构造函数, 构造一个空的索引堆, 可容纳m_capacity个元素
    IndexMinHeap(int m_capacity) {

        m_data = new Item[m_capacity+1];
        m_indexes = new int[m_capacity+1];
        m_reverse = new int[m_capacity+1];

        for( int i = 0 ; i <= m_capacity ; i ++ )
            m_reverse[i] = 0;

        m_count = 0;
        this->m_capacity = m_capacity;
    }

    ~IndexMinHeap(){
        delete[] m_data;
        delete[] m_indexes;
        delete[] m_reverse;
    }

    // 返回索引堆中的元素个数
    int size(){
        return m_count;
    }

    // 返回一个布尔值, 表示索引堆中是否为空
    bool is_empty(){
        return m_count == 0;
    }

    // 向最小索引堆中插入一个新的元素, 新元素的索引为i, 元素为item
    // 传入的i对用户而言,是从0索引的
    void insert(int index, Item item){
        assert( m_count + 1 <= m_capacity );
        assert( index + 1 >= 1 && index + 1 <= m_capacity );

        index += 1;
        m_data[index] = item;
        m_indexes[m_count+1] = index;
        m_reverse[index] = m_count+1;
        m_count++;
        up_update(m_count);
    }

    // 从最小索引堆中取出堆顶元素, 即索引堆中所存储的最小数据
    Item extractMin(){
        assert( m_count > 0 );

        Item ret = m_data[m_indexes[1]];
        std::swap( m_indexes[1] , m_indexes[m_count] );
        m_reverse[m_indexes[m_count]] = 0;
        m_count--;

        if(m_count){
            m_reverse[m_indexes[1]] = 1;
            down_update(1);
        }

        return ret;
    }

    // 从最小索引堆中取出堆顶元素的索引
    int extractMinIndex(){
        assert( m_count > 0 );

        int ret = m_indexes[1] - 1;
        std::swap( m_indexes[1] , m_indexes[m_count] );
        m_reverse[m_indexes[m_count]] = 0;
        m_count--;

        if(m_count){
            m_reverse[m_indexes[1]] = 1;
            down_update(1);
        }

        return ret;
    }

    // 获取最小索引堆中的堆顶元素
    Item getMin(){
        assert( m_count > 0 );
        return m_data[m_indexes[1]];
    }

    // 获取最小索引堆中的堆顶元素的索引
    int getMinIndex(){
        assert( m_count > 0 );
        return m_indexes[1]-1;
    }

    // 查看索引i所在的位置是否存在元素
    bool contain(int index){

        return m_reverse[index+1] != 0;
    }

    // 获取最小索引堆中索引为i的元素
    Item getItem(int index){
        assert( contain(index) );
        return m_data[index+1];
    }

    // 将最小索引堆中索引为i的元素修改为newItem
    void change(int index , Item newItem){

        assert( contain(index) );
        index += 1;
        m_data[index] = newItem;

        up_update( m_reverse[index] );
        down_update( m_reverse[index] );
    }

private:
    Item *m_data;     // 最小索引堆中的数据
    int *m_indexes;   // 最小索引堆中的索引, m_indexes[x] = i 表示索引i在x的位置
    int *m_reverse;   // 最小索引堆中的反向索引, m_reverse[i] = x 表示索引i在x的位置
    int m_count;
    int m_capacity;

    // 索引堆中, 数据之间的比较根据m_data的大小进行比较, 但实际操作的是索引
    void up_update( int k ){

        while( k > 1 && m_data[m_indexes[k/2]] > m_data[m_indexes[k]] ){
            std::swap(m_indexes[k/2] , m_indexes[k]);
            m_reverse[m_indexes[k/2]] = k/2;
            m_reverse[m_indexes[k]] = k;
            k /= 2;
        }
    }

    // 索引堆中, 数据之间的比较根据m_data的大小进行比较, 但实际操作的是索引
    void down_update( int k ){

        while( 2*k <= m_count ){
            int j = 2*k;
            if( j + 1 <= m_count && m_data[m_indexes[j]] > m_data[m_indexes[j+1]] )
                j += 1;

            if( m_data[m_indexes[k]] <= m_data[m_indexes[j]] )
                break;

            std::swap( m_indexes[k] , m_indexes[j] );
            m_reverse[m_indexes[k]] = k;
            m_reverse[m_indexes[j]] = j;
            k = j;
        }
    }


};

template<typename T>
void heapSortUsingIndexMinHeap(T arr[], int n){

    IndexMinHeap<T> indexMinHeap = IndexMinHeap<T>(n);
    for( int i = 0 ; i < n ; i ++ )
        indexMinHeap.insert( i , arr[i] );

    for( int i = 0 ; i < n ; i ++ )
        arr[i] = indexMinHeap.extractMin();
}


#endif //HEAP_INDEXMINHEAP_H