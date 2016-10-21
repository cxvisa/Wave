CREDITS
-------

The core Framework Wave was originally developed by Vidyasagara Guntaka and his
team at Brocade Communications Systems, Inc.  It was developed as part of a 
n-master controller that managed / controlled Brocade VCS fabrics.  Brocade
shipped 48 node clusters based on this framework.  The framework is capable of
n-master clustering with distributed persistence among many other neat
features.  The list of features is out of scope of this document.

The framework was used in Storage Virtualzation, Network Virtualization among
many other areas.  It was used to simulate multi core Cavium network processors
due to its verstile distributed and multi threaded message based interfaces.

A complete list of features will run into more than hundred lines.

Around December of 2013, Brocade decided to donate the code to open source
community under Apache License 2.0 as part of its obligations when it joined
OpenDayLight project as a Platinum member.

The source code can be accessed from the following location:

https://github.com/brocadeodl/ODL-Proxy/tree/genesis

Vidyasagara Guntaka maintains a private repository on GitHub further
developing this framework and hopes to make it public for general usage.  He is
currently coding C++ and Java variants of the framework and has Python and Go
variants in sight so that the micro services running in Wave cluster can be
polyglot.


CODE LAYOUT
-----------

Wave/
├── application
├── build
├── postboot
├── projects
├── resourcegenerator
└── source

* source
    * contains almost all of the Wave Framework code.
* application 
    * contains various top level Applications created with the Wave Code.
* projects
    * contains various IDE specific setups (ex. eclipse etc)
* resourcegenerator
    * contains the source code for Wave Resource ID generation from XML files.
    * Wave has good localization / internationalization support in terms
      of Resource IDs.  Error messages etc., need not be hard coded into
      source files.
* postboot
    * Another utility internally used by Wave code.
* build
    * When the code is built, it creates various levels of directories
      for object files and libraries etc.,
    * It also contains dynamiclly generated code (ex. Resource IDs).
    * The layout will be based on OS and Architecture type
    * The Debug and Optimized versions based on gmake options will be
      placed in different directories

BUILDING THE CODE
-----------------

The following build instructions are provided from Linux build host perspective.
(In general tested on Fedora distributions).

1.  Make sure that all of the dependencies listed in the installation command
    mentioned in the file Wave/source/PREREQUISITES
    If all of the dependencies are not installed, there will be compilation
     errors.
2.  cd to Wave/application
3.  Issue the following command
    * gmake -j 10
    * change arguments to -j in the above command based on number of cpus
      available for compilation.
4.  If you prefer non verbose compilation, you can issue the following command
    prior to issuing the gmake command
    * export MAKEFLAGS=-s
