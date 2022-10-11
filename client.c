#include <arpa/inet.h>
#include <errno.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define LOG(fmt, args...) \
    printf("[%s %d]" fmt, __FILE__, __LINE__, ##args)

void errExit(const char *desc) {
    perror(desc);
    exit(-1);
}

void *recvMsg(void *arg) {
    long fd = (long)arg;
    for (;;) {
        char msg[1024] = {};
        if (recv(fd, msg, sizeof(msg), 0) <= 0) {
            return NULL;
        }
        printf("%s\n>", msg);
        fflush(stdout);
    }
}
void connectServer(const char *ip, unsigned short port) {
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        errExit("socket");
    }
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = inet_addr(ip);
    int ret = connect(sockfd, (const struct sockaddr *)&addr, sizeof(addr));
    if (ret != 0) {
        errExit("connect");
    }
    char name[128] = {};
    printf("请给自己取个网名：");
    scanf("%s", name);
    printf(">");
    send(sockfd, name, strlen(name) + 1, 0);

    pthread_t id;
    pthread_create(&id, NULL, recvMsg, (void *)(long)sockfd);
    for (;;) {
        char buf[1024] = {};
        scanf("%s", buf);
        printf(">");
        ret = send(sockfd, buf, strlen(buf) + 1, 0);
        if (ret <= 0) {
            LOG("%s\n", strerror(errno));
            break;
        }
        if (strcmp(buf, "!quit") == 0) {
            break;
        }
    }
    close(sockfd);
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("usage：%s <ip> <port>\n", argv[0]);
        return -1;
    }
    connectServer(argv[1], atoi(argv[2]));
    return 0;
}
