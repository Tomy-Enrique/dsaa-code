git add .
git commit -m "注释"

添加远程仓库地址
git remote add origin https://github.com/Tomy-Enrique/dsaa-code.git
修改远程仓库地址
git remote set-url origin https://github.com/Tomy-Enrique/dsaa-code.git
删除远程仓库地址
git remote rm origin

git push origin master

更新push
git push --force https://github.com/Tomy-Enrique/dsaa-code.git

列出分支
git branch
建立分支
git branch <branch>
切换分支
git checkout <branch>
删除分支
git branch -d <branch> 
合并分支
git merge <branch>
推送分支
git push origin <branch>

查看远程分支
git branch -r
删除远程分支
git branch -r -d origin/<branch>

删除远程仓库文件
git rm -r --cached <file>
git commit -m ""
git push origin master