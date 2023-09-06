
#include <SmartPointers/ProducerConsumer.h>
#include <gtest/gtest.h>

#include <algorithm>
#include <regex>

namespace smartPointers
{
auto countPattern(const std::string &pattern, const std::string &input);
auto countPattern(const std::string &pattern, const std::string &input)
{
    std::regex regex_pattern(pattern);
    auto words_begin = std::sregex_iterator(input.begin(), input.end(), regex_pattern);
    auto words_end = std::sregex_iterator();

    return std::distance(words_begin, words_end);
}

class TestProducerConsumer : public ::testing::TestWithParam<std::array<int, 4>>
{};

TEST(TestProducerConsumer, Steps)
{
    int numProducedItems = 10;
    std::chrono::milliseconds productionDelay(10);
    std::chrono::milliseconds consumerADelay(0);
    std::chrono::milliseconds consumerBDelay(0);
    ProducerConsumer pc(numProducedItems, productionDelay, consumerADelay, consumerBDelay);

    testing::internal::CaptureStdout();
    pc.start();
    auto consoleOut = testing::internal::GetCapturedStdout();
    EXPECT_EQ(countPattern("Produced \\d+\nConsumer \\w consumed \\d+\n", consoleOut), numProducedItems);
}

TEST(TestProducerConsumer, SlowCustomerA)
{
    int numProducedItems = 10;
    std::chrono::milliseconds productionDelay(0);
    std::chrono::milliseconds consumerADelay(200);
    std::chrono::milliseconds consumerBDelay(0);
    ProducerConsumer pc(numProducedItems, productionDelay, consumerADelay, consumerBDelay);

    testing::internal::CaptureStdout();
    pc.start();
    auto consoleOut = testing::internal::GetCapturedStdout();
    std::cout << consoleOut << std::endl;

    EXPECT_EQ(countPattern("Produced \\d+\n", consoleOut), numProducedItems);
    EXPECT_LE(countPattern("Consumer A consumed \\d+\n", consoleOut), 2);
    EXPECT_GE(countPattern("Consumer B consumed \\d+\n", consoleOut), 8);
}
TEST(TestProducerConsumer, SlowCustomerB)
{
    int numProducedItems = 10;
    std::chrono::milliseconds productionDelay(0);
    std::chrono::milliseconds consumerADelay(0);
    std::chrono::milliseconds consumerBDelay(200);
    ProducerConsumer pc(numProducedItems, productionDelay, consumerADelay, consumerBDelay);

    testing::internal::CaptureStdout();
    pc.start();
    auto consoleOut = testing::internal::GetCapturedStdout();

    EXPECT_EQ(countPattern("Produced \\d+\n", consoleOut), numProducedItems);
    EXPECT_GE(countPattern("Consumer A consumed \\d+\n", consoleOut), 8);
    EXPECT_LE(countPattern("Consumer B consumed \\d+\n", consoleOut), 2);
}

TEST_P(TestProducerConsumer, Pipeline)
{
    int numProducedItems = GetParam()[0];
    std::chrono::milliseconds productionDelay(GetParam()[1]);
    std::chrono::milliseconds consumerADelay(GetParam()[2]);
    std::chrono::milliseconds consumerBDelay(GetParam()[3]);
    ProducerConsumer pc(numProducedItems, productionDelay, consumerADelay, consumerBDelay);

    testing::internal::CaptureStdout();
    pc.start();
    auto consoleOut = testing::internal::GetCapturedStdout();

    EXPECT_EQ(countPattern("Produced \\d+\n", consoleOut), numProducedItems);
    EXPECT_EQ(countPattern("Consumer \\w consumed \\d+\n", consoleOut), numProducedItems);
}

INSTANTIATE_TEST_CASE_P(Pipeline,
                        TestProducerConsumer,
                        ::testing::Values(std::array<int, 4>{10, 0, 1, 1},
                                          std::array<int, 4>{10, 10, 1, 3},
                                          std::array<int, 4>{10, 2, 3, 6},
                                          std::array<int, 4>{10, 10, 0, 0},
                                          std::array<int, 4>{10, 3, 2, 1},
                                          std::array<int, 4>{10, 4, 1, 6},
                                          std::array<int, 4>{10, 5, 10, 10}));

}  // namespace smartPointers