///
/// Binary tree implementation - level order implementation that builds a complete binary tree
///

#include <iostream>
#include <memory>
#include <vector>
#include <queue>
#include <cassert>

using namespace std;


class BinaryTreeNode
{
public:
    BinaryTreeNode(const int key) : key_(key)
    {
    }

    shared_ptr<BinaryTreeNode> leftChild;
    shared_ptr<BinaryTreeNode> rightChild;

    const int getKey() { return key_; }
private:
    const int key_;

};

class BinaryTree
{
public:
    BinaryTree(const vector<int>& levelOrderSequence)
    {
        if (levelOrderSequence.empty()) { return; }
        assert(root_ == nullptr);
        std::queue< shared_ptr<BinaryTreeNode> > nodeQueue;
        std::queue<int> depthQueue;
        root_ = shared_ptr<BinaryTreeNode>(new BinaryTreeNode(levelOrderSequence[0]));
        nodeQueue.push(root_);
        std::size_t sequenceIndex = 1;
        while (!nodeQueue.empty())
        {
            if (sequenceIndex == levelOrderSequence.size()) { return; }
            auto node = nodeQueue.front();
            nodeQueue.pop();
            const int leftKey = levelOrderSequence[sequenceIndex++];
            node->leftChild = shared_ptr<BinaryTreeNode>(new BinaryTreeNode(leftKey));
            nodeQueue.push(node->leftChild);
            if (sequenceIndex == levelOrderSequence.size()) { return; }
            const int rightKey = levelOrderSequence[sequenceIndex++];
            node->rightChild = shared_ptr<BinaryTreeNode>(new BinaryTreeNode(rightKey));
            nodeQueue.push(node->rightChild);
        }
    }

    /// level order printing
    void print()
    {
        if (root_ == nullptr) { return; }
        std::queue< shared_ptr<BinaryTreeNode> > nodeQueue;
        std::queue<int> depthQueue;
        nodeQueue.push(root_);
        depthQueue.push(0);
        int currentDepth = 0;
        while (!nodeQueue.empty())
        {
            assert(nodeQueue.size() == depthQueue.size());
            auto node = nodeQueue.front();
            auto nodeDepth = depthQueue.front();
            nodeQueue.pop();
            depthQueue.pop();
            auto leftChild = node->leftChild;
            auto rightChild = node->rightChild;
            if (leftChild)
            {
                nodeQueue.push(leftChild);
                depthQueue.push(nodeDepth + 1);
            }
            if (rightChild)
            {
                nodeQueue.push(rightChild);
                depthQueue.push(nodeDepth + 1);
            }
            if (nodeDepth > currentDepth)
            {
                assert(nodeDepth = currentDepth + 1);
                std::cout << "\n";
                currentDepth = nodeDepth;
            }
            std::cout << node->getKey() << " ";
        }
        std::cout << "\n";
    }
            

private:
    shared_ptr<BinaryTreeNode> root_ = nullptr;
};


void testFn1()
{
    std::cout << "Test Fn 1" << std::endl;
    std::vector<int> levelOrderSequence = { 0, 1, 2, 3, 4, 5, 6 , 7, 8, 9, 10 };
    auto bt = BinaryTree(levelOrderSequence);
    bt.print();
}

int main(int argc, char** argv)
{
    testFn1();
    return 0;
}