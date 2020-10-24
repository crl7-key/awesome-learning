# Docker

`Docker`是一个开源的应用容器引擎,容器`containers`其实是一个虚拟化的独立的环境,是基于`Go`语言开发的,可以让开发者打包他们的应用以及依赖包到一个轻量级、可移植的容器中,然后发布到任何流行的`Linux`机器上,也可以实现虚拟化。容器是完全使用沙箱机制,相互之间不会有任何接口,更重要的是容器性能开销极低.  
Docker的思想来自集装箱,即隔离,打包装箱,每个箱子都是互相隔离的,每一个容器内都有一个属于自己的文件系统,互不影响。

## 目录
* [Docker的应用场景](#Docker的应用场景)
* [Docker 的优点](#Docker-的优点)  
* [Docker 架构](#Docker-架构) 
* [Docker 的安装](#Docker-的安装) 
* [Docker 原理](#Docker-原理) 
* [Docker 命令](#Docker-命令)  
* [Docker 容器使用](#Docker-容器使用)  
    - [容器内运行应用程序](#容器内运行应用程序)
    - [启动容器 运行交互式的容器](#启动容器-运行交互式的容器)
    - [退出当前的容器](#退出当前的容器)
    - [启动容器 后台模式](#启动容器-后台模式)
    - [停止容器](#停止容器)
    - [启动已停止运行的容器](#启动已停止运行的容器)
    - [进入容器](#进入容器)
    - [导出容器](#导出容器)
    - [导入容器](#导入容器)
    - [删除容器](#删除容器)
    - [查询最后一次创建的容器](#查询最后一次创建的容器)
* [Docker 镜像使用](#Docker-镜像使用) 
    - [列出镜像列表](#列出镜像列表)
    - [获取镜像](#获取镜像)
    - [查找镜像](#查找镜像)
    - [删除镜像](#删除镜像)
    - [设置镜像标签](#设置镜像标签)


## Docker的应用场景
- `Web`应用的自动化打包和发布。  
- 自动化测试和持续集成、发布。  
- 在服务型环境中部署和调整数据库或其他的后台应用。   
- 从头编译或者扩展现有的`OpenShift` 或`Cloud Foundry`平台来搭建自己的`PaaS`环境。    


## Docker 的优点  
- 快速,一致地交付应用程序和部署  
- 更便捷的升级和扩缩容  
- 更简单的系统运维  
- 更高效的计算资源利用  

## Docker 架构 
`Docker` 包括三个基本概念:  
镜像（`Image`）：`Docker`镜像（`Image`）,就相当于是一个`root`文件系统。比如官方镜像`ubuntu:16.04`就包含了完整的一套`Ubuntu16.04`最小系统`root`文件系统。  
容器（`Container`）：镜像（`Image`）和容器（`Container`）的关系，就像是面向对象程序设计中的类和实例一样,镜像是静态的定义,容器是镜像运行时的实体。容器可以被创建、启动、停止、删除、暂停等。   
仓库（`Repository`）：仓库可看成一个代码控制中心,用来保存镜像。

## Docker 的安装
推荐按着[官方文档](https://docs.docker.com/get-docker/)来安装。  
可以使用`docker --version`来查看是否安装成功。

## Docker 原理
`Docker`是一个client-Server结构的系统,Docker的守护进程运行在宿主机上,通过Socket从客户端访问
`Docker-Server`接收到`Docker-Client`的指令,就会执行这个命令

## Docker 命令

```
$ docker --help

管理命令:
  container   管理容器
  image       管理镜像
  network     管理网络
命令：
  attach      介入到一个正在运行的容器
  build       根据 Dockerfile 构建一个镜像
  commit      根据容器的更改创建一个新的镜像
  cp          在本地文件系统与容器中复制 文件/文件夹
  create      创建一个新容器
  exec        在容器中执行一条命令
  images      列出镜像
  kill        杀死一个或多个正在运行的容器    
  logs        取得容器的日志
  pause       暂停一个或多个容器的所有进程
  ps          列出所有容器
  pull        拉取一个镜像或仓库到 registry
  push        推送一个镜像或仓库到 registry
  rename      重命名一个容器
  restart     重新启动一个或多个容器
  rm          删除一个或多个容器
  rmi         删除一个或多个镜像
  run         在一个新的容器中执行一条命令
  search      在 Docker Hub 中搜索镜像
  start       启动一个或多个已经停止运行的容器
  stats       显示一个容器的实时资源占用
  stop        停止一个或多个正在运行的容器
  tag         为镜像创建一个新的标签
  top         显示一个容器内的所有进程
  unpause     恢复一个或多个容器内所有被暂停的进程
  version     显示docker版本信息
  info        显示docker的系统信息
```

## Docker 容器使用

### 容器内运行应用程序
> docker run [OPTIONS] IMAGE[:TAG|@DIGEST] [COMMAND] [ARG...]   
```shell
docker run ubuntu /bin/echo "hello world"
```
参数
- `docker`: `Docker`的二进制执行文件。   

- `run`: 与前面的`docker`组合来运行一个容器。  

- `ubuntu`: 指定要运行的镜像,Docker首先从本地主机上查找镜像是否存在,如果不存在,`Docker`就会从镜像仓库`Docker Hub`下载公共镜像。  

- `/bin/echo "Hello world"`: 在启动的容器里执行的命令   

### 启动容器 运行交互式的容器
```shell
docker run -it ubuntu /bin/bash 
```
参数：

- `-t`: 在新容器内指定一个伪终端或终端。   
- `-i`: 允许对容器内的标准输入 (STDIN) 进行交互。  

### 退出当前的容器
可以通过运行`exit`命令或者使用`CTRL+D`来退出容器。



### 启动容器 后台模式
在使用 `-d`参数时,容器启动后会进入后台
```shell
docker run -d ubuntu /bin/sh -c "while true; do echo hello world; sleep 1; done"
```
执行之后会出现一长串字符例如:
> 163ea2389e3ff893b39c192c48d7fa32c775de1a0696036f839ab9ef34307273

如果需要确认容器有在运行可以通过`docker ps`来进行查看。  


输出详情介绍：  

- `CONTAINER ID`: 容器`ID`。  
- `IMAGE`: 使用的镜像。  
- `COMMAND`: 启动容器时运行的命令。  
- `CREATED`: 容器的创建时间。  
- `STATUS`: 容器状态。  
- `PORTS`: 容器的端口信息和使用的连接类型（tcp\udp）。  
- `NAMES`: 自动分配的容器名称   

在宿主主机内使用`docker logs  CONTAINER ID`可以查看容器内的标准输出
```
docker logs 163ea2389e3f
```

### 停止容器
> docker stop [OPTIONS] CONTAINER [CONTAINER...]  
可以使用`docker stop CONTAINER ID`命令来停止容器：  
```shell
docker stop 163ea2389e3f
```


### 启动已停止运行的容器  

查看所有的容器命令如下：
```
docker ps -a  
```

使用`docker start CONTAINER ID`启动一个已停止的容器  
```shell
docker start 163ea2389e3f
```

### 进入容器
想要进入容器，可以通过以下指令进入：
- `docker attach CONTAINER ID`
- `docker exec`：推荐使用`docker exec`命令,因为此退出容器终端,不会导致容器的停止。  

例如：
使用`docker attach`命令:
```shell
docker attach 163ea2389e3f
```
注意： 如果从这个容器退出，会导致容器的停止。    

使用`exec`命令:
```shell
docker exec -it 163ea2389e3f /bin/bash
```


### 导出容器
如果要导出本地某个容器，可以使用`docker export CONTAINER ID`命令
```shell
docker export 163ea2389e3f > ubuntu.tar
```

### 导入容器
可以使用`docker import`从容器快照文件中再导入为镜像，以下实例将快照文件 ubuntu.tar 导入到镜像 test/ubuntu:v1:
```
 cat docker/ubuntu.tar | docker import - test/ubuntu:v1
```

也可以通过指定 URL 或者某个目录来导入，例如：
```shell
docker import http://example.com/exampleimage.tgz example/imagerepo
```

### 删除容器
删除容器使用`docker rm `命令：
```
docker rm -f 163ea2389e3f
```

### 查询最后一次创建的容器
可以使用命令`docker ps -l`查询最后一次创建的容器



## Docker 镜像使用

### 列出镜像列表
> docker image COMMAND   
可以使用`docker images`来列出本地主机上的镜像
```shell
docker images

REPOSITORY          TAG                 IMAGE ID            CREATED             SIZE
ubuntu              latest              d70eaf7277ea        21 hours ago        72.9MB
hello-world         latest              bf756fb1ae65        9 months ago        13.3kB
```

各个选项说明:
- `REPOSITORY`：表示镜像的仓库源  
- `TAG`：镜像的标签    
- `IMAGE ID`：镜像ID    
- `CREATED`：镜像创建时间    
- `SIZE`：镜像大小   



### 获取镜像

可以使用`docker pull imageName`命令获取镜像   
例如：  
使用`docker pull`命令来载入`ubuntu`镜像：  
```shell
docker pull ubuntu  
```


### 查找镜像
> docker search [OPTIONS] TERM    
可以从`Docker Hub`[网站](https://hub.docker.com/)来搜索镜像

```shell
docker search httpd
```

- `NAME`: 镜像仓库源的名称  
- `DESCRIPTION`: 镜像的描述  
- `OFFICIAL`: 是否`docker`官方发布    
- `stars`: 类似`Github`里面的`star`,表示点赞、喜欢的意思。    
- `AUTOMATED`: 自动构建。


### 删除镜像
> docker rmi [OPTIONS] IMAGE [IMAGE...]   
镜像删除使用`docker rmi`命令,比如我们删除`hello-world`镜像：
```shell
docker rmi hello-world
```


### 设置镜像标签
> docker tag SOURCE_IMAGE[:TAG] TARGET_IMAGE[:TAG]   
可以使用`docker tag`命令,为镜像添加一个新的标签
```shell
docker tag 0e5574283393 fedora/httpd:version1.0
```


**[⬆ 返回顶部](#目录)**