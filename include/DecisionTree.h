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

template<typename T, typename L>
struct Data
{
public:
    Data(const std::vector<T>& data, const L label) :
        _data(data), _label(label)
    {
    }

    std::vector<T> getData() const
    {
        return _data;
    }

    L getLabel() const
    {
        return _label;
    }

private:
    std::vector<T> _data;
    L _label;
};

template<typename T, typename L>
class Node
{
public:
    Node(const T value, const std::size_t index,
        const Node<T, L>* leftNode,
        const Node<T, L>* rightNode) :
        _value(value), _index(index)
    {
        assert(leftNode);
        assert(rightNode);

        _leftNode = const_cast<Node<T, L>*>(leftNode);
        _rightNode = const_cast<Node<T, L>*>(rightNode);
    }

    Node(const L label) :
        _label(label), _leftNode(nullptr), _rightNode(nullptr)
    {
    }

    ~Node()
    {
        if (_leftNode)
            delete _leftNode;

        if (_rightNode)
            delete _rightNode;
    }

    inline T getFeatureValue() const
    {
        return _value;
    }

    inline std::size_t getFeatureIndex() const
    {
        return _index;
    }

    inline L getLabel() const
    {
        return _label;
    }

    inline bool isLeaf() const
    {
        return _leftNode == nullptr && _rightNode == nullptr;
    }

    inline Node<T, L>* getLeftNode() const
    {
        return _leftNode;
    }

    inline Node<T, L>* getRightNode() const
    {
        return _rightNode;
    }

private:
    T _value;
    L _label;
    std::size_t _index;
    Node<T, L>* _leftNode;
    Node<T, L>* _rightNode;
};

template<typename T, typename L>
class DecisionTree
{
public:
    DecisionTree(const std::shared_ptr<Node<T, L>> rootNode, const std::function<bool(T, T)> predicate) :
        _rootNode(rootNode), _predicate(predicate)
    {
    }

    L predict(const std::vector<T>& data)
    {
        Node<T, L>* nextNode = _rootNode.get();

        for (;;)
        {
            if (nextNode->isLeaf())
            {
                return nextNode->getLabel();
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
    std::shared_ptr<Node<T, L>> _rootNode;
};

};

};

#endif
