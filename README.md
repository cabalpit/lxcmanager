# Lxc Manager #

LXC Manager provide a set of functions to visually manage LXC unprivileged containers. The applciation use LXC Api to manage LXC. To use the application you must have LXC installed on your linux machine.

### What is this repository for? ###

* LXC Manager is for configure LXC unprivileged containers. The application can create containers, start, stop, destroy and configure unprivileged containers.
* Version 1.0
* [Learn More](https://lxcmanager.elpexdynamic.com)

### How do I get set up? ###

* Qt SDK Qt 5.15
* environment g++ v10 and c++11
* Dependencies: lxc-dev 4.0 installed and zlib installed (file compression)
> ```
> ~:# apt install lxc lxc-dev
> ~:# apt install zlib1g-dev
> ```
* Database configuration: Qt SQLite
* How to run tests: use [Qt test](https://doc.qt.io/qt-5/qtest-overview.html) 
* Deployment instructions: Use Qt deploy application to create installer.

### Contribution guidelines ###

* Writing tests in separate folder with Qt unit test.
* Code review
* Other guidelines we use camelcase, 
	- For attribute members of the class use m_ to prefix the name of attributes, 
	- For methods of the class use Qt style example: 
	
	> ```
        > class MyClass;
        >
        > // attributes of class
        > int m_value;
        > char *m_filePath;
        >
	> //setter 
	> void setPath(const char *path);
	>
	> // getter
	> char *path() const;
	> ``` 

### LXC Functionalities ###

* List containers.
* Create containers.
* Start/Stop containers.
* Delete containers.
* Stat containers.
* Configure container.

### Who do I talk to? ###

* Repo owner : pcata (contact:pcata@elpexdynami.com)

### How to install LXC ###
To know how to install LXC on your local machine please visit the following website:

* [Official site](https://linuxcontainers.org/)
* [Debian LXC](https://wiki.debian.org/LXC)
* [Stéphane GRABER](https://stgraber.org/2013/12/20/lxc-1-0-blog-post-series/)
* [ElpexDynamic](https://lxcmanager.elpexdynamic.com/lxcdoc)
* [Github project](https://github.com/lxc/lxc)
* [Wikipedia](https://en.wikipedia.org/wiki/LXC)
