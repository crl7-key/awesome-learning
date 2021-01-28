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
* [Docker 镜像使用](#Docker-镜像使用) 
    - [列出镜像列表](#列出镜像列表)
    - [获取镜像](#获取镜像)
    - [查找镜像](#查找镜像)
    - [删除镜像](#删除镜像)
    - [设置镜像标签](#设置镜像标签) 
    - [commit镜像构成](#commit镜像构成)
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
* [使用 Dockerfile 定制镜像](#使用-Dockerfile-定制镜像)
    * [FROM 指定基础镜像](#FROM-指定基础镜像)
    * [RUN 执行命令](#RUN-执行命令)
    * [构建镜像](#构建镜像)
    * [COPY 复制文件](#COPY-复制文件)
    * [ADD 更高级的复制文件](#ADD-更高级的复制文件)
    * [CMD 容器启动命令](#CMD-容器启动命令)
    * [ENTRYPOINT 入口点](#ENTRYPOINT-入口点) 
    * [ENV 设置环境变量](#ENV-设置环境变量)
    * [ARG 构建参数](#ARG-构建参数)
    * [VOLUME 定义匿名卷](#VOLUME-定义匿名卷)
    * [EXPOSE 声明端口](#EXPOSE-声明端口)
    * [WORKDIR 指定工作目录](#WORKDIR-指定工作目录)
    * [USER 指定当前用户](#USER-指定当前用户)
    * [HEALTHCHECK 健康检查](#HEALTHCHECK-健康检查)
    * [LABEL 指令](#LABEL-指令)
    * [SHELL 指令](#SHELL-指令)

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

```sh
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

```shell
docker images --help
```
可选项:
```sh
 -a, --all              显示所有镜像
      --digests         Show digests
  -f, --filter filter   Filter output based on conditions provided
      --format string   Pretty-print images using a Go template
      --no-trunc        Don't truncate output
  -q, --quiet           只显示镜像id
```

### 获取镜像
>  docker pull [OPTIONS] NAME[:TAG|@DIGEST]
   
可以使用`docker pull imageName`命令获取镜像   
例如：  
使用`docker pull`命令来载入`ubuntu`镜像：  
```shell
docker pull ubuntu  
```

可选项:
```sh
--all-tags , -a		下载存储库中所有标记的图像
--disable-content-trust	true	Skip image verification
--platform		experimental (daemon)API 1.32+
Set platform if server is multi-platform capable
--quiet , -q		禁止详细输出,只显示镜像id
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

可选项：
```sh
  -f, --filter filter   Filter output based on conditions provided
      --format string   Pretty-print search using a Go template
      --limit int       Max number of search results (default 25)
      --no-trunc        Don't truncate output
```
例如：
```sh
docker search mysql --filter=stars=3000 #从Docker Hub搜索stars量大于3000的镜像
```

### 删除镜像
> docker rmi [OPTIONS] IMAGE [IMAGE...]    

镜像删除使用`docker rmi`命令,比如我们删除`hello-world`镜像：
```shell
docker rmi -f hello-world
```

可选项:
```sh
  -f, --force      强制删除
      --no-prune   Do not delete untagged parents
```

### 设置镜像标签
> docker tag SOURCE_IMAGE[:TAG] TARGET_IMAGE[:TAG]   

可以使用`docker tag`命令,为镜像添加一个新的标签
```shell
docker tag 0e5574283393 fedora/httpd:version1.0
```

### commit镜像构成
当我们运行一个容器的时候（如果不使用卷的话），我们做的任何文件修改都会被记录于容器存储层里。而`Docker`提供了一个`docker commit`命令，可以将容器的存储层保存下来成为镜像。换句话说，就是在原有镜像的基础上，再叠加上容器的存储层，并构成新的镜像。以后我们运行这个新镜像的时候，就会拥有原有容器最后的文件变化。   
`docker commit`的语法格式为：
```sh
docker commit [选项] <容器ID或容器名> [<仓库名>[:<标签>]]
```
定制镜像`commit`后,可以用`docker history`具体查看镜像内的历史记录或者使用`docker images ls`查看新定制的镜像。


`docker commit`命令除了学习之外，还有一些特殊的应用场合，比如被入侵后保存现场等。但是，不要使用`docker commit`定制镜像，定制镜像应该使用`Dockerfile`来完成

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
```sh
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



### 使用 Dockerfile 定制镜像

镜像的定制实际上就是定制每一层所添加的配置、文件。使用`docker commit`意味着所有对镜像的操作都是黑箱操作，生成的镜像也被称为**黑箱镜像**，换句话说，就是除了制作镜像的人知道执行过什么命令、怎么生成的镜像，别人根本无从得知。而且，即使是这个制作镜像的人，过一段时间后也无法记清具体的操作。这种黑箱镜像的维护工作是非常痛苦的。以及后期修改的话，每一次修改都会让镜像更加臃肿一次，所删除的上一层的东西并不会丢失，会一直如影随形的跟着这个镜像，即使根本无法访问到。这会让镜像更加臃肿。   


如果我们可以把每一层修改、安装、构建、操作的命令都写入一个脚本，用这个脚本来构建、定制镜像，那么无法重复的问题、镜像构建透明性的问题、体积的问题就都会解决。这个脚本就是 `Dockerfile`。    

`Dockerfile`是一个文本文件，其内包含了一条条的**指令(Instruction)**，每一条指令构建一层，因此每一条指令的内容，就是描述该层应当如何构建。  

以定制`nginx`镜像为例:  
在一个空白目录中，建立一个文本文件，并命名为`Dockerfile`：
```sh
$ mkdir mynginx
$ cd mynginx
$ touch Dockerfile
```
其内容为：
```dockerfile
FROM nginx
RUN echo '<h1>Hello, Docker!</h1>' > /usr/share/nginx/html/index.html
```

   
#### FROM 指定基础镜像
所谓定制镜像，那一定是以一个镜像为基础，在其上进行定制。而`FROM`就是指定基础镜像，因此一个`Dockerfile`中`FROM`是必备的指令，并且必须是第一条指令。


在[Docker Hub](https://hub.docker.com/search?q=&type=image&image_filter=official)上有非常多的高质量的官方镜像，有可以直接拿来使用的服务类的镜像，如`nginx`、`redis`、`mongo`、`mysql`、`httpd`、`php`、`tomcat`等；也有一些方便开发、构建、运行各种语言应用的镜像，如`node`、`openjdk`、`python`、`ruby`、`golang`等。可以在其中寻找一个最符合我们最终目标的镜像为基础镜像进行定制。


如果没有找到对应服务的镜像，官方镜像中还提供了一些更为基础的操作系统镜像，如`ubuntu`、`debian`、`centos`、`fedora`、`alpine`等，这些操作系统的软件库为我们提供了更广阔的扩展空间。

除了选择现有镜像为基础镜像外，`Docker`还存在一个特殊的镜像，名为`scratch`。这个镜像是虚拟的概念，并不实际存在，它表示一个空白的镜像。
```sh
FROM scratch
...
```
如果以`scratch`为基础镜像的话，意味着不以任何镜像为基础，接下来所写的指令将作为镜像第一层开始存在。    

不以任何系统为基础，直接将可执行文件复制进镜像的做法并不罕见，比如`swarm`、`etcd`。对于`Linux`下静态编译的程序来说，并不需要有操作系统提供运行时支持，所需的一切库都已经在可执行文件里了，因此直接`FROM scratch`会让镜像体积更加小巧。使用`Go`语言开发的应用很多会使用这种方式来制作镜像，这也是为什么有人认为`Go`是特别适合容器微服务架构的语言的原因之一。

#### RUN 执行命令
`RUN`指令是用来执行命令行命令的。由于命令行的强大能力，`RUN`指令在定制镜像时是最常用的指令之一。其格式有两种：
- `shell`格式：`RUN <命令>`，就像直接在命令行中输入的命令一样。刚才写的`Dockerfile`中的`RUN`指令就是这种格式。
```sh
RUN echo '<h1>Hello, Docker!</h1>' > /usr/share/nginx/html/index.html
```

- `exec`格式：`RUN ["可执行文件", "参数1", "参数2"]`，这更像是函数调用中的格式。


`Union FS`是有最大层数限制的，比如`AUFS`，曾经是最大不得超过`42`层，现在是不得超过`127`层。

`Dockerfile`正确的写法：
```dockerfile
FROM debian:stretch

RUN set -x; buildDeps='gcc libc6-dev make wget' \
    && apt-get update \
    && apt-get install -y $buildDeps \
    && wget -O redis.tar.gz "http://download.redis.io/releases/redis-6.0.10.tar.gz" \
    && mkdir -p /usr/src/redis \
    && tar -xzf redis.tar.gz -C /usr/src/redis --strip-components=1 \
    && make -C /usr/src/redis \
    && make -C /usr/src/redis install \
    && rm -rf /var/lib/apt/lists/* \
    && rm redis.tar.gz \      
    && rm -r /usr/src/redis \
    && apt-get purge -y --auto-remove $buildDeps  # 清理缓存文件
```
其上，所有的命令只有一个目的，就是编译、安装`redis`可执行文件。因此没有必要建立很多层，这只是一层的事情。因此，这里没有使用很多个`RUN`一一对应不同的命令，而是仅仅使用一个`RUN`指令，并使用`&&`将各个所需命令串联起来。

为了格式化还进行了换行。`Dockerfile`支持`Shell`类的行尾添加` \ `的命令换行方式，以及行首` # `进行注释的格式。良好的格式，比如换行、缩进、注释等，会让维护、排障更为容易，这是一个比较好的习惯。

还可以看到这一组命令的最后添加了清理工作的命令，删除了为了编译构建所需要的软件，清理了所有下载、展开的文件，并且还清理了`apt` 缓存文件。这是很重要的一步，我们之前说过，镜像是多层存储，每一层的东西并不会在下一层被删除，会一直跟随着镜像。因此镜像构建时，一定要确保每一层只添加真正需要添加的东西，任何无关的东西都应该清理掉。


#### 构建镜像
在`Dockerfile`文件所在目录执行:
```sh
docker build -t nginx:v1 .
```
这里我们使用了`docker build `命令进行镜像构建。其格式为：
```sh
docker build [选项] <上下文路径/URL/->
```

#### COPY 复制文件
格式：
```dockerfile
COPY [--chown=<user>:<group>] <源路径>... <目标路径>
COPY [--chown=<user>:<group>] ["<源路径1>",... "<目标路径>"]
```
和`RUN`指令一样，也有两种格式，一种类似于命令行，一种类似于函数调用。

- `COPY`指令将从构建上下文目录中` <源路径> `的文件/目录复制到新的一层的镜像内的 `<目标路径> `位置。比如：
```dockerfile
COPY conf.json /usr/src/app/
```
- `<源路径>` 可以是多个，甚至可以是通配符，其通配符规则要满足`Go`的`filepath.Match`规则，如：
```dockerfile
COPY hom* /mydir/
COPY hom?.txt /mydir/
```
- `<目标路径>` 可以是容器内的绝对路径，也可以是相对于工作目录的相对路径（工作目录可以用`WORKDIR`指令来指定）。目标路径不需要事先创建，如果目录不存在会在复制文件前先行创建缺失目录。

此外，还需要注意一点，使用`COPY`指令，源文件的各种元数据都会保留。比如读、写、执行权限、文件变更时间等。这个特性对于镜像定制很有用。特别是构建相关文件都在使用 `Git`进行管理的时候。
在使用该指令的时候还可以加上`--chown=<user>:<group>`选项来改变文件的所属用户及所属组。
```dockerfile
COPY --chown=55:mygroup files* /mydir/
COPY --chown=bin files* /mydir/
COPY --chown=1 files* /mydir/
COPY --chown=10:11 files* /mydir/
```
如果源路径为文件夹，复制的时候不是直接复制该文件夹，而是将文件夹中的内容复制到目标路径。


#### ADD 更高级的复制文件
`ADD`指令和`COPY`的格式和性质基本一致。但是在`COPY`基础上增加了一些功能。

比如 `<源路径>`可以是一个`URL`，这种情况下，`Docker`引擎会试图去下载这个链接的文件放到 `<目标路径> `去。下载后的文件权限自动设置为`600`，如果这并不是想要的权限，那么还需要增加额外的一层`RUN`进行权限调整，另外，如果下载的是个压缩包，需要解压缩，也一样还需要额外的一层`RUN`指令进行解压缩。所以不如直接使用`RUN`指令，然后使用`wget`或者`curl`工具下载，处理权限、解压缩、然后清理无用文件更合理。因此，这个功能其实并不实用，而且不推荐使用。

如果 `<源路径> `为一个`tar`压缩文件的话，压缩格式为`gzip`, `bzip2` 以及 `xz` 的情况下，`ADD`指令将会自动解压缩这个压缩文件到 <目标路径> 去。

在某些情况下，这个自动解压缩的功能非常有用，比如官方镜像`ubuntu`中：
```dockerfile
FROM scratch
ADD ubuntu-xenial-core-cloudimg-amd64-root.tar.gz /
...
```
但在某些情况下，如果真的是希望复制个压缩文件进去，而不解压缩，这时就不可以使用 `ADD`命令了。

在`Docker`官方的 [Dockerfile 最佳实践文档](https://docs.docker.com/develop/develop-images/dockerfile_best-practices/) 中要求，尽可能的使用`COPY`，因为`COPY`的语义很明确，就是复制文件而已，而`ADD`则包含了更复杂的功能，其行为也不一定很清晰。最适合使用`ADD`的场合，就是所提及的需要自动解压缩的场合。

另外需要注意的是，`ADD`指令会令镜像构建缓存失效，从而可能会令镜像构建变得比较缓慢。

因此在`COPY`和`ADD`指令中选择的时候，可以遵循这样的原则，所有的文件复制均使用 `COPY`指令，仅在需要自动解压缩的场合使用`ADD`。

在使用该指令的时候还可以加上`--chown=<user>:<group> `选项来改变文件的所属用户及所属组。
```dockerfile
ADD --chown=55:mygroup files* /mydir/
ADD --chown=bin files* /mydir/
ADD --chown=1 files* /mydir/
ADD --chown=10:11 files* /mydir/
```

#### CMD 容器启动命令
`CMD`指令的格式和`RUN`相似，也是两种格式：
- `shell`格式：`CMD <命令>`
- `exec`格式：`CMD ["可执行文件", "参数1", "参数2"...]`
- 参数列表格式：`CMD ["参数1", "参数2"...]`。在指定了`ENTRYPOINT`指令后，用`CMD`指定具体的参数。

`Docker`不是虚拟机，容器就是进程。既然是进程，那么在启动容器的时候，需要指定所运行的程序及参数。`CMD`指令就是用于指定默认的容器主进程的启动命令的。

在运行时可以指定新的命令来替代镜像设置中的这个默认命令，比如，`ubuntu`镜像默认的`CMD`是`/bin/bash`，如果我们直接`docker run -it ubuntu`的话，会直接进入 `bash`。我们也可以在运行时指定运行别的命令，如`docker run -it ubuntu cat /etc/os-release`。这就是用`cat /etc/os-release`命令替换了默认的`/bin/bash`命令了，输出了系统版本信息。

在指令格式上，一般推荐使用`exec`格式，这类格式在解析时会被解析为`JSON`数组，因此一定要使用双引号 `"`，而不要使用单引号。

如果使用`shell`格式的话，实际的命令会被包装为`sh -c`的参数的形式进行执行。比如：
```dockerfile
CMD echo $HOME
```
在实际执行中，会将其变更为：
```dockerfile
CMD [ "sh", "-c", "echo $HOME" ]
```
这就是为什么我们可以使用环境变量的原因，因为这些环境变量会被`shell`进行解析处理。

`Docker`不是虚拟机，容器中的应用都应该以前台执行，而不是像虚拟机、物理机里面那样，用`systemd`去启动后台服务，容器内没有后台服务的概念。

当将`CMD`写成：
```dockerfile
CMD service nginx start
```
发现容器执行后就立即退出了。甚至在容器内去使用`systemctl`命令结果却发现根本执行不了。这就是因为没有搞明白前台、后台的概念，没有区分容器和虚拟机的差异，依旧在以传统虚拟机的角度去理解容器。

对于容器而言，其启动程序就是容器应用进程，容器就是为了主进程而存在的，主进程退出，容器就失去了存在的意义，从而退出，其它辅助进程不是它需要关心的东西。

而使用`service nginx start`命令，则是希望`upstart`来以后台守护进程形式启动 `nginx`服务。而刚才说了`CMD service nginx start`会被理解为`CMD [ "sh", "-c", "service nginx start"]`，因此主进程实际上是`sh`。那么当`service nginx start`命令结束后，`sh`也就结束了，`sh`作为主进程退出了，自然就会令容器退出。

正确的做法是直接执行`nginx`可执行文件，并且要求以前台形式运行。比如：
```dockerfile
CMD ["nginx", "-g", "daemon off;"]
```

#### ENTRYPOINT 入口点
`ENTRYPOINT`的格式和`RUN`指令格式一样，分为`exec`格式和`shell`格式。

`ENTRYPOINT`的目的和`CMD`一样，都是在指定容器启动程序及参数。`ENTRYPOINT`在运行时也可以替代，不过比CMD要略显繁琐，需要通过`docker run `的参数`--entrypoint`来指定。

当指定了`ENTRYPOINT`后，`CMD`的含义就发生了改变，不再是直接的运行其命令，而是将`CMD`的内容作为参数传给`ENTRYPOINT` 指令，换句话说实际执行时，将变为：
```docker
<ENTRYPOINT> "<CMD>"
```
那么有了`CMD`后，为什么还要有`ENTRYPOINT`呢？这种 `<ENTRYPOINT> "<CMD>"` 有什么好处?

**场景一：让镜像变成像命令一样使用**    
假设我们需要一个得知自己当前公网`IP`的镜像，那么可以先用`CMD`来实现：
```docker
FROM ubuntu:18.04
RUN apt-get update \
    && apt-get install -y curl \
    && rm -rf /var/lib/apt/lists/*
CMD [ "curl", "-s", "http://myip.ipip.net" ]
```
假如我们使用`docker build -t myip .` 来构建镜像的话，如果我们需要查询当前公网`IP`，只需要执行：
```sh
docker run myip
当前 IP：14.17.22.22  来自于：中国 广东 深圳  电信
```
这么看起来好像可以直接把镜像当做命令使用了，不过命令总有参数，如果我们希望加参数呢？比如从上面的`CMD`中可以看到实质的命令是 `curl`，那么如果我们希望显示`HTTP`头信息，就需要加上`-i`参数。那么我们可以直接加`-i `参数给`docker run myip`？

```sh
$ docker run myip -i
docker: Error response from daemon: OCI runtime create failed: container_linux.go:370: starting container process caused: exec: "-i": executable file not found in $PATH: unknown.
```
我们可以看到可执行文件找不到的报错，`executable file not found`。之前我们说过，跟在镜像名后面的是`command`，运行时会替换 `CMD`的默认值。因此这里的`-i`替换了原来的`CMD`，而不是添加在原来的`curl -s http://myip.ipip.net `后面。而` -i `根本不是命令，所以自然找不到。

那么如果我们希望加入`-i`这参数，我们就必须重新完整的输入这个命令：
```sh
$ docker run myip curl -s http://myip.ipip.net -i
```
这显然不是很好的解决方案，而使用`ENTRYPOINT`就可以解决这个问题。现在我们重新用`ENTRYPOINT`来实现这个镜像：
```dockerfile
FROM ubuntu:18.04
RUN apt-get update \
    && apt-get install -y curl \
    && rm -rf /var/lib/apt/lists/*
ENTRYPOINT [ "curl", "-s", "http://myip.ipip.net" ]
```
这次再来尝试直接使用`docker run myip -i`：
```sh
$ docker run myip 
当前 IP：14.17.22.22  来自于：中国 广东 深圳  电信

$ docker run myip -i
HTTP/1.1 200 OK
Content-Length: 66
Content-Type: text/plain; charset=utf-8
Date: Thu, 28 Jan 2021 03:33:42 GMT
Set-Cookie: __jsluid_h=cfcf6aeb5f7a4eb7953e602c451813a7; max-age=31536000; path=/; HttpOnly
X-Cache: bypass
X-Cache: MISS from SZ-SQUIDWEB-30
X-Cache-Lookup: MISS from SZ-SQUIDWEB-30:8080
X-Via-Jsl: 1d9bd9a,-

当前 IP：14.17.22.22  来自于：中国 广东 深圳  电信
```
可以看到，这次成功了。这是因为当存在`ENTRYPOINT`后，`CMD`的内容将会作为参数传给`ENTRYPOINT`，而这里`-i`就是新的`CMD`，因此会作为参数传给`curl`，从而达到了我们预期的效果。

**场景二：应用运行前的准备工作**  
启动容器就是启动主进程，但有些时候，启动主进程前，需要一些准备工作。

比如`mysql`类的数据库，可能需要一些数据库配置、初始化的工作，这些工作要在最终的`mysql`服务器运行之前解决。

此外，可能希望避免使用`root`用户去启动服务，从而提高安全性，而在启动服务前还需要以`root`身份执行一些必要的准备工作，最后切换到服务用户身份启动服务。或者除了服务外，其它命令依旧可以使用`root`身份执行，方便调试等。

这些准备工作是和容器`CMD`无关的，无论`CMD`为什么，都需要事先进行一个预处理的工作。这种情况下，可以写一个脚本，然后放入`ENTRYPOINT`中去执行，而这个脚本会将接到的参数（也就是 `<CMD>`）作为命令，在脚本最后执行。比如官方镜像`redis`中就是这么做的：
```dockerfile
FROM alpine:3.4
...
RUN addgroup -S redis && adduser -S -G redis redis
...
ENTRYPOINT ["docker-entrypoint.sh"]

EXPOSE 6379
CMD [ "redis-server" ]
``` 
可以看到其中为了`redis`服务创建了`redis`用户，并在最后指定了`ENTRYPOINT`为`docker-entrypoint.sh`脚本。
```sh
#!/bin/sh
...
# allow the container to be started with `--user`
if [ "$1" = 'redis-server' -a "$(id -u)" = '0' ]; then
	find . \! -user redis -exec chown redis '{}' +
	exec gosu redis "$0" "$@"
fi

exec "$@"
```
该脚本的内容就是根据`CMD`的内容来判断，如果是`redis-server`的话，则切换到`redis`用户身份启动服务器，否则依旧使用`root`身份执行。比如：
```sh
$ docker run -it redis id
uid=0(root) gid=0(root) groups=0(root)
```

#### ENV 设置环境变量
格式有两种：

- `ENV <key> <value>`
- `ENV <key1>=<value1> <key2>=<value2>...`   

这个指令很简单，就是设置环境变量而已，无论是后面的其它指令，如`RUN`，还是运行时的应用，都可以直接使用这里定义的环境变量。
```dockerfile
ENV VERSION=1.0 DEBUG=on \
    NAME="Happy Feet"
```
定义了环境变量，那么在后续的指令中，就可以使用这个环境变量。

#### ARG 构建参数
- 格式：`ARG <参数名>[=<默认值>]`

构建参数和`ENV`的效果一样，都是设置环境变量。所不同的是，`ARG`所设置的构建环境的环境变量，在将来容器运行时是不会存在这些环境变量的。但是不要因此就使用`ARG`保存密码之类的信息，因为`docker history`还是可以看到所有值的。

```dockerfile
# 只在 FROM 中生效
ARG DOCKER_USERNAME=library

FROM ${DOCKER_USERNAME}/alpine

# 要想在 FROM 之后使用，必须再次指定,在FROM 之后使用变量，必须在每个阶段分别指定
ARG DOCKER_USERNAME=library

RUN set -x ; echo ${DOCKER_USERNAME}

FROM ${DOCKER_USERNAME}/alpine

# 在FROM 之后使用变量，必须在每个阶段分别指定
ARG DOCKER_USERNAME=library

RUN set -x ; echo ${DOCKER_USERNAME}
```

#### VOLUME 定义匿名卷
格式为：

- `VOLUME ["<路径1>", "<路径2>"...]`
- `VOLUME <路径>`

容器运行时应该尽量保持容器存储层不发生写操作，对于数据库类需要保存动态数据的应用，其数据库文件应该保存于卷(`volume`)中，为了防止运行时用户忘记将动态文件所保存目录挂载为卷，在`Dockerfile`中，我们可以事先指定某些目录挂载为匿名卷，这样在运行时如果用户不指定挂载，其应用也可以正常运行，不会向容器存储层写入大量数据。

```dockerfile
VOLUME /data
```
这里的`/data`目录就会在运行时自动挂载为匿名卷，任何向`/data`中写入的信息都不会记录进容器存储层，从而保证了容器存储层的无状态化。当然，运行时可以覆盖这个挂载设置。比如：
```sh
docker run -d -v mydata:/data xxxx
```
在这行命令中，就使用了`mydata`这个命名卷挂载到了`/data`这个位置，替代了`Dockerfile`中定义的匿名卷的挂载配置。

#### EXPOSE 声明端口
格式为:`EXPOSE <端口1> [<端口2>...]`。

`EXPOSE`指令是声明运行时容器提供服务端口，这只是一个声明，在运行时并不会因为这个声明应用就会开启这个端口的服务。在`Dockerfile`中写入这样的声明有两个好处，一个是帮助镜像使用者理解这个镜像服务的守护端口，以方便配置映射；另一个用处则是在运行时使用随机端口映射时，也就是`docker run -P`时，会自动随机映射`EXPOSE`的端口。

要将`EXPOSE`和在运行时使用`-p <宿主端口>:<容器端口> `区分开来。
`-p`，是映射宿主端口和容器端口，换句话说，就是将容器的对应端口服务公开给外界访问，而`EXPOSE`仅仅是声明容器打算使用什么端口而已，并不会自动在宿主进行端口映射。


#### WORKDIR 指定工作目录
格式为 `WORKDIR <工作目录路径>`。

使用`WORKDIR`指令可以来指定工作目录（或者称为当前目录），以后各层的当前目录就被改为指定的目录，如该目录不存在，`WORKDIR`会帮你建立目录。
```dockerfile
WORKDIR /app

RUN echo "hello" > world.txt
```
上述就会将`hello`输入到`/app/world.txt`中去。

如果你的`WORKDIR`指令使用的相对路径，那么所切换的路径与之前的`WORKDIR`有关：
```dockerfile
WORKDIR /a
WORKDIR b
WORKDIR c

RUN pwd
```
`pwd`输出的结果为`/a/b/c`。

#### USER 指定当前用户
格式：`USER <用户名>[:<用户组>]`

`USER` 指令和` WORKDIR `相似，都是改变环境状态并影响以后的层。`WORKDIR` 是改变工作目录，`USER `则是改变之后层的执行` RUN`, `CMD` 以及 `ENTRYPOINT `这类命令的身份。

tips:`USER` 只是帮助你切换到指定用户而已，这个用户必须是事先建立好的，否则无法切换。
```dockerfile
RUN groupadd -r redis && useradd -r -g redis redis
USER redis
RUN [ "redis-server" ]
```
如果以`root`执行的脚本，在执行期间希望改变身份，比如希望以某个已经建立好的用户来运行某个服务进程，不要使用`su`或者`sudo`，这些都需要比较麻烦的配置，而且在`TTY`缺失的环境下经常出错。建议使用`gosu`。

```dockerfile
# 建立 redis 用户，并使用 gosu 换另一个用户执行命令
RUN groupadd -r redis && useradd -r -g redis redis
# 下载 gosu
RUN wget -O /usr/local/bin/gosu "https://github.com/tianon/gosu/releases/download/1.12/gosu-amd64" \
    && chmod +x /usr/local/bin/gosu \
    && gosu nobody true
# 设置 CMD，并以另外的用户执行
CMD [ "exec", "gosu", "redis", "redis-server" ]
```

#### HEALTHCHECK 健康检查
- `HEALTHCHECK [选项] CMD <命令>`：设置检查容器健康状况的命令
- `HEALTHCHECK NONE`：如果基础镜像有健康检查指令，使用这行可以屏蔽掉其健康检查指令

`HEALTHCHECK` 指令是告诉`Docker`应该如何进行判断容器的状态是否正常，这是`Docker 1.12`引入的新指令。

在没有`HEALTHCHECK`指令前，`Docker`引擎只可以通过容器内主进程是否退出来判断容器是否状态异常。很多情况下这没问题，但是如果程序进入死锁状态，或者死循环状态，应用进程并不退出，但是该容器已经无法提供服务了。在`1.12`以前，`Docker`不会检测到容器的这种状态，从而不会重新调度，导致可能会有部分容器已经无法提供服务了却还在接受用户请求。


而自`1.12`之后，`Docker`提供了`HEALTHCHECK`指令，通过该指令指定一行命令，用这行命令来判断容器主进程的服务状态是否还正常，从而比较真实的反应容器实际状态。

当在一个镜像指定了`HEALTHCHECK`指令后，用其启动容器，初始状态会为`starting`，在`HEALTHCHECK`指令检查成功后变为`healthy`，如果连续一定次数失败，则会变为`unhealthy`。

`HEALTHCHECK`支持下列选项：

- `--interval=<间隔>`：两次健康检查的间隔，默认为`30`秒；
- `--timeout=<时长>`：健康检查命令运行超时时间，如果超过这个时间，本次健康检查就被视为失败，默认`30`秒；
- `--retries=<次数>`：当连续失败指定次数后，则将容器状态视为`unhealthy`，默认 `3`次。

和`CMD`, `ENTRYPOINT` 一样，`HEALTHCHECK`只可以出现一次，如果写了多个，只有最后一个生效。

在`HEALTHCHECK [选项] CMD `后面的命令，格式和`ENTRYPOINT`一样，分为`shell`格式和`exec`格式。命令的返回值决定了该次健康检查的成功与否：`0：成功`；`1：失败`；`2：保留，不要使用这个值`。

假设我们有个镜像是个最简单的`Web`服务，我们希望增加健康检查来判断其`Web`服务是否在正常工作，我们可以用`curl`来帮助判断，其`Dockerfile`的`HEALTHCHECK`可以这么写：
```dockerfile
FROM nginx
RUN apt-get update && apt-get install -y curl && rm -rf /var/lib/apt/lists/*
HEALTHCHECK --interval=5s --timeout=3s \
  CMD curl -fs http://localhost/ || exit 1
```
这里我们设置了每`5`秒检查一次（这里为了试验所以间隔非常短，实际应该相对较长），如果健康检查命令超过`3`秒没响应就视为失败，并且使用`curl -fs http://localhost/ || exit 1 `作为健康检查命令。

使用`docker build`来构建这个镜像：
```sh
$ docker build -t myweb:v1 .
```
构建好了后，我们启动一个容器：
```sh
$ docker run -d --name web -p 80:80 myweb:v1
```
当运行该镜像后，可以通过`docker container ls`看到最初的状态为` (health: starting)`：
```sh
$ docker container ls
CONTAINER ID   IMAGE      COMMAND                  CREATED         STATUS                   PORTS                NAMES
f21658a26698   myweb:v1   "/docker-entrypoint.…"   7 seconds ago   Up 6 seconds (healthy: starting)   0.0.0.0:80->80/tcp   web
```
在等待几秒钟后，再次`docker container ls`，就会看到健康状态变化为了 `(healthy)`：
```sh
$ docker container ls
CONTAINER ID   IMAGE      COMMAND                  CREATED          STATUS                    PORTS                NAMES
f21658a26698   myweb:v1   "/docker-entrypoint.…"   41 seconds ago   Up 39 seconds (healthy)   0.0.0.0:80->80/tcp   web
```

如果健康检查连续失败超过了重试次数，状态就会变为 `(unhealthy)`。

为了帮助排障，健康检查命令的输出（包括 `stdout` 以及 `stderr`）都会被存储于健康状态里，可以用 `docker inspect `来查看。


#### LABEL 指令
`LABEL` 指令用来给镜像以键值对的形式添加一些元数据（`metadata`）。
```dockerfile
LABEL <key>=<value> <key>=<value> <key>=<value> ...
```
我们还可以用一些标签来申明镜像的作者、文档地址等：
```dockerfile
LABEL org.opencontainers.image.authors="yeasy"

LABEL org.opencontainers.image.documentation="https://yeasy.gitbooks.io"
```
具体可以参考 [https://github.com/opencontainers/image-spec/blob/master/annotations.md]()

#### SHELL 指令
格式：`SHELL ["executable", "parameters"]`

`SHELL `指令可以指定 `RUN` `ENTRYPOINT` `CMD` 指令的 `shell`，`Linux` 中默认为 `["/bin/sh", "-c"]`
```dockerfile
SHELL ["/bin/sh", "-c"]

RUN lll ; ls

SHELL ["/bin/sh", "-cex"]

RUN lll ; ls
```

两个`RUN`运行同一命令，第二个`RUN`运行的命令会打印出每条命令并当遇到错误时退出。

当 `ENTRYPOINT` `CMD` 以 `shell` 格式指定时，`SHELL` 指令所指定的 `shell` 也会成为这两个指令的 `shell`
```dockerfile
SHELL ["/bin/sh", "-cex"]

# /bin/sh -cex "nginx"
ENTRYPOINT nginx
```
```dockerfile
SHELL ["/bin/sh", "-cex"]

# /bin/sh -cex "nginx"
CMD nginx
```




**[⬆ 返回顶部](#目录)**