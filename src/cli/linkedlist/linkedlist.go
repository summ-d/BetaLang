package linkedlist

type Node[Data any] struct {
	prev *Node[Data]
	data Data
	next *Node[Data]
}

func NewNode[Data any](d Data) Node[Data] {
	n := Node[Data]{prev: nil, data: d, next: nil}
	return n
}

type LinkedList[Data any] struct {
	head *Node[Data]
	tail *Node[Data]
}

type function[Data any] func(d Data)

func MakeEmptyList[Data any]() LinkedList[Data] {
	ll := LinkedList[Data]{head: nil, tail: nil}
	return ll
}

func MakeList[Data any](d Data) LinkedList[Data] {
	h := NewNode[Data](d)
	t := Node[Data]{prev: &h, next: nil}
	h.next = &t
	ll := LinkedList[Data]{head: &h, tail: &t}
	return ll
}

func (ll LinkedList[Data]) Push(d Data) {

}

func (ll LinkedList[Data]) Insert(d Data, pos int) {

}

func (ll LinkedList[Data]) Append(d Data) {

}

func (ll LinkedList[Data]) Front() Data {
	return ll.head.data
}

func (ll LinkedList[Data]) At(pos int) {

}

func (ll LinkedList[Data]) ForEach(fun function[Data]) {
	for temp := ll.head; temp.next != nil; temp = temp.next {
		fun(temp.data)
	}
}
