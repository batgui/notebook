git是一个分布式管理系统

### 基本命令

将目录变成git可管理的仓库
```bash
git init
```
添加文件到git仓库
```bash
git add 
git commit -m "message" 	
```
查看添加结果
```bash
git status
```
查看修改内容
```bash
git diff README.txt
```
查看历史记录
```bash
git log --pretty=oneline	
```
回退到上一个版本
```bash
git reset --hard HEAD^
```
上上个版本用HEAD^^
```bash
git reset --hard 1094a
```
查看历史git命令
```bash
git reflog
```

查看工作区和版本库里面最新版本的区别：
```bash
git diff HEAD -- readme.txt
```
丢掉工作区的修改
```bash
git checkout -- readme.txt
```
将远程库与本地仓库关联
```bash
git remote add origin <address>
```
将本地仓库的内容添加到远程库中
```bash
git push -u origin master
```

### git 分支管理

创建并切换分支
```bash
git checkout -b dev
```
查看当前分支

```bash
git branch
```
切换到 master分支
```bash
git checkout master

```
合并指定分支到当前分支

```bash
git merge dev
```

删除分支：
```bash
git branch -d <name>
```
查看分支合并图
```bash
git log --graph --pretty=oneline --abbrev-commit
```

禁用fastforward的git merge,默认fastforward看不出曾经有合并，用--no-ff参数合并后的历史有分支。
```bash
git merge --no-ff -m "merge with no-ff" dev
```

当遇到一个bug时，我们可以通过新的临时分支来修复，修复将临时分支删除。

把当前工作现场存储起来
```bash

git stash
```
查看工作现场
```bash
git stash list
```
工作现场恢复
```bash
git stash apply
git stash drop
```
或者
```bash
git stash pop
```

在创建新功能的时候最好新建一个feature 分支在上面开发，完成后合并删除该分支。

丢弃一个没有合并过的分支
```bash
git branch -D <branch_name>

```

在本地创建和远程对应的分支

```bash
git checkout -b branch-name origin/branch-name
```

建立本地分支和远程分支的关联
```bash
git branch --set-upstream branch-name origin/branch-name
```
