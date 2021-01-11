package single_linked_list

// 声明Node节点
type Node struct {
	Value interface{}

	next *Node
}

func (n *Node) Next() *Node {
	return n.next
}

type SingleLinkedList struct {
	front  *Node
	length int
}

// Init 初始化
func (s *SingleLinkedList) Init() *SingleLinkedList {
	s.length = 0
	return s
}

// New 创建一个链表
func New() *SingleLinkedList {
	return new(SingleLinkedList).Init()
}

// Front 返回头节点
func (s *SingleLinkedList) Front() *Node {
	return s.front
}

// Back 返回尾节点
func (s *SingleLinkedList) Back() *Node {
	currentNode := s.front
	for currentNode != nil && currentNode.next != nil {
		currentNode = currentNode.next
	}
	return currentNode
}

// Append 添加尾节点
func (s *SingleLinkedList) Append(n *Node) {
	if s.front == nil {
		s.front = n
	} else {
		currentNode := s.front

		for currentNode.next != nil {
			currentNode = currentNode.next
		}
		currentNode.next = n
	}
	s.length++
}

// Prepend 添加头节点
func (s *SingleLinkedList) Prepend(n *Node) {
	if s.front == nil {
		s.front = n
	} else {
		n.next = s.front
		s.front = n
	}
	s.length++
}

// InsertBefore 在指定节点前添加节点
func (s *SingleLinkedList) InsertBefore(insert *Node, before *Node) {
	if s.front == before {
		insert.next = before
		s.front = insert
		s.length++
	} else {
		currentNode := s.front
		for currentNode != nil && currentNode.next != nil && currentNode.next != before {
			currentNode = currentNode.next
		}

		if currentNode.next == before {
			insert.next = before
			currentNode.next = insert
			s.length++
		}
	}
}

// InsertAfter 在指定节点后添加节点
func (s *SingleLinkedList) InsertAfter(insert *Node, after *Node) {
	currentNode := s.front
	for currentNode != nil && currentNode != after && currentNode.next != nil {
		currentNode = currentNode.next
	}

	if currentNode == after {
		insert.next = after.next
		after.next = insert
		s.length++
	}
}

// Remove 删除节点
func (s *SingleLinkedList) Remove(n *Node) {
	if s.front == n {
		s.front = n.next
		s.length--
	} else {
		currentNode := s.front

		// search for node n
		for currentNode != nil && currentNode.next != nil && currentNode.next != n {
			currentNode = currentNode.next
		}

		// see if current's next node is n
		// if it's not n, then node n wasn't found in list s
		if currentNode.next == n {
			currentNode.next = currentNode.next.next
			s.length--
		}
	}
}

func (s *SingleLinkedList) Len() int {
	return s.length
}
