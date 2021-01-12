package single_linked_list

import (
	"container/list"
	"fmt"
	"testing"
)

func TestLinkList(t *testing.T) {
	// 创建一个链表
	alist := list.New()

	fmt.Println("Size before : ", alist.Len())

	//向链表中添加元素
	alist.PushBack("a")
	alist.PushBack("b")
	alist.PushBack("c")

	fmt.Println("Size after insert(push): ", alist.Len())

	// 遍历
	for e := alist.Front(); e != nil; e = e.Next() {
		fmt.Println(e.Value.(string))
	}

	//移除元素
	alist.Remove(alist.Front())
	alist.Remove(alist.Front())
	alist.Remove(alist.Front())

	fmt.Println("Size after remove(pop) : ", alist.Len())
}

func TestSingleLinkList(t *testing.T) {
	// 创建一个链表
	alist := New()

	fmt.Println("LinkList Size : ", alist.Len())

	// 向链表中添加元素
	data := &Node{
		Value: "test",
	}
	alist.Append(data)
	fmt.Println("LinkList Size : ", alist.Len())

	// 遍历
	for e := alist.Front(); e != nil; e = e.Next() {
		fmt.Println(e.Value.(string))
	}
	//移除元素
	alist.Remove(alist.Front())
	fmt.Println("Size after remove(pop) : ", alist.Len())

}
