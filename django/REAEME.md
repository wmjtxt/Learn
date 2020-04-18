学习Django
====

主要参考：

* 一个浅显易懂的Django教程: [A Complete Beginner's Guide to Django](https://simpleisbetterthancomplex.com/series/beginners-guide/1.11/)

* Github上中文翻译（进行中）repo: [A Complete Beginner's Guide to Django 翻译计划](https://github.com/wzhbingo/django-beginners-guide)

根据上面的教程一步一步执行命令，感觉还是会忘，所以就总结一个简略版，加深记忆，同时也方便以后回看。

# 目录
@[TOC]

- [0.环境搭建](###0环境搭建)
- [1.新建Django项目](###1新建django项目)
- [2.Django应用](#2django应用)
- [3.第一个视图：Hello,World](#3第一个视图helloworld)
- [4.系统设计](#4系统设计)
- [5.Django模型设计](#5django模型设计)
- [6.迁移模型](#6迁移模型)
- [7.模型操作](#7模型操作)
- [8.测试](#8测试)
- [9.静态文件设置](#9静态文件设置)
- [10.Django Admin](#10djangoadmin)
- [11.]()
- [12.]()

## 建站步骤（简略）
### 0.环境搭建
* 安装python3
    * 略
* 安装Virtualenv
    * `sudo pip3 install virtualenv`
* 使用virtualenv
    * 新建文件夹myproject : `mkdir myproject`、 `cd myproject`
    * 创建虚拟环境 : `virtualenv venv -p python3`
    * 激活虚拟环境 : `source venv/bin/activate`
    * 退出虚拟环境 : `deactivate`
* 安装Django
    * `pip install django==1.11.4`

### 1.新建Django项目

* **创建Django项目**: 在myproject文件夹下，开启虚拟环境后，执行下面的命令，创建新的Django项目, 其中`myproject`为项目名称:
    * `django-admin startproject myproject`

* **查看目录结构**: 创建项目成功后，可以使用命令`tree myproject`查看myproject的目录结构，其中的主要文件如下:
    * manage.py
    * \_\_init\_\_.py
    * settings.py
    * urls.py
    * wsgi.py

* **开启服务器**: 在manage.py所在文件夹下，执行下面的命令，开启网络服务器:
    * `python manage.py runserver`

### 2.Django应用

* 在Django项目中，有两个重要的概念：
    * **app**: 完成某个任务的web应用程序, app由models（数据库表）, views（视图）, templates（模板）, tests（测试）组成。
    * **project**: 是配置和应用的集合, 一个项目由一个或多个应用组成。

* **创建Django应用**: 在manage.py所在文件夹执行以下命令,其中`boards`为app名称
    * `django-admin startapp boards`
* **文件解释**: 创建boards应用后，会生成一个以boards为名的文件夹，其中的主要文件（夹）如下：
    * **migrations/**: 存储一些文件，以跟踪models.py文件的变更，用来保持数据库和models.py的同步
    * **admin.py**: Django admin配置文件
    * **apps.py**: 本应用的配置文件
    * **models.py**: 定义web应用数据实例
    * **tests.py**: 单元测试
    * **views.py**: 处理web应用程序请求响应周期的文件

* **启用boards应用**
    * 找到settings.py的`INSTALLED_APPS`列表, 将应用`'boards'`添加到该列表中。

### 3.第一个视图：Hello, World!

在views.py和urls.py中添加如下代码:

views.py
```python
from django.http import HttpResponse#new
def home(request):#new
    return HttpResponse('Hello, World!')#new
```
urls.py
```python
from django.conf.urls import url
from django.contrib import admin

from boards import views #new

urlpatterns = [
    url(r'^$', views.home, name='home'),#new
    url(r'^admin/', admin.site.urls),
]
```

执行命令`python manage.py runserver`，在浏览器打开http://127.0.0.1:8000，可以看到效果啦

### 4.系统设计
项目是一个论坛系统，由多个板块(Boards)组成, 板块由主题帖(Topic)组成，主题帖里有回复帖(Post)，主题帖和回复帖均由用户(User)创建。

所以这个项目共包含四个类Board, Topic, Post, User。由于Django在contrib中内置了User类，所以只需创建其余三个类。

以下两方面需要考虑：

* **各类之间的关系**: 
    * Board and Topic: 1-0..\*
    * Topic and Post: 1-1..\*
    * Topic and User: 0..\*-1
    * Post and User: 0..\*-1
* **各类（模型）的设计**: 
    * Board: 包含两个字段：name和description
    * Topic: 包括四个字段：subject，last\_update，starter, board
    * Post: 有一个message字段，用于存储回复内容，create\_at，update\_at

### 5.Django模型设计

Board, Topic, Post这些模型的设计对应着应用程序的数据库设计。

根据上面的模型设计，相关代码实现在boards/models.py文件中。
```python
from django.db import models
from django.contrib.auth.models import User


class Board(models.Model):
    name = models.CharField(max_length=30, unique=True)
    description = models.CharField(max_length=100)


class Topic(models.Model):
    subject = models.CharField(max_length=255)
    last_updated = models.DateTimeField(auto_now_add=True)
    board = models.ForeignKey(Board, related_name='topics')
    starter = models.ForeignKey(User, related_name='topics')


class Post(models.Model):
    message = models.TextField(max_length=4000)
    topic = models.ForeignKey(Topic, related_name='posts')
    created_at = models.DateTimeField(auto_now_add=True)
    updated_at = models.DateTimeField(null=True)
    created_by = models.ForeignKey(User, related_name='posts')
    updated_by = models.ForeignKey(User, null=True, related_name='+')
```

上面所有模型都是django.db.models.Model类的子类，每个类都将被转换成数据库表。

### 6.迁移模型

迁移模型就是告诉Django创建数据库，分两步

第一步，执行`python manage.py makemigrations`，执行完产生一个0000\_initial.py文件，该文件代表了应用的当前状态，相当于做了一个汇总，为接下来转换数据库做准备。

第二步，执行`python manage.py migrate`，这一步根据迁移文件生成数据库。

### 7.模型操作

建好模型，就可以对它进行操作了。

操作之前，要先启动Python shell:

`python manage.py shell`

对模型进行操作的方法总结如下:

|操作|代码示例|
|-|-|
|创建一个对象而不保存|board = Board()|
|保存一个对象|board.save()|
|数据库中创建并保存一个对象|Board.objects.create(name='..',description='..')|
|列出所有对象|Board.objects.all()|
|通过字段标识获取单个对象|Board.objects.get(id=1)|


### 8.测试

测试环节非常重要。比如下面的简单例子:

```python
from django.core.urlresolvers import reverse
from django.test import TestCase

class HomeTests(TestCase):
    def test_home_view_status_code(self):
        url = reverse('home')
        response = self.client.get(url)
        self.assertEquals(response.status_code, 200)
```
这是一个非常简单但非常有用的测试用例，测试的是请求URL后返回的响应状态码。状态码200意味着成功。当有很多个视图（比如上百个），
用上述测试，只需一个命令，就能够测试是否所有视图返回成功。如果没有自动化测试，我们就需要逐一检查每个页面。

若要查看更详细的信息，可以设置verbosity为2
`python manage.py test --verbosity=2`
`verbosity为0表示无输出，为1表示正常输出，2表示详细输入`

### 9.静态文件设置

静态文件是指CSS, JavaScript


### 10.Django Admin

### 11.
