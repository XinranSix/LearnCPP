#include <cstddef>
#include <format>
#include <ostream>
#include <queue>
#include <stack>
#include <iostream>
#include <gtest/gtest.h>
#include <stdexcept>

template <typename T>
class PacketBuffer {
public:
    explicit PacketBuffer(size_t maxSize = 0);

    virtual ~PacketBuffer() = default;

    bool bufferPacket(T const &packet);

    [[nodiscard]] T getNextPacket();

private:
    std::queue<T> m_packets;
    size_t m_maxSize;
};

template <typename T>
PacketBuffer<T>::PacketBuffer(size_t maxSize) : m_maxSize { maxSize } {}

template <typename T>
bool PacketBuffer<T>::bufferPacket(T const &packet) {
    if (m_maxSize > 0 && m_packets.size() == m_maxSize) {
        return false;
    }
    m_packets.push(packet);
    return true;
}

template <typename T>
T PacketBuffer<T>::getNextPacket() {
    if (m_packets.empty()) {
        throw std::out_of_range { "Buffer is empty" };
    }

    T temp { m_packets.front() };
    m_packets.pop();
    return temp;
}

class IPPacket final {
public:
    explicit IPPacket(int id) : m_id { id } {}

    int getID() const {
        return m_id;
    }

private:
    int m_id;
};

TEST(容器适配器, queue示例_网络数据包缓冲) {
    PacketBuffer<IPPacket> ipPacket { 3 };

    for (int i { 1 }; i <= 4; ++i) {
        if (!ipPacket.bufferPacket(IPPacket { i })) {
            std::cout << "Packet " << i << " dropped (queue is full)." << std::endl;
        }
    }

    while (true) {
        try {
            IPPacket packet { ipPacket.getNextPacket() };
            std::cout << "Processing packet " << packet.getID() << std::endl;
        } catch (std::out_of_range const &) {
            std::cout << "Queue is empty." << std::endl;
            break;
        }
    }
}

class Error final {
public:
    Error(int priority, std::string errorString)
        : m_priority { priority }, m_errorString { std::move(errorString) } {}

    int getPriority() const {
        return m_priority;
    }

    std::string const &getFrrorString() const {
        return m_errorString;
    }

    auto operator<=>(Error const &rhs) const {
        return getPriority() <=> rhs.getPriority();
    }

private:
    int m_priority;
    std::string m_errorString;
};

std::ostream &operator<<(std::ostream &os, Error const &err) {
    os << std::format("{} (priority {})", err.getPriority(), err.getPriority());
    return os;
}

class ErrorCorrelatot final {
public:
    void addError(Error const &error) {
        m_errors.push(error);
    }

    [[nodiscard]] Error getError() {
        if (m_errors.empty()) {
            throw std::out_of_range { "No more errors." };
        }
        Error top { m_errors.top() };
        m_errors.pop();
        return top;
    }

private:
    std::priority_queue<Error> m_errors;
};

TEST(容器适配器, priority_queue示例_错误相关器) {
    ErrorCorrelatot ec;
    ec.addError({ 3, "Unable to read file" });
    ec.addError({ 1, "Incorrect entry from user" });
    ec.addError({ 10, "Unable to allocate memory!" });

    while (true) {
        try {
            Error e { ec.getError() };
            std::cout << e << std::endl;
        } catch (std::out_of_range const &) {
            std::cout << "Finished processing errors" << std::endl;
            break;
        }
    }
}

TEST(容器适配器, stack) {}

int main(int argc, char *argv[]) {
    printf("Running main() from %s\n", __FILE__);
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
