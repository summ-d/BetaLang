package linkedlist;

type Node[Data any] struct{
	prev *Node[Data];
	data Data;
	next *Node[Data];
}

type LinkedList[Data any] struct{
	head *Node[Data];
}