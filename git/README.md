# Git的学习:see_no_evil:  
> Git 是一个开源的分布式版本控制系统，用于敏捷高效地处理任何或小或大的项目。  

关于版本控制
VCS:(Concurrent Versions System)是一种记录一个或若干文件内容变化，以便将来查阅特定版本修订情况的系统

本地版本控制系统
RCS:(Revision Control System)在硬盘上保存补丁集(补丁集是指文件修改前后的变化）;通过应用所有的补丁可以重新计算出各个版本的文件内容。

集中化的版本控制系统
SCCS:(Source Code Control System)版本库集中放在中央服务器。

分布式版本控制系统
DVCS: 把集中式版本控制系统的服务端和客户端都交给参与开发的客户端来保管，只有需要不同开发者合并时，才需要一个中转站来完成。

下面的内容就是列举了常用的 Git 命令和一些小技巧，可以通过 "页面内查找" 的方式进行快速查询：`Ctrl/Command+f`。


## 目录
* [展示帮助信息](#展示帮助信息)
* [配置本机的用户名和Email地址](#配置本机的用户名和Email地址)  
* [Git-ssh创建](#ssh创建)  
* [Git-创建仓库](#Git-创建仓库) 
* [Git-增加文件](#Git-增加文件)  
* [Git-删除文件](#Git-删除文件)  
* [Git-代码提交](#Git-代码提交)  
* [Git-查看信息](#Git-查看信息) 
* [Git-分支](Git-分支) 
* [Git-列出所有远程分支](#Git-列出所有远程分支) 
* [Git-列出所有本地和远程分支](#Git-列出所有本地和远程分支) 
* [快速切换到上一个分支](#快速切换到上一个分支)
* [删除已经合并到 master 的分支](#删除已经合并到 master 的分支)
* [展示本地分支关联远程仓库的情况](#展示本地分支关联远程仓库的情况)  
* [关联远程分支](#关联远程分支)
* [查看远程分支和本地分支的对应关系](#查看远程分支和本地分支的对应关系)
* [远程删除了分支本地也想删除](#远程删除了分支本地也想删除)
* [创建并切换到本地分支](#创建并切换到本地分支)
* [从远程分支中创建并切换到本地分支](#从远程分支中创建并切换到本地分支)
* [删除本地分支](#删除本地分支)
* [删除远程分支](#删除远程分支)
* [重命名本地分支](#重命名本地分支)
* [放弃工作区的修改](#放弃工作区的修改)
* [恢复删除的文件](#恢复删除的文件)
* [以新增一个 commit 的方式还原某一个 commit 的修改](#以新增一个-commit-的方式还原某一个-commit-的修改)
* [回到某个 commit 的状态，并删除后面的 commit](#回到某个-commit-的状态并删除后面的-commit)
* [修改上一个 commit 的描述](#修改上一个-commit-的描述)
* [查看commit历史](#查看commit历史)
* [查看某段代码是谁写的](#查看某段代码是谁写的)
* [显示本地更新过 HEAD 的 git 命令记录](#显示本地更新过 HEAD 的 git 命令记录)
* [修改作者名](#修改作者名)
* [修改远程仓库的 url](#修改远程仓库的 url)
* [增加远程仓库](#增加远程仓库)
* [列出所有远程仓库](#列出所有远程仓库)
* [合并指定分支到当前分支](#合并指定分支到当前分支)
* [选择一个commit 合并到当前分支](#选择一个commit 合并到当前分支)
* [回到远程仓库的状态](#回到远程仓库的状态)   
* [重设第一个 commit](#重设第一个 commit) 
* [查看冲突文件列表](#查看冲突文件列表)
* [展示工作区和暂存区的不同](#展示工作区和暂存区的不同)
* [展示暂存区和最近版本的不同](#展示暂存区和最近版本的不同)
* [下载远程仓库的所有变动](#下载远程仓库的所有变动)
* [取回远程仓库的变化，并与本地分支合并](#取回远程仓库的变化，并与本地分支合并)
* [上传本地指定分支到远程仓库](#上传本地指定分支到远程仓库)
* [强行推送当前分支到远程仓库,即使有冲突](#强行推送当前分支到远程仓库,即使有冲突)
* [推送所有分支到远程仓库](#推送所有分支到远程仓库)
* [恢复暂存区的指定文件到工作区](#恢复暂存区的指定文件到工作区)
* [恢复某个commit的指定文件到暂存区和工作区](#恢复某个commit的指定文件到暂存区和工作区)
* [恢复暂存区的所有文件到工作区](#恢复暂存区的所有文件到工作区)
* [重置暂存区的指定文件，与上一次commit保持一致，但工作区不变](#重置暂存区的指定文件，与上一次commit保持一致，但工作区不变)
* [重置暂存区与工作区，与上一次commit保持一致](#重置暂存区与工作区，与上一次commit保持一致)
* [重置当前分支的指针为指定commit，同时重置暂存区，但工作区不变](#重置当前分支的指针为指定commit，同时重置暂存区，但工作区不变)
* [git配置http和socks代理](#git配置http和socks代理)
* [git配置ssh代理](#git配置ssh代理)


## 展示帮助信息
```sh
git help -g
```
The command output as below:

```
The common Git guides are:
   attributes          Defining attributes per path
   cli                 Git command-line interface and conventions
   core-tutorial       A Git core tutorial for developers
   cvs-migration       Git for CVS users
   diffcore            Tweaking diff output
   everyday            A useful minimum set of commands for Everyday Git
   glossary            A Git Glossary
   hooks               Hooks used by Git
   ignore              Specifies intentionally untracked files to ignore
   modules             Defining submodule properties
   namespaces          Git namespaces
   repository-layout    Git Repository Layout
   revisions           Specifying revisions and ranges for Git
   tutorial            A tutorial introduction to Git
   tutorial-2          A tutorial introduction to Git: part two
   workflows           An overview of recommended workflows with Git

'git help -a' and 'git help -g' list available subcommands and some concept guides. See 'git help <command>' or 'git help <concept>' to read about a specific subcommand or concept.
```

## 配置本机的用户名和Email地址

```sh
git config --global user.name "your name"
git config --global user.email "your email@example.com"
```

## Git ssh创建

```sh
ssh-keygen -t rsa -C 'your email@example.com'
```

## Git 创建仓库

```sh
git init
```

## Git 增加文件
添加指定文件到暂存区

```sh
git add <file1> <file2> ...
```

当然也可以使用如下命令添加指定目录到暂存区,包括子目录

```sh
git add <dir>
```

添加当前目录的所有文件到暂存区

```
git add .
```

## Git 删除文件

```
git rm <file1> <file2> ...
```

## Git 代码提交
提交暂存区到仓库区
```
git commit -m <message>
```

提交暂存区的指定文件到仓库区

```
git commit <file1> <file2> ... -m <message>
```
提交时显示所有diff信息

```
git commit -v
```

## Git 查看信息

```sh
git status
```

## Git 分支
列出所有本地分支

```
git branch 
```

## 列出所有远程分支
-r 参数相当于:remote
```sh
git branch -r
```

## 列出所有远程分支和远程分支
-a 参数相当于: all
```sh
git branch -a
```

新建一个分支,但仍然停留在当前分支
```sh
git branch [branch-name]
```

## 快速切换到上一个分支

```sh
git checkout -
```

## 删除已经合并到 master 的分支

```sh
git branch --merged master | grep -v '^\*\|  master' | xargs -n 1 git branch -d
```

## 展示本地分支关联远程仓库的情况
```sh
git branch -vv
```

## 关联远程分支

关联之后，`git branch -vv` 就可以展示关联的远程分支名了，同时推送到远程仓库直接：`git push`，不需要指定远程仓库了。
```sh
git branch -u origin/mybranch
```

## 查看远程分支和本地分支的对应关系

```sh
git remote show origin
```

## 远程删除了分支本地也想删除

```sh
git remote prune origin
```

## 创建并切换到本地分支
```sh
git checkout -b <branch-name>
```

## 从远程分支中创建并切换到本地分支

```sh
git checkout -b <branch-name> origin/<branch-name>
```

## 删除本地分支

```sh
git branch -d <local-branchname>
```

## 删除远程分支

```sh
git push origin --delete <remote-branchname>
```

或者

```sh
git push origin :<remote-branchname>
```

## 重命名本地分支

```sh
git branch -m <new-branch-name>
```

## 放弃工作区的修改
```sh
git checkout <file-name>
```

## 恢复删除的文件

```sh
git rev-list -n 1 HEAD -- <file_path> #得到 deleting_commit

git checkout <deleting_commit>^ -- <file_path> #回到删除文件 deleting_commit 之前的状态
```

## 以新增一个 commit 的方式还原某一个 commit 的修改

```sh
git revert <commit-id>
```

## 回到某个commit的状态,并删除后面的commit
和 revert的区别: reset命令会抹去某个commit-id之后的所有commit
```sh
git reset <commit-id>  #默认就是-mixed参数。

git reset  -- mixed HEAD^  #回退至上个版本，它将重置HEAD到另外一个commit,并且重置暂存区以便和HEAD相匹配，但是也到此为止。工作区不会被更改。

git reset -- soft HEAD~3  #回退至三个版本之前，只回退了commit的信息，暂存区和工作区与回退之前保持一致。如果还要提交，直接commit即可  

git reset -- hard <commit-id>  #彻底回退到指定commit-id的状态，暂存区和工作区也会变为指定commit-id版本的内容
```

## 修改上一个commit的描述
如果暂存区有改动，同时也会将暂存区的改动提交到上一个commit
```sh
git commit --amend
```

## 查看 commit 历史
```sh
git log
```

## 查看某段代码是谁写的

blame 的意思为‘责怪’，你懂的。

```sh
git blame <file-name>
```

## 显示本地更新过 HEAD 的 git 命令记录

每次更新了 HEAD 的 git 命令比如 commint、amend、cherry-pick、reset、revert 等都会被记录下来（不限分支），就像 shell 的 history 一样。
这样你可以 reset 到任何一次更新了 HEAD 的操作之后，而不仅仅是回到当前分支下的某个 commit 之后的状态。

```sh
git reflog
```

## 修改作者名

```sh
git commit --amend --author='Author Name <email@address.com>'
```

## 修改远程仓库的 url

```sh
git remote set-url origin <URL>
```

## 增加远程仓库

```sh
git remote add origin <remote-url>
```

## 列出所有远程仓库

```sh
git remote
```

## 合并指定分支到当前分支

```sh
git merge <branch-name>
```

## 选择一个commit 合并到当前分支

```sh
git cherry-pick <commit-id>
```

## 回到远程仓库的状态

抛弃本地所有的修改，回到远程仓库的状态。
```sh
git fetch --all && git reset --hard origin/master
```
## 重设第一个 commit

也就是把所有的改动都重新放回工作区，并**清空所有的 commit**，这样就可以重新提交第一个 commit 了
```sh
git update-ref -d HEAD
```
## 查看冲突文件列表
展示工作区的冲突文件列表
```sh
git diff --name-only --diff-filter=U
```
## 展示工作区和暂存区的不同
输出**工作区**和**暂存区**的 different (不同)。
```sh
git diff
```

还可以展示本地仓库中任意两个 commit 之间的文件变动：
```sh
git diff <commit-id> <commit-id>
```

## 下载远程仓库的所有变动

```sh
git fetch <remote>
```

## 取回远程仓库的变化，并与本地分支合并

```sh
git pull <remote> <branch>
```

## 上传本地指定分支到远程仓库

```sh
git push <remote> <branch>
```

## 强行推送当前分支到远程仓库,即使有冲突

```sh
git push <remote> --force
```

或者
```sh
git push -f <remote-name> <branch-name>
```

## 推送所有分支到远程仓库

```sh
git push <remote> -all
```

## 恢复暂存区的指定文件到工作区

```sh
git checkout <file>
```

## 恢复某个commit的指定文件到暂存区和工作区

```sh
git checkout <commit-id> <file>
```

## 恢复暂存区的所有文件到工作区

```sh
git chekcout .
```

## 重置暂存区的指定文件，与上一次commit保持一致，但工作区不变

```sh
git reset <file>
```

## 重置暂存区与工作区，与上一次commit保持一致

```sh
git reset --hard
```

## 重置当前分支的指针为指定commit，同时重置暂存区，但工作区不变

```sh
git reset <commit-id>
```


## git 配置 http 和 socks 代理

```sh
git config --global https.proxy 'http://127.0.0.1:8001'   # 适用于 privoxy 将 socks 协议转为 http 协议的 http 端口
git config --global http.proxy 'http://127.0.0.1:8001'
git config --global socks.proxy "127.0.0.1:1080"
```

## git 配置 ssh 代理

```sh
$ cat ~/.ssh/config
Host gitlab.com
ProxyCommand nc -X 5 -x 127.0.0.1:1080 %h %p    # 直接使用 shadowsocks 提供的 socks5 代理端口

Host github.com
ProxyCommand nc -X 5 -x 127.0.0.1:1080 %h %p    
```
**[⬆ 返回顶部](#目录)**



