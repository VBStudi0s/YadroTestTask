#include <gtest/gtest.h>
#include <fstream>

#include "Tape/TapeHandler.h"

TEST(TapeTests, Empty)
{
    std::ofstream file("empty");
    file<<"";
    file.close();
    TapeHandler tape("empty");
    ASSERT_TRUE(tape.is_empty());
}

TEST(TapeTests, Read)
{
    std::ofstream file("read");
    for(int i=0; i<10; i++)
        file<<i<<'\n';
    file.close();
    TapeHandler tape("read");
    ASSERT_FALSE(tape.is_empty());
    ASSERT_TRUE(tape.is_start());
    ASSERT_FALSE(tape.is_end());
    int i=0;
    while(!tape.is_end())
    {
        ASSERT_EQ(tape.read(), i++);
        tape.right();
    }
    ASSERT_TRUE(tape.is_end());
    ASSERT_EQ(9, tape.read());
}

int main()
{
    ::testing::InitGoogleTest();

    return RUN_ALL_TESTS();
}