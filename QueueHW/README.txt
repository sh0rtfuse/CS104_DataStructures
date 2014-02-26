Homework 7 Questions

2a. The heap property states that for a minheap, each node is greater than or equal to its parent node and for a maxheap, each node is is less than or equal to its parent node.

2b. Formula for Child Nodes: 2x+d, where x is the index and d is the child number (2x+1 for 1st child, 2x+2 for 2nd, etc)

Formula for Parent Nodes: (x-1)/d (Technically, we take the floor of this as well but we’re using positive integers)

**Root of my tree is array index 0**

2c. Progressions of node (n) = 1+d+d^2+…+d^h, where h is the height of the complete d-ary tree.
	(d^(h+1)-1)/(d-1) = n -> logd(d^(h+1)-1)/logd(d-1) = logd(n) - > h = logd(nd)-1
	-> h = logd(n)+logd(d)-1 -> h = logd(n) OR Theta(logd(n))

	h = Theta(logd(n))

2d. Since the height is Theta(logd(n)), your add should be O(logd(n)). Peek is O(n), since you’re returning the highest priority element and traverse the tree to get the value. Remove is O(nlogd(n)) because of constant time finding the value plus time to delete.

2e. As d increae, Remove becomes faster at a greater rate than Add, while Peek remains constant.

3a. The List implementation using a Linked List is the best choice because it generally faster at at access and insertion compared to an array-based implementation. A linkedlist implementation also benefits from more efficient resizing at runtime to accommodate a growing heap compare to a vector. 