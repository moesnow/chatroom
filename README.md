# chatroom

基于TCP的多人聊天室

## 编译

```bash
git clone https://github.com/moesnow/chatroom.git
cd chatroom
make
```

## 用法

```bash
./server <ip> <port>
```

```bash
./client <ip> <port>
```

## 示例

```bash
➜  ~ ./server 127.0.0.1 4000
```

```bash
➜  ~ ./client 127.0.0.1 4000
请给自己取个网名：mike
>当前在线人数:1
>john进入聊天室，大家欢迎!
>welcome!
>john:thanks~
>john:goodbye
>bye
>john离开了聊天室!
```

```bash
➜  ~ ./client 127.0.0.1 4000
请给自己取个网名：john
>当前在线人数:2
>mike:welcome!
>thanks~
>goodbye
>mike:bye
```

