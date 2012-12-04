;loader
;load this file to be able to use GeLiSo from Lisp (e.g., (load "/Users/saschavancauwelaert/Documents/EPL/PhD/code/GeLiSo/GeLiSo/lispsources/load.lisp"))
;currently, it must be done after having launched the C++ application of GeLiSo (i.e., build/bin/gelisoexec)

;change current directory to GeLiSo lisp source directory
(change-directory "/Users/saschavancauwelaert/Documents/EPL/PhD/code/GeLiSo/GeLiSo/lispsources/")
;(change-directory "/Users/saschavancauwelaert/Documents/EPL/PhD/code/GeLiSo_interface/GeLiSo/lispsources/")

;load the needed files
(load "channel.lisp")
(load "GecodeManager.lisp")
(load "open music add-ons/CPRel_utils.lisp")