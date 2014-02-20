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

#include <gtest/gtest.h>
#include <mla/mla.h>

using namespace MLA;
using namespace MLA::DT;

TEST(DicisionTree, RGBClassifier)
{
    enum State
    {
        ON,
        OFF
    };

    enum Color
    {
        White,
        Red,
        Green,
        Blue,
        Magenta,
        Yellow,
        Cyan,
        Black
    };

    typedef Node<State, Color> RGBNode;

    const std::vector<State> whiteColor = {ON, ON, ON};
    const std::vector<State> redColor = {ON, OFF, OFF};
    const std::vector<State> greenColor = {OFF, ON, OFF};
    const std::vector<State> blueColor = {OFF, OFF, ON};
    const std::vector<State> magentaColor = {ON, OFF, ON};
    const std::vector<State> yellowColor = {ON, ON, OFF};
    const std::vector<State> cyanColor = {OFF, ON, ON};
    const std::vector<State> blackColor = {OFF, OFF, OFF};

    const std::shared_ptr<RGBNode> node(
        new RGBNode(ON, 0,
            new RGBNode(ON, 1,
                new RGBNode(ON, 2,
                    new RGBNode(White),
                    new RGBNode(Yellow)),
                new RGBNode(ON, 2,
                    new RGBNode(Magenta),
                    new RGBNode(Red))
            ),
            new RGBNode(OFF, 1,
                new RGBNode(OFF, 2,
                    new RGBNode(Black),
                    new RGBNode(Blue)),
                new RGBNode(OFF, 2,
                    new RGBNode(Green),
                    new RGBNode(Cyan))
            )
        )
    );

    DecisionTree<State, Color> tree(node, [](const State a, const State b) {
        return a == b;
    });

    EXPECT_EQ(tree.predict(whiteColor), White);
    EXPECT_EQ(tree.predict(redColor), Red);
    EXPECT_EQ(tree.predict(greenColor), Green);
    EXPECT_EQ(tree.predict(blueColor), Blue);
    EXPECT_EQ(tree.predict(magentaColor), Magenta);
    EXPECT_EQ(tree.predict(yellowColor), Yellow);
    EXPECT_EQ(tree.predict(cyanColor), Cyan);
    EXPECT_EQ(tree.predict(blackColor), Black);
}
