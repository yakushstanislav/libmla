/*
   Copyright (c) 2014 Stanislav Yakush (st.yakush@yandex.ru)

   Permission is hereby granted, free of charge, to any person obtaining a copy
   of this software and associated documentation files (the "Software"), to deal
   in the Software without restriction, including without limitation the rights
   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
   copies of the Software, and to permit persons to whom the Software is
   furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in all
   copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
   SOFTWARE.
*/

#ifndef __MLA_DECISION_TREE_H__
#define __MLA_DECISION_TREE_H__

namespace MLA {

namespace DT {

template<typename T, typename C>
class Node
{
public:
    Node(const T value, const std::size_t index,
        const Node<T, C>* leftNode,
        const Node<T, C>* rightNode) :
        _value(value), _index(index)
    {
        assert(leftNode);
        assert(rightNode);

        _leftNode = const_cast<Node<T, C>*>(leftNode);
        _rightNode = const_cast<Node<T, C>*>(rightNode);
    }

    Node(const C value) :
        _class(value), _leftNode(nullptr), _rightNode(nullptr)
    {
    }

    ~Node()
    {
        if (_leftNode)
            delete _leftNode;

        if (_rightNode)
            delete _rightNode;
    }

    inline T getFeatureValue()
    {
        return _value;
    }

    inline std::size_t getFeatureIndex()
    {
        return _index;
    }

    inline C getClass()
    {
        return _class;
    }

    inline bool isLeaf()
    {
        return _leftNode == nullptr && _rightNode == nullptr;
    }

    inline Node<T, C>* getLeftNode()
    {
        return _leftNode;
    }

    inline Node<T, C>* getRightNode()
    {
        return _rightNode;
    }

private:
    T _value;
    C _class;
    std::size_t _index;
    Node<T, C>* _leftNode;
    Node<T, C>* _rightNode;
};

template<typename T, typename C>
class DecisionTree
{
public:
    DecisionTree(const std::shared_ptr<Node<T, C>> rootNode, const std::function<bool(T, T)> predicate) :
        _rootNode(rootNode), _predicate(predicate)
    {
    }

    C predict(const std::vector<T>& data)
    {
        Node<T, C>* nextNode = _rootNode.get();

        for (;;)
        {
            if (nextNode->isLeaf())
            {
                return nextNode->getClass();
            }

            const std::size_t index = nextNode->getFeatureIndex();
            const T value = nextNode->getFeatureValue();

            if (_predicate(data[index], value))
            {
                nextNode = nextNode->getLeftNode();
            }
            else
            {
                nextNode = nextNode->getRightNode();
            }
        }
    }

private:
    std::function<bool(T, T)> _predicate;
    std::shared_ptr<Node<T, C>> _rootNode;
};

};

};

#endif
