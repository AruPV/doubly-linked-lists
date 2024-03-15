#include <gtest/gtest.h>
#include <stdexcept>
#include "../incl/linked-lists.hpp"

class NodeTest : public testing::Test {
	protected:
		Node<int> int_node = Node(1);
		Node<bool> bool_node = Node(true);
		Node<float> float_node = Node(2.2f);
		Node<std::string> string_node = Node(std::string("hey"));
		Node<std::string> parent_node = Node(std::string("father"));
		Node<std::string> child_node = Node(std::string("child"), &parent_node);
};

class LinkedListTest : public testing::Test {
	protected:
		void SetUp() override{
			size_one_list.addLeft(1);
			size_two_list.addLeft(1);
			size_two_list.addLeft(2);
			for (int i =0; i<30; i++){
				big_list.addLeft(i);
			}
		}
	LinkedList<int> empty_list;
	LinkedList<int> size_one_list;
	LinkedList<int> size_two_list;
	LinkedList<int> big_list;
};

TEST_F(NodeTest, IntNodeTest){
	EXPECT_EQ(int_node.toString(), "1");
	EXPECT_EQ(int_node.next, nullptr);
}

TEST_F(NodeTest, BoolNodeTest){
	EXPECT_EQ(bool_node.toString(), "1");
	EXPECT_EQ(bool_node.next, nullptr);
}

TEST_F(NodeTest, FloatNodeTest){
	EXPECT_EQ(float_node.toString(), "2.200000");
	EXPECT_EQ(float_node.next, nullptr);
}

TEST_F(NodeTest, StringNodeTest){
	EXPECT_EQ(string_node.toString(), "hey");
	EXPECT_EQ(string_node.next, nullptr);
}

TEST_F(NodeTest, ChildNodeTest){
	EXPECT_EQ(child_node.next, &parent_node);
}

// Add left test

TEST_F(LinkedListTest, AddLeftToEmpty){
	empty_list.addLeft(1);
	EXPECT_EQ(empty_list.getHead(), empty_list.getTail());
}

TEST_F(LinkedListTest, AddLeftToOnceAdded){
	auto temp = size_one_list.getHead(); 
	size_one_list.addLeft(2);
	EXPECT_EQ(size_one_list.getHead()->next, temp);
}

TEST_F(LinkedListTest, AddLeftToTwiceAdded){
	auto temp = size_two_list.getHead(); 
	size_two_list.addLeft(3);
	EXPECT_EQ(size_two_list.getHead()->next, temp);
}

TEST_F(LinkedListTest, AddLeftToManyAdded){
	auto temp = big_list.getHead(); 
	big_list.addLeft(3);
	EXPECT_EQ(big_list.getHead()->next, temp);
}

//Add right tests
TEST_F(LinkedListTest, AddRightToEmpty){
	empty_list.addRight(1);
	EXPECT_EQ(empty_list.getHead(), empty_list.getTail());
}

TEST_F(LinkedListTest, AddRightToOnceAdded){
	auto temp = size_one_list.getTail(); 
	EXPECT_EQ(size_one_list.getTail(), temp);
	size_one_list.addRight(2);
	EXPECT_EQ(temp->next, size_one_list.getTail());
}

TEST_F(LinkedListTest, AddRightToTwiceAdded){
	auto temp = size_two_list.getTail(); 
	EXPECT_EQ(size_two_list.getTail(), temp);
	size_two_list.addRight(3);
	EXPECT_EQ(temp->next, size_two_list.getTail());
}

TEST_F(LinkedListTest, AddRightToManyAdded){
	auto temp = big_list.getTail(); 
	EXPECT_EQ(big_list.getTail(), temp);
	big_list.addRight(3);
	EXPECT_EQ(temp->next, big_list.getTail());
}

//Test ToString
TEST_F(LinkedListTest, ToStringEmptyList){
	EXPECT_EQ(empty_list.toString(), "EMPTY");
}

TEST_F(LinkedListTest, ToStringOnceAdded){
	EXPECT_EQ(size_one_list.toString(), "head->[1]<-tail");
}

TEST_F(LinkedListTest, ToStringTwiceAdded){
	EXPECT_EQ(size_two_list.toString(), "head->[2]->[1]<-tail");
	size_two_list.addRight(3);
	EXPECT_EQ(size_two_list.toString(), "head->[2]->[1]->[3]<-tail");
}

//Test RemoveLeft
TEST_F(LinkedListTest, RemoveLeftEmpty){
	EXPECT_THROW(empty_list.removeLeft(), std::length_error);
}

TEST_F(LinkedListTest, RemoveLeftOne){
	size_one_list.removeLeft();
	EXPECT_EQ(size_one_list.getTail(), size_one_list.getHead());
	EXPECT_EQ(nullptr, size_one_list.getHead());
}

TEST_F(LinkedListTest, RemoveLeftTwo){
	Node<int>* new_head = size_two_list.getHead()->next;
	size_two_list.removeLeft();
	EXPECT_EQ(size_two_list.getTail(), size_two_list.getHead());
	EXPECT_EQ(size_two_list.getHead(), new_head);
}

TEST_F(LinkedListTest, RemoveLeftMany){
	Node<int>* new_head = big_list.getHead()->next;
	big_list.removeLeft();
	EXPECT_NE(big_list.getHead(), big_list.getTail());
	EXPECT_EQ(big_list.getHead(), new_head);
}

//Test RemoveRight
TEST_F(LinkedListTest, RemoveRightEmpty){
	EXPECT_THROW(empty_list.removeRight(), std::length_error);
}

TEST_F(LinkedListTest, RemoveRightOne){
	size_one_list.removeRight();
	EXPECT_EQ(size_one_list.getTail(), size_one_list.getHead());
	EXPECT_EQ(nullptr, size_one_list.getTail());
	EXPECT_THROW(empty_list.removeRight(), std::length_error);
}

TEST_F(LinkedListTest, RemoveRightTwo){
	int old_tail_value = size_two_list.getTail()->data;
	EXPECT_EQ(size_two_list.removeRight(), old_tail_value);
	EXPECT_EQ(size_two_list.getHead(), size_two_list.getTail());
	EXPECT_EQ(size_two_list.getTail()->data, 2); 
}

TEST_F(LinkedListTest, RemoveRightMany){
	EXPECT_EQ(big_list.removeRight(), 0);
	EXPECT_EQ(big_list.removeRight(), 1);
	EXPECT_NE(big_list.getTail(), big_list.getHead());
	EXPECT_EQ(big_list.getTail()->data, 2); 
}

