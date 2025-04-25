#include <iostream>
#include <string>

int main() {
    int n_commands;
    std::cin >> n_commands;

    int b_capacity = n_commands + 1;
    int *q_buffer = new int[b_capacity];
    int *dq_buffer = new int[b_capacity];

    int q_head = 0, q_tail = 0;
    int dq_head = 0, dq_tail = 0;

    auto is_q_empty = [&]() { return q_head == q_tail; };
    auto q_size = [&]() { return (q_tail - q_head + b_capacity) % b_capacity; };
    auto is_dq_empty = [&]() { return dq_head == dq_tail; };
    auto dq_front = [&]() { return dq_buffer[dq_head]; };
    auto dq_back = [&]() { return dq_buffer[(dq_tail - 1 + b_capacity) % b_capacity]; };

    std::string command;
    while (n_commands--) {
        std::cin >> command;
        if (command == "enqueue") {
            int value;
            std::cin >> value;
            q_buffer[q_tail] = value;
            q_tail = (q_tail + 1) % b_capacity;
            while (!is_dq_empty() && dq_back() > value) {
                dq_tail = (dq_tail - 1 + b_capacity) % b_capacity;
            }
            dq_buffer[dq_tail] = value;
            dq_tail = (dq_tail + 1) % b_capacity;
            std::cout << "ok\n";
        } else if (command == "dequeue") {
            if (is_q_empty()) {
                std::cout << "error\n";
            } else {
                int front_value = q_buffer[q_head];
                q_head = (q_head + 1) % b_capacity;
                if (!is_dq_empty() && dq_front() == front_value) {
                    dq_head = (dq_head + 1) % b_capacity;
                }
                std::cout << front_value << "\n";
            }
        } else if (command == "front") {
            if (is_q_empty()) {
                std::cout << "error\n";
            } else {
                std::cout << q_buffer[q_head] << "\n";
            }
        } else if (command == "size") {
            std::cout << q_size() << "\n";
        } else if (command == "clear") {
            q_head = q_tail = dq_head = dq_tail = 0;
            std::cout << "ok\n";
        } else if (command == "min") {
            if (is_q_empty()) {
                std::cout << "error\n";
            } else {
                std::cout << dq_front() << "\n";
            }
        }
    }

    delete[] q_buffer;
    delete[] dq_buffer;
    return 0;
}
