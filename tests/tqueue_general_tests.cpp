#include <gtest/gtest.h>
#include "tqueue.h"

TEST(TQueueTest, Constructor)
{
    EXPECT_NO_THROW(tqueue<std::string> t_queue;);
    EXPECT_NO_THROW(tqueue<int> t_queue;);
    EXPECT_NO_THROW(tqueue<char> t_queue;);
}

TEST(TQueueTest, Empty)
{
    tqueue<std::string> t_queue;
    EXPECT_EQ(t_queue.empty(), true);
    t_queue.push("Hello");
    EXPECT_EQ(t_queue.empty(), false);
    t_queue.push("World");
    EXPECT_EQ(t_queue.empty(), false);
    t_queue.pop();
    EXPECT_EQ(t_queue.empty(), false);
    t_queue.pop();
    EXPECT_EQ(t_queue.empty(), true);
}

TEST(TQueueTest, Size)
{
    tqueue<std::string> t_queue;
    EXPECT_EQ(t_queue.size(), 0);
    t_queue.push("Hello");
    EXPECT_EQ(t_queue.size(), 1);
    t_queue.push("World");
    EXPECT_EQ(t_queue.size(), 2);
    t_queue.push("!");
    EXPECT_EQ(t_queue.size(), 3);
    t_queue.pop();
    EXPECT_EQ(t_queue.size(), 2);
    t_queue.pop();
    EXPECT_EQ(t_queue.size(), 1);
    t_queue.pop();
    EXPECT_EQ(t_queue.size(), 0);
}

TEST(TQueueTest, PushPop)
{
    tqueue<std::string> t_queue;
    t_queue.push("Hello");
    EXPECT_EQ(t_queue.front(), "Hello");
    EXPECT_EQ(t_queue.back(), "Hello");
    EXPECT_EQ(t_queue.size(), 1);
    t_queue.push("World");
    EXPECT_EQ(t_queue.front(), "Hello");
    EXPECT_EQ(t_queue.back(), "World");
    EXPECT_EQ(t_queue.size(), 2);
    t_queue.push("!");
    EXPECT_EQ(t_queue.front(), "Hello");
    EXPECT_EQ(t_queue.back(), "!");
    EXPECT_EQ(t_queue.size(), 3);
    t_queue.pop();
    EXPECT_EQ(t_queue.front(), "World");
    EXPECT_EQ(t_queue.back(), "!");
    EXPECT_EQ(t_queue.size(), 2);
    t_queue.pop();
    EXPECT_EQ(t_queue.front(), "!");
    EXPECT_EQ(t_queue.back(), "!");
    EXPECT_EQ(t_queue.size(), 1);
    t_queue.pop();
    EXPECT_EQ(t_queue.size(), 0);
}

TEST(TQueueTest, front)
{
    tqueue<std::string> t_queue;
    t_queue.push("Hello");
    EXPECT_EQ(t_queue.front(), "Hello");
    t_queue.push("World");
    EXPECT_EQ(t_queue.front(), "Hello");
    t_queue.push("!");
    EXPECT_EQ(t_queue.front(), "Hello");
    t_queue.pop();
    EXPECT_EQ(t_queue.front(), "World");
    t_queue.pop();
    EXPECT_EQ(t_queue.front(), "!");
    t_queue.pop();
}

TEST(TQueueTest, back)
{
    tqueue<std::string> t_queue;
    t_queue.push("Hello");
    EXPECT_EQ(t_queue.back(), "Hello");
    t_queue.push("World");
    EXPECT_EQ(t_queue.back(), "World");
    t_queue.push("!");
    EXPECT_EQ(t_queue.back(), "!");
    t_queue.pop();
    EXPECT_EQ(t_queue.back(), "!");
    t_queue.pop();
    EXPECT_EQ(t_queue.back(), "!");
    t_queue.pop();
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
