package main

/**
 * Definition for singly-linked list.
 **/ 
 type ListNode struct {
	 Val int
    Next *ListNode
}

func hasCycle(head *ListNode) bool {
	if head == nil  {
        return false;
    }
    
    walker := head;
    runner := head;
   for runner.Next != nil && runner.Next.Next != nil {
		runner = runner.Next.Next
		walker = walker.Next
		if walker == runner {
			return true
		}
	}
	return false
    
}

func main() {
	
}

