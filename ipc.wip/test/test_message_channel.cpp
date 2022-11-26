#include "message_channel.hpp"

#include "test.hpp"
#include "log.hpp"

#include <string>

REGISTER_TEST(test_message_channel) {
    MessageChannel<int> provider;
    ASSERT_EQ(true, provider.Init(MessageChannelAccessType::CREATE_ONLY,
                                  "test_channel", 10));
    MessageChannel<int> consumer;
    ASSERT_EQ(true, provider.Init(MessageChannelAccessType::OPEN_ONLY,
                                  "test_channel", 0));
    LINFO(test) << "here";
    provider.Push(1, 2012);
    provider.Push(2, 2013);
    provider.Push(3, 2014);

    DataVisitor<int> visitor;

    return true;
}

int main() {
    InitFailureHandle();
    RunTests();
    return 0;
}