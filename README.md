# ChaseLight

## 介绍
**ChaseLight** 是基于 Cocos2D-X 3.15 引擎版本创建的一个简单游戏 demo。
玩家通过操作**主星**，向目标星体前进，通过达成条件（规定时间内达到规定得分）来完成目标；行进过程中，会发生星体之间的碰撞，与**圆星**碰撞会获得其部分能量并计算得分，与其他**星体**（如流星，方星等）碰撞则会损失部分能量，当能量耗尽时游戏结束。

## 演示
![Markdown](http://i1.buimg.com/1949/f144b64d416fe9d5.png)
![Markdown](http://i1.buimg.com/1949/755b373f796502fa.png)
![Markdown](http://i1.buimg.com/1949/a3bc4fe942222dcd.png)
![Markdown](http://i1.buimg.com/1949/ebbcc06170a2e9ea.png)

## 项目结构
**ChaseLight**的代码结构：
![Markdown](http://i1.buimg.com/1949/8916e6ce2b2f8f70.png)

Cocos2d-x采用导演、场景、层的概念，以此为基础建立项目结构，**ChaseLight**也不例外。以下：
- Monitor：监视器，管理场景表现所需要的操作，如操作音频、计时器、对象池等；
- Platform：平台，存放需要多平台兼容处理时的代码，如多点触摸、各平台的 SDK 等；
- Reference：引用，一些头文件的集合，也包括一些常用的变量、常量，如事件类型、渲染层级标记等；
- Resolution：解决方案，计划中是方第三方库用的，所以称之为解决方案，如 d3des 加解密，LevelDB（*后来发现在真机上有问题，就废弃了 LevelDB*）等；
- Scene：核心部分，负责场景的表现，细分为场景 Scene、层 Layer、组件 Com、辅助方法 Util，这些都直接与 UI 相关；
- Service：服务，相当于后台，存放配置解析、数据库操作等代码；
- Game：游戏是单进程的，因此应该设计为一个单例，Game 是唯一的，游戏的状态（启动、关闭、进入前台，进入后台等）应该由其统一把控；如在启动时会启动对应所有相关的服务 Service，在结束时关闭所有服务；
- 其他
