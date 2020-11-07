# CSP vs Actor
- 和`Actor`的直接通讯不同,CSP模式则是通过`Channel`进行通讯的,更松耦合一些。
- `Go`中`channel`是有容量限制并且独立于处理`Groutine`,而如`Erlang`,`Actor`模式中的`mailbox`容量是无限的,接收进程也总是被动地处理消息.